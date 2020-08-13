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

#if defined(HAL_GPIO_ENABLE)&&(HAL_GPIO_ENABLE)

static GPIO_TypeDef* const pin_to_port_map[CHIP_PIN_NUM] = PIN_TO_PORT_MAP;
static const uint8_t pin_to_gpiopin_map[CHIP_PIN_NUM] = PIN_TO_GPIOPIN_MAP;
// static const uint8_t pin_to_adc_channel_map[CHIP_PIN_NUM] = PIN_TO_ADC_CHANNEL_MAP;
static uint16_t m_exti_to_pin[16] = { NULL };

void hal_gpio_init(void)
{
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
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

void hal_gpio_pin_write(uint16_t gpio_pin, GPIO_PinState PinState)
{
	assert_param(gpio_pin <= CHIP_PIN_NUM);
	HAL_GPIO_WritePin(pin_to_port_map[gpio_pin - 1], GPIO_PIN_0 << pin_to_gpiopin_map[gpio_pin - 1], PinState);
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

IRQn_Type hal_gpio_pin2exti_irqn(uint16_t gpio_pin)
{
	assert_param(gpio_pin <= CHIP_PIN_NUM);
	assert_param(pin_to_gpiopin_map[gpio_pin - 1] != NO_GPIO);

	switch (pin_to_gpiopin_map[gpio_pin - 1])
	{
	case 0:
		return EXTI0_IRQn;
	case 1:
		return EXTI1_IRQn;
	case 2:
		return EXTI2_IRQn;
	case 3:
		return EXTI3_IRQn;
	case 4:
		return EXTI4_IRQn;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		return EXTI9_5_IRQn;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	default:
		return EXTI15_10_IRQn;
	}
}

void hal_gpio_cfg_exti(uint16_t gpio_pin, hal_gpio_exti_t mode, hal_gpio_pull_t pin_pull, uint8_t irq_priority)
{
	uint32_t old_irq_priority;
	uint32_t old_irq_subpriority;

	IRQn_Type exti_irqn;
	GPIO_InitTypeDef GPIO_InitStruct = {
			.Mode = mode,
			.Pull = pin_pull,
	};

	assert_param(gpio_pin <= CHIP_PIN_NUM);
	assert_param(pin_to_gpiopin_map[gpio_pin - 1] != NO_GPIO);
	assert_param(m_exti_to_pin[pin_to_gpiopin_map[gpio_pin - 1]] == NULL);

	GPIO_InitStruct.Pin = GPIO_PIN_0 << pin_to_gpiopin_map[gpio_pin - 1];
	HAL_GPIO_Init(pin_to_port_map[gpio_pin - 1], &GPIO_InitStruct);

	exti_irqn = hal_gpio_pin2exti_irqn(gpio_pin);
	if (!NVIC_GetEnableIRQ(exti_irqn))
	{
		HAL_NVIC_SetPriority(exti_irqn, irq_priority >> 4, irq_priority & 0x0F);
		HAL_NVIC_EnableIRQ(exti_irqn);
	}
	else
	{        //Interrupt was enable, check whether there is conflict in priority configuration
		HAL_NVIC_GetPriority(exti_irqn, HAL_NVIC_GetPriorityGrouping(), &old_irq_priority, &old_irq_subpriority);
		assert_param((old_irq_priority != (irq_priority >> 4)) || (old_irq_subpriority != (irq_priority & 0x0F)));
	}

	m_exti_to_pin[pin_to_gpiopin_map[gpio_pin - 1]] = gpio_pin;
}

#endif // HAL_GPIO_ENABLE

#endif // HAL_GPIO_C

