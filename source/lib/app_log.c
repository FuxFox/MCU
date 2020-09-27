/*!*****************************************************************************
* @file     app_log.c
* @brief
* @author	 FuxFox
* @version  V1.0
* @date     2020/08/18
*******************************************************************************/
#ifndef APP_LOG_C
#define APP_LOG_C

#include "app_log.h"

#if (defined(APP_LOG_ENABLE) && APP_LOG_ENABLE)

void app_log_init(void)
{

}

void app_log_print_array_to_hex(uint8_t* str, uint8_t* arry, uint8_t size)
{
	printf("%s", str);

	while (size--)
	{
		printf("0x%x,", *arry++);
	}
	printf("\r\n");
}

#endif // APP_LOG_ENABLE

#if APP_LOG_ASSERT_ENABLE
void app_error_assert(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,*/
	APP_LOG_ERROR("Wrong parameters value: file %s on line %d\r\n", file, line);
	while (1);
}
#endif

#endif // APP_LOG_C
