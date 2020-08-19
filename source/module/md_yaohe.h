/*!*****************************************************************************
* @file     md_yaohe.h
* @brief
* @author   FuxFox
* @version  V1.0
* @date     2019/09/16
*******************************************************************************/
#ifndef MD_YAOHE_H
#define MD_YAOHE_H

/**
* @defgroup md_yaohe
* @ingroup module
* @brief        A Specific application of QUECTEL M26
* @details
* @{ */

#include "app_config.h"

#include "md_m26.h"
#include "md_clock.h"
#include "ble_module.h"
/*================================= Module Config ============================*/

#define MD_YAOHE_GET_URL        CFG_YAOHE_BACKEND_URL
#define MD_YAOHE_POST_URL        CFG_YAOHE_BACKEND_URL

#define MD_YAOHE_MEDICATION_PLAN_BUFF_SIZE        CFG_YAOHE_MEDICATION_PLAN_BUFF_SIZE
/*================================= Data Type ================================*/

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

/*================================= Public Interface =========================*/

/*!*****************************************************************************
* @brief      initialize
* @param[in]    void
* @return    TRUE if success
*******************************************************************************/
bool md_yaohe_init(void);

/*!*****************************************************************************
* @brief      get serial number
* @param[in]    void
* @return     char*
*******************************************************************************/
char* md_yaohe_get_serial_number(void);

/*!*****************************************************************************
* @brief      handshake with server
* @param[in]    void
* @return     0 if failure
*******************************************************************************/
bool md_yaohe_server_handshake(void);

/*!*****************************************************************************
* @brief      sync
* @param[in]    void
* @return     void
*******************************************************************************/
void md_yaohe_medication_plans_sync(void);

/*!*****************************************************************************
* @brief      notify alarm event to server
* @param[in]    void
* @return     void
*******************************************************************************/
bool md_yaohe_alarm_notify(md_yaohe_msg_enum msg, char* id, uint8_t hour, uint8_t min);

/*!*****************************************************************************
* @brief      notify door action
* @param[in]    md_yaohe_door_action_enum msg
* @return     void
*******************************************************************************/
bool md_yaohe_door_action_notify(md_yaohe_door_action_enum msg);

/** @}*/ //end of group md_yaohe
#endif // MD_YAOHE_H
