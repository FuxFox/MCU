/*******************************************************************************
 * Module: drv_wtn6040
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/09/29 16:03          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_wtn6040.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/09/29
  *******************************************************************************/
#ifndef DRV_WTN6040_C
#define DRV_WTN6040_C

#include "drv_wtn6040.h"


/*!*****************************************************************************
\brief      initialize
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_wtn6040_init(void)
{
    app_gpio_cfg_input(DRV_WTN6040_BUSY_PIN, NRF_GPIO_PIN_PULLUP);
    app_gpio_cfg_output(DRV_WTN6040_DATA_PIN);
    app_gpio_pin_set(DRV_WTN6040_DATA_PIN);

    drv_wtn6040_set_volume(15);
}

/*!*****************************************************************************
\brief      is busy ?
\details
\param[in]    void
\return     bool TRUE£ºyes, i am busy
******************************************************************************/
bool drv_wtn6040_is_busy(void)
{
    return !app_gpio_pin_read(DRV_WTN6040_BUSY_PIN);
}

/*!*****************************************************************************
\brief      send byte
\details
\param[in]    uint8_t byte
\return     void
******************************************************************************/
static void drv_wtn6040_send_byte(uint8_t byte)
{
    uint8_t mask;

    //start
    app_gpio_pin_clear(DRV_WTN6040_DATA_PIN);
    app_delay_ms(5);

    for (mask = 1; mask; mask <<= 1)
    {
        app_gpio_pin_set(DRV_WTN6040_DATA_PIN);

        if (byte & mask)
        {
            app_delay_us(DRV_WTN6040_DELAY_UINT_US * 3);
            app_gpio_pin_clear(DRV_WTN6040_DATA_PIN);
            app_delay_us(DRV_WTN6040_DELAY_UINT_US);
        }
        else
        {
            app_delay_us(DRV_WTN6040_DELAY_UINT_US);
            app_gpio_pin_clear(DRV_WTN6040_DATA_PIN);
            app_delay_us(DRV_WTN6040_DELAY_UINT_US * 3);
        }
    }

    app_gpio_pin_set(DRV_WTN6040_DATA_PIN);
}

/*!*****************************************************************************
\brief      set volume
\details        only in idle state that the volume can be change
\param[in]    uint8_t volume £º range[0~15], greater the value, larger the volume
\return     void
******************************************************************************/
void drv_wtn6040_set_volume(uint8_t volume)
{
    ASSERT(volume < 16);
    drv_wtn6040_send_byte(0xE0 + volume);
}

/*!*****************************************************************************
\brief      mute for several microsecond
\details
\param[in]    uint16_t ms : mute time, Must be an integral multiple of 10, range[10~2550]
\return     void
******************************************************************************/
void drv_wtn6040_mute_ms(uint16_t ms)
{
    ASSERT((ms <= 2550) && (ms >= 10));
    drv_wtn6040_send_byte(0xF8);
    //delay_ms(4);
    drv_wtn6040_send_byte(ms / 10);
}

/*!*****************************************************************************
\brief      stop playback
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_wtn6040_stop(void)
{
    drv_wtn6040_send_byte(0xFE);
}

/*!*****************************************************************************
\brief      playback
\details
\param[in]    drv_wtn6040_audio_enum audio £º audio id
\param[in]    bool continue_mode £º TRUE-> wait last audio done ; FALSE-> interject last audio
\return     void
******************************************************************************/
void drv_wtn6040_play(drv_wtn6040_audio_enum audio, bool continue_mode)
{
    NRF_LOG_DEBUG("play audio:%d", audio);

    if (continue_mode)
    {
        drv_wtn6040_send_byte(0xF3);
        app_delay_ms(2);
    }
    drv_wtn6040_send_byte(audio);
}

#if (TEST_ENABLE)
/*!*****************************************************************************
\brief      test
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_wtn6040_test(void)
{
    LOG_DEBUG("================== DRV_WTN6040 test ===============")
    LOG_DEBUG("is wtn6040 busy? : %d", drv_wtn6040_is_busy());
    drv_wtn6040_play(DRV_WTN6040_AUDIO_NUM_0, true);
    LOG_DEBUG("is wtn6040 busy? : %d", drv_wtn6040_is_busy());
    drv_wtn6040_play(DRV_WTN6040_AUDIO_MUTE_20MS, true);
    drv_wtn6040_play(DRV_WTN6040_AUDIO_NUM_0, true);
    drv_wtn6040_play(DRV_WTN6040_AUDIO_NUM_1, false);

    drv_wtn6040_set_volume(0);
    drv_wtn6040_play(DRV_WTN6040_AUDIO_NUM_0, true);

    drv_wtn6040_set_volume(15);

    drv_wtn6040_play(DRV_WTN6040_AUDIO_NUM_2, true);
    drv_wtn6040_play(DRV_WTN6040_AUDIO_NUM_3, true);
    drv_wtn6040_play(DRV_WTN6040_AUDIO_NUM_4, true);
    drv_wtn6040_play(DRV_WTN6040_AUDIO_NUM_5, true);
    drv_wtn6040_play(DRV_WTN6040_AUDIO_NUM_6, true);
    drv_wtn6040_play(DRV_WTN6040_AUDIO_NUM_7, true);
    drv_wtn6040_play(DRV_WTN6040_AUDIO_NUM_8, true);
    drv_wtn6040_play(DRV_WTN6040_AUDIO_NUM_9, true);

    drv_wtn6040_play(DRV_WTN6040_AUDIO_DOT, true);
    drv_wtn6040_play(DRV_WTN6040_AUDIO_FAILED, true);
    drv_wtn6040_play(DRV_WTN6040_AUDIO_SUCCESSED, true);

    LOG_DEBUG("is wtn6040 busy? : %d", drv_wtn6040_is_busy());
    app_delay_ms(500);
    LOG_DEBUG("is wtn6040 busy? : %d", drv_wtn6040_is_busy());

}
#endif
#endif // DRV_WTN6040_C
