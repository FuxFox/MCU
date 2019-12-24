/*******************************************************************************
 * LICENSE : Apache 2.0
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/27 10:35          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * @file     app_button.h
  * @brief
  * @author   FuxFox
  * @version  V1.0
  * @date       2019/11/27
  *******************************************************************************/
#ifndef APP_BUTTON_H
#define APP_BUTTON_H

  /*! @defgroup app_button_public Public
  * @ingroup app_button
  * @brief    This module is used for keyboard scanning and provides callback.Support long-press detection.
              The module will scan(Polling) gpio pin in timer interrupt.

     example:
        #include "ui_button.h"
        #define UI_BUTTON_LIST	{		\
            {PIN_BUTTON_1,	APP_GPIO_NOPULL, APP_BUTTON_ACTIVE_LOW, ui_button_handler},\
            {PIN_BUTTON_2,	APP_GPIO_NOPULL, APP_BUTTON_ACTIVE_LOW, ui_button_handler},\
            {PIN_BUTTON_3,	APP_GPIO_NOPULL, APP_BUTTON_ACTIVE_LOW, ui_button_handler},\
            {PIN_BUTTON_4,	APP_GPIO_NOPULL, APP_BUTTON_ACTIVE_LOW, my_button_handler},\
            {PIN_BUTTON_5,	APP_GPIO_NOPULL, APP_BUTTON_ACTIVE_LOW, your_button_handler},\
        }//The button list is an array of app_button_cfg_t

        APP_BUTTON_LIST_DEF(m_button_list, UI_BUTTON_LIST);

        void ui_button_init(void)
        {
            app_button_init(&m_button_list);
            app_button_enable();

        }

    @note   If you want to use this module for matrix keyboard, 
            you can scan row(column) with this module, then manual check column(row) in button's callback function.
  * @{ */

#include "app_config.h"

#include "app_gpio.h"
#include "app_timer.h"
//********************************* Module Config *******************************/

#define APP_BUTTON_SCAN_INTERVAL              CFG_BUTTON_SCAN_INTERVAL              /*!< button scan interval , in ms */
#define APP_BUTTON_DETECTION_DELAY            CFG_BUTTON_DETECTION_DELAY            //currently not implemented
#define APP_BUTTON_LONG_PRESS_DETECT_DELAY    CFG_BUTTON_LONG_PRESS_DETECT_DELAY    /*!< long-press interval */
#define APP_BUTTON_REALTIME_MODE              CFG_BUTTON_REALTIME_MODE              /*!< if true, the callback function of active button will be called in interrupt
                                                                                    else,    will be called in main loop*/

//********************************* Data Type ***********************************/

typedef enum
{
    APP_BUTTON_RELEASE,
    APP_BUTTON_PRESS,
    APP_BUTTON_LONG_PRESS,
} app_button_action_t;

/*! The button action callback function typedef 
@param button_pin : the pin number of the active button
@param action : the action of the active button \ref app_button_action_t
*/
typedef void (*app_button_callback)(uint8_t button_pin, app_button_action_t action);

typedef enum
{
    APP_BUTTON_ACTIVE_LOW,      /*!< low level active */
    APP_BUTTON_ACTIVE_HIGH      /*!< high level active */
} app_button_active_level_t;

typedef const struct
{
    uint8_t button_pin;                     /*!< The pin of chip which connected to the button */
    app_gpio_pull_t pin_pull;               /*!< The pin pull state */
    app_button_active_level_t active_level;
    app_button_callback callback;           /*!< will be call if button active */
} app_button_cfg_t;

/*! button state */
typedef struct
{
    bool is_press;
    uint16_t long_press_cnt;
} app_button_sta_t;

typedef const struct
{
    app_button_cfg_t* button_list;
    app_button_sta_t* button_sta;
    uint8_t button_cnt;
} app_button_t;


//********************************* Public Interface ****************************/

/*!*****************************************************************************
\brief  	Use this macro to define a button list

\param[in]	_name   The name of the list
\param[in]	_list   An array of app_button_cfg_t
*******************************************************************************/
#define APP_BUTTON_LIST_DEF(_name, _list)    \
    static app_button_cfg_t _name##_cfg[] = _list;     \
    static app_button_sta_t _name##_sta[ARRAY_SIZE(_name##_cfg)] = {0}; \
    static app_button_t _name = {_name##_cfg, _name##_sta, ARRAY_SIZE(_name##_cfg)};



void app_button_init(app_button_t* init);
void app_button_enable(void);
void app_button_disable(void);

//********************************* Private Interface ***************************/

static void app_button_scan(void);

/*! @}*/ //end of group app_button
#endif   // APP_BUTTON_H
