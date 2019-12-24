/*******************************************************************************
 * Module: drv_wtn6040
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/09/29 16:03          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_wtn6040.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/09/29
  *******************************************************************************/
#ifndef DRV_WTN6040_H
#define DRV_WTN6040_H

  /*! \defgroup drv_wtn6040_public Public
  \ingroup drv_wtn6040
  \brief      Customized WTN6040 driver
  \details
  * @{ */

#include "app_globle.h"


  //********************************* Module Config *******************************/

#define DRV_WTN6040_DATA_PIN    AUDIO_DATA
#define DRV_WTN6040_BUSY_PIN    AUDIO_BUSY

#define DRV_WTN6040_DELAY_UINT_US        200        /*!< bus delay, in microsecond, range[40 ~ 400] */    

//********************************* Data Type ***********************************/

/*! Audio list */
typedef enum
{
    DRV_WTN6040_AUDIO_MUTE_20MS = 0,
    DRV_WTN6040_AUDIO_NUM_1,
    DRV_WTN6040_AUDIO_NUM_2,
    DRV_WTN6040_AUDIO_NUM_3,
    DRV_WTN6040_AUDIO_NUM_4,
    DRV_WTN6040_AUDIO_NUM_5,
    DRV_WTN6040_AUDIO_NUM_6,
    DRV_WTN6040_AUDIO_NUM_7,
    DRV_WTN6040_AUDIO_NUM_8,
    DRV_WTN6040_AUDIO_NUM_9,
    DRV_WTN6040_AUDIO_NUM_0,
    DRV_WTN6040_AUDIO_DOT,
    DRV_WTN6040_AUDIO_SUCCESSED,
    DRV_WTN6040_AUDIO_FAILED,
}drv_wtn6040_audio_enum;



//********************************* Public Interface ****************************/

void drv_wtn6040_init(void);

bool drv_wtn6040_is_busy(void);
void drv_wtn6040_mute_ms(uint16_t ms);
void drv_wtn6040_stop(void);
void drv_wtn6040_play(drv_wtn6040_audio_enum audio, bool continue_mode);
void drv_wtn6040_set_volume(uint8_t volume);

void drv_wtn6040_test(void);
//********************************* Private Interface ***************************/

static void drv_wtn6040_send_byte(uint8_t byte);



/*! @}*/ //end of group drv_wtn6040
#endif // DRV_WTN6040_H
