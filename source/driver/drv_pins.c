/*******************************************************************************
 *
 * Module: drv_pins
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/16 16:59          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_pins.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/16
  *******************************************************************************/
#ifndef DRV_PINS_C
#define DRV_PINS_C

#include "drv_pins.h"

static uint8_t m_input_pins[] = PIN_INPUT_LIST;
static uint8_t m_output_init_low_pins[] = PIN_OUTPUT_LIST_INIT_LOW;
static uint8_t m_output_init_hight_pins[] = PIN_OUTPUT_LIST_INIT_HIGHT;


/*!*****************************************************************************
\brief      initialize
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_pins_init(void)
{
    uint8_t i;

    for (i = 0; i < sizeof(m_input_pins); i++)
    {
        app_gpio_cfg_input(m_input_pins[i], APP_GPIO_NOPULL);
    }

    for (i = 0; i < sizeof(m_output_init_low_pins); i++)
    {
        app_gpio_pin_write(m_output_init_low_pins[i], GPIO_PIN_RESET);
        app_gpio_cfg_output(m_output_init_low_pins[i]);
    }

    for (i = 0; i < sizeof(m_output_init_hight_pins); i++)
    {
        app_gpio_pin_write(m_output_init_hight_pins[i], GPIO_PIN_SET);
        app_gpio_cfg_output(m_output_init_hight_pins[i]);
    }

}






#endif // DRV_PINS_C
