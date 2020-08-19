/*!*****************************************************************************
* @file     md_m26.h
* @brief    
* @author   FuxFox
* @version  V1.0
* @date     2019/09/05
*************************************************************************/
#ifndef MD_M26_H
#define MD_M26_H

/*!
* @defgroup md_m26
* @ingroup module
* @brief      QUECTEL M26 IOT module
* @note       this implemented base on NRF52832, you can modify to use for other MCU.
* @{ */

#include "app_config.h"

#include "drv_m26.h"
#include "cJSON.h"
#include "ble_module.h"
/*================================= Module Config ============================*/

#define MD_M26_RX_WAIT_TIME_MAX 300   /**< Max Rx waiting time, in ms */
#define MD_M26_RETRY_TIMES_MAX  5     /**< Max retry times */


/*================================= Data Type ================================*/





/*================================= Public Interface =========================*/

/*!*****************************************************************************
* @brief      initialize
* @param[in]    void
* @return     bool    TRUE if success
*******************************************************************************/
bool md_m26_init(error_handler handler);

/*!*****************************************************************************
* @brief      re-initialize
* @param[in]    void
* @return     bool TRUE if success
*******************************************************************************/
bool md_m26_reinit(void);

/*!*****************************************************************************
* @brief      set HTTP url
* @param[in]    void
* @return     void
*******************************************************************************/
bool md_m26_http_set_url(const char* url);

/*!*****************************************************************************
* @brief      HTTP get request
* @param[out]    char* response   buffer to receive response from server
* @param[in]    size_t resp_size       size of receive buffer
* @return     size_t              actually size of received data
* @note
        The response return from M26 is start with "CONNECT"
*******************************************************************************/
size_t md_m26_http_get(char* url, char* response, size_t size);

/*!*****************************************************************************
* @brief      HTTP post and get response
* @param[in]    char * post       POST data
* @param[in]    char * response   buffer to receive response from server
* @param[in]    size_t size       size of response received buffer
* @return     size_t            actually size of received data
* @note
        The response return from M26 is start with "CONNECT"
*******************************************************************************/
size_t md_m26_http_post(char* url, char* post, char* response, size_t size);

/*!*****************************************************************************
* @brief      get local time from M26. Format£ºyy/mm/dd, hh:mm:ss+zz
* @param[in]    char * time       receive buffer, size > 22
* @return     bool TRUE if success
*******************************************************************************/
bool md_m26_get_time(char* time);

/*!*****************************************************************************
* @brief      GET M26 IMEI
* @details        15 digit number
* @param[in]    uint8_t * res         a buffer to receive IMEI, size >= 16
* @return     bool   TRUE if success
*******************************************************************************/
bool md_m26_get_IMEI(char* res);

/*!*****************************************************************************
* @brief      send command and check ACK
* @param[in]    const char * str      AT command string
* @param[in]    const char * ack      expectant ACK string
* @param[in]    uint32_t wait_ms      max waiting time, in ms
* @return     bool TRUE if success
*******************************************************************************/
bool md_m26_send_check_ack_ms(const char* str, const char* ack, uint32_t wait_ms);

/*!*****************************************************************************
* @brief      send command and get ACK
* @param[in]    const char * str      AT command string
* @param[in]    const char * ack      Buffer to receive ACK
* @param[in]    uint32_t wait_ms      max waiting time, in ms
* @return     void
*******************************************************************************/
void md_m26_send_and_get_ack(const char* str, char* ack, uint32_t len, uint32_t wait_ms);

#define md_m26_send_check_ack(str, ack)        md_m26_send_check_ack_ms(str, ack, MD_M26_RX_WAIT_TIME_MAX)
#define md_m26_send_check_ok(str)            md_m26_send_check_ack_ms(str, "OK", MD_M26_RX_WAIT_TIME_MAX)

/** @}*/ //end of group md_m26
#endif // MD_M26_H
