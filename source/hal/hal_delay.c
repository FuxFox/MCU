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

/*!*****************************************************************************
\brief      initialize the soft delay function
            call this function after system clock initialization.

\return     void
******************************************************************************/
void hal_delay_init(void)
{
    //TODO
}

/*!*****************************************************************************
\brief      blocked delay in us

\param[in]    uint32_t nus
\return     void
******************************************************************************/
void hal_delay_us(uint32_t nus)
{
    //TODO
}


#endif // DELAY_C


#endif // DELAY_C








































