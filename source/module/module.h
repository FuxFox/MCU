/*******************************************************************************
 * Module: module
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/07/26 15:21          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     module.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/07/26
 *******************************************************************************/
#ifndef MODULE_H
#define MODULE_H

/*! \defgroup module_public Public
\ingroup module
\brief      module layer
\details 
* @{ */

#include "app_globle.h"

#include "driver.h"
#include "md_battery.h"
//********************************* Module Config *******************************/
                                




//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/

void module_init(void);



//********************************* Private Interface ***************************/

static bool md_shutdown_handler(nrf_pwr_mgmt_evt_t event);
//static void leds_init(void);
static void module_battery_change_callback(uint8_t battery_percent);

/*! @}*/ //end of group module
#endif // MODULE_H
