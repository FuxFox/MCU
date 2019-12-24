/*******************************************************************************
 * Module: drv_m26
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/09/03 19:09          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     drv_m26.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/09/03
 *******************************************************************************/
#ifndef DRV_M26_H
#define DRV_M26_H

/*! \defgroup drv_m26_public Public
\ingroup drv_m26
\brief       QUECTEL M26 IOT module driver
        This driver is implemented base on NRF52832 with nrf_serial(UART) library.
\details 
* @{ */
#include "app_config.h"



//********************************* Module Config *******************************/
                                
#define DRV_M26_UART_HWFC                CFG_M26_UART_HWFC
#define DRV_M26_UART_BAUDRATE            NRFX_CONCAT_2(NRF_UART_BAUDRATE_, CFG_M26_UART_BAUDRATE)
//#define DRV_M26_UART_TX_BUF_SIZE        256                         /**< UART TX buffer size. */
//#define DRV_M26_UART_RX_BUF_SIZE        256                         /**< UART RX buffer size. */

#define DRV_M26_RX_PIN            PIN_RX
#define DRV_M26_TX_PIN            PIN_TX
#define DRV_M26_CTS_PIN            PIN_CTS
#define DRV_M26_RTS_PIN            PIN_RTS

#define DRV_M26_PWRKEY            PIN_M26_PWRKEY

#define SERIAL_FIFO_TX_SIZE 512
#define SERIAL_FIFO_RX_SIZE 512
#define SERIAL_BUFF_TX_SIZE 1
#define SERIAL_BUFF_RX_SIZE 1
//********************************* Data Type ***********************************/


typedef void (*error_handler)(uint32_t);



//********************************* Public Interface ****************************/

bool drv_m26_init(error_handler handler);
void drv_m26_reboot(void);
bool drv_m26_reinit(void);
void drv_m26_serial_reinit(void);
void drv_m26_startup(void);
void drv_m26_shutdown(void);

size_t drv_m26_TxRx(const char* tx, char* rx, size_t rx_len, uint32_t timeout_ms);


void drv_m26_clean_rx_queue(void);
bool drv_m26_is_ready(void);
//********************************* Private Interface ***************************/

static void drv_m26_serial_event_handler(struct nrf_serial_s const* p_serial, nrf_serial_event_t event);



/*! @}*/ //end of group drv_m26
#endif // DRV_M26_H
