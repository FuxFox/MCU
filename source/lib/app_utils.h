/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/07/10 14:23          V1.0             build this file
 *
 *******************************************************************************/
#ifndef APP_UTILS_H
#define APP_UTILS_H

/*! \defgroup app_utils_public Public
\ingroup app_utils
\brief 
\details 
* @{ */

#include "app_config.h"


//********************************* Module Config *******************************/
								




//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/

/*!*****************************************************************************
\brief  	get checksum
\param[in]	uint8_t * dat
\param[in]	uint32_t len
\return     uint32_t
******************************************************************************/
uint32_t app_utils_get_checksum(uint8_t* dat, uint32_t len);









/*! @}*/ //end of group app_utils
#endif // APP_UTILS_H
