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
  * \file     app_gpio.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/12
  *******************************************************************************/
#ifndef APP_GPIO_C
#define APP_GPIO_C

#include "app_gpio.h"

#if defined(APP_GPIO_ENABLE)&&(APP_GPIO_ENABLE)

static GPIO_TypeDef* const pin_to_port_map[CHIP_PIN_NUM] = PIN_TO_PORT_MAP;
static const uint8_t pin_to_gpiopin_map[CHIP_PIN_NUM] = PIN_TO_GPIOPIN_MAP;
// static const uint8_t pin_to_adc_channel_map[CHIP_PIN_NUM] = PIN_TO_ADC_CHANNEL_MAP;
static uint16_t m_exti_to_pin[16] = { NULL };

/*!*****************************************************************************
\brief  	module initialize
\param[in]	void
\return     void
******************************************************************************/
void app_gpio_init(void)
{
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
}

/*!*****************************************************************************
\brief      gpio configure
\details
\param[in]    uint16_t pin_number               Pin number of chip to be configure
\param[in]    app_gpio_mode_enum mode
\param[in]    app_gpio_pull_enum pin_pull
\param[in]    app_gpio_speed_enum output_speed  If configure to input, this param not use
\return     void
******************************************************************************/
void app_gpio_cfg(uint16_t pin_number, app_gpio_mode_enum mode, app_gpio_pull_t pin_pull, app_gpio_speed_enum output_speed)
{
    GPIO_InitTypeDef GPIO_InitStruct = {
            .Mode = mode,
            .Pull = pin_pull,
            .Speed = output_speed,
    };
    assert_param(pin_number <= CHIP_PIN_NUM);

    GPIO_InitStruct.Pin = GPIO_PIN_0 << pin_to_gpiopin_map[pin_number - 1];

    HAL_GPIO_Init(pin_to_port_map[pin_number - 1], &GPIO_InitStruct);
}

/*!*****************************************************************************
\brief      pin read
\details
\param[in]    uint16_t pin_number              Pin number of chip to be configure
\return     GPIO_PinState
******************************************************************************/
GPIO_PinState app_gpio_pin_read(uint16_t pin_number)
{
    assert_param(pin_number <= CHIP_PIN_NUM);
    return HAL_GPIO_ReadPin(pin_to_port_map[pin_number - 1], GPIO_PIN_0 << pin_to_gpiopin_map[pin_number - 1]);
}

/*!*****************************************************************************
\brief      pin write
\details
\param[in]    uint16_t pin_number
\param[in]    GPIO_PinState PinState
\return     void
******************************************************************************/
void app_gpio_pin_write(uint16_t pin_number, GPIO_PinState PinState)
{
    assert_param(pin_number <= CHIP_PIN_NUM);
    HAL_GPIO_WritePin(pin_to_port_map[pin_number - 1], GPIO_PIN_0 << pin_to_gpiopin_map[pin_number - 1], PinState);
}

/*!*****************************************************************************
\brief      toggle gpio pin
\details
\param[in]    uint16_t pin_number
\return     void
******************************************************************************/
void app_gpio_pin_toggle(uint16_t pin_number)
{
    assert_param(pin_number <= CHIP_PIN_NUM);
    HAL_GPIO_TogglePin(pin_to_port_map[pin_number - 1], GPIO_PIN_0 << pin_to_gpiopin_map[pin_number - 1]);

}

/*!*****************************************************************************
\brief      deinit gpio configuration
\details
\param[in]    uint16_t pin_number
\return     void
******************************************************************************/
void app_gpio_deinit(uint16_t pin_number)
{
    uint8_t gpio_index;
    IRQn_Type exti_irqn;

    assert_param(pin_number <= CHIP_PIN_NUM);

    gpio_index = pin_to_gpiopin_map[pin_number - 1];

    if (m_exti_to_pin[gpio_index] == pin_number)
    {
        m_exti_to_pin[gpio_index] = NULL;
        exti_irqn = app_gpio_pin2exti_irqn(pin_number);
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

    HAL_GPIO_DeInit(pin_to_port_map[pin_number - 1], GPIO_PIN_0 << gpio_index);
}

/*!*****************************************************************************
\brief      chip pin to GPIO PIN [0~15] mapping
\details
\param[in]    uint16_t pin_number
\return     uint8_t
******************************************************************************/
uint8_t app_gpio_pin2gpiopin(uint16_t pin_number)
{
    assert_param(pin_number <= CHIP_PIN_NUM);
    assert_param(pin_to_gpiopin_map[pin_number - 1] != NO_GPIO);
    return pin_to_gpiopin_map[pin_number - 1];
}

/*!*****************************************************************************
\brief      chip pin to EXTI irq channel mapping
\details
\param[in]    uint16_t pin_number
\return     IRQn_Type
******************************************************************************/
IRQn_Type app_gpio_pin2exti_irqn(uint16_t pin_number)
{
    assert_param(pin_number <= CHIP_PIN_NUM);
    assert_param(pin_to_gpiopin_map[pin_number - 1] != NO_GPIO);

    switch (pin_to_gpiopin_map[pin_number - 1])
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

/*!*****************************************************************************
\brief      configure gpio to EXTI
\details
\param[in]    uint16_t pin_number
\param[in]    app_gpio_exti_t mode
\param[in]    app_gpio_pull_t pin_pull
\param[in]    uint8_t irq_priority £º bit7~bit4: main-priority, bit3_bit0: sub-priority
\return     void
******************************************************************************/
void app_gpio_cfg_exti(uint16_t pin_number, app_gpio_exti_t mode, app_gpio_pull_t pin_pull, uint8_t irq_priority)
{
    uint32_t old_irq_priority;
    uint32_t old_irq_subpriority;

    IRQn_Type exti_irqn;
    GPIO_InitTypeDef GPIO_InitStruct = {
            .Mode = mode,
            .Pull = pin_pull,
    };

    assert_param(pin_number <= CHIP_PIN_NUM);
    assert_param(pin_to_gpiopin_map[pin_number - 1] != NO_GPIO);
    assert_param(m_exti_to_pin[pin_to_gpiopin_map[pin_number - 1]] == NULL);

    GPIO_InitStruct.Pin = GPIO_PIN_0 << pin_to_gpiopin_map[pin_number - 1];
    HAL_GPIO_Init(pin_to_port_map[pin_number - 1], &GPIO_InitStruct);

    exti_irqn = app_gpio_pin2exti_irqn(pin_number);
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

    m_exti_to_pin[pin_to_gpiopin_map[pin_number - 1]] = pin_number;
}

#endif

#endif // APP_GPIO_C
