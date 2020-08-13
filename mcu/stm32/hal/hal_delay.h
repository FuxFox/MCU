/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/06/23 15:11          V1.0             build this file
 *
 *******************************************************************************/
#ifndef HAL_DELAY_H
#define HAL_DELAY_H

/*! \defgroup hal_delay
\brief Blocking-Delay. Implemented base on STM32F103 with HAL.
\details 
* @{ */

#include "app_config.h"


//********************************* Module Config *******************************/
					

//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/


/*!*****************************************************************************
\brief      initialize the soft delay function
            call this function after system clock initialization.
\return     void
******************************************************************************/
void hal_delay_init(void);

/*!*****************************************************************************
\brief      blocking delay in us
\param[in]    uint32_t nus
\return     void
******************************************************************************/
void hal_delay_us(uint32_t nus);

/*!*****************************************************************************
\brief      blocking delay in ms
\param[in]    uint32_t nms
\note        SysTick->LOAD is 24bit register, therefore, the max delay of ms are:
				nms <= 0xffffff / (SYSCLK / 8 / 1000),
				SYSCLK unit: Hz, nms unit: ms,
				if SYSCLK is 72000000 Hz, nms <= 1864
\return     void
******************************************************************************/
#if defined(HAL_ENABLED)&&(HAL_ENABLED)
#define hal_delay_ms(nms) HAL_Delay(nms)
#else
void hal_delay_ms(uint32_t nms);
#endif




/*! @}*/ //end of group hal_delay
#endif // HAL_DELAY_H
