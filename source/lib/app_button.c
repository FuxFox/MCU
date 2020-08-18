/*!*****************************************************************************
* @file     app_button.c
* @brief    
* @author   FuxFox
* @version  V1.0
* @date     2019/11/27
*******************************************************************************/
#ifndef APP_BUTTON_C
#define APP_BUTTON_C

#include "app_button.h"
#include "app_timer.h"
#include "app_error.h"
#include "app_utils.h"

#if defined(APP_BUTTON_ENABLE) && (APP_BUTTON_ENABLE)
#if APP_BUTTON_LINEAR_ENABLE
static app_timer_id_t m_linear_scan_timer;
static app_button_linear_t *m_linear_keyboard;
static void app_button_linear_scan(void*);

void app_button_linear_init(app_button_linear_t *linear)
{
	uint8_t i;
    app_button_linear_cfg_t *p_button_cfg;

	assert_param(linear);
	m_linear_keyboard = linear;
	i = linear->button_cnt;
	p_button_cfg = linear->button_list;

	while (i--)
	{
        assert_param(p_button_cfg->callback);
		hal_gpio_cfg_input(p_button_cfg->button_pin, p_button_cfg->pin_pull);
		p_button_cfg++;
	}

	m_linear_scan_timer = app_timer_create(APP_TIMER_MODE_REPEATED, app_button_linear_scan, APP_BUTTON_REALTIME_MODE);
    assert_param(m_linear_scan_timer);
	app_timer_start(m_linear_scan_timer, APP_BUTTON_SCAN_INTERVAL, NULL);
}

/*!*****************************************************************************
* @brief      button scan in timer interrupt
* @param[in]    void
* @return     void
*******************************************************************************/
static void app_button_linear_scan(void* param)
{
    uint8_t i;
    app_button_linear_cfg_t *p_button_cfg;
    app_button_linear_sta_t *p_button_sta;

    for (i = 0; i < m_linear_keyboard->button_cnt; i++)
    {
        p_button_cfg = m_linear_keyboard->button_list + i;
        p_button_sta = m_linear_keyboard->button_sta + i;

        if ((app_button_active_level_t)hal_gpio_pin_read(p_button_cfg->button_pin) == p_button_cfg->active_level)
        {
            if (p_button_sta->is_press)
            {
                p_button_sta->long_press_cnt += APP_BUTTON_SCAN_INTERVAL;
                if (p_button_sta->long_press_cnt >= APP_BUTTON_LONG_PRESS_DETECT_DELAY)
                {
					p_button_sta->long_press_cnt = 0;
                    p_button_cfg->callback(p_button_cfg->button_pin, APP_BUTTON_LONG_PRESS);
                }
            }
            else
            {
                p_button_sta->is_press = true;
                p_button_sta->long_press_cnt = 0;
                p_button_cfg->callback(p_button_cfg->button_pin, APP_BUTTON_PRESS);
            }
        }
        else
        {
            if (p_button_sta->is_press)
            {
                p_button_sta->is_press = false;
                p_button_cfg->callback(p_button_cfg->button_pin, APP_BUTTON_RELEASE);
            }
        }
    }
}

void app_button_linear_enable(void)
{
    app_timer_start(m_linear_scan_timer, APP_BUTTON_SCAN_INTERVAL, NULL);
}

void app_button_linear_disable(void)
{
    app_timer_stop(m_linear_scan_timer);
}

bool app_button_linear_is_pressed(uint8_t button_pin)
{
	uint8_t i = m_linear_keyboard->button_cnt;
    app_button_linear_cfg_t* button_cfg = m_linear_keyboard->button_list;

    while (i--)
    {
		if (button_cfg->button_pin == button_pin)
		{
			return (hal_gpio_pin_read(button_pin) == (bool)button_cfg->active_level);
		}
        button_cfg++;
    }

    return false;
}

#endif // APP_BUTTON_LINEAR_ENABLE


#if APP_BUTTON_MATRIX_ENABLE
static app_timer_id_t m_matrix_scan_timer;
static app_button_matrix_t* m_matrix_keyboard;
static void app_button_matrix_scan(void*);

void app_button_matrix_init(app_button_matrix_t* matrix)
{
	uint8_t i;
	app_button_matrix_cfg_t* matrix_cfg = matrix->button_cfg;

	assert_param(matrix);
	assert_param(matrix->button_cfg->matrix_callback);
	m_matrix_keyboard = matrix;

	for (i = 0; i < APP_BUTTON_MATRIX_OUTPUT_BANDWIDE; i++)
	{
		hal_gpio_cfg_output(matrix_cfg->output_pins[i]);
		hal_gpio_pin_write(matrix_cfg->output_pins[i], matrix_cfg->active_level);
	}

	for (i = 0; i < APP_BUTTON_MATRIX_INPUT_BANDWIDE; i++)
	{
		hal_gpio_cfg_input(matrix_cfg->input_pins[i], matrix_cfg->input_pin_pull);
	}

	m_matrix_scan_timer = app_timer_create(APP_TIMER_MODE_REPEATED, app_button_matrix_scan, APP_BUTTON_REALTIME_MODE);
	assert_param(m_matrix_scan_timer);
	app_timer_start(m_matrix_scan_timer, APP_BUTTON_SCAN_INTERVAL, (void*)matrix);
}

/*!*****************************************************************************
* @brief  	Matrix keyboard scan
* @param[in]	void* para : pointer to app_button_matrix_t
* @return     void
*******************************************************************************/
static void app_button_matrix_scan(void* para)
{
	app_button_matrix_t* matrix = (app_button_matrix_t*)para;
	app_button_matrix_cfg_t* matrix_cfg = matrix->button_cfg;
	app_button_matrix_sta_t* matrix_sta = matrix->button_sta;
	uint32_t keys_state = 0;
	uint32_t bit_mask, bit_tmp;
	uint8_t i, j;

	//Matrix scan
	for (i = 0; i < APP_BUTTON_MATRIX_INPUT_BANDWIDE; i++)
	{
		if ((app_button_active_level_t)hal_gpio_pin_read(matrix_cfg->input_pins[i]) == matrix_cfg->active_level)
		{
			for (j = 0; j < APP_BUTTON_MATRIX_OUTPUT_BANDWIDE; j++)//close all output channel
			{
				hal_gpio_pin_write(matrix_cfg->output_pins[j], !matrix_cfg->active_level);
			}
#if APP_BUTTON_MATRIX_ALLOW_GND_AS_OUTPUT_LINE
			//If still active after close all channel,that mean an output line was connected to GND.		
			if ((app_button_active_level_t)hal_gpio_pin_read(matrix_cfg->input_pins[i]) == matrix_cfg->active_level)
			{
				j = app_utils_get_array_member_index_uint8(APP_BUTTON_MATRIX_GND_LINE,
					(uint8_t*)matrix_cfg->output_pins, APP_BUTTON_MATRIX_OUTPUT_BANDWIDE);// get output line (GND)

				keys_state |= 1 << APP_BUTTON_MATRIX_KEY_ID(i, j);
			}
			else
#endif
			{
				for (j = 0; j < APP_BUTTON_MATRIX_OUTPUT_BANDWIDE; j++)//scan output line
				{
					hal_gpio_pin_write(matrix_cfg->output_pins[j], matrix_cfg->active_level);
					if ((app_button_active_level_t)hal_gpio_pin_read(matrix_cfg->input_pins[i]) == matrix_cfg->active_level)
					{
						keys_state |= 1 << APP_BUTTON_MATRIX_KEY_ID(i, j);
					}
					else
					{
						keys_state &= ~(1 << APP_BUTTON_MATRIX_KEY_ID(i, j));
					}
					hal_gpio_pin_write(matrix_cfg->output_pins[j], !matrix_cfg->active_level);
				}
			}

			for (j = 0; j < APP_BUTTON_MATRIX_OUTPUT_BANDWIDE; j++)//open all output channel
			{
				hal_gpio_pin_write(matrix_cfg->output_pins[j], matrix_cfg->active_level);
			}
		}
	}

// #if APP_BUTTON_MATRIX_COMBINATION_SUPPORT
// 	//check combination
// 	app_button_matrix_combination_cfg_t* combination = &matrix_cfg->combination;
// 	if (keys_state || matrix_sta->keys_pressed_mark)
// 	{
// 		for (i = 0; i < ARRAY_SIZE(combination->combination_list); i++)
// 		{
// 			if (combination->combination_list[i] == keys_state)
// 			{
// 				if (combination->pressed_time_cnt >= APP_BUTTON_LONG_PRESS_DETECT_DELAY)
// 				{
// 					combination->pressed_time_cnt = 0;
// 					combination->combination_callback(keys_state, APP_BUTTON_LONG_PRESS);
// 				}
// 				else if (combination->pressed_time_cnt)
// 				{
// 					combination->pressed_time_cnt += APP_BUTTON_SCAN_INTERVAL;
// 				}
// 				else
// 				{
// 					combination->pressed_time_cnt = APP_BUTTON_SCAN_INTERVAL;
// 					combination->combination_callback(keys_state, APP_BUTTON_PRESS);
// 				}
// 			}
// 			else if (combination->combination_list[i] == matrix_sta->keys_pressed_mark)
// 			{
// 
// 			}
// 		}
// 	}
// #endif

	//check state change
	bit_tmp = keys_state ^ matrix_sta->keys_pressed_mark;
	if (bit_tmp)
	{
		for (i = 0, bit_mask = 1;
			i < APP_BUTTON_MATRIX_INPUT_BANDWIDE * APP_BUTTON_MATRIX_OUTPUT_BANDWIDE;
			i++, bit_mask <<= 1)
		{
			if (bit_tmp & bit_mask)
			{
				matrix_cfg->matrix_callback(i, 
					(matrix_sta->keys_pressed_mark & bit_mask) ? APP_BUTTON_RELEASE : APP_BUTTON_PRESS,
					keys_state);
			}
		}
	}

	//check long press
	bit_tmp = keys_state & matrix_sta->keys_pressed_mark;
	if (bit_tmp)
	{
		for (i = 0, bit_mask = 1;
			i < APP_BUTTON_MATRIX_INPUT_BANDWIDE * APP_BUTTON_MATRIX_OUTPUT_BANDWIDE;
			i++, bit_mask <<= 1)
		{
			if (bit_tmp & bit_mask)
			{
				matrix_sta->long_press_cnt[i] += APP_BUTTON_SCAN_INTERVAL;
				if (matrix_sta->long_press_cnt[i] >= APP_BUTTON_LONG_PRESS_DETECT_DELAY)
				{
					matrix_sta->long_press_cnt[i] = 0;
					matrix_cfg->matrix_callback(i, APP_BUTTON_LONG_PRESS, keys_state);
				}
			}
		}
	}

	matrix_sta->keys_pressed_mark = keys_state;
}

void app_button_matrix_enable(void)
{
	app_timer_start(m_matrix_scan_timer, APP_BUTTON_SCAN_INTERVAL, NULL);
}

void app_button_matrix_disable(void)
{
	app_timer_stop(m_matrix_scan_timer);
}

#endif // APP_BUTTON_MATRIX_ENABLE
#endif // APP_BUTTON_ENABLE
#endif // APP_BUTTON_C
