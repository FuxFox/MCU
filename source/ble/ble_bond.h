/*******************************************************************************
 * Module: ble_bond
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/07 10:13          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     ble_bond.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/11/07
 *******************************************************************************/
#ifndef BLE_BOND_H
#define BLE_BOND_H

/*! \defgroup ble_bond_public Public
\ingroup ble_bond
\brief      BLE module for NRF52832
\details    BLE bond relative code
* @{ */

#include "app_globle.h"

#include "ble_adv.h"
//********************************* Module Config *******************************/
                                




//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/

void ble_bond_init(void);

void ble_bond_whitelist_set(pm_peer_id_list_skip_t skip);
void ble_bond_identities_set(pm_peer_id_list_skip_t skip);
void ble_bond_delete(void);
pm_peer_id_t ble_bond_get_peer_id(void);

//********************************* Private Interface ***************************/

static void ble_bond_pm_evt_handler(pm_evt_t const* p_evt);




/*! @}*/ //end of group ble_bond
#endif // BLE_BOND_H
