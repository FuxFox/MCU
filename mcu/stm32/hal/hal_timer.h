/*******************************************************************************
* LICENSE : Apache 2.0
*           
* History:
*    <author>         <time>             <version>             <desc>
*      FuxFox	      2020/06/23 10:41          V1.0             build this file
*
*******************************************************************************/
#ifndef HAL_TIMER_H
#define HAL_TIMER_H

/**
* @defgroup hal_timer
* @ingroup HAL
* @brief	 STM32 Timer HAL
* @details 
* @{ */

#include "app_config.h"


/*================================= Data Type ================================*/

/** 
* @defgroup HAL_TIMER_TIMEBASE_TYPE
* @{ */
#define HAL_TIMER_TIMEBASE_RTC            0
#define HAL_TIMER_TIMEBASE_TIM            1
/** @}*/ //end of group HAL_TIMER_TIMEBASE_TYPE

/** Select the time base that use for app_timer, \ref HAL_TIMER_TIMEBASE_TYPE */
#define HAL_TIMER_TIMEBASE		CFG_HAL_TIMER_TIMEBASE
/** the interrupt main-priority of timebase tick */
#define HAL_TIMER_TIMEBASE_IRQ_PRIORITY        CFG_HAL_TIMEBASE_IRQ_PRIORITY

#if (HAL_TIMER_TIMEBASE == HAL_TIMER_TIMEBASE_TIM)
/** the hardware timer used for timebase, can be [2-7]. e.g if use TIM4, this value will be 4. Base timers are recommended */
#define HAL_TIMEBASE_TIM_ID                6
#endif




/*================================= Data Type ================================*/





/*================================= Public Interface =========================*/

/*!*****************************************************************************
* @brief  	initialize timebase ,now used for app_timer
* @param[in]	uint16_t ms : interval of ticks.
* @return     void
*******************************************************************************/
void hal_timer_timebase_init(uint16_t ms);

/*!*****************************************************************************
* @brief  	stop timebase
* @param[in]	void
* @return     void
*******************************************************************************/
void hal_timer_timebase_pause(void);

/*!*****************************************************************************
* @brief  	resume timebase
* @param[in]	void
* @return     void
*******************************************************************************/
void hal_timer_timebase_resume(void);




/** @}*/ //end of group hal_timer
#endif // HAL_TIMER_H
