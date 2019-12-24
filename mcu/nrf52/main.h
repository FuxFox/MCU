/*******************************************************************************
 * Module: main
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/05/21 11:40          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     main.h
 * \brief    main.h for nrf52832
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/05/21
 *******************************************************************************/
#ifndef MAIN_H
#define MAIN_H

/*! \defgroup main_public Public
\ingroup main
\brief 
\details 
* @{ */


#include "app_globle.h"
#include "driver.h"
#include "module.h"
#include "ui.h"
#include "ble_module.h"
#include "test/test.h"

void assert_nrf_callback(uint16_t line_num, const uint8_t* p_file_name);

static void main_nrf_preinit(void);
static void timers_init(void);
static void log_init(void);
static void power_management_init(void);
static void idle_state_handle(void);

/*! @}*/ //end of group main
#endif // MAIN_H
