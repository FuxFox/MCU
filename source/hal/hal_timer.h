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

/*! \defgroup hal_timer
\brief	 Timer HAL Template
\details 
* @{ */

#include "app_config.h"


//********************************* Module Config *******************************/
								




//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/


/*!*****************************************************************************
\brief  	initialize timebase ,now used for app_timer
\param[in]	uint16_t ms : interval of ticks.
\return     void
******************************************************************************/
void hal_timer_timebase_init(uint16_t ms);

/*!*****************************************************************************
\brief  	stop timebase
\param[in]	void
\return     void
******************************************************************************/
void hal_timer_timebase_pause(void);

/*!*****************************************************************************
\brief  	resume timebase
\param[in]	void
\return     void
******************************************************************************/
void hal_timer_timebase_resume(void);




/*! @}*/ //end of group hal_timer
#endif // HAL_TIMER_H
