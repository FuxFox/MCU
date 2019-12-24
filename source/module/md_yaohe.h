/*******************************************************************************
 * Module: md_yaohe
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/09/16 14:08          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     md_yaohe.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/09/16
  *******************************************************************************/
#ifndef MD_YAOHE_H
#define MD_YAOHE_H

  /*! \defgroup md_yaohe_public Public
  \ingroup md_yaohe
  \brief        A Specific application of QUECTEL M26
  \details
  * @{ */

#include "app_config.h"

#include "md_m26.h"
#include "md_clock.h"
#include "ble_module.h"
  //********************************* Module Config *******************************/

#define MD_YAOHE_GET_URL        CFG_YAOHE_BACKEND_URL
#define MD_YAOHE_POST_URL        CFG_YAOHE_BACKEND_URL

#define MD_YAOHE_MEDICATION_PLAN_BUFF_SIZE        CFG_YAOHE_MEDICATION_PLAN_BUFF_SIZE
//********************************* Data Type ***********************************/

typedef enum
{
    MD_YAOHE_MSG_ALARMAUDIT,
    MD_YAOHE_MSG_COMFIRM,
    MD_YAOHE_MSG_COMFIRMDELAY,
}md_yaohe_msg_enum;

typedef enum
{
    MD_YAOHE_DOOR_ACTION_CLOSE,
    MD_YAOHE_DOOR_ACTION_OPEN,

}md_yaohe_door_action_enum;

//********************************* Public Interface ****************************/

bool md_yaohe_init(void);
char* md_yaohe_get_serial_number(void);
bool md_yaohe_server_handshake(void);

void md_yaohe_medication_plans_sync(void);


bool md_yaohe_alarm_notify(md_yaohe_msg_enum msg, char* id, uint8_t hour, uint8_t min);
bool md_yaohe_door_action_notify(md_yaohe_door_action_enum msg);
//********************************* Private Interface ***************************/
static void md_yaohe_https_config(void);

static bool md_yaohe_send_post_waite_succeed(/*cJSON* root*/char* post);
static bool md_yaohe_send_post_and_recieve(char* post, char* response, size_t rx_size);
/*! @}*/ //end of group md_yaohe
#endif // MD_YAOHE_H
