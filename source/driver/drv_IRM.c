/*******************************************************************************
 *
 * Module: drv_IRM
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/13 17:01          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_IRM.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/11/13
  *******************************************************************************/
#ifndef DRV_IRM_C
#define DRV_IRM_C

#include "drv_IRM.h"

#if defined(DRV_IRM_ENABLE)&&(DRV_IRM_ENABLE)

#if defined(APP_LOG_LEVEL) && (APP_LOG_LEVEL > DRV_IRM_LOG_LEVEL)
#undef APP_LOG_LEVEL
#define APP_LOG_LEVEL    DRV_IRM_LOG_LEVEL
#endif // APP_LOG_LEVEL
#define APP_LOG_MODULE_SYMBLE    "DRV_IRM"
#include "app_log.h"

static uint16_t m_timer_tick_per_us;
static drv_IRM_instance_t* m_IRM_instance_list[DRV_IRM_INSTANCE_NUM_MAX] = { NULL };
/*!*****************************************************************************
\brief      Initialize an IRM instance
            Configure GPIO pin as EXTI
\param[in]    void
\return     void
******************************************************************************/
void drv_IRM_init(drv_IRM_instance_t* instance)
{
    uint8_t exti_line;

    m_timer_tick_per_us = app_delay_systick_per_us();

    exti_line = app_gpio_pin2gpiopin(instance->data_pin);
    assert_param(m_IRM_instance_list[exti_line] == NULL);
    assert_param(instance->callback);

    app_gpio_cfg_exti(instance->data_pin, APP_GPIO_EXTI_RISING_FALLING, APP_GPIO_PULLDOWN, (DRV_IRM_EXTI_IRQ_PRIORITY << 4) | DRV_IRM_EXTI_IRQ_SUB_PRIORITY);
    m_IRM_instance_list[exti_line] = instance;
}

/*!*****************************************************************************
\brief  	get time duration, in us
\param[in]	drv_IRM_instance_data_t * instance_data
\return     uint16_t
******************************************************************************/
static uint16_t drv_IRM_get_duration(drv_IRM_instance_data_t* instance_data)
{
    uint32_t cur_time_val;
    uint16_t duration;

    cur_time_val = HAL_GetTick();
    if (cur_time_val < instance_data->old_ms_value)
    {
        duration = UINT32_MAX - instance_data->old_ms_value + cur_time_val + 1;
    }
    else
    {
        duration = cur_time_val - instance_data->old_ms_value;
    }

    duration *= 1000;
    cur_time_val = (SysTick->LOAD - SysTick->VAL) / m_timer_tick_per_us;

    if (cur_time_val < instance_data->old_us_value)
    {
        duration += cur_time_val;
        duration -= instance_data->old_us_value;
    }
    else
    {
        duration += cur_time_val - instance_data->old_us_value;
    }

    return duration;
}

/*!*****************************************************************************
\brief      Infrared Receiver, must called in corresponding EXTI interrupt
\details
\param[in]    uint8_t exti_line [0~15]
\return     void
******************************************************************************/
void drv_IRM_receive(uint8_t exti_line)
{
    const drv_IRM_protocol_t* protocol = &m_IRM_instance_list[exti_line]->protocal;
    drv_IRM_instance_data_t* data = m_IRM_instance_list[exti_line]->data;
    bool is_high_level = app_gpio_pin_read(m_IRM_instance_list[exti_line]->data_pin);
    uint16_t duration;

    assert_param(m_IRM_instance_list[exti_line]);

    duration = drv_IRM_get_duration(data);
    data->old_us_value = (SysTick->LOAD - SysTick->VAL) / m_timer_tick_per_us;
    data->old_ms_value = HAL_GetTick();
    LOG_DEBUG("duration:%d", duration);

    switch (data->rx_status)
    {
    case DRV_IRM_RX_IDLE:
        if (!is_high_level)//receive START
        {
            data->rx_status = DRV_IRM_RX_START;
            LOG_INFO("RX start");
        }
        break;
    case DRV_IRM_RX_START:
        if (is_high_level)
        {
            if ((duration >= (protocol->start_low_us - DRV_IRM_TIMING_OFFSET_US))
                && (duration <= (protocol->start_low_us + DRV_IRM_TIMING_OFFSET_US)))//START LOW
            {
                //do nothing
            }
            else
            {
                data->rx_status = DRV_IRM_RX_IDLE;
            }
        }
        else
        {
            if ((duration >= (protocol->start_high_us - DRV_IRM_TIMING_OFFSET_US))
                && (duration <= (protocol->start_high_us + DRV_IRM_TIMING_OFFSET_US)))//START HIGH
            {
                data->rx_status = DRV_IRM_RX_DATA;
                data->rx_bit_cnt = 0;
                memset(data->rx_buff, 0, 4);
            }
            else if ((duration >= (protocol->repeat_high_us - DRV_IRM_TIMING_OFFSET_US))
                && (duration <= (protocol->repeat_high_us + DRV_IRM_TIMING_OFFSET_US)))//REPEAT
            {
                m_IRM_instance_list[exti_line]->callback(data->rx_buff[0], data->rx_buff[2]);
                data->rx_status = DRV_IRM_RX_IDLE;
                LOG_ERROR("error0");
            }
        }
        break;
    case DRV_IRM_RX_DATA:
        if (is_high_level)
        {
            if ((duration >= (protocol->logic_0_low_us - DRV_IRM_TIMING_OFFSET_US))
                && (duration <= (protocol->logic_0_low_us + DRV_IRM_TIMING_OFFSET_US)))
            {
                //do nothing? or something to do
                //do nothing for NEC protocol
            }
            else if ((duration >= (protocol->logic_1_low_us - DRV_IRM_TIMING_OFFSET_US))
                && (duration <= (protocol->logic_1_low_us + DRV_IRM_TIMING_OFFSET_US)))
            {
                //do nothing? or something to do
                //do nothing for NEC protocol
            }
            else
            {
                data->rx_status = DRV_IRM_RX_IDLE;
                LOG_ERROR("error1");
            }
        }
        else
        {
            if ((duration >= (protocol->logic_0_high_us - DRV_IRM_TIMING_OFFSET_US))
                && (duration <= (protocol->logic_0_high_us + DRV_IRM_TIMING_OFFSET_US)))
            {
                //do nothing? or something to do
                //do nothing for NEC protocol
            }
            else if ((duration >= (protocol->logic_1_high_us - DRV_IRM_TIMING_OFFSET_US))
                && (duration <= (protocol->logic_1_high_us + DRV_IRM_TIMING_OFFSET_US)))
            {
                data->rx_buff[data->rx_bit_cnt >> 3] |= (0x80 >> (data->rx_bit_cnt & 0x07));
            }
            else
            {
                data->rx_status = DRV_IRM_RX_IDLE;
                LOG_ERROR("error2");
            }

            data->rx_bit_cnt++;
            if (data->rx_bit_cnt >= 32)
            {
                if (((data->rx_buff[2] == (~data->rx_buff[3] & 0xFF)) || (data->rx_buff[2] == data->rx_buff[3]))
                    && ((data->rx_buff[0] == (~data->rx_buff[1] & 0xFF)) || (data->rx_buff[0] == data->rx_buff[1])))
                {
                    LOG_DEBUG("callback");
                    m_IRM_instance_list[exti_line]->callback(data->rx_buff[0], data->rx_buff[2]);
                }
                LOG_DEBUG_ARRAY(data->rx_buff, 4);
                LOG_INFO("RX done");
                data->rx_status = DRV_IRM_RX_IDLE;
            }
        }
        break;
    default:
        break;
    }
}


#endif


#endif // DRV_IRM_C
