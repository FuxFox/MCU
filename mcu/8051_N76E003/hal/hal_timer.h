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
* @brief 
* @details 
* @{ */

#include "app_config.h"


/*================================= Module Config ============================*/





/*================================= Data Type ================================*/





/*================================= Public Interface =========================*/


/*!*****************************************************************************
* @brief  	init timebase ,now used for app_timer
* @param[in]	uint16_t ms : currently not used.
* @return     void
*******************************************************************************/
void hal_timer_timebase_init(uint16_t ms);

/*!*****************************************************************************
* @brief  	reload timebase timer manually
* @param[in]	void
* @return     void
*******************************************************************************/
void hal_timer_timebase_reload(void);

#define hal_timer_timebase_pause() clr_TR0
#define hal_timer_timebase_resume() set_TR0


/** @}*/ //end of group hal_timer
#endif // HAL_TIMER_H
