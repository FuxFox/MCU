/*******************************************************************************
 * Module: ble_adv
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/07 10:39          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     ble_adv.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/11/07
 *******************************************************************************/
#ifndef BLE_ADV_H
#define BLE_ADV_H

/*! \defgroup ble_adv_public Public
\ingroup ble_adv
\brief  BLE module for NRF52832
\details    BLE advertising relative code.
* @{ */

#include "app_globle.h"

#include "ble_bond.h"
//********************************* Module Config *******************************/
                                




//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/

void ble_adv_init(void);
void ble_adv_start(void);




void ble_adv_disconnect_disabled(void);
void ble_adv_config_get(ble_adv_modes_config_t* p_config);
//********************************* Private Interface ***************************/

static void ble_adv_event_handler(ble_adv_evt_t ble_adv_evt);



static void ble_adv_error_handler(uint32_t nrf_error);
/*! @}*/ //end of group ble_adv
#endif // BLE_adv_H
