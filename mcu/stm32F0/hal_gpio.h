/*******************************************************************************
* LICENSE : Apache 2.0
*           
* History:
*    <author>         <time>             <version>             <desc>
*      FuxFox	      2020/05/22 09:07          V1.0             build this file
*
*******************************************************************************/
#ifndef HAL_GPIO_H
#define HAL_GPIO_H

/**
* @defgroup hal_gpio
* @ingroup HAL
* @brief	STM32 GPIO HAL
* @details 
*     This module is designed to use the pin number of chip to control gpio.
*     This module is implemented base on STM32f030F4P6 with HAL.
*     So, if you want to use this module for others MCU, you need to modify 
*     all code that related to hardware, and implement a pin-map for MCU.
*     For example, \see stm32f030F4P6_pinmap.h
* @{ */

#include "app_config.h"

/*================================= Data Type ================================*/

#define HAL_GPIO_DEFAULT_OUTPUT_SPEED GPIO_SPEED_FREQ_HIGH

/*================================= Data Type ================================*/

/** GPIO pin level */
typedef enum
{
	HAL_GPIO_LOW = GPIO_PIN_RESET,
	HAL_GPIO_HIGH = GPIO_PIN_SET,
}hal_gpio_state_t;

/** gpio pin pull state */
typedef enum
{
	HAL_GPIO_NOPULL   = GPIO_NOPULL,
	HAL_GPIO_PULLUP   = GPIO_PULLUP,
	HAL_GPIO_PULLDOWN = GPIO_PULLDOWN,
}hal_gpio_pull_t;

typedef enum
{
	HAL_GPIO_MODE_INPUT              = GPIO_MODE_INPUT,             /*!< Input Floating Mode */
	HAL_GPIO_MODE_OUTPUT_PP          = GPIO_MODE_OUTPUT_PP,         /*!< Output Push Pull Mode */
	HAL_GPIO_MODE_OUTPUT_OD          = GPIO_MODE_OUTPUT_OD,         /*!< Output Open Drain Mode */
	HAL_GPIO_MODE_AF_PP              = GPIO_MODE_AF_PP,             /*!< Alternate Function Push Pull Mode */
	HAL_GPIO_MODE_AF_OD              = GPIO_MODE_AF_OD,             /*!< Alternate Function Open Drain Mode */
	HAL_GPIO_MODE_AF_INPUT           = HAL_GPIO_MODE_INPUT,        /*!< Alternate Function Input Mode */

	HAL_GPIO_MODE_ANALOG             = GPIO_MODE_ANALOG,            /*!< Analog Mode */

	HAL_GPIO_MODE_IT_RISING          = GPIO_MODE_IT_RISING,         /*!< External Interrupt Mode with Rising edge trigger detection */
	HAL_GPIO_MODE_IT_FALLING         = GPIO_MODE_IT_FALLING,        /*!< External Interrupt Mode with Falling edge trigger detection */
	HAL_GPIO_MODE_IT_RISING_FALLING  = GPIO_MODE_IT_RISING_FALLING, /*!< External Interrupt Mode with Rising/Falling edge trigger detection */

	HAL_GPIO_MODE_EVT_RISING         = GPIO_MODE_EVT_RISING,        /*!< External Event Mode with Rising edge trigger detection */
	HAL_GPIO_MODE_EVT_FALLING        = GPIO_MODE_EVT_FALLING,       /*!< External Event Mode with Falling edge trigger detection  */
	HAL_GPIO_MODE_EVT_RISING_FALLING = GPIO_MODE_EVT_RISING_FALLING,/*!< External Event Mode with Rising/Falling edge trigger detection */
}hal_gpio_mode_enum;

typedef enum
{
	HAL_GPIO_EXTI_RISING         = GPIO_MODE_IT_RISING,         /*!< External Interrupt Mode with Rising edge trigger detection */
	HAL_GPIO_EXTI_FALLING        = GPIO_MODE_IT_FALLING,        /*!< External Interrupt Mode with Falling edge trigger detection */
	HAL_GPIO_EXTI_RISING_FALLING = GPIO_MODE_IT_RISING_FALLING, /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
}hal_gpio_exti_t;

/*================================= Public Interface =========================*/

/*!*****************************************************************************
* @brief  	initialize hal_gpio module
* @param[in]	void
* @return     void
*******************************************************************************/
void hal_gpio_init(void);

/*!*****************************************************************************
* @brief  	configure pin as gpio
* @param[in]	uint16_t gpio_pin	:	gpio pin number
* @param[in]	hal_gpio_mode_enum mode		
* @param[in]	hal_gpio_pull_t pin_pull
* @return     void
*******************************************************************************/
void hal_gpio_cfg(uint16_t gpio_pin, hal_gpio_mode_enum mode, hal_gpio_pull_t pin_pull);

/*!*****************************************************************************
* @brief  	read pin state
* @param[in]	uint16_t gpio_pin	:	gpio pin number
* @return     bool	: true if high, false if low
*******************************************************************************/
bool hal_gpio_pin_read(uint16_t gpio_pin);

/*!*****************************************************************************
* @brief  	set pin state
* @param[in]	uint16_t gpio_pin	:	gpio pin number
* @param[in]	hal_gpio_state_t pin_state
* @return     void
*******************************************************************************/
void hal_gpio_pin_write(uint16_t gpio_pin, hal_gpio_state_t PinState);

/*!*****************************************************************************
* @brief      configure gpio as output
* @details        PP£¬NOPULL£¬SPEED_FREQ_HIGH
* @param[in]    uint16_t gpio_pin
* @return     void
*******************************************************************************/
#define hal_gpio_cfg_output(gpio_pin)            hal_gpio_cfg(gpio_pin, HAL_GPIO_MODE_OUTPUT_PP, HAL_GPIO_NOPULL)

/*!*****************************************************************************
* @brief      configure gpio as input
* @param[in]    uint8_t gpio_pin
* @param[in]    hal_gpio_pull_t pin_pull
* @return     void
*******************************************************************************/
#define hal_gpio_cfg_input(gpio_pin, pin_pull)        hal_gpio_cfg(gpio_pin, (hal_gpio_mode_enum)GPIO_MODE_INPUT, pin_pull)

/*!*****************************************************************************
* @brief  configure gpio as analog function
* @param[in]    uint8_t gpio_pin
* @return void
********************************************************************************/
#define hal_gpio_cfg_analog(gpio_pin)            hal_gpio_cfg(gpio_pin, HAL_GPIO_MODE_ANALOG, HAL_GPIO_NOPULL)

/*!*****************************************************************************
* @brief      toggle gpio pin
* @param[in]    uint16_t gpio_pin
* @return     void
*******************************************************************************/
void hal_gpio_pin_toggle(uint16_t gpio_pin);

/*!*****************************************************************************
* @brief      deinit gpio configuration
* @param[in]    uint16_t gpio_pin
* @return     void
*******************************************************************************/
void hal_gpio_deinit(uint16_t gpio_pin);

/*!*****************************************************************************
* @brief      chip pin to GPIO PIN [0~15]
* @param[in]    uint16_t gpio_pin
* @return     uint8_t
*******************************************************************************/
uint8_t hal_gpio_pin2gpiopin(uint16_t gpio_pin);

GPIO_TypeDef* hal_gpio_pin2gpioport(uint16_t gpio_pin);

/** @}*/ //end of group hal_gpio
#endif // HAL_GPIO_H
