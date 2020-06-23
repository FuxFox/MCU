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

/*! \defgroup hal_delay_public Public
\ingroup hal_delay
\brief 
\details 
* @{ */

#include "app_config.h"


//********************************* Module Config *******************************/
								




//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/


void hal_delay_init(void);
void hal_delay_us(uint32_t nus);


//********************************* Private Interface ***************************/





/*! @}*/ //end of group hal_delay
#endif // HAL_DELAY_H
