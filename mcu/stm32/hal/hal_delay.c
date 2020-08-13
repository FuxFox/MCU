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
#include "stm32f1xx_hal_conf.h"
#if defined(HAL_DELAY_ENABLE)&&(HAL_DELAY_ENABLE)

static uint8_t  fac_us = 0;  //systick per us               

void hal_delay_init(void)
{
#if defined(HAL_ENABLED)&&(HAL_ENABLED)
    fac_us = SystemCoreClock / (1000000U / HAL_GetTickFreq());
#else
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);
    fac_us = SystemCoreClock / 8000000;
    //fac_ms=(uint16_t)fac_us*1000;                     
    SysTick->LOAD = 0xffffff;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
#endif
}

void hal_delay_ms(uint32_t nms)
{
    while (nms--)
    {
        hal_delay_us(1000);
    };
}


void hal_delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt;
    uint32_t reload = SysTick->LOAD;

    ticks = nus * fac_us;
    tcnt = 0;
    told = SysTick->VAL;
    while (ticks)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
                tcnt += told - tnow;        //systick is count down.
            else
                tcnt += reload - tnow + told;
            told = tnow;
            if (tcnt >= ticks)
                break;
        }
    };
}


uint16_t hal_delay_systick_per_us(void)
{
    return fac_us;
}

#endif 


#endif // DELAY_C








































