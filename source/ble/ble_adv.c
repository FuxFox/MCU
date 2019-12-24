/*******************************************************************************
 * Module: ble_adv
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/07 10:39          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     ble_adv.c
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/11/07
 *******************************************************************************/
#ifndef BLE_ADV_C
#define BLE_ADV_C

#include "ble_adv.h"

BLE_ADVERTISING_DEF(m_advertising);                                                 /**< Advertising module instance. */

static ble_uuid_t m_adv_uuids[] = { {BLE_UUID_DEVICE_INFORMATION_SERVICE, BLE_UUID_TYPE_BLE}/*{GLASSES_UUID_SERVICE, ble_module_Service_Glasses_GetInfo(BLE_SERVICE_GLASSES_GET_UUIDTYPE)}*/ };

/*!*****************************************************************************
\brief      initialize
\details        Encodes the required advertising data and passes it to the stack.
                Also builds a structure to be passed to the stack when starting advertising.
\param[in]    void
\return     void
******************************************************************************/
void ble_adv_init(void)
{
        uint32_t               err_code;
        ble_advertising_init_t init;

        memset(&init, 0, sizeof(init));

        init.advdata.name_type = BLE_ADVDATA_FULL_NAME;
        init.advdata.include_appearance = true;
        init.advdata.flags = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
        init.advdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
        init.advdata.uuids_complete.p_uuids = m_adv_uuids;
//        init.advdata.p_tx_power_level = &tx_power_level;

        ble_adv_config_get(&init.config);

        init.evt_handler = ble_adv_event_handler;
        init.error_handler = ble_adv_error_handler;

        err_code = ble_advertising_init(&m_advertising, &init);
        APP_ERROR_CHECK(err_code);

        ble_advertising_conn_cfg_tag_set(&m_advertising, APP_BLE_CONN_CFG_TAG);
}


/*!*****************************************************************************
\brief      get adv configuration
\details
\param[in]    ble_adv_modes_config_t * p_config
\return     void
******************************************************************************/
void ble_adv_config_get(ble_adv_modes_config_t* p_config)
{
        memset(p_config, 0, sizeof(ble_adv_modes_config_t));

#if SEC_PARAM_BOND
        p_config->ble_adv_whitelist_enabled = true;
        p_config->ble_adv_directed_high_duty_enabled = true;
        p_config->ble_adv_directed_enabled = false;
        p_config->ble_adv_directed_interval = 0;
        p_config->ble_adv_directed_timeout = 0;
#endif
#if APP_ADV_FAST_ENABLE
        p_config->ble_adv_fast_enabled = true;
        p_config->ble_adv_fast_interval = APP_ADV_FAST_INTERVAL;
        p_config->ble_adv_fast_timeout = APP_ADV_FAST_DURATION;
#endif
#if APP_ADV_SLOW_ENABLE
        p_config->ble_adv_slow_enabled = true;
        p_config->ble_adv_slow_interval = APP_ADV_SLOW_INTERVAL;
        p_config->ble_adv_slow_timeout = APP_ADV_SLOW_DURATION;
#endif
}

/**@brief Function for handling advertising events.
 *
 * @details This function will be called for advertising events which are passed to the application.
 *
 * @param[in] ble_adv_evt  Advertising event.
 */
static void ble_adv_event_handler(ble_adv_evt_t ble_adv_evt)
{
        ret_code_t err_code;

        switch (ble_adv_evt)
        {
        case BLE_ADV_EVT_DIRECTED_HIGH_DUTY:
                NRF_LOG_INFO("High Duty Directed advertising.");
                break;
        case BLE_ADV_EVT_DIRECTED:
                NRF_LOG_INFO("Directed advertising.");
                break;
        case BLE_ADV_EVT_FAST:
                NRF_LOG_INFO("Fast advertising.");
                break;
        case BLE_ADV_EVT_SLOW:
                NRF_LOG_INFO("Slow advertising.");
                break;
        case BLE_ADV_EVT_FAST_WHITELIST:
                NRF_LOG_INFO("Fast advertising with whitelist.");
                break;
        case BLE_ADV_EVT_SLOW_WHITELIST:
                NRF_LOG_INFO("Slow advertising with whitelist.");
                break;
        case BLE_ADV_EVT_IDLE:
//                sleep_mode_enter();
                break;
#if SEC_PARAM_BOND
        case BLE_ADV_EVT_WHITELIST_REQUEST:
        {
                ble_gap_addr_t whitelist_addrs[BLE_GAP_WHITELIST_ADDR_MAX_COUNT];
                ble_gap_irk_t  whitelist_irks[BLE_GAP_WHITELIST_ADDR_MAX_COUNT];
                uint32_t       addr_cnt = BLE_GAP_WHITELIST_ADDR_MAX_COUNT;
                uint32_t       irk_cnt = BLE_GAP_WHITELIST_ADDR_MAX_COUNT;

                err_code = pm_whitelist_get(whitelist_addrs, &addr_cnt,
                        whitelist_irks, &irk_cnt);
                APP_ERROR_CHECK(err_code);
                NRF_LOG_DEBUG("pm_whitelist_get returns %d addr in whitelist and %d irk whitelist",
                        addr_cnt, irk_cnt);

                // Set the correct identities list (no excluding peers with no Central Address Resolution).
                ble_bond_identities_set(PM_PEER_ID_LIST_SKIP_NO_IRK);

                // Apply the whitelist.
                err_code = ble_advertising_whitelist_reply(&m_advertising, whitelist_addrs,    addr_cnt, whitelist_irks, irk_cnt);
                APP_ERROR_CHECK(err_code);
        } break; //BLE_ADV_EVT_WHITELIST_REQUEST

        case BLE_ADV_EVT_PEER_ADDR_REQUEST:
        {
                pm_peer_data_bonding_t peer_bonding_data;
                pm_peer_id_t peer_id = ble_bond_get_peer_id();

                // Only Give peer address if we have a handle to the bonded peer.
                if (peer_id != PM_PEER_ID_INVALID)
                {
                        err_code = pm_peer_data_bonding_load(peer_id, &peer_bonding_data);
                        if (err_code != NRF_ERROR_NOT_FOUND)
                        {
                                APP_ERROR_CHECK(err_code);

                                // Manipulate identities to exclude peers with no Central Address Resolution.
                                ble_bond_identities_set(PM_PEER_ID_LIST_SKIP_ALL);

                                ble_gap_addr_t* p_peer_addr = &(peer_bonding_data.peer_ble_id.id_addr_info);
                                err_code = ble_advertising_peer_addr_reply(&m_advertising, p_peer_addr);
                                APP_ERROR_CHECK(err_code);
                        }
                }
        } break; //BLE_ADV_EVT_PEER_ADDR_REQUEST
#endif

        default:
                break;
        }
}

/**@brief Function for handling advertising errors.
 *
 * @param[in] nrf_error  Error code containing information about what went wrong.
 */
static void ble_adv_error_handler(uint32_t nrf_error)
{
        APP_ERROR_HANDLER(nrf_error);
}
/**@brief Function for starting advertising.
 */
void ble_adv_start(void)
{
        uint32_t err_code = ble_advertising_start(&m_advertising, BLE_ADV_MODE_FAST);
        APP_ERROR_CHECK(err_code);

        NRF_LOG_DEBUG("advertising is started");
}

/*!*****************************************************************************
\brief      Prevent device from advertising on disconnect.
\details
\param[in]    void
\return     void
******************************************************************************/
void ble_adv_disconnect_disabled(void)
{
        ble_adv_modes_config_t config;

        ble_adv_config_get(&config);
        config.ble_adv_on_disconnect_disabled = true;
        ble_advertising_modes_config_set(&m_advertising, &config);
}
// advertising without white list
// if (m_conn_handle == BLE_CONN_HANDLE_INVALID)
// {
//         err_code = ble_advertising_restart_without_whitelist(&m_advertising);
//         if (err_code != NRF_ERROR_INVALID_STATE)
//         {
//                 APP_ERROR_CHECK(err_code);
//         }
// }

#endif // BLE_ADVERTISING_C
