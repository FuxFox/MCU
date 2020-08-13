/*******************************************************************************
 *
 * Module: app_timer
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/21 17:48          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     app_timer.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/21
  *******************************************************************************/
#ifndef APP_TIMER_H
#define APP_TIMER_H

  /*! \defgroup app_timer
  \brief      A software timer module implemented base on HAL.
              You can configure the soft timer as real-time mode(callback in interrupt) or not(callback in main loop).
              Support single-shot and repeated mode.

      example:
          app_timer_id_t blink_timer;

          void ui_init(void)
          {
              app_timer_init();//init before use other function

              blink_timer = app_timer_create(APP_TIMER_MODE_REPEATED, ui_led_blink, false);
              app_timer_start(blink_timer, 1000, NULL);//timer period in 1000ms
          }

          void ui_led_blink(void* param)
          {
              hal_gpio_pin_toggle(PIN_LED);
          }

  \details
  * @{ */
#include "app_config.h"

  //********************************* Module Config *******************************/

#define APP_TIMER_TIMEBASE                     CFG_APP_TIMER_TIMEBASE           /*!< Select the time base that use for app_timer, \ref APP_TIMER_TIMEBASE_TYPE */
#define APP_TIMER_TIMEBASE_IRQ_PRIORITY        CFG_APP_TIMEBASE_IRQ_PRIORITY    /*!< the interrupt main-priority of timebase tick */
#define APP_TIMER_SOFTTIMER_MAX                CFG_APP_TIMER_NUM_MAX            /*!< the max amount of soft timer */



//********************************* Data Type ***********************************/

/**@brief Timer modes. */
typedef enum
{
    APP_TIMER_MODE_SINGLE_SHOT,                 /**< The timer will expire only once. */
    APP_TIMER_MODE_REPEATED                     /**< The timer will restart each time it expires. */
} app_timer_mode_t;

typedef void (*app_timer_handle)(void*);

typedef struct app_timer_struct
{
    uint32_t counter;
    uint32_t delay;
	bool is_pending;
	bool is_active;
    bool is_realtime;
    bool is_repeat;
    app_timer_handle    callback;
    void*    callback_param;
    struct app_timer_struct* last;
    struct app_timer_struct* next;
}app_timer_t;

typedef app_timer_t* app_timer_id_t;



//********************************* Public Interface ****************************/



/*!*****************************************************************************
\brief      initialize the app_timer module
\details
\param[in]    void
\return     uint32_t \ref HAL_StatusTypeDef
******************************************************************************/
uint32_t app_timer_init(void);

/*!*****************************************************************************
\brief      start a soft timer
\details        the timer specific by timer_id must be created
\param[in]    app_timer_id_t timer_id        the specific timer id, return by \ref app_timer_create()
\param[in]    uint32_t delay_ms            the timer expire time, in ms
\param[in]    void* param            the pointer to the param need by timer callback functon
\return     void
******************************************************************************/
void app_timer_start(app_timer_id_t timer_id, uint32_t delay_ms, void* param);

/*!*****************************************************************************
\brief      stop a timer specified by timer_id

\param[in]    app_timer_id_t timer_id
\return     void
******************************************************************************/
void app_timer_stop(app_timer_id_t timer_id);

/*!*****************************************************************************
\brief      pause the app_timer module
\details
            stop the hardware timer which app_timer used,
            all soft timer will pause
\param[in]    void
\return     void
******************************************************************************/
void app_timer_pause(void);

/*!*****************************************************************************
\brief      resume the app_timer from pause
\details
            start the hardware timer which app_timer used,
            all soft timer will resume to running(if activated)
\param[in]    void
\return     void
******************************************************************************/
void app_timer_resume(void);


/*!*****************************************************************************
\brief      create a soft timer
\details
\param[in]    app_timer_mode_t mode        : single shot or repeat \see app_timer_mode_t
\param[in]    uint32_t delay_ms            : delay time , in ms
\param[in]    app_timer_handle callback    : the function will be call when timer expire
\param[in]    bool is_realtime            : if true, the callback function will be call in interrupt,
                                        if false, will call in main loop
\return     app_timer_id_t                : timer id ,can use to delete or stop the timer,
                                        will be NULL if function false.
******************************************************************************/
app_timer_id_t app_timer_create(app_timer_mode_t mode, app_timer_handle callback, bool is_realtime);


/*!*****************************************************************************
\brief      delete a soft timer
\details
\param[in]    app_timer_id_t timer_id        : the timer specific to delete, the id was return by \ref app_timer_create()
\return     void
******************************************************************************/
void app_timer_delete(app_timer_id_t timer_id);



/*!*****************************************************************************
\brief      pending poll in main thread

\param[in]    void
\return     void
\note            this function must called in main loop to call the callback function for
            not real time timer, when the timer was expired and pending.
******************************************************************************/
void app_timer_process_poll(void);


//********************************* Private Interface ***************************/


/*!*****************************************************************************
\brief      1ms process in timebase interrupt

\param[in]    void
\return     void
\note        you can use hardware timer or RTC as timebase. timebase must configure as 1ms interrupt,
            and this function must called in timebase interrupt handler
******************************************************************************/
void app_timer_process_IT(void);



/*! @}*/ //end of group app_timer
#endif // APP_TIMER_H
