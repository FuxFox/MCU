/*!*****************************************************************************
 * @file     hal_gpio.c
 * @brief
 * @author	 FuxFox
 * @version  V1.0
 * @date     2020/08/17
 ******************************************************************************/
#ifndef HAL_GPIO_C
#define HAL_GPIO_C

#include "hal_gpio.h"

void hal_gpio_init(void)
{

}

void hal_gpio_cfg(uint8_t gpio_pin, hal_gpio_mode_enum mode, hal_gpio_pull_t pin_pull)
{
	switch (mode)
	{
	case HAL_GPIO_MODE_INPUT:
		break;
	case HAL_GPIO_MODE_OUTPUT:
		break;
	case HAL_GPIO_MODE_ANALOG:
		break;
	case HAL_GPIO_MODE_EXTI_LOW:
	case HAL_GPIO_MODE_EXTI_HIGH:
		break;
	case HAL_GPIO_MODE_EXTI_FALLING:
	case HAL_GPIO_MODE_EXTI_RISING:
		break;
	case HAL_GPIO_MODE_EXTI_RISING_FALLING:
		break;
	default:
		break;
	}
}

bool hal_gpio_pin_read(uint8_t port_pin)
{

}

void hal_gpio_pin_write(uint8_t gpio_pin, hal_gpio_state_t pin_state)
{
	
}

void hal_gpio_pin_toggle(uint8_t gpio_pin)
{
	hal_gpio_pin_write(gpio_pin, !hal_gpio_pin_read(gpio_pin));
}

#endif // HAL_GPIO_C

