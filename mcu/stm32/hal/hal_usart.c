/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/08/13 18:55          V1.0             build this file
 *
 *******************************************************************************/
#ifndef HAL_USART_C
#define HAL_USART_C

#include "hal_usart.h"


#if defined(HAL_USART_ENABLE)&&(HAL_USART_ENABLE)

void hal_usart_init(UART_HandleTypeDef* huart, uint8_t tx_pin, uint8_t rx_pin, uint32_t baud)
{
    HAL_StatusTypeDef error_code;

    huart->Init.BaudRate = baud;

    hal_gpio_cfg(tx_pin, HAL_GPIO_MODE_AF_PP, HAL_GPIO_PULLUP, HAL_GPIO_SPEED_FREQ_HIGH);
    hal_gpio_cfg_input(rx_pin, HAL_GPIO_PULLUP);

    hal_usart_enable(huart);
    error_code = HAL_UART_Init(huart);
    HAL_ERROR_CHECK(error_code);
}

void hal_usart_deinit(UART_HandleTypeDef* huart, uint8_t tx_pin, uint8_t rx_pin)
{
    hal_usart_disable(huart);

    HAL_UART_DeInit(huart);

    hal_gpio_deinit(tx_pin);
    hal_gpio_deinit(rx_pin);
}

void hal_usart_disable(UART_HandleTypeDef* huart)
{
    switch ((uint32_t)huart->Instance)
    {
    case (uint32_t)USART1:
        __HAL_RCC_USART1_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(USART1_IRQn);
        break;
    case (uint32_t)USART2:
        __HAL_RCC_USART2_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(USART2_IRQn);
        break;
    case (uint32_t)USART3:
        __HAL_RCC_USART3_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(USART3_IRQn);
        break;
    case (uint32_t)UART4:
        __HAL_RCC_UART4_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(UART4_IRQn);
        break;
    case (uint32_t)UART5:
        __HAL_RCC_UART5_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(UART5_IRQn);
        break;
    default:
        break;
    }
}


void hal_usart_enable(UART_HandleTypeDef* huart)
{
    switch ((uint32_t)huart->Instance)
    {
    case (uint32_t)USART1:
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_AFIO_REMAP_USART1_ENABLE();
        HAL_NVIC_SetPriority(USART1_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        break;
    case (uint32_t)USART2:
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_AFIO_REMAP_USART2_ENABLE();
        HAL_NVIC_SetPriority(USART2_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
        break;
    case (uint32_t)USART3:
        __HAL_RCC_USART3_CLK_ENABLE();
        __HAL_AFIO_REMAP_USART3_ENABLE();
        HAL_NVIC_SetPriority(USART3_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(USART3_IRQn);
        break;
    case (uint32_t)UART4:
        __HAL_RCC_UART4_CLK_ENABLE();
        HAL_NVIC_SetPriority(UART4_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(UART4_IRQn);
        break;
    case (uint32_t)UART5:
        __HAL_RCC_UART5_CLK_ENABLE();
        HAL_NVIC_SetPriority(UART5_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(UART5_IRQn);
        break;
    default:
        break;
    }
}

#endif

#endif // HAL_USART_C
