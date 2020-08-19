/*!*****************************************************************************
* @file     md_led_pwm.h
* @brief    
* @author   FuxFox
* @version  V1.0
* @date     2019/09/02
*******************************************************************************/
#ifndef MD_LED_PWM_H
#define MD_LED_PWM_H

/**
* @defgroup md_led_pwm
* @ingroup module
* @brief      This is a led control module implemented base on NRF52832, with PWM.
*			Support blink and breathing.
* @{ */

#include "app_config.h"


/*================================= Module Config ============================*/

#define MD_LED_PWM_PIN                   LED_1                    
#define MD_LED_PWM_LED_ACTIVE_STATE       LEDS_ACTIVE_STATE

#define MD_LED_PWM_ID                    CFG_LED_PWM_ID                           /**< PWM id for nrf52 */
#define MD_LED_PWM_FREQ_HZ               CFG_LED_PWM_FREQ_HZ                      /**< PWM frequency, in HZ, recommend [50~1000]*/
#define MD_LED_PWM_CLK                   NRF_PWM_CLK_125kHz                       /**< PWM clock */
#define MD_LED_PWM_CONTER_TOP            (16000000 / (1<<MD_LED_PWM_CLK) / MD_LED_PWM_FREQ_HZ)   //counter reload value ,[3~32767]
#define MD_LED_PWM_BREATH_STEP_INTERVAL   CFG_LED_PWM_BREATH_STEP_INTERVAL         /**< breathing lamp step interval , in ms*/
#define MD_LED_PWM_FAST_BLINK_INTERVAL    CFG_LED_PWM_FAST_BLINK_INTERVAL          /**< fast blink, half of period, in ms */
#define MD_LED_PWM_SLOWLY_BLINK_INTERVAL  CFG_LED_PWM_SLOWLY_BLINK_INTERVAL        /**< slowly blink, half of period, in ms */

#define MD_LED_PWM_VALUE_LED_ON          (MD_LED_PWM_LED_ACTIVE_STATE? 0 : 0x8000)
#define MD_LED_PWM_VALUE_LED_OFF         (MD_LED_PWM_LED_ACTIVE_STATE? 0x8000 : 0)

#define MD_LED_PWM_SEQ_BREATH            {0,8,16,24,32,40,48,56,76,84,92,100,100,100,92,84,76,56,48,40,32,24,16,8,0}        //breathing lamp sequence(low level duty cycle)

/*================================= Data Type ================================*/

typedef void (*led_pwm_event_callback)(nrf_drv_pwm_evt_type_t event_type);



/*================================= Public Interface =========================*/

/*!*****************************************************************************
* @brief      initialize
* @param[in]    led_pwm_event_callback func     a callback when pwm event occur
* @return     void
*******************************************************************************/
void md_led_pwm_init(led_pwm_event_callback func);

/*!*****************************************************************************
* @brief      breathing 
* @param[in]    uint8_t cnt : times of breath, if 0, meaning forever
* @return     void
*******************************************************************************/
void md_led_pwm_breath(uint8_t cnt);

/*!*****************************************************************************
* @brief      LED blink sequence
* @param[in]    uint16_t on_time              LED on(off) time, in ms
* @param[in]    uint16_t blink_interval       delay between blink, in ms
* @param[in]    uint16_t cnt                  times of blink
* @return     void
*******************************************************************************/
void md_led_pwm_blinkEx(uint16_t onoff_interval, uint16_t seq_interval, uint16_t cnt);

/*!*****************************************************************************
* @brief      stop pwm
* @param[in]    void
* @return     void
*******************************************************************************/
void md_led_pwm_stop(bool wait_for_end);

/*!*****************************************************************************
* @brief      is pwm stop ?
* @param[in]    void
* @return     bool
*******************************************************************************/
bool md_led_pwm_is_stopped(void);

/*!*****************************************************************************
* @brief      is breathing ?
* @param[in]    void
* @return     bool
*******************************************************************************/
bool md_led_pwm_is_breathing(void);

/*!*****************************************************************************
* @brief      fast blink
* @param[in]    uint8_t time_ms      blink duration, in ms
* @return     void
*******************************************************************************/
void md_led_pwm_blink_fast(uint8_t time_s);

/*!*****************************************************************************
* @brief      slowly blink
* @param[in]    uint8_t time_ms blink duration, in ms
* @return     void
*******************************************************************************/
void md_led_pwm_blink_slowly(uint8_t time_s);


/** @}*/ //end of group md_led_pwm
#endif // MD_LED_H
