/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/08/13 16:00          V1.0             build this file
 *
 *******************************************************************************/
#ifndef APP_LOG_C
#define APP_LOG_C

#include "app_log.h"

#if (defined(APP_LOG_ENABLE) && APP_LOG_ENABLE)

void app_log_init(void)
{

}

void app_log_print_array_to_hex(uint8_t* str,uint8_t *arry, uint8_t size)
{
		printf("%s", str);

		while (size--)
		{
				printf("0x%x,", *arry++);
		}
		printf("\r\n");
}

#endif // APP_LOG_ENABLE

#endif // APP_LOG_C
