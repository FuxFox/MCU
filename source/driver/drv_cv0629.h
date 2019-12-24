/*******************************************************************************
 *
 * Module: drv_CV0629
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/21 09:14          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_cv0629.h
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/21
  *******************************************************************************/
#ifndef DRV_CV0629_H
#define DRV_CV0629_H

  /*! \defgroup drv_CV0629_public Public
  \ingroup drv_CV0629
  \details      KEWEINIDI CV0629 driver.(a cup distribute device)
                This driver is implemented base on STM32F103xx with HAL.

  * @{ */


#include "app_usart.h"
  //********************************* Module Config *******************************/

#define DRV_CV0629_COMMUNICATION_TIMEOUT_MS        1000
//********************************* Data Type ***********************************/

typedef enum
{
    DRV_CV0629_CMD_TEST_CONNECTION   = 0x00,        /*!< test connectivity */
    DRV_CV0629_CMD_GET_STATUS        = 0x02,        /*!< get device status */
    DRV_CV0629_CMD_STATUS_CHECK      = 0x04,        /*!< query status (while in not blocking mode) */
    DRV_CV0629_CMD_GET_STUFF_NOBLOCK = 0x03,        /*!< distribute stuff in not blocking mode */
    DRV_CV0629_CMD_GET_STUFF_BLOCK   = 0x05,        /*!< distribute stuff in blocking mode */
}drv_cv0629_cmd_enum;

typedef struct
{
    bool is_lack_stuff;
    bool is_falling;
    bool is_error;
}drv_cb0629_sta_struct;

/*! CV0629 instance structure */
typedef struct
{
    uint8_t addr;       /*!< device address, [0-255] */
    uint16_t frame_id;
    bool is_connected;

    UART_HandleTypeDef* uart_instance;
    uint8_t tx_pin;
    uint8_t rx_pin;
    IRQn_Type irq_type;
}drv_cv0629_instance_t;


//********************************* Public Interface ****************************/

/*!*****************************************************************************
\brief  	Use this macro to quickly define an instance

\param[in]	_name   :   The name of this instance
\param[in]	_uart   :   The UART instance use for this instance
\param[in]	_tx_pin :   The UART TX pin number of the MCU use for this instance
\param[in]	_rx_pin :   The UART RX pin number of the MCU use for this instance
\param[in]	_addr   :   Address of the instance, can be [0 - 255]
*******************************************************************************/
#define DRV_CV0629_INSTANCE(_name, _uart, _tx_pin, _rx_pin, _addr)           \
    APP_UART_DEF(_name##_##_uart, _uart);                                    \
    static drv_cv0629_instance_t _name = {                                   \
        .tx_pin = _tx_pin,                                                   \
        .rx_pin = _rx_pin,                                                   \
        .addr = _addr,                                                       \
        .uart_instance = &_name##_##_uart,                                   \
    }                

void drv_cv0629_init(drv_cv0629_instance_t* instance);


bool drv_cv0629_connection_test(drv_cv0629_instance_t* instance);
drv_cb0629_sta_struct drv_cv0629_get_status(drv_cv0629_instance_t* instance);
bool drv_cv0629_get_stuff(drv_cv0629_instance_t* instance);
bool drv_cv0629_is_lack_stuff(drv_cv0629_instance_t* instance);
//********************************* Private Interface ***************************/

static uint8_t drv_cv0629_get_checksum(uint8_t* data, uint8_t len);
static bool drv_cv0629_is_data_valid(uint8_t* data, uint8_t len);
static void drv_cv0629_get_target_frame(drv_cv0629_instance_t* instance, drv_cv0629_cmd_enum cmd, uint8_t* frame);
/*! @}*/ //end of group drv_CV0629
#endif // DRV_CV0629_H
