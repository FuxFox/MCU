/*******************************************************************************
 * LICENSE : Apache 2.0
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/29 17:47          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_rgb_led.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/11/29
  *******************************************************************************/
#ifndef DRV_RGB_LED_C
#define DRV_RGB_LED_C

#include "drv_rgb_led.h"

/*!*****************************************************************************
\brief      initialize
\details
\param[in]    drv_RGB_instance_t * instance
\return     void
******************************************************************************/
void drv_rgb_led_init(drv_RGB_instance_t* instance)
{
    app_gpio_cfg_output(instance->pin_red);
    app_gpio_cfg_output(instance->pin_green);
    app_gpio_cfg_output(instance->pin_blue);
}


/*!*****************************************************************************
\brief      set led color

\param[in]    drv_RGB_instance_t * instance
\param[in]    drv_RGB_color_t color
\return     void
******************************************************************************/
void drv_rgb_led_set(drv_RGB_instance_t* instance, drv_RGB_color_t color)
{
    if (instance->is_active_high)
    {
    }
    else
    {
        color = ~color;
    }

    app_gpio_pin_write(instance->pin_red, color & DRV_RGB_RED);
    app_gpio_pin_write(instance->pin_green, color & DRV_RGB_GREEN);
    app_gpio_pin_write(instance->pin_blue, color & DRV_RGB_BLUE);
}

/*!*****************************************************************************
\brief      get current led color

\param[in]    drv_RGB_instance_t * instance
\return     drv_RGB_color_t
******************************************************************************/
drv_RGB_color_t drv_rgb_led_get(drv_RGB_instance_t* instance)
{
    drv_RGB_color_t color = DRV_RGB_OFF;

    color |= app_gpio_pin_read(instance->pin_red) ? DRV_RGB_RED : DRV_RGB_OFF;
    color |= app_gpio_pin_read(instance->pin_green) ? DRV_RGB_GREEN : DRV_RGB_OFF;
    color |= app_gpio_pin_read(instance->pin_blue) ? DRV_RGB_BLUE : DRV_RGB_OFF;

    return    (instance->is_active_high) ? color : ((~color) & DRV_RGB_WHITE);
}

#endif // DRV_RGB_LED_C
