/*******************************************************************************
 *
 * Module: drv_cs1237
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/28 15:31          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_cs1237.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/28
  *******************************************************************************/
#ifndef DRV_CS1237_C
#define DRV_CS1237_C

#include "drv_cs1237.h"

  /*!*****************************************************************************
  \brief  	initialize
  \param[in]	drv_cs1237_instance_t * instance
  \return     void
  ******************************************************************************/
void drv_cs1237_init(drv_cs1237_instance_t* instance)
{
    drv_spi_init(instance);
    app_gpio_cfg(instance->sck_pin, APP_GPIO_MODE_OUTPUT_OD, APP_GPIO_NOPULL, APP_GPIO_SPEED_FREQ_HIGH);
}

/*!*****************************************************************************
\brief      get adc value(24bit)
\details
\param[in]    drv_cs1237_instance_t * instance    
\param[in]    uint32_t * value   pointer use to receive a value
\return     bool TRUE if success
******************************************************************************/
bool drv_cs1237_get_value(drv_cs1237_instance_t* instance, int32_t* value)
{
    uint8_t data[3];
    uint32_t dat = 0;

    if (!drv_cs1237_is_ready(instance))
    {
        return false;
    }

    drv_spi_Rx(instance, data, 3);
    dat = data[0];
    dat <<= 8;
    dat |= data[1];
    dat <<= 8;
    dat |= data[2];

    *value = (dat & 0x00800000) ? -((~(dat - 1)) & 0x007FFFFF) : dat; // trans format to int32_t    

    return true;
}

/*
void drv_cs1237_send_byte(drv_cs1237_instance_t* instance, uint8_t byte)
{
        uint8_t mask;

        app_gpio_cfg_output(instance->miso_pin);

        for (mask = 0x80; mask; mask >>=1)
        {
                app_gpio_pin_write(instance->sck_pin, GPIO_PIN_SET); // CLK=1;
                app_delay_us(1);
                app_gpio_pin_write(instance->miso_pin, (mask & byte)? GPIO_PIN_SET : GPIO_PIN_RESET);
                app_gpio_pin_write(instance->sck_pin, GPIO_PIN_RESET); // CLK=0;
                app_delay_us(1);
        }
}

uint8_t drv_cs1237_read_byte(drv_cs1237_instance_t* instance)
{
        uint8_t mask, data = 0;

        app_gpio_cfg_input(instance->miso_pin, APP_GPIO_NOPULL);

        for (mask = 0x80; mask; mask >>=1)
        {
                app_gpio_pin_write(instance->sck_pin, GPIO_PIN_SET);    // CLK=1;
                app_delay_us(1);
                app_gpio_pin_write(instance->sck_pin, GPIO_PIN_RESET);    // CLK=0;
                app_delay_us(1);
                if (app_gpio_pin_read(instance->miso_pin))
                {
                        data |= mask;
                }
        }

        return data;
}

/ *!*****************************************************************************
\brief      发送指定个数的时钟信号
\details
\param[in]    uint8_t num
\return     void
****************************************************************************** /
void drv_cs1237_send_clk(drv_cs1237_instance_t* instance, uint8_t num)
{
        while (num--)
        {
                app_gpio_pin_write(instance->sck_pin, GPIO_PIN_SET);    // CLK=1;
                app_delay_us(1);
                app_gpio_pin_write(instance->sck_pin, GPIO_PIN_RESET);    // CLK=0;
                app_delay_us(1);
        }
}
*/
/*!*****************************************************************************
\brief      is chip ready
\details
\param[in]    drv_cs1237_instance_t * instance
\return     bool
******************************************************************************/
bool drv_cs1237_is_ready(drv_cs1237_instance_t* instance)
{
    uint8_t time_cnt = 0;

    while (app_gpio_pin_read(instance->miso_pin))//wait ready
    {
        if (++time_cnt >= 250)
        {
            return false;//timeout
        }
        app_delay_ms(1);
    }

    return true;
}

/*
// read chip configure register
unsigned char drv_cs1237_read_cfg(drv_cs1237_instance_t* instance)
{
        unsigned char dat=0;//读取到的数据

        if (!drv_cs1237_is_ready(instance))
        {
                return false;
        }

        drv_cs1237_send_clk(instance, 29);

        drv_cs1237_send_byte(instance, DRV_CS1237_CMD_READ_CFG);

        dat = drv_cs1237_read_byte(instance);

        //第46个脉冲
        drv_cs1237_send_clk(instance, 1);

        app_gpio_cfg_output(instance->miso_pin);
        app_gpio_pin_write(instance->miso_pin, GPIO_PIN_SET); //OUT引脚拉高

        return dat;
}
*/

#endif // DRV_CS1237_C
