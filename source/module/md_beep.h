/*******************************************************************************
 * Module: md_beep
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/07/26 16:16          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     md_beep.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/07/26
 *******************************************************************************/
#ifndef MD_BEEP_H
#define MD_BEEP_H

/*! \defgroup md_beep_public Public
\ingroup md_beep
\brief      A beep module implemented base on NRF52832, provide advanced control of buzzer.
            Support single beep, beep in ms, a sequence of beep, a number of sequences of beep.
\note       If you want to use this in other MCU, you need to modify or implement something:
            app_timer: a (soft) timer.
            drv_buzzer: the driver for buzzer.
* @{ */

#include "app_config.h"

#include "drv_buzzer.h"
//********************************* Module Config *******************************/

#define MD_BEEP_ON_TIME_DEF        500        /*!< Default buzzer on time, in ms */




//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/


void md_beep_init(void);

void md_beep_beep(void);
void md_beep_beepEx(uint16_t beep_time);
void md_beep_sequence(uint16_t on_time, uint16_t off_time, uint16_t beep_num);
void md_beep_sequenceEx(uint16_t on_time, uint16_t off_time, uint8_t beep_cnt, uint16_t seq_interval, uint8_t seq_cnt);
void md_beep_stop(void);
bool md_beep_is_on(void);
//********************************* Private Interface ***************************/

static void md_beep_timer_handler(void* p_context);



/*! @}*/ //end of group md_beep
#endif // MD_beep_H
