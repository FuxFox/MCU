/*******************************************************************************
 *
 * Module: ble_app_service
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/07/29 17:46          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     ble_app_service.h
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/07/29
 *******************************************************************************/
#ifndef BLE_APP_SERVICE_H
#define BLE_APP_SERVICE_H

/*! \defgroup ble_app_service_public Public
\ingroup ble_app_service
\details       BLE module for NRF52832
               BLE service implemented for user application. 
* @{ */

#include "app_config.h"

#include "module.h"
#include "drv_power.h"

#ifdef __cplusplus
extern "C" {
#endif

//********************************* Module Config *******************************/
                                
#define BLE_APP_SVC_UUID_BASE        {0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

#define BLE_APP_SVC_UUID_SERVICE            0xFFB0

#define BLE_APP_SVC_CHAR_UUID_CONTROL        0xFFB1
#define BLE_APP_SVC_CHAR_UUID_MAC            0xFFB2


//********************************* Data Type ***********************************/

typedef enum
{
        BLE_APP_SVC_GET_UUIDTYPE = 0,
}ble_app_svc_get_t;

/*!< 服务特征索引 */
typedef enum
{
        BLE_APP_SVC_CHAR_INDEX_CONTROL,
        BLE_APP_SVC_CHAR_INDEX_MAC,

        BLE_APP_SVC_CHAR_INDEX_MAX,
}ble_app_svc_char_index_t;

/*! ble 控制命令 */
typedef enum
{
        BLE_CMD_SHUTDOWN,            /*!< 关机 */
        BLE_CMD_LASER_ONOFF,    /*!< 激光开关 */
        BLE_CMD_FLASH_LED_ONOFF,        /*!< 补光灯开关 */
        BLE_CMD_ATMOSPHERE_LAMP_ONOFF,        /*!< 氛围灯开关 */
        BLE_CMD_MOTOR_SET_STEP,    /*!< 电机步数设置 */
        BLE_CMD_MOTOR_CTRL        /*!< 电机控制 */
}ble_app_svc_cmd_t;

typedef void (*ble_service_write_handler_t) (uint8_t const* new_state);
/*! 服务特性结构体 */
typedef struct
{
        uint16_t uuid;
        uint8_t data_len;
        bool writeable;
        bool notify;
        bool is_var_len;
        ble_service_write_handler_t write_handler;
}ble_service_char_struct;

//********************************* Public Interface ****************************/

extern uint32_t ble_app_svc_init(void);

//extern uint32_t Ble_Service_Casher_GetInfo(BLE_APP_SERVICE_GET_e info);
extern void ble_app_svc_set_char_value(ble_app_svc_char_index_t char_index, uint8_t* data, uint8_t len);


//********************************* Private Interface ***************************/

static void ble_app_svc_event_callback(ble_evt_t const* p_ble_evt, void* p_context);
static uint32_t ble_app_svc_add_characteristic(void);
static void ble_app_svc_control_handler(uint8_t const* command);
static void ble_app_svc_get_mac(ble_gap_addr_t* mac);
#ifdef __cplusplus
}
#endif





/*! @}*/ //end of group ble_app_service
#endif // BLE_APP_SERVICE_H
