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

/** 
* @defgroup hal_delay
* @ingroup HAL
* @brief Blocking-Delay HAL Template
* @details 
* @{ */

#include "app_config.h"

#include <sleep.h>

/*================================= Module Config ============================*/


/*================================= Data Type ================================*/





/*================================= Public Interface =========================*/


/*!*****************************************************************************
* @brief      initialize the soft delay function
*             call this function after system clock initialization.
* @return     void
*******************************************************************************/
#define hal_delay_init()

/*!*****************************************************************************
* @brief      blocking delay in us
* @param[in]    uint64_t nus
* @return     void
*******************************************************************************/
#define hal_delay_us(nus) usleep(nus)

/*!*****************************************************************************
* @brief      blocking delay in ms
* @param[in]    uint64_t nms
* @return     void
*******************************************************************************/
#define hal_delay_ms(nms) msleep(nms)

/*!*****************************************************************************
* @brief      blocking delay in s
* @param[in]    uint64_t ns
* @return     void
*******************************************************************************/
#define hal_delay_s(ns)sleep(ns)



/** @} */ //end of group hal_delay
#endif // HAL_DELAY_H
