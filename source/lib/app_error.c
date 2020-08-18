/*!*****************************************************************************
* @file     app_error.c
* @brief
* @author	 FuxFox
* @version  V1.0
* @date     2020/08/18
*******************************************************************************/
#ifndef APP_ERROR_C
#define APP_ERROR_C

#include "app_error.h"
#include "app_log.h"

void app_error_init(void)
{
    //currently nothing
}

void app_error_assert(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,*/
    APP_LOG_ERROR("Wrong parameters value: file %s on line %d\r\n", file, line);
    while (1);
}

void app_error_handler(uint32_t error_code, uint8_t* file, uint32_t line)
{
    APP_LOG_ERROR("Error 0x%x occurred at: file %s on line %d\r\n", error_code, file, line);
    while (1);
}



#endif // APP_ERROR_C
