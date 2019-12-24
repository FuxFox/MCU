/*******************************************************************************
 * Module: md_clock
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/09/03 14:45          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     md_clock.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/09/03
  *******************************************************************************/
#ifndef MD_CLOCK_H
#define MD_CLOCK_H

  /*! \defgroup md_clock_public Public
  \ingroup md_clock
  \brief
          This is a clock module, with alarm function.Implemented base on NRF52832.
  @note   This module used app_timer module
  * @{ */

#include "app_config.h"
#include <time.h>

  //********************************* Module Config *******************************/

#define MD_CLOCK_ALARM_MAX                CFG_CLOCK_ALARM_MAX        /*!< max amount of alarm */

#define MD_CLOCK_ALARM_ID_LEN    36        /*!< alarm id max len */
//********************************* Data Type ***********************************/

typedef struct tm        md_clock_struct;

typedef struct
{
    char    id[MD_CLOCK_ALARM_ID_LEN + 1];
    uint8_t    hour;
    uint8_t    minute;
}md_clock_alarm_struct;

typedef enum
{
    MD_CLOCK_MSG_STEP_MINUTE,        /*!< minute change */
    MD_CLOCK_MSG_STEP_HOUR,            /*! hour change */
    MD_CLOCK_MSG_ALARM_EXPIRE        /*!< alarm alert */
}md_clock_msg_enum;

typedef void (*md_clock_callback)(md_clock_msg_enum, md_clock_alarm_struct*);

//********************************* Public Interface ****************************/

void md_clock_init(md_clock_callback callback);

md_clock_struct* md_clock_get(void);
time_t md_clock_timestamp_get(void);
void md_clock_time_sync(md_clock_struct* time);
bool md_clock_is_time_to_alarm(void);
void md_clock_alarm_add(char* id, uint8_t hour, uint8_t min);
void md_clock_alarm_delete(char* reminder_id);
void md_clock_alarm_delete_all(void);
//********************************* Private Interface ***************************/

static void md_clock_callback_NULL(md_clock_msg_enum msg, md_clock_alarm_struct* alarm);
static void md_clock_sec_handler(void* context);

/*! @}*/ //end of group md_clock
#endif // MD_CLOCK_H
