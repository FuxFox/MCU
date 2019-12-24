/*******************************************************************************
 * Module: ble_module
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/07/29 16:53          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     ble_module.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/07/29
 *******************************************************************************/
#ifndef BLE_MODULE_H
#define BLE_MODULE_H

/*! \defgroup ble_public Public
\ingroup ble
\brief      BLE module for NRF52832
\details 
* @{ */

#include "app_globle.h"
#include "ble_service_casher.h"
#include "ble_bas.h"
#include "ble_dis.h"
#include "ble_adv.h"
#include "ble_bond.h"
#include "ui_lcd.h"
//********************************* Module Config *******************************/
                                




//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/

void ble_module_init(void);

void ble_module_SetDeviceName(uint8_t const* name, uint8_t len);

void ble_module_keyboard_notify(uint8_t keycode);
bool ble_module_is_connect(void);
void ble_module_battery_level_update(uint8_t battery_level);

//********************************* Private Interface ***************************/

static void ble_module_buttonless_dfu_sdh_state_observer(nrf_sdh_state_evt_t state, void* p_context);
static void ble_module_disconnect(uint16_t conn_handle, void* p_context);
static void ble_module_dfu_evt_handler(ble_dfu_buttonless_evt_type_t event);
static void ble_module_gap_params_init(void);
static void ble_module_gatt_init(void);
static void ble_module_nrf_qwr_error_handler(uint32_t nrf_error);
static void ble_module_services_init(void);
static void ble_module_on_conn_params_evt(ble_conn_params_evt_t* p_evt);
static void ble_module_conn_params_error_handler(uint32_t nrf_error);
static void ble_module_connection_params_init(void);
static void ble_module_evt_handler(ble_evt_t const* p_ble_evt, void* p_context);
static void ble_module_stack_init(void);
/*! @}*/ //end of group ble
#endif // BLE_H
