/*******************************************************************************
 *
 * Module: app_gpio
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/12 14:38          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     app_gpio.h
  * \brief    This module is designed to use the pin number of chip to control gpio.
              This module is implemented base on STM32f103xxx with HAL.
              So, if you want to use this module for others MCU, you need to modify all code that related to hardware,
              then, you need to implement a pin-map for MCU. For example, \see stm32f1xxVxx_pinmap.h

  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/12
  *******************************************************************************/
#ifndef APP_GPIO_H
#define APP_GPIO_H

#include "app_config.h"

  /*! gpio pin pull state */
typedef enum
{
    APP_GPIO_NOPULL                  = GPIO_NOPULL,
    APP_GPIO_PULLUP                  = GPIO_PULLUP,
    APP_GPIO_PULLDOWN                = GPIO_PULLDOWN,
}app_gpio_pull_t;

typedef enum
{
    APP_GPIO_MODE_INPUT              = GPIO_MODE_INPUT,                /*!< Input Floating Mode                   */
    APP_GPIO_MODE_OUTPUT_PP          = GPIO_MODE_OUTPUT_PP,            /*!< Output Push Pull Mode                 */
    APP_GPIO_MODE_OUTPUT_OD          = GPIO_MODE_OUTPUT_OD,            /*!< Output Open Drain Mode                */
    APP_GPIO_MODE_AF_PP              = GPIO_MODE_AF_PP,                /*!< Alternate Function Push Pull Mode     */
    APP_GPIO_MODE_AF_OD              = GPIO_MODE_AF_OD,                /*!< Alternate Function Open Drain Mode    */
    APP_GPIO_MODE_AF_INPUT           = APP_GPIO_MODE_INPUT,            /*!< Alternate Function Input Mode         */

    APP_GPIO_MODE_ANALOG             = GPIO_MODE_ANALOG,               /*!< Analog Mode  */

    APP_GPIO_MODE_IT_RISING          = GPIO_MODE_IT_RISING,            /*!< External Interrupt Mode with Rising edge trigger detection          */
    APP_GPIO_MODE_IT_FALLING         = GPIO_MODE_IT_FALLING,           /*!< External Interrupt Mode with Falling edge trigger detection         */
    APP_GPIO_MODE_IT_RISING_FALLING  = GPIO_MODE_IT_RISING_FALLING,    /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */

    APP_GPIO_MODE_EVT_RISING         = GPIO_MODE_EVT_RISING,           /*!< External Event Mode with Rising edge trigger detection               */
    APP_GPIO_MODE_EVT_FALLING        = GPIO_MODE_EVT_FALLING,          /*!< External Event Mode with Falling edge trigger detection              */
    APP_GPIO_MODE_EVT_RISING_FALLING = GPIO_MODE_EVT_RISING_FALLING,   /*!< External Event Mode with Rising/Falling edge trigger detection       */
}app_gpio_mode_enum;

typedef enum
{
    APP_GPIO_SPEED_FREQ_LOW          = (GPIO_CRL_MODE0_1),             /*!< Low speed */
    APP_GPIO_SPEED_FREQ_MEDIUM       = (GPIO_CRL_MODE0_0),             /*!< Medium speed */
    APP_GPIO_SPEED_FREQ_HIGH         = (GPIO_CRL_MODE0),               /*!< High speed */
}app_gpio_speed_enum;


typedef enum
{
    APP_GPIO_EXTI_RISING             = GPIO_MODE_IT_RISING,            /*!< External Interrupt Mode with Rising edge trigger detection          */
    APP_GPIO_EXTI_FALLING            = GPIO_MODE_IT_FALLING,           /*!< External Interrupt Mode with Falling edge trigger detection         */
    APP_GPIO_EXTI_RISING_FALLING     = GPIO_MODE_IT_RISING_FALLING,    /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */
}app_gpio_exti_t;



void app_gpio_init(void);
void app_gpio_cfg(uint16_t pin_number, app_gpio_mode_enum mode, app_gpio_pull_t pin_pull, app_gpio_speed_enum output_speed);

/*!*****************************************************************************
\brief      configure gpio as output
\details        PP£¬NOPULL£¬SPEED_FREQ_HIGH
\param[in]    uint16_t pin_number
\return     void
******************************************************************************/
#define app_gpio_cfg_output(pin_number)            app_gpio_cfg(pin_number, APP_GPIO_MODE_OUTPUT_PP, APP_GPIO_NOPULL, APP_GPIO_SPEED_FREQ_HIGH)

/*!*****************************************************************************
\brief      configure gpio as input
\details
\param[in]    uint16_t pin_number
\return     void
******************************************************************************/
#define app_gpio_cfg_input(pin_number, pin_pull)        app_gpio_cfg(pin_number, (app_gpio_mode_enum)GPIO_MODE_INPUT, pin_pull, APP_GPIO_SPEED_FREQ_LOW)

/*!*****************************************************************************
\brief  configure gpio as analog function

\param    void
\return void
*******************************************************************************/
#define app_gpio_cfg_analog(pin_number)            app_gpio_cfg(pin_number, APP_GPIO_MODE_ANALOG, APP_GPIO_NOPULL, APP_GPIO_SPEED_FREQ_LOW)

void app_gpio_cfg_exti(uint16_t pin_number, app_gpio_exti_t mode, app_gpio_pull_t pin_pull, uint8_t irq_priority);
GPIO_PinState app_gpio_pin_read(uint16_t pin_number);
void app_gpio_pin_write(uint16_t pin_number, GPIO_PinState PinState);
void app_gpio_pin_toggle(uint16_t pin_number);
void app_gpio_deinit(uint16_t pin_number);

uint8_t app_gpio_pin2gpiopin(uint16_t pin_number);
IRQn_Type app_gpio_pin2exti_irqn(uint16_t pin_number);


#endif // APP_GPIO_H
