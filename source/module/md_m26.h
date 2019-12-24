/*******************************************************************************
 * Module: md_m26
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/09/05 14:05          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     md_m26.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/09/05
 *************************************************************************/
#ifndef MD_M26_H
#define MD_M26_H

/*! \defgroup md_m26_public Public
\ingroup md_m26
\brief      QUECTEL M26 IOT module 
\note       this implemented base on NRF52832, you can modify to use for other MCU.
\details 
* @{ */

#include "app_config.h"

#include "drv_m26.h"
#include "cJSON.h"
#include "ble_module.h"
//********************************* Module Config *******************************/
                                
#define MD_M26_RX_WAIT_TIME_MAX        300                /*!< Max Rx waiting time, in ms */
#define MD_M26_RETRY_TIMES_MAX         5                  /*!< Max retry times */


//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/

bool md_m26_init(error_handler handler);

bool md_m26_reinit(void);
bool md_m26_http_set_url(const char* url);
size_t md_m26_http_get(char* url, char* response, size_t size);
size_t md_m26_http_post(char* url, char* post, char* response, size_t size);
bool md_m26_get_time(char* time);

bool md_m26_get_IMEI(char* res);
bool md_m26_send_check_ack_ms(const char* str, const char* ack, uint32_t wait_ms);
void md_m26_send_and_get_ack(const char* str, char* ack, uint32_t len, uint32_t wait_ms);
#define md_m26_send_check_ack(str, ack)        md_m26_send_check_ack_ms(str, ack, MD_M26_RX_WAIT_TIME_MAX)
#define md_m26_send_check_ok(str)            md_m26_send_check_ack_ms(str, "OK", MD_M26_RX_WAIT_TIME_MAX)
//********************************* Private Interface ***************************/

static void md_m26_configure(void);




static bool md_m26_check_ready(void);
/*! @}*/ //end of group md_m26
#endif // MD_M26_H
