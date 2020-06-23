/*******************************************************************************
 *
 * Module: log
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/22 10:51          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     log.h
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/10/22
 *******************************************************************************/
#ifndef LOG_H
#define LOG_H

/*! \defgroup log_public Public
\ingroup log
\brief            simple LOG module , used SEGGER RTT
\details 
* @{ */

#include "app_config.h"
//********************************* Module Config *******************************/
                                
#define APP_LOG_CHANNEL_DEF 0

#ifndef APP_LOG_MODULE_SYMBLE
#define APP_LOG_MODULE_SYMBLE "USER"
#endif
//********************************* Data Type ***********************************/

/*! \defgroup APP_LOG_LEVEL_TYPE
*
* @{ */
#define APP_LOG_LEVEL_NONE         0
#define APP_LOG_LEVEL_INFO         1
#define APP_LOG_LEVEL_ERROR        2
#define APP_LOG_LEVEL_WARNING      3
#define APP_LOG_LEVEL_DEBUG        4

/*! @}*/ //end of group APP_LOG_LEVEL_TYPE

/*! log type enum */
typedef enum
{
    LOG_TYPE_NONE,
    LOG_TYPE_INFO,
    LOG_TYPE_ERROR,
    LOG_TYPE_WARNING,
    LOG_TYPE_DEBUG            
}app_log_type_t;

//********************************* Public Interface ****************************/
void app_log_init(void);
void app_log_output(uint8_t channel, app_log_type_t type, const char* module_symble, const char* sformat, ...);
void app_log_print_array_to_hex(uint8_t channel, uint8_t* arry, uint8_t size);

#define LOG(log_type, sformat, ...) app_log_output(APP_LOG_CHANNEL_DEF, log_type, APP_LOG_MODULE_SYMBLE, sformat, ##__VA_ARGS__)


#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_INFO)
#define LOG_INFO(sformat, ...) LOG(LOG_TYPE_INFO, sformat, ##__VA_ARGS__)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_ERROR)
#define LOG_ERROR(sformat, ...) LOG(LOG_TYPE_WARNING, sformat, ##__VA_ARGS__)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_WARNING)
#define LOG_WARNING(sformat, ...) LOG(LOG_TYPE_ERROR, sformat, ##__VA_ARGS__)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_DEBUG)
#define LOG_DEBUG(sformat, ...)  LOG(LOG_TYPE_DEBUG, sformat, ##__VA_ARGS__)
#define LOG_DEBUG_ARRAY(arr, size) app_log_print_array_to_hex(APP_LOG_CHANNEL_DEF, arr, size);
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

//********************************* Private Interface ***************************/





/*! @}*/ //end of group log
#endif // LOG_H
