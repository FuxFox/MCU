/*******************************************************************************
* LICENSE : Apache 2.0
*           
* History:
*    <author>         <time>             <version>             <desc>
*      FuxFox	      2020/08/13 16:01          V1.0             build this file
*
*******************************************************************************/
#ifndef APP_LOG_H
#define APP_LOG_H

/**
* @defgroup app_log
* @ingroup lib
* @brief		simple LOG module
* @details 
* @{ */

#include "app_config.h"

/*================================= Data Type ================================*/
#define APP_LOG_ENABLE		CFG_LOG_ENABLE
#define APP_LOG_LEVEL		CFG_LOG_LEVEL
#define APP_LOG_ASSERT_ENABLE CFG_LOG_ASSERT_ENABLE

#define APP_LOG_CHANNEL_DEF	CFG_LOG_CHANNEL_DEF

#define APP_LOG_MODULE_SYMBLE_ENABLE	CFG_LOG_MODULE_SYMBLE_ENABLE
#ifndef APP_LOG_MODULE_SYMBLE
#define APP_LOG_MODULE_SYMBLE "USER"
#endif
/*================================= Data Type ================================*/

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
* @brief  	initialize UART or other channel to print log
* @param[in]	void
* @return     void
*******************************************************************************/
#if (APP_LOG_ENABLE && APP_LOG_LEVEL)
void app_log_init(void);
#else
#define app_log_init()
#endif

/*!*****************************************************************************
* @brief  	Print an array to Hex
* @param[in]	uint8_t * str : prompt information
* @param[in]	uint8_t * arry
* @param[in]	uint8_t size
* @return     void
*******************************************************************************/
void app_log_print_array_to_hex(uint8_t* str, uint8_t* arry, uint8_t size);

#if APP_LOG_MODULE_SYMBLE_ENABLE
#define LOG(log_type, sformat, ...) print(#log_type APP_LOG_MODULE_SYMBLE sformat "\r\n", ##__VA_ARGS__)
#else
#define LOG(log_type, sformat, ...) print(#log_type sformat "\r\n", ##__VA_ARGS__)
#endif

#if APP_LOG_ENABLE
#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_INFO)
#define APP_LOG_INFO(sformat, ...) LOG(INFO, sformat, ##__VA_ARGS__)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_ERROR)
#define APP_LOG_ERROR(sformat, ...) LOG(ERROR, sformat, ##__VA_ARGS__)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_WARNING)
#define APP_LOG_WARNING(sformat, ...) LOG(WARNING, sformat, ##__VA_ARGS__)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_DEBUG)
#define APP_LOG_DEBUG(sformat, ...)  LOG(DEBUG, sformat, ##__VA_ARGS__)
#define APP_LOG_DEBUG_ARRAY(_str, _arr, _size) app_log_print_array_to_hex((uint8_t*)_str, _arr, _size);
#endif
#else

#ifndef APP_LOG_INFO
#define APP_LOG_INFO(sformat, ...) 
#endif
#ifndef APP_LOG_WARNING
#define APP_LOG_WARNING(sformat, ...) 
#endif
#ifndef APP_LOG_ERROR
#define APP_LOG_ERROR(sformat, ...) 
#endif
#ifndef APP_LOG_DEBUG
#define APP_LOG_DEBUG(sformat, ...) 
#define APP_LOG_DEBUG_ARRAY(_str, _arr, _size)
#endif
#endif


#if APP_LOG_ASSERT_ENABLE

/**
* @brief  Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  file: pointer to the source file name
* @param  line: assert_param error line source number
* @retval None
*/
void app_log_assert(uint8_t* file, uint32_t line);

/**
* @brief  The assert_param macro is used for function's parameters check.
* @param  expr If expr is false, it calls assert_failed function
*         which reports the name of the source file and the source
*         line number of the call that failed.
*         If expr is true, it returns no value.
* @retval None
*/
#define assert_param(expr) ((expr) ? (void)0U : app_error_assert((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
#else
#define assert_param(expr) ((void)0U)
#endif /* APP_LOG_ASSERT_ENABLE */







/** @}*/ //end of group app_log
#endif // APP_LOG_H
