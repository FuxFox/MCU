/*******************************************************************************
 * Module: drv_buzzer
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/07/26 14:43          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     drv_buzzer.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/07/26
 *******************************************************************************/
#ifndef DRV_BUZZER_H
#define DRV_BUZZER_H

/*! \defgroup drv_buzzer_public Public
\ingroup drv_buzzer
\brief      A passive buzzer driver for NRF52832 with PWM.
\details 
* @{ */

#include "app_config.h"


//********************************* Module Config *******************************/
#define DRV_BUZZER_CONTROL_PIN        PIN_BUZZER        /*!< GPIO pin to control buzzer */
#define DRV_BUZZER_PWM_FREQ_HZ        CFG_BUZZER_FREQ   /*!< buzzer frequency in Hz, recommend value: [1000 - 4000] */


 


//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/


void drv_buzzer_init(void);
void drv_buzzer_on(void);
void drv_buzzer_off(void);
bool drv_buzzer_is_on(void);
//********************************* Private Interface ***************************/


/*! @}*/ //end of group drv_buzzer
#endif // DRV_BUZZER_H
