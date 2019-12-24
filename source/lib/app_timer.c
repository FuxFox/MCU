/*******************************************************************************
 *
 * Module: app_timer
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/21 17:49          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     app_timer.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/21
  *******************************************************************************/
#ifndef APP_TIMER_C
#define APP_TIMER_C

#include "app_timer.h"

#if defined(APP_TIMER_ENABLE)&&(APP_TIMER_ENABLE)

#if (APP_TIMER_TIMEBASE == APP_TIMER_TIMEBASE_RTC)
RTC_HandleTypeDef m_timebase_rtc;
#elif (APP_TIMER_TIMEBASE == APP_TIMER_TIMEBASE_TIM)
TIM_HandleTypeDef m_timebase_timer;
#endif

static app_timer_t* p_timer_head;
static app_timer_t m_app_timers[APP_TIMER_SOFTTIMER_MAX];
static bool m_is_module_initialized = false;


uint32_t app_timer_init(void)
{
    memset(m_app_timers, 0, sizeof(m_app_timers));
    p_timer_head = NULL;
    m_is_module_initialized = true;

#if (APP_TIMER_TIMEBASE == APP_TIMER_TIMEBASE_RTC)
    __IO uint32_t counter = 0U;

    /* Enable RTC Clock */
    __HAL_RCC_RTC_ENABLE();

    m_timebase_rtc.Instance = RTC;
    /* Configure RTC time base to 10Khz */
    m_timebase_rtc.Init.AsynchPrediv = (HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_RTC) / 10000) - 1;
    m_timebase_rtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
    HAL_ERROR_CHECK(HAL_RTC_Init(&m_timebase_rtc));

    /* Disable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_DISABLE(&m_timebase_rtc);

    /* Clear flag alarm A */
    __HAL_RTC_ALARM_CLEAR_FLAG(&m_timebase_rtc, RTC_FLAG_ALRAF);

    counter = 0U;
    /* Wait till RTC ALRAF flag is set and if Time out is reached exit */
    while (__HAL_RTC_ALARM_GET_FLAG(&m_timebase_rtc, RTC_FLAG_ALRAF) != RESET)
    {
        if (counter++ == SystemCoreClock / 48U) /* Timeout = ~ 1s */
        {
            return HAL_ERROR;
        }
    }

    /* Set RTC COUNTER MSB word */
    m_timebase_rtc.Instance->ALRH = 0x00U;
    /* Set RTC COUNTER LSB word */
    m_timebase_rtc.Instance->ALRL = 0x09U;

    /* RTC Alarm Interrupt Configuration: EXTI configuration */
    __HAL_RTC_ALARM_EXTI_ENABLE_IT();
    __HAL_RTC_ALARM_EXTI_ENABLE_RISING_EDGE();

    /* Clear Second and overflow flags */
    CLEAR_BIT(m_timebase_rtc.Instance->CRL, (RTC_FLAG_SEC | RTC_FLAG_OW));

    /* Set RTC COUNTER MSB word */
    m_timebase_rtc.Instance->CNTH = 0x00U;
    /* Set RTC COUNTER LSB word */
    m_timebase_rtc.Instance->CNTL = 0x00U;

    /* Configure the Alarm interrupt */
    __HAL_RTC_ALARM_ENABLE_IT(&m_timebase_rtc, RTC_IT_ALRA);

    /* Enable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(&m_timebase_rtc);

    /* Wait till RTC is in INIT state and if Time out is reached exit */
    counter = 0U;
    while ((m_timebase_rtc.Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
    {
        if (counter++ == SystemCoreClock / 48U)/* Timeout = ~ 1s */
        {
            return HAL_ERROR;
        }
    }

    HAL_NVIC_SetPriority(RTC_Alarm_IRQn, APP_TIMER_TIMEBASE_IRQ_PRIORITY, 0U);
    HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);

    return HAL_OK;
#elif (APP_TIMER_TIMEBASE == APP_TIMER_TIMEBASE_TIM)

    RCC_ClkInitTypeDef    clkconfig;
    uint32_t              uwTimclock, uwAPB1Prescaler = 0U;
    uint32_t              uwPrescalerValue = 0U;
    uint32_t              pFLatency;

    /* Get clock configuration */
    HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

    /* Get APB1 prescaler */
    uwAPB1Prescaler = clkconfig.APB1CLKDivider;

    /* Compute TIM2 clock */
    if (uwAPB1Prescaler == RCC_HCLK_DIV1)
    {
        uwTimclock = HAL_RCC_GetPCLK1Freq();
    }
    else
    {
        uwTimclock = 2 * HAL_RCC_GetPCLK1Freq();
    }

    /* Compute the prescaler value to have TIM2 counter clock equal to 1MHz */
    uwPrescalerValue = (uint32_t)((uwTimclock / 1000000U) - 1U);

    m_timebase_timer.Instance = CONCAT_2(TIM, APP_TIMEBASE_TIM_ID);
    m_timebase_timer.Init.CounterMode = TIM_COUNTERMODE_UP;
    m_timebase_timer.Init.Prescaler = uwPrescalerValue;
    m_timebase_timer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    m_timebase_timer.Init.Period = 999;
    m_timebase_timer.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    CONCAT_3(__HAL_RCC_TIM, APP_TIMEBASE_TIM_ID, _CLK_ENABLE(););

    HAL_NVIC_SetPriority(CONCAT_3(TIM, APP_TIMEBASE_TIM_ID, _IRQn), APP_TIMER_TIMEBASE_IRQ_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(CONCAT_3(TIM, APP_TIMEBASE_TIM_ID, _IRQn));

    if (HAL_TIM_Base_Init(&m_timebase_timer) == HAL_OK)
    {
        return HAL_TIM_Base_Start_IT(&m_timebase_timer);
    }

    return HAL_ERROR;
#endif
}

void app_timer_start(app_timer_id_t timer_id, uint32_t delay_ms)
{
    assert_param(timer_id && delay_ms);

    timer_id->counter = delay_ms;
    timer_id->delay = delay_ms;
    timer_id->is_active = true;
    timer_id->is_pending = false;
}

void app_timer_stop(app_timer_id_t timer_id)
{
    assert_param(timer_id);

    timer_id->is_active = false;
}

void app_timer_pause(void)
{
#if (APP_TIMER_TIMEBASE == APP_TIMER_TIMEBASE_RTC)
    /* Disable RTC ALARM update Interrupt */
    __HAL_RTC_ALARM_DISABLE_IT(&m_timebase_rtc, RTC_IT_ALRA);
#elif (APP_TIMER_TIMEBASE == APP_TIMER_TIMEBASE_TIM)
    /* Disable TIM4 update Interrupt */
    HAL_TIM_Base_Stop_IT(&m_timebase_timer);
#endif    
}

void app_timer_resume(void)
{
#if (APP_TIMER_TIMEBASE == APP_TIMER_TIMEBASE_RTC)
    __IO uint32_t counter = 0U;

    /* Disable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_DISABLE(&m_timebase_rtc);

    /* Set RTC COUNTER MSB word */
    m_timebase_rtc.Instance->CNTH = 0x00U;
    /* Set RTC COUNTER LSB word */
    m_timebase_rtc.Instance->CNTL = 0x00U;

    /* Clear Second and overflow flags */
    CLEAR_BIT(m_timebase_rtc.Instance->CRL, (RTC_FLAG_SEC | RTC_FLAG_OW | RTC_FLAG_ALRAF));

    /* Enable RTC ALARM Update interrupt */
    __HAL_RTC_ALARM_ENABLE_IT(&m_timebase_rtc, RTC_IT_ALRA);

    /* Enable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(&m_timebase_rtc);

    /* Wait till RTC is in INIT state and if Time out is reached exit */
    while ((m_timebase_rtc.Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
    {
        if (counter++ == SystemCoreClock / 48U) /* Timeout = ~ 1s */
        {
            break;
        }
    }
#elif (APP_TIMER_TIMEBASE == APP_TIMER_TIMEBASE_TIM)
    HAL_TIM_Base_Start_IT(&m_timebase_timer);
#endif
}


app_timer_id_t app_timer_create(app_timer_mode_t mode, app_timer_handle callback, bool is_realtime)
{
    if (m_is_module_initialized)
    {
        assert_param(callback);

        for (uint8_t i = 0; i < APP_TIMER_SOFTTIMER_MAX; i++)
        {
            if (m_app_timers[i].callback == NULL)
            {
                m_app_timers[i].is_realtime = is_realtime;
                m_app_timers[i].is_repeat = mode;
                m_app_timers[i].callback = callback;
                m_app_timers[i].next = p_timer_head;
                if (p_timer_head)
                {
                    m_app_timers[i].next->last = &m_app_timers[i];
                }
                p_timer_head = &m_app_timers[i];
                return &m_app_timers[i];
            }
        }
    }
    return NULL;
}

void app_timer_delete(app_timer_id_t timer_id)
{
    assert_param(timer_id);

    if (timer_id && timer_id->callback)
    {
        if (timer_id == p_timer_head)
        {

            p_timer_head = timer_id->next;
            if (p_timer_head)
            {
                p_timer_head->last = NULL;
            }
        }
        else
        {
            timer_id->last->next = timer_id->next;
            if (timer_id->next)
            {
                timer_id->next->last = timer_id->last;
            }
        }

        memset(timer_id, 0, sizeof(app_timer_t));
    }
}


void app_timer_process_IT(void)
{
    app_timer_t* p_timer;

    for (p_timer = p_timer_head; p_timer; p_timer = p_timer->next)
    {
        if (p_timer->is_active)
        {
            p_timer->counter--;
            if (p_timer->counter == 0)
            {
                if (p_timer->is_realtime)
                {
                    p_timer->callback();
                }
                else
                {
                    p_timer->is_pending = true;
                }

                if (p_timer->is_repeat)
                    p_timer->counter = p_timer->delay;
                else
                    p_timer->is_active = false;
            }
        }
    }
}

void app_timer_process_poll(void)
{
    app_timer_t* p_timer;

    for (p_timer = p_timer_head; p_timer; p_timer = p_timer->next)
    {
        if (p_timer->is_pending)
        {
            p_timer->is_pending = false;
            p_timer->callback();
        }
    }
}


#if (APP_TIMER_TIMEBASE == APP_TIMER_TIMEBASE_RTC)
/**
  * @brief  ALARM A Event Callback in non blocking mode
  * @note   This function is called  when RTC_ALARM interrupt took place, inside
  * RTC_ALARM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  hrtc RTC handle
  * @retval None
  */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef* hrtc)
{
    __IO uint32_t counter = 0U;


    app_timer_process_IT();

    __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

    /* Set RTC COUNTER MSB word */
    WRITE_REG(hrtc->Instance->CNTH, 0x00U);
    /* Set RTC COUNTER LSB word */
    WRITE_REG(hrtc->Instance->CNTL, 0x00U);

    /* Clear Second and overflow flags */
    CLEAR_BIT(hrtc->Instance->CRL, (RTC_FLAG_SEC | RTC_FLAG_OW));

    /* Enable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

    /* Wait till RTC is in INIT state and if Time out is reached exit */
    while ((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
    {
        if (counter++ == SystemCoreClock / 48U) /* Timeout = ~ 1s */
        {
            break;
        }
    }
}

/**
  * @brief  This function handles RTC ALARM interrupt request.
  * @retval None
  */
void RTC_Alarm_IRQHandler(void)
{
    HAL_RTC_AlarmIRQHandler(&m_timebase_rtc);
}

#elif (APP_TIMER_TIMEBASE == APP_TIMER_TIMEBASE_TIM)

/**
  * @brief  This function handles TIM interrupt request.
  * @retval None
  */
void TIM6_IRQHandler(void)
{
    __HAL_TIM_CLEAR_IT(&m_timebase_timer, TIM_IT_UPDATE);
    app_timer_process_IT();
}

#endif

#endif

#endif // APP_TIMER_C
