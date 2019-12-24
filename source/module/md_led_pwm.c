/*******************************************************************************
 * Module: md_led_pwm
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/09/02 09:27          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     md_led_pwm.c
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/09/02
 *******************************************************************************/
#ifndef MD_LED_PWM_C
#define MD_LED_PWM_C

#include "md_led_pwm.h"

static nrf_drv_pwm_t m_pwm = NRF_DRV_PWM_INSTANCE(MD_LED_PWM_ID);
static led_pwm_event_callback m_callback;

/*! This array cannot be allocated on stack (hence "static") and it must be in RAM(no const). */ 
static nrf_pwm_values_common_t m_breath_seq[] = MD_LED_PWM_SEQ_BREATH; 
       
static bool m_is_breathing = false;

/*!*****************************************************************************
\brief      initialize
\details
\param[in]    led_pwm_event_callback func     a callback when pwm event occur
\return     void
******************************************************************************/
void md_led_pwm_init(led_pwm_event_callback func)
{
        uint8_t i;

        m_callback = func;

        for (i = 0; i < ARRAY_SIZE(m_breath_seq); i++)
        {
#if (MD_LED_PWM_LED_ACTIVE_STATE)
                m_breath_seq[i] = MD_LED_PWM_CONTER_TOP * (100 - m_breath_seq[i]) / 100;
#else
                m_breath_seq[i] = MD_LED_PWM_CONTER_TOP * m_breath_seq[i] / 100;
#endif
        }

        nrf_drv_pwm_config_t const config0 =
        {
            .output_pins =
            {
                MD_LED_PWM_PIN | (MD_LED_PWM_LED_ACTIVE_STATE? 0 : NRF_DRV_PWM_PIN_INVERTED), // channel 0, idle is low level if MD_LED_PWM_LED_ACTIVE_STATE is 1
                NRF_DRV_PWM_PIN_NOT_USED, // channel 1
                NRF_DRV_PWM_PIN_NOT_USED, // channel 2
                NRF_DRV_PWM_PIN_NOT_USED  // channel 3
            },
            .irq_priority = APP_IRQ_PRIORITY_LOWEST,
            .base_clock = MD_LED_PWM_CLK,
            .count_mode = NRF_PWM_MODE_UP,
            .top_value = MD_LED_PWM_CONTER_TOP,
            .load_mode = NRF_PWM_LOAD_COMMON,
            .step_mode = NRF_PWM_STEP_AUTO
        };
        APP_ERROR_CHECK(nrf_drv_pwm_init(&m_pwm, &config0, md_led_pwm_event_handler));
}

/*!*****************************************************************************
\brief      breathing 
\details
\param[in]    uint8_t cnt : times of breath, if 0, meaning forever
\return     void
******************************************************************************/
void md_led_pwm_breath(uint8_t cnt)
{
        nrf_pwm_sequence_t const seq0 =
        {
            .values.p_common = m_breath_seq,
            .length = NRF_PWM_VALUES_LENGTH(m_breath_seq),
            .repeats = MD_LED_PWM_BREATH_STEP_INTERVAL / ((1000 * 10 / MD_LED_PWM_FREQ_HZ + 5) / 10),
            .end_delay = 0
        };

        if (cnt)
        {
                nrf_drv_pwm_simple_playback(&m_pwm, &seq0, cnt, NRF_DRV_PWM_FLAG_STOP | NRF_DRV_PWM_FLAG_NO_EVT_FINISHED);
        }
        else
        {
                nrf_drv_pwm_simple_playback(&m_pwm, &seq0, 1, NRF_DRV_PWM_FLAG_LOOP | NRF_DRV_PWM_FLAG_NO_EVT_FINISHED);
        }

        m_is_breathing = true;
}


/*!*****************************************************************************
\brief      LED blink sequence
\details
\param[in]    uint16_t on_time              LED on(off) time, in ms
\param[in]    uint16_t blink_interval       delay between blink, in ms
\param[in]    uint16_t cnt                  times of blink
\return     void
******************************************************************************/
void md_led_pwm_blinkEx(uint16_t on_time, uint16_t blink_interval, uint16_t cnt)
{
        // This array cannot be allocated on stack (hence "static") and it must
        // be in RAM.
        static nrf_pwm_values_common_t seq[2] = { MD_LED_PWM_VALUE_LED_ON, MD_LED_PWM_VALUE_LED_OFF };

        nrf_pwm_sequence_t const seq0 =
        {
            .values.p_common = seq,
            .length = NRF_PWM_VALUES_LENGTH(seq),
            .repeats = on_time / ((1000 * 10 / MD_LED_PWM_FREQ_HZ + 5) / 10),
            .end_delay = blink_interval / ((1000 * 10 / MD_LED_PWM_FREQ_HZ + 5) / 10)
        };

        (void)nrf_drv_pwm_simple_playback(&m_pwm, &seq0, cnt, NRFX_PWM_FLAG_STOP | NRF_DRV_PWM_FLAG_NO_EVT_FINISHED);
}

/*!*****************************************************************************
\brief      stop pwm
\details
\param[in]    void
\return     void
******************************************************************************/
void md_led_pwm_stop(bool wait_for_end)
{
        nrf_drv_pwm_stop(&m_pwm, wait_for_end);
}

/*!*****************************************************************************
\brief      stop imediately
\details
\param[in]    void
\return     void
******************************************************************************/
// void md_led_pwm_stop_immediately(void)
// {
//         md_led_pwm_blinkEx(0, 0, 1); 
// }

/*!*****************************************************************************
\brief      is pwm stop ?
\details
\param[in]    void
\return     bool
******************************************************************************/
bool md_led_pwm_is_stopped(void)
{
        return nrf_drv_pwm_is_stopped(&m_pwm);
}

/*!*****************************************************************************
\brief      is breathing ?
\details
\param[in]    void
\return     bool
******************************************************************************/
bool md_led_pwm_is_breathing(void)
{
        return m_is_breathing;
}
/*!*****************************************************************************
\brief      fast blink
\details
\param[in]    uint8_t time_ms      blink duration, in ms
\return     void
******************************************************************************/
void md_led_pwm_blink_fast(uint8_t time_s)
{
        md_led_pwm_blinkEx(MD_LED_PWM_FAST_BLINK_INTERVAL, 0, (uint32_t)time_s * 1000 / (MD_LED_PWM_FAST_BLINK_INTERVAL * 2));
}

/*!*****************************************************************************
\brief      slowly blink
\details
\param[in]    uint8_t time_ms blink duration, in ms
\return     void
******************************************************************************/
void md_led_pwm_blink_slowly(uint8_t time_s)
{
        md_led_pwm_blinkEx(MD_LED_PWM_SLOWLY_BLINK_INTERVAL, 0, (uint32_t)time_s * 1000 / (MD_LED_PWM_SLOWLY_BLINK_INTERVAL * 2));
}

/*!*****************************************************************************
\brief      pwm event handler
\details
\param[in]    nrfx_pwm_evt_type_t event_type
\return     void
******************************************************************************/
static void md_led_pwm_event_handler(nrf_drv_pwm_evt_type_t event_type)
{
        switch (event_type)
        {
        case NRFX_PWM_EVT_FINISHED:
                NRF_LOG_DEBUG("PWM event finished");

                break;
        case NRFX_PWM_EVT_STOPPED:
                NRF_LOG_DEBUG("PWM stop");
                m_is_breathing = false;
                break;
        default:
                break;
        }

        if (m_callback)
        {
                m_callback(event_type);
        }
}
#endif // MD_LED_C
