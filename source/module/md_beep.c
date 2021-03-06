/*!*****************************************************************************
* @file     md_beep.c
* @brief
* @author   FuxFox
* @version  V1.0
* @date     2019/07/26
*******************************************************************************/
#ifndef MD_BEEP_C
#define MD_BEEP_C

#include "md_beep.h"
#include "drv_buzzer.h"

APP_TIMER_DEF(m_beep_timer_id);  /**< Polling timer id. */

typedef struct
{
    bool beep_enable;           /**< is beeping ? */
    uint16_t on_time;           /**< buzzer on time, in ms */
    uint16_t off_time;          /**< buzzer off time, in ms */
    uint16_t sequence_interval; /**< interval between sequences, in ms */
    uint8_t beep_cnt;           /**< counter of beeped */
    uint8_t beep_num;           /**< number of beep per sequence */
    uint8_t sequence_num;       /**< number of sequence */
}md_beep_sta_struct;

static md_beep_sta_struct m_beep_cfg;
static void md_beep_timer_handler(void* p_context);

void md_beep_init(void)
{
    ret_code_t err_code;

    memset(&m_beep_cfg, 0, sizeof(m_beep_cfg));
    err_code = app_timer_create(&m_beep_timer_id, APP_TIMER_MODE_SINGLE_SHOT, md_beep_timer_handler);
    APP_ERROR_CHECK(err_code);
}

/*!*****************************************************************************
* @brief      app_timer handler, turn the buzzer on or off
* @param[in]    void * p_context
* @return     void
*******************************************************************************/
static void md_beep_timer_handler(void* p_context)
{
    if (drv_buzzer_is_on())
    {
        drv_buzzer_off();

        if (m_beep_cfg.beep_cnt == 0)
        {
            if (m_beep_cfg.sequence_num == 0)
            {
                m_beep_cfg.beep_enable = false;
            }
            else
            {
                m_beep_cfg.sequence_num--;
                m_beep_cfg.beep_cnt = m_beep_cfg.beep_num;
                app_timer_start(m_beep_timer_id, APP_TIMER_TICKS(m_beep_cfg.sequence_interval + m_beep_cfg.off_time), NULL);
            }
        }
        else
        {
            app_timer_start(m_beep_timer_id, APP_TIMER_TICKS(m_beep_cfg.off_time), NULL);
        }
        //                NRF_LOG_DEBUG("beeper off!");
    }
    else
    {
        m_beep_cfg.beep_cnt--;
        drv_buzzer_on();
        app_timer_start(m_beep_timer_id, APP_TIMER_TICKS(m_beep_cfg.on_time), NULL);
    }
}

void md_beep_beep(void)
{
    md_beep_beepEx(MD_BEEP_ON_TIME_DEF);
}

void md_beep_beepEx(uint16_t beep_time)
{
    md_beep_stop();

    m_beep_cfg.beep_enable = true;
    m_beep_cfg.on_time = beep_time;
    m_beep_cfg.beep_cnt = 1;
    app_timer_start(m_beep_timer_id, APP_TIMER_TICKS(1), NULL);
}

void md_beep_sequence(uint16_t on_time, uint16_t off_time, uint16_t beep_num)
{
    md_beep_sequenceEx(on_time, off_time, beep_num, 0, 0);
}

void md_beep_sequenceEx(uint16_t on_time, uint16_t off_time, uint8_t beep_num, uint16_t seq_interval, uint8_t seq_num)
{
    md_beep_stop();

    m_beep_cfg.beep_enable = true;
    m_beep_cfg.on_time = on_time;
    m_beep_cfg.off_time = off_time;
    m_beep_cfg.sequence_interval = seq_interval;
    m_beep_cfg.beep_num = beep_num;
    m_beep_cfg.beep_cnt = beep_num;
    m_beep_cfg.sequence_num = seq_num;

    app_timer_start(m_beep_timer_id, APP_TIMER_TICKS(1), NULL);     //start timer at 1 ms to quickly goto timer handler
}

void md_beep_stop(void)
{
    if (m_beep_cfg.beep_enable)
    {
        app_timer_stop(m_beep_timer_id);
        drv_buzzer_off();
        memset(&m_beep_cfg, 0, sizeof(m_beep_cfg));
    }
}

bool md_beep_is_on(void)
{
    return m_beep_cfg.beep_enable;
}


#endif // MD_beep_C
