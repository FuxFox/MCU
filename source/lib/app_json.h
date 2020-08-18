/*******************************************************************************
* LICENSE : Apache 2.0
*           
* History:
*    <author>         <time>             <version>             <desc>
*      FuxFox	      2020/07/08 16:05          V1.0             build this file
*
*******************************************************************************/
#ifndef APP_JSON_H
#define APP_JSON_H

/** 
* @defgroup app_json
* @ingroup lib
* @brief
* @details 
* @{ */

#include "app_config.h"


/*================================= Module Config ============================*/





/*================================= Data Type ================================*/





/*================================= Public Interface =========================*/

void app_json_get_value_by_key(void);

/*!*****************************************************************************
* @brief  	find json key-value by key from src,then return the pointer of value,
*            return NULL if not found.
* @param[in]	uint8_t * src
* @param[in]	uint8_t * key
* @return     uint8_t*
*******************************************************************************/
uint8_t* app_json_find_value_by_key(uint8_t* src, uint8_t* key);

/*!*****************************************************************************
* @brief  	return true if the string value of 'key' is match 'except_value'
* @param[in]	uint8_t * src
* @param[in]	uint8_t * key
* @param[in]	uint8_t * except_value
* @return     bool
*******************************************************************************/
bool app_json_is_str_match(uint8_t* src, uint8_t* key, uint8_t* except_value);

/*!*****************************************************************************
* @brief  	get uint8_t value from src by key
* @param[in]	uint8_t * src
* @param[in]	uint8_t * key
* @return     uint8_t
*******************************************************************************/
uint8_t app_json_get_int8(uint8_t* src, uint8_t* key);








/** @}*/ //end of group app_json
#endif // APP_JSON_H
