/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/08/13 18:58          V1.0             build this file
 *
 *******************************************************************************/
#ifndef HAL_USART_H
#define HAL_USART_H

/*! \defgroup hal_usart
\brief      This module is the encapsulation of HAL Library for STM32f103xxx
\details
* @{ */

#include "hal_config.h"

#include "hal_gpio.h"
//********************************* Module Config *******************************/





//********************************* Data Type ***********************************/

/*! Define an UART instance quickly */
#define HAL_UART_DEF(_name, _uart)                    \
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

/*!*****************************************************************************
\brief  	initialize an instance
\param[in]	UART_HandleTypeDef * huart      The _name parameter which you used at HAL_UART_DEF()
\param[in]	uint8_t tx_pin                  The pin number of chip as TX pin
\param[in]	uint8_t rx_pin                  The pin number of chip as RX pin
\param[in]	uint32_t baud                   The baud rate
\return     void
******************************************************************************/
void hal_usart_init(UART_HandleTypeDef* huart, uint8_t tx_pin, uint8_t rx_pin, uint32_t baud);

/*!*****************************************************************************
\brief      deinit uart
\param[in]    UART_HandleTypeDef * huart
\param[in]    uint8_t tx_pin
\param[in]    uint8_t rx_pin
\return     void
******************************************************************************/
void hal_usart_deinit(UART_HandleTypeDef* huart, uint8_t tx_pin, uint8_t rx_pin);

/*!*****************************************************************************
\brief      disable uart clock and irq
\param[in]    UART_HandleTypeDef * huart
\return     void
******************************************************************************/
void hal_usart_disable(UART_HandleTypeDef* huart);

/*!*****************************************************************************
\brief      enable uart clock and irq
\param[in]    UART_HandleTypeDef * huart
\return     void
******************************************************************************/
void hal_usart_enable(UART_HandleTypeDef* huart);

//********************************* Private Interface ***************************/





/*! @}*/ //end of group hal_usart
#endif // HAL_USART_H
