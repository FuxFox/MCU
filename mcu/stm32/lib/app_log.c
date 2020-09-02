 /*!
* \file     log.c
* \brief
* \author   FuxFox
* \version  V1.0
* \date       2019/10/22
*******************************************************************************/
#ifndef LOG_C
#define LOG_C

#include "app_log.h"

#if (defined(APP_LOG_ENABLE) && APP_LOG_ENABLE)

void app_log_init(void)
{
    SEGGER_RTT_Init();
}

void app_log_print_array_to_hex(uint8_t* arry, uint8_t size)
{
    SEGGER_RTT_printf(APP_LOG_CHANNEL_DEF, "<debug>|%s ->array:", APP_LOG_MODULE_SYMBLE);

    while (size--)
    {
        SEGGER_RTT_printf(APP_LOG_CHANNEL_DEF, "0x%x,", *arry++);
    }
    SEGGER_RTT_printf(APP_LOG_CHANNEL_DEF, "\r\n");
}

#endif






#endif // LOG_C
