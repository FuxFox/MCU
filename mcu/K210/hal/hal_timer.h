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
* @brief	 Timer HAL for K210
* @details 配置硬件定时器，尤其是要为 app_timer 提供的时基
* 
* @{ */

#include "app_config.h"


/*================================= Module Config ============================*/
#define HAL_TIMER_HARDWARE_TIMER_ID 0	/**< K210有3个timer，默认使用Timer0。参数范围[0~2]。 */
#define HAL_TIMER_IRQ_PRIORITY		3	/**< 时基的中断优先级 */



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




/** @} */ //end of group hal_timer
#endif // HAL_TIMER_H
