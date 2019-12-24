/*******************************************************************************
 * LICENSE : Apache 2.0
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/29 17:46          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_rgb_led.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/11/29
  *******************************************************************************/
#ifndef DRV_RGB_LED_H
#define DRV_RGB_LED_H

/*! \defgroup drv_rgb_led_public Public
\ingroup drv_rgb_led
\brief         RGB LED driver
\details
* @{ */

#include "app_config.h"
#include "app_gpio.h"
//********************************* Module Config *******************************/





//********************************* Data Type ***********************************/

/*! LED active level */
typedef enum
{
    DRV_RGB_ACTIVE_LOW,         /*!< mean the led was common VCC */
    DRV_RGB_ACTIVE_HIGH,        /*!< mean the led was common GND */
}drv_RGB_active_level_t;

/*! LED color enum */
typedef enum
{
    DRV_RGB_OFF    = 0x00,
    DRV_RGB_BLUE   = (0x01 << 0),
    DRV_RGB_GREEN  = (0x01 << 1),
    DRV_RGB_RED    = (0x01 << 2),
    DRV_RGB_YELLOW = (DRV_RGB_RED | DRV_RGB_GREEN),
    DRV_RGB_PINK   = (DRV_RGB_RED | DRV_RGB_BLUE),
    DRV_RGB_CYAN   = (DRV_RGB_GREEN | DRV_RGB_BLUE),
    DRV_RGB_WHITE  = (DRV_RGB_RED | DRV_RGB_GREEN | DRV_RGB_BLUE),
}drv_RGB_color_t;

/*! RGB LED instance */
typedef const struct
{
    uint8_t pin_red;                  /*!< pin number of MCU that connected to LED red pin */
    uint8_t pin_green;                /*!< pin number of MCU that connected to LED green pin */
    uint8_t pin_blue;                 /*!< pin number of MCU that connected to LED blue pin */
    drv_RGB_active_level_t is_active_high;    /*! LED active level */
}drv_RGB_instance_t;


//********************************* Public Interface ****************************/

/*!*****************************************************************************
\brief  	use this macro to quickly define a LED instance

\param[in]	_name       name of instance
\param[in]	_pin_red    pin number of MCU that connected to LED red pin
\param[in]	_pin_green  pin number of MCU that connected to LED green pin
\param[in]	_pin_blue   pin number of MCU that connected to LED blue pin
\param[in]	_active_level   LED active level, \ref drv_RGB_active_level_t
\return     
\retval	
*******************************************************************************/
#define DRV_RGB_INSTANCE(_name, _pin_red, _pin_green, _pin_blue, _active_level)        \
    drv_RGB_instance_t _name = {_pin_red, _pin_green, _pin_blue, _active_level}

void drv_rgb_led_init(drv_RGB_instance_t* instance);
void drv_rgb_led_set(drv_RGB_instance_t* instance, drv_RGB_color_t color);
drv_RGB_color_t drv_rgb_led_get(drv_RGB_instance_t* instance);

//********************************* Private Interface ***************************/





/*! @}*/ //end of group drv_rgb_led
#endif // DRV_RGB_LED_H
