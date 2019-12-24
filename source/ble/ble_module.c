/*******************************************************************************
 * Module: ble_module
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/07/29 16:53          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     ble.c
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/07/29
 *******************************************************************************/
#ifndef BLE_MODULE_C
#define BLE_MODULE_C

#include "ble_module.h"

NRF_BLE_GATT_DEF(m_gatt);                                                       /**< GATT module instance. */
NRF_BLE_QWR_DEF(m_qwr);                                                         /**< Context for the Queued Write module.*/
BLE_BAS_DEF(m_battery_service);

static uint16_t m_conn_handle = BLE_CONN_HANDLE_INVALID;                        /**< Handle of the current connection. */


//static md_store_divice_name_struct m_device_name;


/*!*****************************************************************************
\brief      ble module initialize
\details
\param[in]    void
\return     void
\author        FuxFox 2019/05/23 09:18
******************************************************************************/
void ble_module_init(void)
{
        ble_module_stack_init();
#if SEC_PARAM_BOND
        ble_bond_init();
#endif
        ble_module_gap_params_init();
        ble_module_gatt_init();
        ble_module_services_init();
        ble_adv_init();
        ble_module_connection_params_init();
        ble_adv_start();

        ble_module_battery_level_update(md_battery_get_percent());
}



static void ble_module_buttonless_dfu_sdh_state_observer(nrf_sdh_state_evt_t state, void * p_context)
{
    if (state == NRF_SDH_EVT_STATE_DISABLED)
    {
        // Softdevice was disabled before going into reset. Inform bootloader to skip CRC on next boot.
        nrf_power_gpregret2_set(BOOTLOADER_DFU_SKIP_CRC);

        //Go to system off.
        nrf_pwr_mgmt_shutdown(NRF_PWR_MGMT_SHUTDOWN_GOTO_SYSOFF);
    }
}

/* nrf_sdh state observer. */
NRF_SDH_STATE_OBSERVER(m_buttonless_dfu_state_obs, 0) =
{
    .handler = ble_module_buttonless_dfu_sdh_state_observer,
};




static void ble_module_disconnect(uint16_t conn_handle, void * p_context)
{
    UNUSED_PARAMETER(p_context);

    ret_code_t err_code = sd_ble_gap_disconnect(conn_handle, BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_WARNING("Failed to disconnect connection. Connection handle: %d Error: %d", conn_handle, err_code);
    }
    else
    {
        NRF_LOG_DEBUG("Disconnected connection handle %d", conn_handle);
    }
}



// YOUR_JOB: Update this code if you want to do anything given a DFU event (optional).
/**@brief Function for handling dfu events from the Buttonless Secure DFU service
 *
 * @param[in]   event   Event from the Buttonless Secure DFU service.
 */
static void ble_module_dfu_evt_handler(ble_dfu_buttonless_evt_type_t event)
{
    switch (event)
    {
        case BLE_DFU_EVT_BOOTLOADER_ENTER_PREPARE:
        {
            NRF_LOG_INFO("Device is preparing to enter bootloader mode.");

            // Prevent device from advertising on disconnect.
            ble_adv_disconnect_disabled();
            // Disconnect all other bonded devices that currently are connected.
            // This is required to receive a service changed indication
            // on bootup after a successful (or aborted) Device Firmware Update.
            uint32_t conn_count = ble_conn_state_for_each_connected(ble_module_disconnect, NULL);
            NRF_LOG_INFO("Disconnected %d links.", conn_count);
            break;
        }

        case BLE_DFU_EVT_BOOTLOADER_ENTER:
            // YOUR_JOB: Write app-specific unwritten data to FLASH, control finalization of this
            //           by delaying reset by reporting false in app_shutdown_handler
            NRF_LOG_INFO("Device will enter bootloader mode.");
            break;

        case BLE_DFU_EVT_BOOTLOADER_ENTER_FAILED:
            NRF_LOG_ERROR("Request to enter bootloader mode failed asynchroneously.");
            // YOUR_JOB: Take corrective measures to resolve the issue
            //           like calling APP_ERROR_CHECK to reset the device.
            APP_ERROR_CHECK(false);
            break;

        case BLE_DFU_EVT_RESPONSE_SEND_ERROR:
            NRF_LOG_ERROR("Request to send a response to client failed.");
            // YOUR_JOB: Take corrective measures to resolve the issue
            //           like calling APP_ERROR_CHECK to reset the device.
            APP_ERROR_CHECK(false);
            break;

        default:
            NRF_LOG_ERROR("Unknown event from ble_dfu_buttonless.");
            break;
    }
}

static void ble_module_gap_params_init(void)
{
        ret_code_t              err_code;
        ble_gap_conn_params_t   gap_conn_params;
        ble_gap_conn_sec_mode_t sec_mode;

        BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

//        md_store_read_config(MD_STORE_TYPE_DEVICE_NAME, (uint8_t*)& m_device_name);

//         if (m_device_name.valid_flag != CFG_STORE_DATA_VALID_FLAG)
//         {
                err_code = sd_ble_gap_device_name_set(&sec_mode, (uint8_t const *)DEVICE_NAME, strlen(DEVICE_NAME));
//                NRF_LOG_DEBUG("Use Default Device Name")
//         }
//         else
//         {
//                 err_code = sd_ble_gap_device_name_set(&sec_mode, m_device_name.name, m_device_name.len);
//                 NRF_LOG_DEBUG("Use Customer Device Name")
//         }

        APP_ERROR_CHECK(err_code);

        memset(&gap_conn_params, 0, sizeof(gap_conn_params));

        gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
        gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
        gap_conn_params.slave_latency = SLAVE_LATENCY;
        gap_conn_params.conn_sup_timeout = CONN_SUP_TIMEOUT;

        err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
        APP_ERROR_CHECK(err_code);
}


/**@brief Function for initializing the GATT module.
 */
static void ble_module_gatt_init(void)
{
        ret_code_t err_code = nrf_ble_gatt_init(&m_gatt, NULL);
        APP_ERROR_CHECK(err_code);
}


/**@brief Function for handling Queued Write Module errors.
 *
 * @details A pointer to this function will be passed to each service which may need to inform the
 *          application about an error.
 *
 * @param[in]   nrf_error   Error code containing information about what went wrong.
 */
static void ble_module_nrf_qwr_error_handler(uint32_t nrf_error)
{
        APP_ERROR_HANDLER(nrf_error);
}


/**@brief Function for initializing services that will be used by the application.
 */
static void ble_module_services_init(void)
{
        ret_code_t         err_code;
        nrf_ble_qwr_init_t qwr_init = { 0 };
        ble_dfu_buttonless_init_t dfus_init = { 0 };
        ble_bas_init_t bas_init = {
                .bl_rd_sec = SEC_OPEN,
                .bl_cccd_wr_sec = SEC_OPEN,
                .bl_report_rd_sec = SEC_OPEN,
//                .evt_handler = NULL,
                .support_notification = true,
//                .p_report_ref = NULL,
                .initial_batt_level = 100
        };
        ble_dis_init_t     dis_init = {
                .dis_char_rd_sec = SEC_OPEN
        };

        // Initialize Queued Write Module.
        qwr_init.error_handler = ble_module_nrf_qwr_error_handler;
        err_code = nrf_ble_qwr_init(&m_qwr, &qwr_init);
        APP_ERROR_CHECK(err_code);

        dfus_init.evt_handler = ble_module_dfu_evt_handler;
        err_code = ble_dfu_buttonless_init(&dfus_init);
        APP_ERROR_CHECK(err_code);

        err_code = ble_bas_init(&m_battery_service, &bas_init);
        APP_ERROR_CHECK(err_code);

        ble_srv_ascii_to_utf8(&dis_init.manufact_name_str, MANUFACTURER_NAME);
        ble_srv_ascii_to_utf8(&dis_init.model_num_str, FIRMWARE_VERSION);
        err_code = ble_dis_init(&dis_init);
        APP_ERROR_CHECK(err_code);

        err_code = Ble_Service_Casher_Init();
        APP_ERROR_CHECK(err_code);
}


/**@brief Function for handling the Connection Parameters Module.
 *
 * @details This function will be called for all events in the Connection Parameters Module that
 *          are passed to the application.
 *
 * @note All this function does is to disconnect. This could have been done by simply
 *       setting the disconnect_on_fail config parameter, but instead we use the event
 *       handler mechanism to demonstrate its use.
 *
 * @param[in] p_evt  Event received from the Connection Parameters Module.
 */
static void ble_module_on_conn_params_evt(ble_conn_params_evt_t* p_evt)
{
        ret_code_t err_code;

        if (p_evt->evt_type == BLE_CONN_PARAMS_EVT_FAILED)
        {
                err_code = sd_ble_gap_disconnect(m_conn_handle, BLE_HCI_CONN_INTERVAL_UNACCEPTABLE);
                APP_ERROR_CHECK(err_code);
        }
}


/**@brief Function for handling a Connection Parameters error.
 *
 * @param[in] nrf_error  Error code containing information about what went wrong.
 */
static void ble_module_conn_params_error_handler(uint32_t nrf_error)
{
        APP_ERROR_HANDLER(nrf_error);
}


/**@brief Function for initializing the Connection Parameters module.
 */
static void ble_module_connection_params_init(void)
{
        ret_code_t             err_code;
        ble_conn_params_init_t cp_init;

        memset(&cp_init, 0, sizeof(cp_init));

        cp_init.p_conn_params = NULL;
        cp_init.first_conn_params_update_delay = FIRST_CONN_PARAMS_UPDATE_DELAY;
        cp_init.next_conn_params_update_delay = NEXT_CONN_PARAMS_UPDATE_DELAY;
        cp_init.max_conn_params_update_count = MAX_CONN_PARAMS_UPDATE_COUNT;
        cp_init.start_on_notify_cccd_handle = BLE_GATT_HANDLE_INVALID;
        cp_init.disconnect_on_fail = false;
        cp_init.evt_handler = ble_module_on_conn_params_evt;
        cp_init.error_handler = ble_module_conn_params_error_handler;

        err_code = ble_conn_params_init(&cp_init);
        APP_ERROR_CHECK(err_code);
}




/**@brief Function for handling BLE events.
 *
 * @param[in]   p_ble_evt   Bluetooth stack event.
 * @param[in]   p_context   Unused.
 */
static void ble_module_evt_handler(ble_evt_t const* p_ble_evt, void* p_context)
{
        ret_code_t err_code;

        switch (p_ble_evt->header.evt_id)
        {
        case BLE_GAP_EVT_CONNECTED:
                NRF_LOG_INFO("Connected");
                m_conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
                err_code = nrf_ble_qwr_conn_handle_assign(&m_qwr, m_conn_handle);
                APP_ERROR_CHECK(err_code);

                ui_lcd_show_bluetooth_icon(true);
                break;

        case BLE_GAP_EVT_DISCONNECTED:
                NRF_LOG_INFO("Disconnected");
                m_conn_handle = BLE_CONN_HANDLE_INVALID;
                ui_lcd_show_bluetooth_icon(false);
//                ble_advertising_advdata_update(&m_advertising,)
                break;
        case BLE_GAP_EVT_SEC_PARAMS_REQUEST:
#if !SEC_PARAM_BOND
                NRF_LOG_ERROR("Pairing not supported");
                err_code = sd_ble_gap_sec_params_reply(m_conn_handle,
                        BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP,
                        NULL,
                        NULL);
//                 APP_ERROR_CHECK(err_code);
#endif
                break;

        case BLE_GAP_EVT_PHY_UPDATE_REQUEST:
        {
                NRF_LOG_DEBUG("PHY update request.");
                ble_gap_phys_t const phys =
                {
                    .rx_phys = BLE_GAP_PHY_AUTO,
                    .tx_phys = BLE_GAP_PHY_AUTO,
                };
                err_code = sd_ble_gap_phy_update(p_ble_evt->evt.gap_evt.conn_handle, &phys);
                APP_ERROR_CHECK(err_code);
        } break;

        case BLE_GATTS_EVT_SYS_ATTR_MISSING:
                // No system attributes have been stored.
                err_code = sd_ble_gatts_sys_attr_set(m_conn_handle, NULL, 0, 0);
                APP_ERROR_CHECK(err_code);
                break;

        case BLE_GATTC_EVT_TIMEOUT:
                // Disconnect on GATT Client timeout event.
                NRF_LOG_DEBUG("GATT Client Timeout.");
                err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gattc_evt.conn_handle,
                        BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
                APP_ERROR_CHECK(err_code);
                break;

        case BLE_GATTS_EVT_TIMEOUT:
                // Disconnect on GATT Server timeout event.
                NRF_LOG_DEBUG("GATT Server Timeout.");
                err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gatts_evt.conn_handle,
                        BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
                APP_ERROR_CHECK(err_code);
                break;

        default:
                // No implementation needed.
                break;
        }
}


/**@brief Function for initializing the BLE stack.
 *
 * @details Initializes the SoftDevice and the BLE event interrupt.
 */
static void ble_module_stack_init(void)
{
        ret_code_t err_code;

        err_code = nrf_sdh_enable_request();
        APP_ERROR_CHECK(err_code);

        // Configure the BLE stack using the default settings.
        // Fetch the start address of the application RAM.
        uint32_t ram_start = 0;
        err_code = nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ram_start);
        APP_ERROR_CHECK(err_code);

        // Enable BLE stack.
        err_code = nrf_sdh_ble_enable(&ram_start);
        APP_ERROR_CHECK(err_code);

        // Register a handler for BLE events.
        NRF_SDH_BLE_OBSERVER(m_ble_observer, APP_BLE_OBSERVER_PRIO, ble_module_evt_handler, NULL);
}



/*!*****************************************************************************
\brief      update battery level for bas service
\details
\param[in]    uint8_t battery_level ： battery percent
\return     void
******************************************************************************/
void ble_module_battery_level_update(uint8_t battery_level)
{
        ret_code_t err_code;

        err_code = ble_bas_battery_level_update(&m_battery_service, battery_level, BLE_CONN_HANDLE_ALL);
        if ((err_code != NRF_SUCCESS) &&
                (err_code != NRF_ERROR_INVALID_STATE) &&
                (err_code != NRF_ERROR_RESOURCES) &&
                (err_code != BLE_ERROR_GATTS_SYS_ATTR_MISSING)
                )
        {
                APP_ERROR_HANDLER(err_code);
        }
}
/*!*****************************************************************************
\brief      修改设备名称
\details
\param[in]    uint8_t const * command
\return     void
******************************************************************************/
// void ble_module_SetDeviceName(uint8_t const* name, uint8_t len)
// {        
//         memcpy(m_device_name.name, name, len);
//         m_device_name.len = len;
//         md_store_write_config(MD_STORE_TYPE_DEVICE_NAME, (uint8_t*)& m_device_name);
//     
//         NRF_LOG_INFO("Device Name Changed!");
// }

/*!*****************************************************************************
\brief      keyboard action notify
\details
\param[in]    uint8_t keycode
\return     void
******************************************************************************/
void ble_module_keyboard_notify(uint8_t keycode)
{
        Ble_Service_Casher_Keyboard_Notify(m_conn_handle, keycode);
}

/*!*****************************************************************************
\brief      is BLE connected ?
\details
\param[in]    void
\return     bool 连接成功返回TRUE
******************************************************************************/
bool ble_module_is_connect(void)
{
        return (m_conn_handle != BLE_CONN_HANDLE_INVALID);
}
#endif // BLE_C
