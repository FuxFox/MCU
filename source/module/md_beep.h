/*!*****************************************************************************
* @file     md_beep.h
* @brief    
* @author   FuxFox
* @version  V1.0
* @date     2019/07/26
*******************************************************************************/
#ifndef MD_BEEP_H
#define MD_BEEP_H

/**
* @defgroup md_beep
* @ingroup module
* @brief      A beep module implemented base on NRF52832, provide advanced control of buzzer.
*           Support single beep, beep in ms, a sequence of beep, a number of sequences of beep.
* @note       If you want to use this in other MCU, you need to modify or implement something:
*           app_timer: a (soft) timer.
*           drv_buzzer: the driver for buzzer.
* @{ */

#include "app_config.h"

/*================================= Module Config ============================*/

#define MD_BEEP_ON_TIME_DEF        500   /**< Default buzzer on time, in ms */




/*================================= Data Type ================================*/





/*================================= Public Interface =========================*/

/*!*****************************************************************************
* @brief      initialize
* @details
* @param[in]    void
* @return     void
*******************************************************************************/
void md_beep_init(void);

/*!*****************************************************************************
* @brief      a single beep
* @param[in]    void
* @return     void
*******************************************************************************/
void md_beep_beep(void);

/*!*****************************************************************************
* @brief      beep in ms
* @param[in]    uint16_t beep_time        buzzer on time, in ms
* @return     void
*******************************************************************************/
void md_beep_beepEx(uint16_t beep_time);

/*!*****************************************************************************
* @brief      a sequence of beep
* @param[in]    uint16_t on_time      buzzer on time, in ms
* @param[in]    uint16_t off_time     buzzer off time, in ms
* @param[in]    uint16_t beep_num     the number of beep
* @return     void
*******************************************************************************/
void md_beep_sequence(uint16_t on_time, uint16_t off_time, uint16_t beep_num);

/*!*****************************************************************************
* @brief      a number of beep sequences
* @param[in]    uint16_t on_time      buzzer on time, in ms
* @param[in]    uint16_t off_time     buzzer off time, in ms, can be 0 if beep_num is 1.
* @param[in]    uint16_t beep_num     the number of beep, minimum is 1.
* @param[in]    uint16_t seq_interval interval of sequences, can be 0 if seq_num is 0.
* @param[in]    uint8_t seq_num       number of sequences, can be 0.
* @return     void
*******************************************************************************/
void md_beep_sequenceEx(uint16_t on_time, uint16_t off_time, uint8_t beep_cnt, uint16_t seq_interval, uint8_t seq_cnt);

/*!*****************************************************************************
* @brief      stop beeping
* @param[in]    void
* @return     void
*******************************************************************************/
void md_beep_stop(void);

/*!*****************************************************************************
* @brief      is beeping ?
* @param[in]    void
* @return     bool
*******************************************************************************/
bool md_beep_is_on(void);




/** @}*/ //end of group md_beep
#endif // MD_beep_H
