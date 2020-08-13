/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/05/06 18:21          V1.0             build this file
 *
 *******************************************************************************/
#ifndef HAL_GPIO_C
#define HAL_GPIO_C

#include "hal_gpio.h"

#define cfg_gpio_to_push_pull(port, bit) 		port##M1 &= ~bit; port##M2 |= bit
#define cfg_gpio_to_input_only(port, bit) 		port##M1 |= bit; port##M2 &= ~bit
#define cfg_gpio_to_quasi(port, bit) 			port##M1 &= ~bit; port##M2 &= ~bit

void hal_gpio_init(void)
{
	// 设置所有的IO脚为标准输入输出模式
	Set_All_GPIO_Quasi_Mode;
}

void hal_gpio_cfg(uint8_t port_pin, hal_gpio_mode_enum mode, hal_gpio_pull_t pin_pull)
{
	uint8_t pin_bit = 1 << (port_pin & 0x0F);

	switch (mode)
	{
	case HAL_GPIO_MODE_INPUT:
/*
		switch (port_pin >> 4)
		{
		case 0:
			cfg_gpio_to_input_only(P0, pin_bit);
			break;
		case 1:
			cfg_gpio_to_input_only(P1, pin_bit);
			break;
// 		case 2: IS NOT GPIO
// 			cfg_gpio_to_pushpull(P2, pin_bit);
// 			break;
		case 3:
			cfg_gpio_to_input_only(P3, pin_bit);
			break;
		default:
			break;
		}
		break;
*/
	case HAL_GPIO_MODE_OUTPUT:
		switch (port_pin >> 4)
		{
		case 0:
			cfg_gpio_to_push_pull(P0, pin_bit);
			break;
		case 1:
			cfg_gpio_to_push_pull(P1, pin_bit);
			break;
// 		case 2: IS NOT GPIO
// 			cfg_gpio_to_pushpull(P2, pin_bit);
// 			break;
		case 3:
			cfg_gpio_to_push_pull(P3, pin_bit);
			break;
		default:
			break;
		}
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
	uint8_t pin_sta = 1 << (port_pin & 0x0F);

	switch (port_pin >> 4)
	{
	case 0:
		pin_sta &= P0;
		break;
	case 1:
		pin_sta &= P1;
		break;
// 	case 2: IS NOT GPIO
// 		pin_sta &= P2;
// 		break;
	case 3:
		pin_sta &= P3;
		break;
	default:
		break;
	}
	return (pin_sta ? true : false);
}

void hal_gpio_pin_write(uint8_t port_pin, hal_gpio_state_t pin_state)
{
	uint8_t pin = 1 << (port_pin & 0x0F);

	switch (port_pin >> 4)
	{
	case 0:
		if (pin_state)
			P0 |= pin;
		else
			P0 &= ~pin;
		break;
	case 1:
		if (pin_state)
			P1 |= pin;
		else
			P1 &= ~pin;
		break;
// 	case 2: IS NOT GPIO
// 		if (pin_state)
// 			P2 |= pin;
// 		else
// 			P2 &= ~pin;
// 		break;
	case 3:
		if (pin_state)
			P3 |= pin;
		else
			P3 &= ~pin;
		break;
	default:
		break;
	}
}
void hal_gpio_pin_toggle(uint8_t port_pin)
{
	hal_gpio_pin_write(port_pin, !hal_gpio_pin_read(port_pin));
}

#endif // HAL_GPIO_C

