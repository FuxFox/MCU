/*******************************************************************************
 *
 * Module: drv_tb6600
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/21 14:16          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_tb6600.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/21
  *******************************************************************************/
#ifndef DRV_TB6600_C
#define DRV_TB6600_C

#include "drv_tb6600.h"

static drv_tb6600_instance_t* m_instances_head = NULL;
TIM_HandleTypeDef htim1;

static bool m_is_driver_stop = true;
static bool m_is_driver_inited = false;

/*!*****************************************************************************
\brief      initialize
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_tb6600_init(drv_tb6600_instance_t* instance, uint16_t speed)
{
    if (!m_is_driver_inited)
    {
        drv_tb6600_timer_init();
        m_is_driver_inited = true;
    }
    app_gpio_cfg_output(instance->clk_pin);
    app_gpio_cfg_output(instance->cw_ccw_pin);
    app_gpio_cfg_output(instance->enable_pin);
    app_gpio_pin_write(instance->clk_pin, GPIO_PIN_RESET);
    app_gpio_pin_write(instance->cw_ccw_pin, GPIO_PIN_RESET);
    app_gpio_pin_write(instance->enable_pin, GPIO_PIN_RESET);

    if (speed > DRV_TB6600_SPEED_RPM_MAX)
    {
        speed = DRV_TB6600_SPEED_RPM_MAX;
    }
    instance->speed_rpm = speed;

    instance->clk_div = DRV_TB6600_SPEED_RPM_MAX / speed * DRV_TB6600_STEP_DIV_MAX / instance->step_division;

    instance->next = m_instances_head;
    m_instances_head = instance;
}
/*!*****************************************************************************
\brief
\details
\param[in]    drv_tb6600_instance_t * instance
\return     bool
******************************************************************************/
bool drv_tb6600_is_enable(drv_tb6600_instance_t* instance)
{
    return instance->is_enable;
}

void drv_tb6600_move_step(drv_tb6600_instance_t* instance, drv_tb6600_dir_t dir, uint32_t step_num)
{
    instance->step_num = step_num;
    instance->step_cnt = 0;
    instance->is_enable = true;

    if (dir != DRV_TB6600_DIR_SAME_AS_LAST)
    {
        app_gpio_pin_write(instance->cw_ccw_pin, (GPIO_PinState)(dir - 1));
    }
    app_gpio_pin_write(instance->enable_pin, GPIO_PIN_SET);

    if (m_is_driver_stop)
    {
        HAL_TIM_Base_Start_IT(&htim1);
        m_is_driver_stop = false;
    }
}

void drv_tb6600_move_angle(drv_tb6600_instance_t* instance, drv_tb6600_dir_t dir, uint32_t angle)
{
    drv_tb6600_move_step(instance, dir, angle / (90 / instance->step_division));
}

void drv_tb6600_stop(drv_tb6600_instance_t* instance)
{
    drv_tb6600_instance_t* node;

    if (!instance->is_enable)
    {
        return;
    }

    instance->is_enable = false;
    app_gpio_pin_write(instance->enable_pin, GPIO_PIN_RESET);
    app_gpio_pin_write(instance->clk_pin, GPIO_PIN_RESET);
    app_gpio_pin_write(instance->cw_ccw_pin, GPIO_PIN_RESET);

    node = m_instances_head;
    while (node)
    {
        if (node->is_enable)
        {
            return;
        }
        node = node->next;
    }

    if (!m_is_driver_stop)
    {
        HAL_TIM_Base_Stop_IT(&htim1);
        m_is_driver_stop = true;
    }
}


/*!*****************************************************************************
\brief      set motor speed
\details
\param[in]    drv_tb6600_instance_t * instance
\param[in]    uint16_t speed
\return     void
******************************************************************************/
void drv_tb6600_set_speed(drv_tb6600_instance_t* instance, uint16_t speed)
{
    if (speed > DRV_TB6600_SPEED_RPM_MAX)
    {
        speed = DRV_TB6600_SPEED_RPM_MAX;
    }
    instance->speed_rpm = speed;
    instance->clk_cnt = 0;
    instance->clk_div = (DRV_TB6600_SPEED_RPM_MAX / speed) * (DRV_TB6600_STEP_DIV_MAX / instance->step_division);
}

/*!*****************************************************************************
\brief      get step counter
\details
\param[in]    drv_tb6600_instance_t * instance
\return     uint32_t
******************************************************************************/
uint32_t drv_tb6600_get_step_counter(drv_tb6600_instance_t* instance)
{
    return instance->step_cnt;
}

/*!*****************************************************************************
\brief  	set direction
\param[in]	drv_tb6600_instance_t * instance
\param[in]	drv_tb6600_dir_t dir
\return     void
******************************************************************************/
void drv_tb6600_set_dir(drv_tb6600_instance_t* instance, drv_tb6600_dir_t dir)
{
    app_gpio_pin_write(instance->cw_ccw_pin, (GPIO_PinState)dir);
}

// void drv_tb6600_get_dir(void)
// {
// 
// }

/*!*****************************************************************************
\brief      timer callback handler
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_tb6600_timer_callback(void)
{
    drv_tb6600_instance_t* node = m_instances_head;

    while (node)
    {
        if (node->is_enable)
        {
            if (++node->clk_cnt >= node->clk_div)
            {
                node->clk_cnt = 0;
                app_gpio_pin_toggle(node->clk_pin);
                if ((node->step_num > 0) && (++node->step_cnt >= node->step_num))
                {
                    drv_tb6600_stop(node);
                }
            }

        }

        node = node->next;
    }
}

void drv_tb6600_timer_init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
    TIM_MasterConfigTypeDef sMasterConfig = { 0 };
    HAL_StatusTypeDef error_code;

    htim1.Instance = DRV_TB6600_TIMER;
    htim1.Init.Prescaler = 71;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = DRV_TB6600_TIME_RELOAD_VAL - 1;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    __HAL_RCC_TIM1_CLK_ENABLE();           
    HAL_NVIC_SetPriority(TIM1_UP_IRQn, DRV_TB6600_TIM_IRQ_PRIORITY, 0);    
    HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);          

    error_code = HAL_TIM_Base_Init(&htim1);
    HAL_ERROR_CHECK(error_code);

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    error_code = HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig);
    HAL_ERROR_CHECK(error_code);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    error_code = HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);
    HAL_ERROR_CHECK(error_code);

}

#endif // DRV_TB6600_C
