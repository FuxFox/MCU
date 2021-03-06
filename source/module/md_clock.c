/*!*****************************************************************************
* @file     md_clock.c
* @brief
* @author   FuxFox
* @version  V1.0
* @date     2019/09/03
*******************************************************************************/
#ifndef MD_CLOCK_C
#define MD_CLOCK_C

#include "md_clock.h"

static md_clock_struct m_clock;
static md_clock_alarm_struct m_alarms[MD_CLOCK_ALARM_MAX];
static md_clock_callback m_callback;
static void md_clock_callback_NULL(md_clock_msg_enum msg, md_clock_alarm_struct* alarm);
static void md_clock_sec_handler(void* context);

APP_TIMER_DEF(m_sec_timer);

void md_clock_init(md_clock_callback callback)
{
    ret_code_t err;

    memset(&m_clock, 0, sizeof(md_clock_struct));
    m_callback = callback ? callback : md_clock_callback_NULL;
    err = app_timer_create(&m_sec_timer, APP_TIMER_MODE_REPEATED, md_clock_sec_handler);
    APP_ERROR_CHECK(err);
    app_timer_start(m_sec_timer, APP_TIMER_TICKS(1000), NULL);
}

/*!*****************************************************************************
* @brief  	second tick handler
* @param[in]	void * context
* @return     void
*******************************************************************************/
static void md_clock_sec_handler(void* context)
{
    if (++m_clock.tm_sec >= 60)
    {
        m_clock.tm_sec = 0;
        if (++m_clock.tm_min >= 60)
        {
            m_clock.tm_min = 0;
            if (++m_clock.tm_hour >= 24)
            {
                m_clock.tm_hour = 0;
            }
            m_callback(MD_CLOCK_MSG_STEP_HOUR, NULL);
        }

        md_clock_is_time_to_alarm();
        m_callback(MD_CLOCK_MSG_STEP_MINUTE, NULL);
    }
}

void md_clock_time_sync(md_clock_struct* time)
{
    memcpy(&m_clock, time, sizeof(md_clock_struct));
}

bool md_clock_is_time_to_alarm(void)
{
    uint8_t i;

    for (i = 0; i < MD_CLOCK_ALARM_MAX; i++)
    {
        if ((m_alarms[i].hour == m_clock.tm_hour) && (m_alarms[i].minute == m_clock.tm_min))
        {
            m_callback(MD_CLOCK_MSG_ALARM_EXPIRE, &m_alarms[i]);
            return true;
        }
    }

    return false;
}

void md_clock_alarm_add(char* id, uint8_t hour, uint8_t min)
{
    uint8_t i;

    for (i = 0; i < MD_CLOCK_ALARM_MAX; i++)
    {
        if (m_alarms[i].id[0] == 0)
        {
            strncpy(m_alarms[i].id, id, MD_CLOCK_ALARM_ID_LEN);
            m_alarms[i].id[MD_CLOCK_ALARM_ID_LEN] = '\0';
            m_alarms[i].hour = hour;
            m_alarms[i].minute = min;

            NRF_LOG_DEBUG("md_clock: add alarm at %d:%d", hour, min);
            return;
        }
    }
}

void md_clock_alarm_delete(char* id)
{
    uint8_t i;

    for (i = 0; i < MD_CLOCK_ALARM_MAX; i++)
    {
        if (!strcmp(m_alarms[i].id, id))
        {
            memset(&m_alarms[i], 0, sizeof(m_alarms[0]));
            NRF_LOG_DEBUG("md_clock: delete alarm id: %d", id);
        }
    }
}

void md_clock_alarm_delete_all(void)
{
    uint8_t i;

    for (i = 0; i < MD_CLOCK_ALARM_MAX; i++)
    {
        if (m_alarms[i].id)
        {
            memset(&m_alarms[i], 0, sizeof(m_alarms[0]));
        }
    }
}

md_clock_struct* md_clock_get(void)
{
    return &m_clock;
}

time_t md_clock_timestamp_get(void)
{
    return (mktime(&m_clock) - 8 * 60 * 60);
}

/*!*****************************************************************************
* @brief      NULL
* @details
* @param[in]    void
* @return     void
*******************************************************************************/
static void md_clock_callback_NULL(md_clock_msg_enum msg, md_clock_alarm_struct* alarm)
{

}
#endif // MD_CLOCK_C
