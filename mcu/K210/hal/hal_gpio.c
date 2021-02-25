/*!*****************************************************************************
* @file     hal_gpio.c
* @brief
* @author	 FuxFox
* @version  V1.0
* @date     2020/08/17
*******************************************************************************/
#ifndef HAL_GPIO_C
#define HAL_GPIO_C

#include "hal_gpio.h"
#include "app_log.h"
#include "fpioa.h"
#include "gpio.h"
#include "gpiohs.h"

#define K210_IO_NUM			48 /**< K210的自由IO数量 */
#define K210_GPIOHS_NUM		32 /**< gpiohs 数量 */
#define K210_GPIO_NUM		8	/**< gpio 数量 */

#define NOT_GPIO 0xFF
#define GPIOHS_BIT_MASK 0x80
#define GPIO_REMAP_BIT_MASK (~GPIOHS_BIT_MASK)

/**< gpio 已占用标记,bit8~39为gpiohs，bit0~7为gpio */
static uint64_t m_gpio_used_mark = 0;

/**< IO 到 GPIO 编号的映射，其中bit7=1表示gpiohs */
static uint8_t m_io_to_gpio_mapping[K210_IO_NUM];

void hal_gpio_init(void)
{
	gpio_init();
	memset(m_io_to_gpio_mapping, NOT_GPIO, sizeof(m_io_to_gpio_mapping));
}

void hal_gpio_cfg(uint8_t gpio_pin, hal_gpio_mode_enum mode, hal_gpio_pull_t pin_pull)
{
	fpioa_function_t gpio_func;
	gpio_drive_mode_t gpio_mode;

	assert_param(gpio_pin < K210_IO_NUM);

	if (m_io_to_gpio_mapping[gpio_pin] == NOT_GPIO)
	{
		uint64_t bit_mask = (mode <= HAL_GPIO_MODE_OUTPUT) ? 1 : (1UL << K210_GPIO_NUM);//确定m_gpio_used_mark的起始扫描位置
		uint8_t i = (mode <= HAL_GPIO_MODE_OUTPUT) ? 0 : K210_GPIO_NUM;//若mode > HAL_GPIO_MODE_OUTPUT, 只能分配gpiohs

		for (; i < (K210_GPIOHS_NUM + K210_GPIO_NUM); bit_mask <<= 1, i++)
		{
			if (m_gpio_used_mark & bit_mask)
			{
			}
			else
			{
				m_gpio_used_mark |= bit_mask;

				if (i < K210_GPIO_NUM)
				{
					gpio_func = FUNC_GPIO0 + i;
					m_io_to_gpio_mapping[gpio_pin] = i;
				}
				else
				{
					gpio_func = FUNC_GPIOHS0 - K210_GPIO_NUM + i;
					m_io_to_gpio_mapping[gpio_pin] = (i - K210_GPIO_NUM) | GPIOHS_BIT_MASK;
				}
				break;
			}
		}

		assert_param(i < (K210_GPIOHS_NUM + K210_GPIO_NUM));
		fpioa_set_function(gpio_pin, gpio_func);
	}

	switch (mode)
	{
	case HAL_GPIO_MODE_INPUT:
	case HAL_GPIO_MODE_OUTPUT:
		gpio_mode = (mode == HAL_GPIO_MODE_INPUT) ? (gpio_drive_mode_t)pin_pull : GPIO_DM_OUTPUT;
		gpio_pin = m_io_to_gpio_mapping[gpio_pin];
		if (gpio_pin & GPIOHS_BIT_MASK)
		{
			gpiohs_set_drive_mode(gpio_pin & GPIO_REMAP_BIT_MASK, gpio_mode);
		}
		else
		{
			gpio_set_drive_mode(gpio_pin, gpio_mode);
		}
		break;
	default:
		break;
	}
}

bool hal_gpio_pin_read(uint8_t gpio_pin)
{
	assert_param(gpio_pin < K210_IO_NUM);
	gpio_pin = m_io_to_gpio_mapping[gpio_pin];
	assert_param(gpio_pin != NOT_GPIO);

	return (bool)((gpio_pin & GPIOHS_BIT_MASK) ?
		gpiohs_get_pin(gpio_pin & GPIO_REMAP_BIT_MASK) : gpio_get_pin(gpio_pin));
}

void hal_gpio_pin_write(uint8_t gpio_pin, hal_gpio_state_t pin_state)
{
	assert_param(gpio_pin < K210_IO_NUM);
	gpio_pin = m_io_to_gpio_mapping[gpio_pin];
	assert_param(gpio_pin != NOT_GPIO);

	if (gpio_pin & GPIOHS_BIT_MASK)
	{
		gpiohs_set_pin(gpio_pin & GPIO_REMAP_BIT_MASK, (gpio_pin_value_t)pin_state);
	}
	else
	{
		gpio_set_pin(gpio_pin, (gpio_pin_value_t)pin_state);
	}
}

void hal_gpio_pin_toggle(uint8_t gpio_pin)
{
	hal_gpio_pin_write(gpio_pin, !hal_gpio_pin_read(gpio_pin));
}

#endif // HAL_GPIO_C

