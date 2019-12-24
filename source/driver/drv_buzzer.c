/*******************************************************************************
 * Module: drv_buzzer
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/07/26 14:47          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_buzzer.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/07/26
  *******************************************************************************/
#ifndef DRV_BUZZER_C
#define DRV_BUZZER_C

#include "drv_buzzer.h"

APP_PWM_INSTANCE(m_buzzer_pwm, 1);                   // Create the instance "PWM1" using TIMER1.

static bool m_buzzer_is_on = false;

/*!*****************************************************************************
\brief      initialize
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_buzzer_init(void)
{
    ret_code_t err_code;

    /* 1-channel PWM, 500Hz, output on DK beeper pins. */
    app_pwm_config_t pwm1_cfg = APP_PWM_DEFAULT_CONFIG_1CH((1000L * 1000 / DRV_BUZZER_PWM_FREQ_HZ), DRV_BUZZER_CONTROL_PIN);  //APP_PWM_DEFAULT_CONFIG_2CH(5000L, BSP_LED_0, BSP_LED_1);

    /* Switch the polarity of the second channel. */
    pwm1_cfg.pin_polarity[0] = APP_PWM_POLARITY_ACTIVE_HIGH;

    /* Initialize and enable PWM. */
    err_code = app_pwm_init(&m_buzzer_pwm, &pwm1_cfg, NULL);
    APP_ERROR_CHECK(err_code);

    //        app_pwm_channel_duty_set(&PWM1, 0, 50); // set pwm duty cycle
}


/*!*****************************************************************************
\brief      buzzer on
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_buzzer_on(void)
{
    if (!m_buzzer_is_on)
    {
        m_buzzer_is_on = true;
        app_pwm_enable(&m_buzzer_pwm);
        app_pwm_channel_duty_set(&m_buzzer_pwm, 0, 50); // set pwm duty cycle
    }
}

/*!*****************************************************************************
\brief      buzzer off
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_buzzer_off(void)
{
    if (m_buzzer_is_on)
    {
        m_buzzer_is_on = false;
        app_pwm_disable(&m_buzzer_pwm);
    }
}

/*!*****************************************************************************
\brief      is buzzer on ?
\details        true is on and false is off;
\param[in]    void
\return     bool
******************************************************************************/
bool drv_buzzer_is_on(void)
{
    return m_buzzer_is_on;
}

#endif // DRV_BUZZER_C
