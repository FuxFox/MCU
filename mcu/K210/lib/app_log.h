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
/*================================= Module Config ============================*/

#define APP_LOG_ENABLE			    CFG_LOG_ENABLE
#define APP_LOG_LEVEL			    CFG_LOG_LEVEL
#define APP_LOG_COLORS_ENABLE	    CFG_LOG_COLORS_ENABLE
#define APP_LOG_TIMESTAMP_ENABLE   CFG_LOG_TIMESTAMP_ENABLE
#define APP_LOG_TAG_ENABLE         CFG_LOG_TAG_ENABLE

#define APP_LOG_ASSERT_ENALBLE     CFG_LOG_ASSERT_ENALBLE

#define APP_LOG_PRINTF printf

#if (APP_LOG_TAG_ENABLE && defined(LOG_TAG))
# define APP_LOG_TAG_FORMAT "%s: "
# define APP_LOG_TAG ,LOG_TAG
#else
# define APP_LOG_TAG_FORMAT
# define APP_LOG_TAG
#endif

#if APP_LOG_TIMESTAMP_ENABLE
# define APP_LOG_TIMESTAMP ,read_cycle()
# define APP_LOG_TIMESTAMP_FORMAT "(%lu) "
#else
# define APP_LOG_TIMESTAMP
# define APP_LOG_TIMESTAMP_FORMAT
#endif
/*================================= Data Type ================================*/

#if APP_LOG_COLORS_ENABLE
# define APP_LOG_COLOR_BLACK   "30"
# define APP_LOG_COLOR_RED     "31"
# define APP_LOG_COLOR_GREEN   "32"
# define APP_LOG_COLOR_BROWN   "33"
# define APP_LOG_COLOR_BLUE    "34"
# define APP_LOG_COLOR_PURPLE  "35"
# define APP_LOG_COLOR_CYAN    "36"
# define APP_LOG_COLOR(COLOR)  "\033[0;" COLOR "m"
# define APP_LOG_BOLD(COLOR)   "\033[1;" COLOR "m"
# define APP_LOG_RESET_COLOR   "\033[0m"
# define APP_LOG_COLOR_E       APP_LOG_COLOR(APP_LOG_COLOR_RED)
# define APP_LOG_COLOR_W       APP_LOG_COLOR(APP_LOG_COLOR_BROWN)
# define APP_LOG_COLOR_I       APP_LOG_COLOR(APP_LOG_COLOR_GREEN)
# define APP_LOG_COLOR_D
# define APP_LOG_COLOR_V
#else /* APP_LOG_COLORS_ENABLE */
# define APP_LOG_COLOR_E
# define APP_LOG_COLOR_W
# define APP_LOG_COLOR_I
# define APP_LOG_COLOR_D
# define APP_LOG_COLOR_V
# define APP_LOG_RESET_COLOR
#endif /* APP_LOG_COLORS_ENABLE */

typedef enum
{
	APP_LOG_LEVEL_NONE,
	APP_LOG_LEVEL_ERROR,
	APP_LOG_LEVEL_WARNING,
	APP_LOG_LEVEL_INFO,
	APP_LOG_LEVEL_DEBUG
}app_log_level_t;

/*================================= Public Interface =========================*/

#if (APP_LOG_ENABLE && APP_LOG_LEVEL)
/*!*****************************************************************************
* @brief  	initialize UART or other channel to print log
* @param[in]	void
* @return     void
*******************************************************************************/
void app_log_init(void);
#else
# undef APP_LOG_LEVEL
# define APP_LOG_LEVEL APP_LOG_LEVEL_NONE
# define app_log_init()
#endif

#define LOG_FORMAT(letter, format) \
    APP_LOG_COLOR_##letter #letter " " APP_LOG_TIMESTAMP_FORMAT APP_LOG_TAG_FORMAT format APP_LOG_RESET_COLOR "\n"\
    APP_LOG_TIMESTAMP APP_LOG_TAG


#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_ERROR)
# define APP_LOG_ERROR(sformat, ...) APP_LOG_PRINTF(LOG_FORMAT(E, sformat), ##__VA_ARGS__)
#else
# define APP_LOG_ERROR(sformat, ...)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_WARNING)
# define APP_LOG_WARNING(sformat, ...) APP_LOG_PRINTF(LOG_FORMAT(W, sformat), ##__VA_ARGS__)
#else
# define APP_LOG_WARNING(sformat, ...)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_INFO)
# define APP_LOG_INFO(sformat, ...) APP_LOG_PRINTF(LOG_FORMAT(I, sformat), ##__VA_ARGS__)
#else
# define APP_LOG_INFO(sformat, ...)
#endif

#if (APP_LOG_LEVEL >= APP_LOG_LEVEL_DEBUG)
/*!*****************************************************************************
* @brief  	Print an array to Hex
* @param[in]	uint8_t * str : prompt information
* @param[in]	uint8_t * arry
* @param[in]	uint8_t size
* @return     void
*******************************************************************************/
void app_log_print_array_to_hex(uint8_t* str, uint8_t* arry, uint8_t size);
# define APP_LOG_DEBUG(sformat, ...)  APP_LOG_PRINTF(LOG_FORMAT(D, sformat), ##__VA_ARGS__)
# define APP_LOG_DEBUG_ARRAY(_str, _arr, _size) app_log_print_array_to_hex((uint8_t*)_str, _arr, _size)
#else
# define APP_LOG_DEBUG(sformat, ...)
# define APP_LOG_DEBUG_ARRAY(_str, _arr, _size)
#endif


#if APP_LOG_ASSERT_ENALBLE
/**
* @brief  The assert_param macro is used for function's parameters check.
* @param  expr If expr is false, it calls assert_failed function
*         which reports the name of the source file and the source
*         line number of the call that failed.
*         If expr is true, it returns no value.
* @retval None
*/
#define assert_param(expr) \
	if ((expr) == 0) \
	{\
		APP_LOG_ERROR("Wrong parameters value: file %s on line %d\n", __FILE__, __LINE__);\
		while (1);\
	}

/* Exported functions ------------------------------------------------------- */
#else
#define assert_param(expr) ((void)0U)

#endif /* USE_FULL_ASSERT */


/** @}*/ //end of group app_log
#endif // APP_LOG_H
