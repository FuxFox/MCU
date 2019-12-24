/*******************************************************************************
 * Module: ble_bond
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/07 10:14          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     ble_bond.c
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/11/07
 *******************************************************************************/
#ifndef BLE_BOND_C
#define BLE_BOND_C

#include "ble_bond.h"

static pm_peer_id_t      m_peer_id;                                 /**< Device reference handle to the current bonded central. */


/*!*****************************************************************************
\brief      initialize
\details
\param[in]    void
\return     void
******************************************************************************/
void ble_bond_init(void)
{
        ble_gap_sec_params_t sec_param;
        ret_code_t           err_code;

        err_code = pm_init();
        APP_ERROR_CHECK(err_code);

        memset(&sec_param, 0, sizeof(ble_gap_sec_params_t));

        // Security parameters to be used for all security procedures.
        sec_param.bond = SEC_PARAM_BOND;
        sec_param.mitm = SEC_PARAM_MITM;
        sec_param.lesc = SEC_PARAM_LESC;
        sec_param.keypress = SEC_PARAM_KEYPRESS;
        sec_param.io_caps = SEC_PARAM_IO_CAPABILITIES;
        sec_param.oob = SEC_PARAM_OOB;
        sec_param.min_key_size = SEC_PARAM_MIN_KEY_SIZE;
        sec_param.max_key_size = SEC_PARAM_MAX_KEY_SIZE;
#if SEC_PARAM_BOND
        sec_param.kdist_own.enc = 1;
        sec_param.kdist_own.id = 1;
        sec_param.kdist_peer.enc = 1;
        sec_param.kdist_peer.id = 1;
#endif

        err_code = pm_sec_params_set(&sec_param);
        APP_ERROR_CHECK(err_code);

        err_code = pm_register(ble_bond_pm_evt_handler);
        APP_ERROR_CHECK(err_code);
}


/**@brief Function for handling Peer Manager events.
 *
 * @param[in] p_evt  Peer Manager event.
 */
static void ble_bond_pm_evt_handler(pm_evt_t const* p_evt)
{
        pm_handler_on_pm_evt(p_evt);
        pm_handler_flash_clean(p_evt);

#if SEC_PARAM_BOND
        switch (p_evt->evt_id)
        {
        case PM_EVT_PEERS_DELETE_SUCCEEDED:
                ble_adv_start();
                break;

        case PM_EVT_PEER_DATA_UPDATE_SUCCEEDED:
                if (p_evt->params.peer_data_update_succeeded.flash_changed
                        && (p_evt->params.peer_data_update_succeeded.data_id == PM_PEER_DATA_ID_BONDING))
                {
                        NRF_LOG_INFO("New Bond, add the peer to the whitelist if possible");
                        // Note: You should check on what kind of white list policy your application should use.

                        ble_bond_whitelist_set(PM_PEER_ID_LIST_SKIP_NO_ID_ADDR);
                }
                break;

        default:
                break;
        }
#endif
}

#if SEC_PARAM_BOND
/**@brief Function for setting filtered whitelist.
 *
 * @param[in] skip  Filter passed to @ref pm_peer_id_list.
 */
void ble_bond_whitelist_set(pm_peer_id_list_skip_t skip)
{
        pm_peer_id_t peer_ids[BLE_GAP_WHITELIST_ADDR_MAX_COUNT];
        uint32_t     peer_id_count = BLE_GAP_WHITELIST_ADDR_MAX_COUNT;

        ret_code_t err_code = pm_peer_id_list(peer_ids, &peer_id_count, PM_PEER_ID_INVALID, skip);
        APP_ERROR_CHECK(err_code);

        NRF_LOG_INFO("\tm_whitelist_peer_cnt %d, MAX_PEERS_WLIST %d",
                peer_id_count + 1,
                BLE_GAP_WHITELIST_ADDR_MAX_COUNT);

        err_code = pm_whitelist_set(peer_ids, peer_id_count);
        APP_ERROR_CHECK(err_code);
}


/**@brief Function for setting filtered device identities.
 *
 * @param[in] skip  Filter passed to @ref pm_peer_id_list.
 */
void ble_bond_identities_set(pm_peer_id_list_skip_t skip)
{
        pm_peer_id_t peer_ids[BLE_GAP_DEVICE_IDENTITIES_MAX_COUNT];
        uint32_t     peer_id_count = BLE_GAP_DEVICE_IDENTITIES_MAX_COUNT;

        ret_code_t err_code = pm_peer_id_list(peer_ids, &peer_id_count, PM_PEER_ID_INVALID, skip);
        APP_ERROR_CHECK(err_code);

        err_code = pm_device_identities_list_set(peer_ids, peer_id_count);
        APP_ERROR_CHECK(err_code);
}


/**@brief Clear bond information from persistent storage.
 */
void ble_bond_delete(void)
{
        ret_code_t err_code;

        NRF_LOG_INFO("Erase bonds!");

        err_code = pm_peers_delete();
        APP_ERROR_CHECK(err_code);
}
#endif

/*!*****************************************************************************
\brief      get peer ID
\details
\param[in]    void
\return     pm_peer_id_t
******************************************************************************/
pm_peer_id_t ble_bond_get_peer_id(void)
{
        return m_peer_id;
}
#endif // BLE_BOND_C
