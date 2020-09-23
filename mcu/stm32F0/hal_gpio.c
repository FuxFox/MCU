/*!*****************************************************************************
* @file     hal_gpio.c
* @brief
* @author	 FuxFox
* @version  V1.0
* @date     2020/08/18
*******************************************************************************/
#ifndef HAL_GPIO_C
#define HAL_GPIO_C

#include "hal_gpio.h"

#if defined(HAL_GPIO_ENABLE)&&(HAL_GPIO_ENABLE)

static GPIO_TypeDef* const pin_to_port_map[CHIP_PIN_NUM] = PIN_TO_PORT_MAP;
static const uint8_t pin_to_gpiopin_map[CHIP_PIN_NUM] = PIN_TO_GPIOPIN_MAP;
// static const uint8_t pin_to_adc_channel_map[CHIP_PIN_NUM] = PIN_TO_ADC_CHANNEL_MAP;
static uint16_t m_exti_to_pin[16] = { NULL };

void hal_gpio_init(void)
{
	/* GPIO Ports Clock Enable */
// 	__HAL_RCC_GPIOE_CLK_ENABLE();
// 	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();//for stm32f030F4P6
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
// 	__HAL_RCC_GPIOD_CLK_ENABLE();
}

void hal_gpio_cfg(uint16_t gpio_pin, hal_gpio_mode_enum mode, hal_gpio_pull_t pin_pull)
{
	GPIO_InitTypeDef GPIO_InitStruct = {
			.Mode = mode,
			.Pull = pin_pull,
			.Speed = HAL_GPIO_DEFAULT_OUTPUT_SPEED,
	};
	assert_param(gpio_pin <= CHIP_PIN_NUM);

	GPIO_InitStruct.Pin = GPIO_PIN_0 << pin_to_gpiopin_map[gpio_pin - 1];

	HAL_GPIO_Init(pin_to_port_map[gpio_pin - 1], &GPIO_InitStruct);
}

bool hal_gpio_pin_read(uint16_t gpio_pin)
{
	assert_param(gpio_pin <= CHIP_PIN_NUM);
	return (bool)HAL_GPIO_ReadPin(pin_to_port_map[gpio_pin - 1], GPIO_PIN_0 << pin_to_gpiopin_map[gpio_pin - 1]);
}

void hal_gpio_pin_write(uint16_t gpio_pin, hal_gpio_state_t PinState)
{
	assert_param(gpio_pin <= CHIP_PIN_NUM);
	gpio_pin--;

	if (PinState)
	{
		pin_to_port_map[gpio_pin]->BSRR = (uint32_t)GPIO_PIN_0 << pin_to_gpiopin_map[gpio_pin];
	}
	else
	{
		pin_to_port_map[gpio_pin]->BRR = (uint32_t)GPIO_PIN_0 << pin_to_gpiopin_map[gpio_pin];
	}
}

void hal_gpio_pin_toggle(uint16_t gpio_pin)
{
	assert_param(gpio_pin <= CHIP_PIN_NUM);
	HAL_GPIO_TogglePin(pin_to_port_map[gpio_pin - 1], GPIO_PIN_0 << pin_to_gpiopin_map[gpio_pin - 1]);

}

void hal_gpio_deinit(uint16_t gpio_pin)
{
	uint8_t gpio_index;
	IRQn_Type exti_irqn;

	assert_param(gpio_pin <= CHIP_PIN_NUM);

	gpio_index = pin_to_gpiopin_map[gpio_pin - 1];

	if (m_exti_to_pin[gpio_index] == gpio_pin)
	{
		m_exti_to_pin[gpio_index] = NULL;
		exti_irqn = hal_gpio_pin2exti_irqn(gpio_pin);
		if (gpio_index <= 4)
		{
			HAL_NVIC_DisableIRQ(exti_irqn);
		}
		else if (gpio_index <= 9)
		{
			if ((m_exti_to_pin[5] == m_exti_to_pin[6])
				&& (m_exti_to_pin[5] == m_exti_to_pin[7])
				&& (m_exti_to_pin[5] == m_exti_to_pin[8])
				&& (m_exti_to_pin[5] == m_exti_to_pin[9]))
			{
				HAL_NVIC_DisableIRQ(exti_irqn);
			}
		}
		else
		{
			if ((m_exti_to_pin[10] == m_exti_to_pin[11])
				&& (m_exti_to_pin[10] == m_exti_to_pin[12])
				&& (m_exti_to_pin[10] == m_exti_to_pin[13])
				&& (m_exti_to_pin[10] == m_exti_to_pin[14])
				&& (m_exti_to_pin[10] == m_exti_to_pin[15]))
			{
				HAL_NVIC_DisableIRQ(exti_irqn);
			}
		}
	}

	HAL_GPIO_DeInit(pin_to_port_map[gpio_pin - 1], GPIO_PIN_0 << gpio_index);
}

uint8_t hal_gpio_pin2gpiopin(uint16_t gpio_pin)
{
	assert_param(gpio_pin <= CHIP_PIN_NUM);
	assert_param(pin_to_gpiopin_map[gpio_pin - 1] != NO_GPIO);
	return pin_to_gpiopin_map[gpio_pin - 1];
}

GPIO_TypeDef* hal_gpio_pin2gpioport(uint16_t gpio_pin)
{
	assert_param(gpio_pin <= CHIP_PIN_NUM);
	assert_param(pin_to_gpiopin_map[gpio_pin - 1] != NO_GPIO);
	return pin_to_port_map[gpio_pin - 1];
}

#endif // HAL_GPIO_ENABLE

#endif // HAL_GPIO_C

