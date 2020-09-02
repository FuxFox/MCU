/*******************************************************************************
*
* Module: log
*           
* History:
*    <author>         <time>             <version>             <desc>
*      FuxFox          2019/10/22 10:51          V1.0             build this file
*
*******************************************************************************/
#ifndef LOG_H
#define LOG_H

/**
* @defgroup app_log
* @ingroup lib
* @brief  simple LOG module , used SEGGER RTT
* @details 
* @{ */

#include "app_config.h"
#include "SEGGER_RTT.h"
/*================================= Module Config ============================*/

#define APP_LOG_CHANNEL_DEF 0

#ifndef APP_LOG_MODULE_SYMBLE
#define APP_LOG_MODULE_SYMBLE "USER"
#endif
/*================================= Data Type ================================*/

/** log type enum */
typedef enum
{
	APP_LOG_LEVEL_NONE,
	APP_LOG_LEVEL_INFO,
	APP_LOG_LEVEL_ERROR,
	APP_LOG_LEVEL_WARNING,
	APP_LOG_LEVEL_DEBUG
}app_log_level_t;

/*================================= Public Interface =========================*/

/*!*****************************************************************************
* @brief      initialize
* @param[in]    void
* @return     void
******************************************************************************/
void app_log_init(void);

/*!*****************************************************************************
* @brief      print an array in HEX mode
* @param[in]    uint8_t * arry
* @param[in]    uint8_t size
* @return     void
******************************************************************************/
void app_log_print_array_to_hex(uint8_t* arry, uint8_t size);

#define LOG(log_type, sformat, ...) SEGGER_RTT_printf(APP_LOG_CHANNEL_DEF, "<"#log_type">|"APP_LOG_MODULE_SYMBLE" -> " sformat"\r\n", ##__VA_ARGS__)


#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_INFO)
#define LOG_INFO(sformat, ...) LOG(info, sformat, ##__VA_ARGS__)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_ERROR)
#define LOG_ERROR(sformat, ...) LOG(warning, sformat, ##__VA_ARGS__)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_WARNING)
#define LOG_WARNING(sformat, ...) LOG(error, sformat, ##__VA_ARGS__)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_DEBUG)
#define LOG_DEBUG(sformat, ...)  LOG(debug, sformat, ##__VA_ARGS__)
#define LOG_DEBUG_ARRAY(arr, size) app_log_print_array_to_hex(arr, size);
#endif

#ifndef LOG_INFO
#define LOG_INFO(sformat, ...) 
#endif
#ifndef LOG_WARNING
#define LOG_WARNING(sformat, ...) 
#endif
#ifndef LOG_ERROR
#define LOG_ERROR(sformat, ...) 
#endif
#ifndef LOG_DEBUG
#define LOG_DEBUG(sformat, ...) 
#define LOG_DEBUG_ARRAY(arr, size)
#endif


/** @}*/ //end of group log
#endif // LOG_H
