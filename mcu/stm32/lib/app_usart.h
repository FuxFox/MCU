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
  * \file     app_usart.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/23
  *******************************************************************************/
#ifndef APP_USART_H
#define APP_USART_H

  /*! \defgroup app_usart_public Public
  \ingroup app_usart
  \brief      This module is the encapsulation of HAL Library for STM32f103xxx
  \details
  * @{ */

#include "app_config.h"

#include "app_gpio.h"
  //********************************* Module Config *******************************/





  //********************************* Data Type ***********************************/

  /*! Define an UART instance quickly */
#define APP_UART_DEF(_name, _uart)                    \
    UART_HandleTypeDef _name = {                      \
    .Instance                = _uart,                 \
    .Init.WordLength         = UART_WORDLENGTH_8B,    \
    .Init.StopBits           = UART_STOPBITS_1,       \
    .Init.Parity             = UART_PARITY_NONE,      \
    .Init.Mode               = UART_MODE_TX_RX,       \
    .Init.HwFlowCtl          = UART_HWCONTROL_NONE,   \
    .Init.OverSampling       = UART_OVERSAMPLING_16,  \
}


//********************************* Public Interface ****************************/

void app_usart_init(UART_HandleTypeDef* huart, uint8_t tx_pin, uint8_t rx_pin, uint32_t baud);
void app_usart_deinit(UART_HandleTypeDef* huart, uint8_t tx_pin, uint8_t rx_pin);
void app_usart_disable(UART_HandleTypeDef* huart);
void app_usart_enable(UART_HandleTypeDef* huart);
//********************************* Private Interface ***************************/





/*! @}*/ //end of group app_usart
#endif // APP_USART_H
