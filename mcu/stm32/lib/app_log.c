/*******************************************************************************
 *
 * Module: log
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/22 11:31          V1.0             build this file
 *
 *******************************************************************************/
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
#include "SEGGER_RTT.h"

#if (defined(APP_LOG_ENABLE) && APP_LOG_ENABLE)

  /*!*****************************************************************************
  \brief      initialize
  \details
  \param[in]    void
  \return     void
  ******************************************************************************/
void app_log_init(void)
{
    SEGGER_RTT_Init();
}

/*!*****************************************************************************
\brief
\param[in]	uint8_t channel                 Output channel
\param[in]	app_log_type_t type
\param[in]	const char * module_symble
\param[in]	const char * sformat
\param[in]	...
\return     void
******************************************************************************/
void app_log_output(uint8_t channel, app_log_type_t type, const char* module_symble, const char* sformat, ...)
{
    char* color, * msg_type;
    va_list ParamList;

    if (type > APP_LOG_LEVEL)
    {
        return;
    }

    switch (type)
    {
    case LOG_TYPE_INFO:
        msg_type = "<info>";
        color = RTT_CTRL_TEXT_WHITE;
        break;
    case LOG_TYPE_WARNING:
        msg_type = "<warning>";
        color = RTT_CTRL_TEXT_YELLOW;
        break;
    case LOG_TYPE_ERROR:
        msg_type = "<error>";
        color = RTT_CTRL_TEXT_RED;
        break;
    case LOG_TYPE_DEBUG:
        msg_type = "<debug>";
        color = RTT_CTRL_TEXT_WHITE;
        break;
    default:
        return;
        //break;
    }

    SEGGER_RTT_printf(channel, "%s%s|%s ->", color, msg_type, module_symble);

    va_start(ParamList, sformat);
    SEGGER_RTT_vprintf(channel, sformat, &ParamList);
    va_end(ParamList);

    SEGGER_RTT_printf(channel, "\r\n");
}


/*!*****************************************************************************
\brief      print an array in HEX mode
\details
\param[in]    uint8_t channel
\param[in]    uint8_t * arry
\param[in]    uint8_t size
\return     void
******************************************************************************/
void app_log_print_array_to_hex(uint8_t channel, uint8_t* arry, uint8_t size)
{
    SEGGER_RTT_printf(0, "%s<debug>|%s ->array:", RTT_CTRL_TEXT_WHITE, APP_LOG_MODULE_SYMBLE);

    while (size--)
    {
        SEGGER_RTT_printf(channel, "0x%x,", *arry++);
    }
    SEGGER_RTT_printf(channel, "\r\n");
}

#endif






#endif // LOG_C
