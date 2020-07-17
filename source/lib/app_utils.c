/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/07/10 14:21          V1.0             build this file
 *
 *******************************************************************************/
#ifndef APP_UTILS_C
#define APP_UTILS_C

#include "app_utils.h"

/*!*****************************************************************************
\brief  	initialize
\details
\param[in]	void
\return     void
******************************************************************************/
void app_utils_init(void)
{

}

uint32_t app_utils_get_checksum(uint8_t* dat, uint32_t len)
{
    uint32_t sum = 0;

    while (len--)
    {
        sum += *dat++;
    }
    return sum;
}




#endif // APP_UTILS_C
