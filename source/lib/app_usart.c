/*******************************************************************************
 *
 * Module: app_usart
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/23 19:36          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     app_usart.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/23
  *******************************************************************************/
#ifndef APP_USART_C
#define APP_USART_C

#include "app_usart.h"


#if defined(APP_USART_ENABLE)&&(APP_USART_ENABLE)
/*!*****************************************************************************
\brief  	initialize an instance
\param[in]	UART_HandleTypeDef * huart      The _name parameter which you used at APP_UART_DEF()
\param[in]	uint8_t tx_pin                  The pin number of chip as TX pin
\param[in]	uint8_t rx_pin                  The pin number of chip as RX pin
\param[in]	uint32_t baud                   The baud rate
\return     void
******************************************************************************/
void app_usart_init(UART_HandleTypeDef* huart, uint8_t tx_pin, uint8_t rx_pin, uint32_t baud)
{
    HAL_StatusTypeDef error_code;

    huart->Init.BaudRate = baud;

    app_gpio_cfg(tx_pin, APP_GPIO_MODE_AF_PP, APP_GPIO_PULLUP, APP_GPIO_SPEED_FREQ_HIGH);
    app_gpio_cfg_input(rx_pin, APP_GPIO_PULLUP);

    app_usart_enable(huart);
    error_code = HAL_UART_Init(huart);
    HAL_ERROR_CHECK(error_code);
}

/*!*****************************************************************************
\brief      deinit uart
\details
\param[in]    UART_HandleTypeDef * huart
\param[in]    uint8_t tx_pin
\param[in]    uint8_t rx_pin
\return     void
******************************************************************************/
void app_usart_deinit(UART_HandleTypeDef* huart, uint8_t tx_pin, uint8_t rx_pin)
{
    app_usart_disable(huart);

    HAL_UART_DeInit(huart);

    app_gpio_deinit(tx_pin);
    app_gpio_deinit(rx_pin);
}
/*!*****************************************************************************
\brief      disable uart clock and irq
\details
\param[in]    UART_HandleTypeDef * huart
\return     void
******************************************************************************/
void app_usart_disable(UART_HandleTypeDef* huart)
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


/*!*****************************************************************************
\brief      enable uart clock and irq
\details
\param[in]    UART_HandleTypeDef * huart
\return     void
******************************************************************************/
void app_usart_enable(UART_HandleTypeDef* huart)
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

#endif // APP_USART_C
