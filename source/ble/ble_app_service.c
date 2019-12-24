/*******************************************************************************
 *
 * Module: ble_app_service
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/05/20 14:00          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     ble_app_service.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/05/20
  *******************************************************************************/
#ifndef BLE_APP_SERVICE_C
#define BLE_APP_SERVICE_C

#include "ble_app_service.h"

#define BLE_CHARACTERISTIC_DEF(_uuid, _init_len, _max_len, _is_var_len, _writeable, _notify)    \
    {                                                                                           \
        .uuid              = _uuid,                                                             \
        .init_len          = _init_len,                                                         \
        .max_len           = _max_len,                                                          \
        .is_var_len        = _is_var_len,                                                       \
        .char_props.read   = 1,                                                                 \
        .char_props.write  = _writeable,                                                        \
        .char_props.notify = _notify,                                                           \
        .read_access       = SEC_OPEN,                                                          \
        .write_access      = _writeable ? SEC_OPEN : SEC_NO_ACCESS,                             \
        .cccd_write_access = SEC_OPEN                                                           \
    }

  /*! characteristic init list */
static const ble_add_char_params_t char_init_list[BLE_APP_SVC_CHAR_INDEX_MAX] = {
        BLE_CHARACTERISTIC_DEF(BLE_APP_SVC_CHAR_UUID_CONTROL, 2, 20, true, true, false),
        BLE_CHARACTERISTIC_DEF(BLE_APP_SVC_CHAR_UUID_MAC, BLE_GAP_ADDR_LEN, BLE_GAP_ADDR_LEN, false, false, false),
};

static const ble_service_write_handler_t char_callback_list[BLE_APP_SVC_CHAR_INDEX_MAX] = {
        ble_app_svc_control_handler, NULL
};

/**@brief glasses Service structure. This structure contains various status information for the service. */
typedef struct
{
    uint16_t                    service_handle;      /**< Handle of LED Button Service (as provided by the BLE stack). */
    uint8_t                     uuid_type;           /**< UUID type for the Service. */

    ble_gatts_char_handles_t    char_handles[BLE_APP_SVC_CHAR_INDEX_MAX];
    uint8_t* p_char_init_value[BLE_APP_SVC_CHAR_INDEX_MAX];
} ble_glasses_service_t;


ble_glasses_service_t m_3Dscanner_service;

NRF_SDH_BLE_OBSERVER(Scanner_service_obs, BLE_APP_SVC_BLE_OBSERVER_PRIO, ble_app_svc_event_callback, NULL);

//extern void ble_module_SetDeviceName(uint8_t const* name, uint8_t len);

/*!*****************************************************************************
\brief      initialize
\details
\param[in]
\return     uint32_t : err_code
\author        FuxFox 2019/05/20 16:47
******************************************************************************/
uint32_t ble_app_svc_init(void)
{
    uint32_t              err_code;
    ble_uuid_t            ble_uuid;
    ble_uuid128_t base_uuid = { BLE_APP_SVC_UUID_BASE };
    uint8_t data = 0;
    ble_gap_addr_t        mac;

    // Add service.
    err_code = sd_ble_uuid_vs_add(&base_uuid, &m_3Dscanner_service.uuid_type);
    APP_ERROR_CHECK(err_code);

    ble_uuid.type = m_3Dscanner_service.uuid_type;
    ble_uuid.uuid = BLE_APP_SVC_UUID_SERVICE;

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &m_3Dscanner_service.service_handle);
    APP_ERROR_CHECK(err_code);

    ble_app_svc_get_mac(&mac);

    m_3Dscanner_service.p_char_init_value[BLE_APP_SVC_CHAR_INDEX_CONTROL] = &data;
    m_3Dscanner_service.p_char_init_value[BLE_APP_SVC_CHAR_INDEX_MAC] = mac.addr;

    ble_app_svc_add_characteristic();

    return NRF_SUCCESS;
}

/*!*****************************************************************************
\brief      get MAC address
\details
\param[out]    ble_gap_addr_t * mac ：mac
\return     void
******************************************************************************/
static void ble_app_svc_get_mac(ble_gap_addr_t* mac)
{
    uint8_t tmp;
    uint32_t err_code = sd_ble_gap_addr_get(mac);
    APP_ERROR_CHECK(err_code);
    //LSB转MSB
    for (uint8_t i = 0; i < BLE_GAP_ADDR_LEN / 2; i++)
    {
        tmp = mac->addr[i];
        mac->addr[i] = mac->addr[BLE_GAP_ADDR_LEN - 1 - i];
        mac->addr[BLE_GAP_ADDR_LEN - 1 - i] = tmp;
    }
}

/*!*****************************************************************************
\brief      add characteristic to service
\details
\param[in]    ble_service_char_struct *characteristic ： 
\return     uint32_t
******************************************************************************/
static uint32_t ble_app_svc_add_characteristic(void)
{
    uint8_t i;
    uint32_t err_code;
    ble_add_char_params_t char_init;

    for (i = 0; i < BLE_APP_SVC_CHAR_INDEX_MAX; i++)
    {
        char_init = char_init_list[i];
        char_init.uuid_type = m_3Dscanner_service.uuid_type;
        char_init.p_init_value = m_3Dscanner_service.p_char_init_value[i];
        err_code = characteristic_add(m_3Dscanner_service.service_handle, &char_init, &m_3Dscanner_service.char_handles[i]);
        APP_ERROR_CHECK(err_code);
    }

    return NRF_SUCCESS;
}


/*!*****************************************************************************
\brief      BLE event callback
\details
\param[in]    p_ble_evt : BLE event \see ble_evt_t
\param[in]    p_context : 
\return     void
******************************************************************************/
static void ble_app_svc_event_callback(ble_evt_t const* p_ble_evt, void* p_context)
{
    ble_gatts_evt_write_t const* p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
    uint8_t i;

    //    NRF_LOG_DEBUG("GATTS write event detected");
    switch (p_ble_evt->header.evt_id)
    {
    case BLE_GATTS_EVT_WRITE:
        if (p_evt_write->uuid.uuid == BLE_UUID_GAP_CHARACTERISTIC_DEVICE_NAME)
        {
//           ble_module_SetDeviceName(p_evt_write->data, p_evt_write->len);
        }
        else
        {
            for (i = 0; i < BLE_APP_SVC_CHAR_INDEX_MAX; i++)
            {
                if (p_evt_write->uuid.uuid == char_init_list[i].uuid)
                {
                    char_callback_list[i](p_evt_write->data);
                }
            }
        }
        break;
    default:
        // No implementation needed.
        break;
    }
}




/*!*****************************************************************************
\brief      control command handler
\details
\param[in]    uint8_t *command
\return     void
\author        FuxFox 2019/05/28 09:32
******************************************************************************/
static void ble_app_svc_control_handler(uint8_t const* command)
{
    switch (command[0])
    {
    case BLE_CMD_SHUTDOWN:
        if (command[1])
        {
            drv_power_poweroff();
        }
        break;
#if defined(MODULE_SUPPORT) || defined(MODULE_LASER)
    case BLE_CMD_LASER_ONOFF:
        nrf_gpio_pin_write(LASER_EN, command[1]);
        break;
    case BLE_CMD_FLASH_LED_ONOFF:
        module_flash_led_ctrl(command[1]);
        break;
#endif
#if defined(MODULE_SUPPORT) || defined(MODULE_TURNTABLE)
    case BLE_CMD_ATMOSPHERE_LAMP_ONOFF:
        nrf_gpio_pin_write(LED_EN, command[1]);
        break;
#endif
#ifdef MODULE_TURNTABLE
    case BLE_CMD_MOTOR_SET_STEP:
        break;
    case BLE_CMD_MOTOR_CTRL:
        break;
#endif
    default:
        break;
    }
}



/*!*****************************************************************************
\brief      取模块信息接口
\details
\param[in]    BLE_APP_SERVICE_GET_e info
\return     uint32_t
\author        FuxFox 2019/05/22 10:43
******************************************************************************/
// uint32_t Ble_Service_Casher_GetInfo(BLE_APP_SERVICE_GET_e info)
// {
//         switch (info)
//         {
//         case BLE_APP_SERVICE_GET_UUIDTYPE:
//                 return m_glasses_service.uuid_type;
//         default:
//                 break;
//         }
//         
//         return 0;
// }



/*!*****************************************************************************
\brief      change characteristic value by application
\details
\param[in]    BLE_APP_SERVICE_SET_e opt
\param[in]    uint8_t data
\return     void
\author        FuxFox 2019/05/27 10:28
******************************************************************************/
void ble_app_svc_set_char_value(ble_app_svc_char_index_t char_index, uint8_t* data, uint8_t len)
{
    ble_gatts_value_t value = {
            .len = len,
            .p_value = data,
    };

    sd_ble_gatts_value_set(NULL, m_3Dscanner_service.char_handles[char_index].value_handle, &value);
}


#endif // BLE_APP_SVC_C
