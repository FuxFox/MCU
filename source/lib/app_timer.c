/*!*****************************************************************************
* @file     app_timer.c
* @brief
* @author	 FuxFox
* @version  V1.0
* @date     2020/08/18
*******************************************************************************/
#ifndef APP_TIMER_C
#define APP_TIMER_C

#include "app_timer.h"
#include "app_error.h"
#include "hal_timer.h"

#if defined(APP_TIMER_ENABLE)&&(APP_TIMER_ENABLE)

static app_timer_t* p_timer_head = NULL;
static app_timer_t m_app_timers[APP_TIMER_SOFTTIMER_MAX] = { 0 };
static bool m_is_module_initialized = false;


uint32_t app_timer_init(void)
{
    m_is_module_initialized = true;

    hal_timer_timebase_init(1);

    return 0;
}

void app_timer_start(app_timer_id_t timer_id, uint32_t delay_ms, void* param)
{
    assert_param(timer_id && delay_ms);

    timer_id->counter = delay_ms;
    timer_id->delay = delay_ms;
    timer_id->is_active = true;
    timer_id->is_pending = false;
    timer_id->callback_param = param;
}

void app_timer_stop(app_timer_id_t timer_id)
{
    assert_param(timer_id);

    timer_id->is_active = false;
    timer_id->is_pending = false;
}

void app_timer_pause(void)
{
    hal_timer_timebase_pause();
}

void app_timer_resume(void)
{
    hal_timer_timebase_resume();
}


app_timer_id_t app_timer_create(app_timer_mode_t mode, app_timer_handle callback, bool is_realtime)
{
    if (m_is_module_initialized)
    {
        assert_param(callback);

        for (uint8_t i = 0; i < APP_TIMER_SOFTTIMER_MAX; i++)
        {
            if (m_app_timers[i].callback == NULL)
            {
                m_app_timers[i].is_realtime = is_realtime;
                m_app_timers[i].is_repeat = mode;
                m_app_timers[i].callback = callback;
                m_app_timers[i].next = p_timer_head;
                if (p_timer_head)
                {
                    m_app_timers[i].next->last = &m_app_timers[i];
                }
                p_timer_head = &m_app_timers[i];
                return &m_app_timers[i];
            }
        }
    }
    return NULL;
}

void app_timer_delete(app_timer_id_t timer_id)
{
    assert_param(timer_id);

    if (timer_id && timer_id->callback)
    {
        if (timer_id == p_timer_head)
        {

            p_timer_head = timer_id->next;
            if (p_timer_head)
            {
                p_timer_head->last = NULL;
            }
        }
        else
        {
            timer_id->last->next = timer_id->next;
            if (timer_id->next)
            {
                timer_id->next->last = timer_id->last;
            }
        }

        memset(timer_id, 0, sizeof(app_timer_t));
    }
}


void app_timer_process_IT(void)
{
    app_timer_t* p_timer;

    for (p_timer = p_timer_head; p_timer; p_timer = p_timer->next)
    {
        if (p_timer->is_active)
        {
            p_timer->counter--;
            if (p_timer->counter == 0)
            {
                if (p_timer->is_realtime)
                {
                    p_timer->callback(p_timer->callback_param);
                }
                else
                {
                    p_timer->is_pending = true;
                }

                if (p_timer->is_repeat)
                    p_timer->counter = p_timer->delay;
                else
                    p_timer->is_active = false;
            }
        }
    }
}

void app_timer_process_poll(void)
{
    app_timer_t* p_timer;

    for (p_timer = p_timer_head; p_timer; p_timer = p_timer->next)
    {
        if (p_timer->is_pending)
        {
            p_timer->is_pending = false;
            p_timer->callback(p_timer->callback_param);
        }
    }
}

#endif // APP_TIMER_ENABLE
#endif // APP_TIMER_C
