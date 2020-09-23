/*!*****************************************************************************
* @file     hal_timer.c
* @brief
* @author	 FuxFox
* @version  V1.0
* @date     2020/08/18
*******************************************************************************/
#ifndef HAL_TIMER_C
#define HAL_TIMER_C

#include "hal_timer.h"

#if defined(HAL_TIMER_ENABLE)&&(HAL_TIMER_ENABLE)

void hal_timer_timebase_init(uint16_t ms)
{	
	// use systick
}

void hal_timer_timebase_pause(void)
{
    HAL_SuspendTick();
}

void hal_timer_timebase_resume(void)
{
    HAL_ResumeTick();
}

#endif

#endif // HAL_TIMER_C
