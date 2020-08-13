/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/06/23 10:41          V1.0             build this file
 *
 *******************************************************************************/
#ifndef HAL_TIMER_C
#define HAL_TIMER_C

#include "hal_timer.h"

void hal_timer_timebase_init(uint16_t ms)
{	
    TIMER0_MODE1_ENABLE;
	clr_T0M;  // TIM_DIV = 12

    hal_timer_timebase_reload();

	set_ET0;  //enable Timer0 interrupt
    set_EA;   //enable interrupts
    set_TR0;  //Timer0 run
}

/*
void hal_timer_timebase_pause(void)
{
	clr_TR0;                                        //Timer stop
}

void hal_timer_timebase_resume(void)
{
	set_TR0;                                        //Timer run
}
*/

void hal_timer_timebase_reload(void)
{
	TH0 = HIBYTE(TIMER_DIV12_VALUE_1ms);
	TL0 = LOBYTE(TIMER_DIV12_VALUE_1ms);
}
#endif // HAL_TIMER_C
