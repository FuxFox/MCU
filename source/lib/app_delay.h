/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/12/07 17:39          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     delay.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/12/07
 *******************************************************************************/
#ifndef DELAY_H
#define DELAY_H

/*! \defgroup app_delay_public Public
\ingroup app_delay
\brief      A blocking delay module. Implemented base on STM32F103 with HAL.
\details 
* @{ */

#include "app_config.h"
//********************************* Module Config *******************************/
                                




//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/

void app_delay_init(void);
void app_delay_us(uint32_t nus);

#if defined(HAL_ENABLED)&&(HAL_ENABLED)
#define app_delay_ms(nms) HAL_Delay(nms)
#else
void app_delay_ms(uint16_t nms);
#endif

uint16_t app_delay_systick_per_us(void);




//********************************* Private Interface ***************************/





/*! @}*/ //end of group app_delay
#endif // DELAY_H




























