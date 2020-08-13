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

/*! \defgroup hal_gpio_public Public
\ingroup hal_gpio
\brief			GPIO HAL for 8051 serial chip
\details 
* @{ */

#include "app_config.h"

/*! GPIO pin level */
typedef enum
{
	HAL_GPIO_LOW = 0,
	HAL_GPIO_HIGH,
}hal_gpio_state_t;

/*! gpio pin pull state */
typedef enum
{
	HAL_GPIO_NOPULL,
	HAL_GPIO_PULLUP,
// 	HAL_GPIO_PULLDOWN = GPIO_PULLDOWN,
}hal_gpio_pull_t;

typedef enum
{
	HAL_GPIO_MODE_INPUT,             
	HAL_GPIO_MODE_OUTPUT,             /*!< PUSH PULL mode */
// 	HAL_GPIO_MODE_ANALOG             = GPIO_MODE_ANALOG,             /*!< Analog    Mode      */

	HAL_GPIO_MODE_EXTI_LOW,             /*!< External Interrupt Mode with LOW level detection */
	HAL_GPIO_MODE_EXTI_HIGH,            /*!< External Interrupt Mode with HIGH level detection */
	HAL_GPIO_MODE_EXTI_FALLING,         /*!< External Interrupt Mode with Falling edge trigger detection */
	HAL_GPIO_MODE_EXTI_RISING,          /*!< External Interrupt Mode with Rising  edge trigger detection */
	HAL_GPIO_MODE_EXTI_RISING_FALLING,  /*!< External  Interrupt Mode  with  Rising/Falling edge trigger detection */
}hal_gpio_mode_enum;


void hal_gpio_init(void);

void hal_gpio_cfg(uint8_t port_pin, hal_gpio_mode_enum mode, hal_gpio_pull_t pin_pull);

/*!*****************************************************************************
\brief  	read pin state
\param[in]	uint8_t port_pin : high 4 bits are port number,low 4 bits are pin number
								e.g. 0x17 means P17
\return     bool
******************************************************************************/
bool hal_gpio_pin_read(uint8_t port_pin);

/*!*****************************************************************************
\brief  	set pin state
\param[in]	uint8_t port_pin : high 4 bits are port number,low 4 bits are pin number
								e.g. 0x17 means P17
\param[in]	hal_gpio_state_t pin_state
\return     void
******************************************************************************/
void hal_gpio_pin_write(uint8_t port_pin, hal_gpio_state_t pin_state);

/*!*****************************************************************************
\brief      configure gpio as output
\details       push pull mode
\param[in]    uint16_t pin_number
\return     void
******************************************************************************/
#define hal_gpio_cfg_output(port_pin)            hal_gpio_cfg(port_pin, HAL_GPIO_MODE_OUTPUT, HAL_GPIO_NOPULL)

/*!*****************************************************************************
\brief      configure gpio as input
\details
\param[in]    uint16_t pin_number
\return     void
******************************************************************************/
#define hal_gpio_cfg_input(port_pin, pin_pull)        hal_gpio_cfg(port_pin, HAL_GPIO_MODE_INPUT, pin_pull)

/*!*****************************************************************************
\brief  configure gpio as analog function

\param    void
\return void
*******************************************************************************/
#define hal_gpio_cfg_analog(port_pin)            hal_gpio_cfg(port_pin, HAL_GPIO_MODE_ANALOG, HAL_GPIO_NOPULL)


void hal_gpio_pin_toggle(uint8_t port_pin);

// void hal_gpio_deinit(uint32_t pin_number);


/*! @}*/ //end of group hal_gpio
#endif // HAL_GPIO_H
