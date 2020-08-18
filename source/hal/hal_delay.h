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


/*================================= Module Config ============================*/

#define HAL_DELAY_SYSTEM_CLK    16000000UL
#define HAL_DELAY_CLK_UNIT_US   (HAL_DELAY_SYSTEM_CLK / 1000000)
#define HAL_DELAY_CLK_UNIT_MS   (HAL_DELAY_SYSTEM_CLK / 1000)

/*================================= Data Type ================================*/





/*================================= Public Interface =========================*/


/*!*****************************************************************************
* @brief      initialize the soft delay function
*             call this function after system clock initialization.
* @return     void
*******************************************************************************/
void hal_delay_init(void);

/*!*****************************************************************************
* @brief      blocking delay in us
* @param[in]    uint32_t nus
* @return     void
*******************************************************************************/
void hal_delay_us(uint32_t nus);

/*!*****************************************************************************
* @brief      blocking delay in ms
* @param[in]    uint32_t nms
* @return     void
*******************************************************************************/
void hal_delay_ms(uint32_t nms);




/** @} */ //end of group hal_delay
#endif // HAL_DELAY_H
