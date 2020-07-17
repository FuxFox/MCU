/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/07/08 16:05          V1.0             build this file
 *
 *******************************************************************************/
#ifndef APP_JSON_C
#define APP_JSON_C

#include "app_json.h"

/*!*****************************************************************************
\brief  	initialize
\details
\param[in]	void
\return     void
******************************************************************************/
void app_json_init(void)
{

}

void app_json_get_value_by_key(void)
{

}

uint8_t* app_json_find_value_by_key(uint8_t* src, uint8_t* key)
{
	uint8_t* ptr_value = strstr(src, key);

	if (ptr_value)
	{
		ptr_value += strlen(key);
	}

	return ptr_value;
}

bool app_json_is_str_match(uint8_t* src, uint8_t* key, uint8_t* except_value)
{
	uint8_t* cur_ptr = app_json_find_value_by_key(src, key);

	if (cur_ptr)
	{
		if (*cur_ptr == '"')//is string
		{
			if (strstr(cur_ptr, except_value))
				return true;
		}
	}

	return false;
}

uint8_t app_json_get_int8(uint8_t* src, uint8_t* key)
{
	uint8_t* cur_ptr = app_json_find_value_by_key(src, key);
	uint8_t i;
	uint8_t num_str[4];

	if (cur_ptr)
	{
		for (i = 0; i < 3; i++)
		{
			if ((cur_ptr[i] == ',') || (cur_ptr[i] == '\0'))
			{
				break;
			}
			num_str[i] = cur_ptr[i];
		}

		if (i)
		{
			num_str[i] = '\0';
			return atoi(num_str);
		}
	}

	return 0;
}





#endif // APP_JSON_C
