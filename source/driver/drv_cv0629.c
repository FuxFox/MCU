/*******************************************************************************
 *
 * Module: drv_CV0629
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/21 09:13          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_cv0629.c
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/21
  *******************************************************************************/
#ifndef DRV_CV0629_C
#define DRV_CV0629_C

#include "drv_cv0629.h"

/*!*****************************************************************************
\brief  	initialize
\param[in]	drv_cv0629_instance_t * instance
\return     void
******************************************************************************/
void drv_cv0629_init(drv_cv0629_instance_t* instance)
{
    app_usart_init(instance->uart_instance, instance->tx_pin, instance->rx_pin, 9600);
    instance->frame_id = 1;
}

/*!*****************************************************************************
\brief      get checksum
\details
\param[in]    uint8_t * data    The data buffer to calculate checksum
\param[in]    uint8_t len       length of the data, in Byte
\return     uint8_t      checksum
******************************************************************************/
static uint8_t drv_cv0629_get_checksum(uint8_t* data, uint8_t len)
{
    uint8_t sum = 0;

    while (len--)
    {
        sum += *data++;
    }

    return sum;
}

/*!*****************************************************************************
\brief      check the checksum
\details
\param[in]    uint8_t * data    The data buffer to be check
\param[in]    uint8_t len       length of the data, in Byte, include the checksum byte follow the data
\return     bool TRUE if success
******************************************************************************/
static bool drv_cv0629_is_data_valid(uint8_t* data, uint8_t len)
{
    return (drv_cv0629_get_checksum(data, len - 1) == data[len - 1]);
}

/*!*****************************************************************************
\brief  	construct a data frame
\param[in]	drv_cv0629_instance_t * instance
\param[in]	drv_cv0629_cmd_enum cmd
\param[in]	uint8_t * frame         Pointer of frame data buffer
\return     void
******************************************************************************/
static void drv_cv0629_get_target_frame(drv_cv0629_instance_t* instance, drv_cv0629_cmd_enum cmd, uint8_t* frame)
{
    frame[0] = 'W';
    frame[1] = 'X';
    frame[2] = instance->addr;
    frame[3] = 0x66;

    frame[4] = instance->frame_id >> 8;
    frame[5] = instance->frame_id;

    instance->frame_id++;

    frame[6] = cmd;
    frame[7] = 0;
    frame[8] = drv_cv0629_get_checksum(frame, 8);
}

/*!*****************************************************************************
\brief  	communication test
\param[in]	drv_cv0629_instance_t * instance
\return     bool TRUE if success
******************************************************************************/
bool drv_cv0629_connection_test(drv_cv0629_instance_t* instance)
{
    uint8_t data[13];

    drv_cv0629_get_target_frame(instance, DRV_CV0629_CMD_TEST_CONNECTION, data);
    HAL_UART_Transmit(instance->uart_instance, data, 9, DRV_CV0629_COMMUNICATION_TIMEOUT_MS);
    if ((HAL_UART_Receive(instance->uart_instance, data, 12/*13*/, DRV_CV0629_COMMUNICATION_TIMEOUT_MS) == HAL_OK)//手册上说是13个字节，实际接收只有12个字节
        && drv_cv0629_is_data_valid(data, 12/*13*/))
    {
        return (data[8] == 1);
    }
    return false;
}

/*!*****************************************************************************
\brief  	get instance's status
\param[in]	drv_cv0629_instance_t * instance
\return     drv_cb0629_sta_struct
******************************************************************************/
drv_cb0629_sta_struct drv_cv0629_get_status(drv_cv0629_instance_t* instance)
{
    uint8_t data[12];
    drv_cb0629_sta_struct sta = { false, false, true };

    drv_cv0629_get_target_frame(instance, DRV_CV0629_CMD_GET_STATUS, data);

    HAL_UART_Transmit(instance->uart_instance, data, 9, DRV_CV0629_COMMUNICATION_TIMEOUT_MS);
    if ((HAL_UART_Receive(instance->uart_instance, data, 12, DRV_CV0629_COMMUNICATION_TIMEOUT_MS) == HAL_OK)
        && drv_cv0629_is_data_valid(data, 12))
    {
        sta.is_lack_stuff = data[8];
        sta.is_falling = data[9];
        sta.is_error = data[10];
    }

    return sta;
}

/*!*****************************************************************************
\brief  	get stuff
\param[in]	drv_cv0629_instance_t * instance
\return     bool TRUE if success
******************************************************************************/
bool drv_cv0629_get_stuff(drv_cv0629_instance_t* instance)
{
    uint8_t data[14];

    drv_cv0629_get_target_frame(instance, DRV_CV0629_CMD_GET_STUFF_NOBLOCK, data);

    HAL_UART_Transmit(instance->uart_instance, data, 9, DRV_CV0629_COMMUNICATION_TIMEOUT_MS);
    memset(data, 0, 14);
    if ((HAL_UART_Receive(instance->uart_instance, data, 14, DRV_CV0629_COMMUNICATION_TIMEOUT_MS) == HAL_OK)
        && drv_cv0629_is_data_valid(data, 14))
    {
        return !data[8];
    }
    return false;
}

/*!*****************************************************************************
\brief      is instance lack for stuff ?
\details
\param[in]    drv_cv0629_instance_t * instance
\return     bool TRUE if success
******************************************************************************/
bool drv_cv0629_is_lack_stuff(drv_cv0629_instance_t* instance)
{
    return  drv_cv0629_get_status(instance).is_lack_stuff;
}
#endif // DRV_CV0629_C
