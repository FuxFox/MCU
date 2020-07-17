/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/27 10:36          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * @file     app_button.c
 * @brief    
 * @author   FuxFox
 * @version  V1.0
 * @date       2019/11/27
 *******************************************************************************/
#ifndef APP_BUTTON_C
#define APP_BUTTON_C

#include "app_button.h"

#if defined(APP_BUTTON_ENABLE) && (APP_BUTTON_ENABLE)

static app_timer_id_t m_button_scan_timer;
static app_button_t *m_buttons;

/*!*****************************************************************************
* @brief      initialize
* @param[in]    app_button_t * init            The button list to be initialized
* @return     void
******************************************************************************/
void app_button_init(app_button_t *init)
{
    app_button_cfg_t *p_button_cfg;

    m_buttons = init;

    for (uint8_t i = 0; i < m_buttons->button_cnt; i++)
    {
        p_button_cfg = m_buttons->button_list + i;
        assert_param(p_button_cfg->callback);
        app_gpio_cfg_input(p_button_cfg->button_pin, p_button_cfg->pin_pull);
    }

    m_button_scan_timer = app_timer_create(APP_TIMER_MODE_REPEATED, app_button_scan, APP_BUTTON_REALTIME_MODE);
    assert_param(m_button_scan_timer);
}

/*!*****************************************************************************
* @brief      button scan in timer interrupt
* @param[in]    void
* @return     void
******************************************************************************/
static void app_button_scan(void)
{
    uint8_t i;
    app_button_cfg_t *p_button_cfg;
    app_button_sta_t *p_button_sta;

    for (i = 0; i < m_buttons->button_cnt; i++)
    {
        p_button_cfg = m_buttons->button_list + i;
        p_button_sta = m_buttons->button_sta + i;

        if ((app_button_active_level_t)app_gpio_pin_read(p_button_cfg->button_pin) == p_button_cfg->active_level)
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

/*!*****************************************************************************
* @brief      enable button detection
* @param[in]    void
* @return     void
******************************************************************************/
void app_button_enable(void)
{
    app_timer_start(m_button_scan_timer, APP_BUTTON_SCAN_INTERVAL);
}

/*!*****************************************************************************
* @brief      disable button detection
* @param[in]    void
* @return     void
******************************************************************************/
void app_button_disable(void)
{
    app_timer_stop(m_button_scan_timer);
}

#endif
#endif // APP_BUTTON_C
