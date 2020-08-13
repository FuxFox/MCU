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

/*! \defgroup app_utils
* \ingroup lib
* \brief
* \details
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

/*!*****************************************************************************
\brief  	get array member index
\param[in]	uint8_t member : member value
\param[in]	uint8_t arr : pointer to array
\param[in]	uint8_t array_size : max number of member in <arr>
\return     uint8_t : return index if member found, or -1 if not found
******************************************************************************/
uint8_t app_utils_get_array_member_index_uint8(uint8_t member, uint8_t* arr, uint8_t array_size);







/*! @}*/ //end of group app_utils
#endif // APP_UTILS_H
