/*!*****************************************************************************
* @file     app_utils.c
* @brief
* @author	 FuxFox
* @version  V1.0
* @date     2020/08/18
*******************************************************************************/
#ifndef APP_UTILS_C
#define APP_UTILS_C

#include "app_utils.h"

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

uint8_t app_utils_get_array_member_index_uint8(uint8_t member, uint8_t* arr, uint8_t array_size)
{
	uint8_t i;

	for (i = 0; i < array_size; i++)
	{
		if (arr[i] == member)
		{
			return i;
		}
	}

	return -1;
}


#endif // APP_UTILS_C
