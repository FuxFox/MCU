/*!*****************************************************************************
* @file     hal_timer.c
* @brief
* @author	 FuxFox
* @version  V1.0
* @date     2020/08/17
*******************************************************************************/
#ifndef HAL_TIMER_C
#define HAL_TIMER_C

#include "hal_timer.h"
#include "timer.h"
#include "plic.h"
#include "sysctl.h"
#include "app_timer.h"

#define TIMEBASE_TIMER	CONCAT_2(TIMER_DEVICE_, HAL_TIMER_HARDWARE_TIMER_ID)
#define TIMEBASE_CHANNEL TIMER_CHANNEL_0

void hal_timer_timebase_init(uint16_t ms)
{	
	plic_init();
	timer_init(TIMEBASE_TIMER);
	timer_set_interval(TIMEBASE_TIMER, TIMEBASE_CHANNEL, ms * 1000000);
	timer_irq_register(TIMEBASE_TIMER, TIMEBASE_CHANNEL, false, HAL_TIMER_IRQ_PRIORITY, (timer_callback_t)app_timer_process_IT, NULL);
	timer_set_enable(TIMEBASE_TIMER, TIMEBASE_CHANNEL, true);
	sysctl_enable_irq();
}

void hal_timer_timebase_pause(void)
{

}

void hal_timer_timebase_resume(void)
{

}

#endif // HAL_TIMER_C
