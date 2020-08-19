/*!*****************************************************************************
* @file     md_clock.h
* @brief
* @author   FuxFox
* @version  V1.0
* @date     2019/09/03
*******************************************************************************/
#ifndef MD_CLOCK_H
#define MD_CLOCK_H

/**
* @defgroup md_clock
* @ingroup module
* @brief
*         This is a clock module, with alarm function.Implemented base on NRF52832.
* @note   This module used app_timer module
* @{ */

#include "app_config.h"
#include <time.h>

/*================================= Module Config ============================*/

#define MD_CLOCK_ALARM_MAX  CFG_CLOCK_ALARM_MAX   /**< max amount of alarm */
#define MD_CLOCK_ALARM_ID_LEN    36  /**< alarm id max len */
/*================================= Data Type ================================*/

typedef struct tm        md_clock_struct;

typedef struct
{
    char    id[MD_CLOCK_ALARM_ID_LEN + 1];
    uint8_t    hour;
    uint8_t    minute;
}md_clock_alarm_struct;

typedef enum
{
	MD_CLOCK_MSG_STEP_MINUTE,        /**< minute change */
	MD_CLOCK_MSG_STEP_HOUR,          /** hour change */
	MD_CLOCK_MSG_ALARM_EXPIRE        /**< alarm alert */
}md_clock_msg_enum;

typedef void (*md_clock_callback)(md_clock_msg_enum, md_clock_alarm_struct*);

/*================================= Public Interface =========================*/

/*!*****************************************************************************
* @brief      initialize
* @param[in]    md_clock_callback callback        this callback function will be call while minute or hour change
* @return     void
*******************************************************************************/
void md_clock_init(md_clock_callback callback);

/*!*****************************************************************************
* @brief      get time
* @param[in]    void
* @return     md_clock_time_struct
*******************************************************************************/
md_clock_struct* md_clock_get(void);

/*!*****************************************************************************
* @brief      get timestamp in ms
* @param[in]    void
* @return   time_t  timestamp in ms
*******************************************************************************/
time_t md_clock_timestamp_get(void);

/*!*****************************************************************************
* @brief      sync time
* @param[in]    void
* @return     void
*******************************************************************************/
void md_clock_time_sync(md_clock_struct* time);

/*!*****************************************************************************
* @brief      if time to alarm ?
* @details    check all alarm
* @param[in]    void
* @return     bool : true OR false
*******************************************************************************/
bool md_clock_is_time_to_alarm(void);

/*!*****************************************************************************
* @brief  	add alarm
* @param[in]	char * id       alarm id, a string(length lest then MD_CLOCK_ALARM_ID_LEN), use to identify alarm
* @param[in]	uint8_t hour    alarm time, [0~23]
* @param[in]	uint8_t min     alarm time, [0~59]
* @return     void
*******************************************************************************/
void md_clock_alarm_add(char* id, uint8_t hour, uint8_t min);

/*!*****************************************************************************
* @brief      delete an alarm
* @param[in]    char *id      The id you previous used for md_clock_alarm_add()
* @return     void
*******************************************************************************/
void md_clock_alarm_delete(char* reminder_id);

/*!*****************************************************************************
* @brief      delete all alarm
* @param[in]    void
* @return     void
*******************************************************************************/
void md_clock_alarm_delete_all(void);


/** @}*/ //end of group md_clock
#endif // MD_CLOCK_H
