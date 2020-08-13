/*******************************************************************************
 *
 * Module: lib_delay
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/12 11:31          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     delay.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/12
  *******************************************************************************/
#ifndef HAL_DELAY_C
#define HAL_DELAY_C

#include "hal_delay.h"
#if defined(HAL_DELAY_ENABLE)&&(HAL_DELAY_ENABLE)

void hal_delay_init(void)
{
    //TODO
}

void hal_delay_us(uint32_t nus)
{
	uint16_t reload = 65536 - 4 * nus + 80;//+80Îó²î²¹³¥

	clr_T2DIV2;																	//Timer2 Clock = Fsys/4 
	clr_T2DIV1;
	set_T2DIV0;
	clr_TF2;
	set_TR2;                                		//Start Timer2
	TL2 = LOBYTE(reload);
	TH2 = HIBYTE(reload);
	while (TF2 != 1);                   		//Check Timer2 Time-Out Flag
	clr_TR2;                                		//Stop Timer2
}


void hal_delay_ms(uint32_t nms)
{
	while (nms--)
	{
		hal_delay_us(1000);
	}
}

#endif 


#endif // DELAY_C








































