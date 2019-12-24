/*******************************************************************************
 *
 * Module: drv_iic
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/12 10:59          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_iic.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/12
  *******************************************************************************/
#ifndef DRV_IIC_C
#define DRV_IIC_C

#include "drv_iic.h"


  /*! \defgroup drv_iic_ctrl_interface
  * @{ */
#define drv_iic_sda_config_input()         app_gpio_cfg_input(instance->sda_pin, APP_GPIO_NOPULL)
#define drv_iic_sda_config_output()        app_gpio_cfg_output(instance->sda_pin)
#define drv_iic_sda_read                   app_gpio_pin_read(instance->sda_pin)  
#define drv_iic_sda_output(state)          app_gpio_pin_write(instance->sda_pin, state)
#define drv_iic_scl_output(state)          app_gpio_pin_write(instance->scl_pin, state)
  /*! @}*/ //end of group drv_iic_ctrl_interface



 /*!*****************************************************************************
 \brief      initialize IIC instance

 \param[in]    drv_iic_instance_t * instance
 \return     bool        TRUE if success
 ******************************************************************************/
bool drv_iic_init(drv_iic_instance_t* instance)
{
    app_gpio_cfg_input(instance->sda_pin, APP_GPIO_PULLUP);
    app_gpio_cfg_output(instance->scl_pin);
    app_gpio_pin_write(instance->scl_pin, GPIO_PIN_SET);
    return drv_iic_address(instance);
}


/*!*****************************************************************************
\brief      send a START to IIC bus

\param[in]    drv_iic_instance_t * instance
\return     void
******************************************************************************/
static void drv_iic_start(drv_iic_instance_t* instance)
{
    drv_iic_sda_config_output();
    drv_iic_sda_output(DRV_IIC_HIGH);
    drv_iic_scl_output(DRV_IIC_HIGH);
    app_delay_us(4);
    drv_iic_sda_output(DRV_IIC_LOW);
    app_delay_us(4);
    drv_iic_scl_output(DRV_IIC_LOW);
}


/*!*****************************************************************************
\brief      send a STOP to IIC bus

\param[in]    drv_iic_instance_t * instance
\return     void
******************************************************************************/
static void drv_iic_stop(drv_iic_instance_t* instance)
{
    drv_iic_sda_config_output();
    drv_iic_scl_output(DRV_IIC_LOW);
    drv_iic_sda_output(DRV_IIC_LOW);
    app_delay_us(4);
    drv_iic_scl_output(DRV_IIC_HIGH);
    drv_iic_sda_output(DRV_IIC_HIGH);
    app_delay_us(4);
}

/*!*****************************************************************************
\brief      send a byte to IIC bus

\param[in]    drv_iic_instance_t * instance
\param[in]    uint8_t txd            The byte to be send
\return     bool                TRUE if success
******************************************************************************/
static bool drv_iic_send_byte(drv_iic_instance_t* instance, uint8_t txd)
{
    uint8_t mask;

    drv_iic_sda_config_output();
    drv_iic_scl_output(DRV_IIC_LOW);
    for (mask = 0x80; mask; mask >>= 1)
    {
        if (txd & mask)
            drv_iic_sda_output(DRV_IIC_HIGH);
        else
            drv_iic_sda_output(DRV_IIC_LOW);
        app_delay_us(2);
        drv_iic_scl_output(DRV_IIC_HIGH);
        app_delay_us(2);
        drv_iic_scl_output(DRV_IIC_LOW);
        app_delay_us(2);
    }

    drv_iic_sda_config_input();
    drv_iic_sda_output(DRV_IIC_HIGH);
    app_delay_us(2);
    drv_iic_scl_output(DRV_IIC_HIGH);
    if (drv_iic_sda_read)
    {
        return false;
    }

    drv_iic_scl_output(DRV_IIC_LOW);
    return true;
}


/*!*****************************************************************************
\brief      read a byte from IIC bus

\param[in]    drv_iic_instance_t * instance
\param[in]    bool ack            If TURE , send ACK to slave after received the byte
\return     uint8_t                The byte
******************************************************************************/
static uint8_t drv_iic_read_byte(drv_iic_instance_t* instance, bool ack)
{
    unsigned char i, receive = 0;

    drv_iic_sda_config_input();//SDA input
    for (i = 0; i < 8; i++)
    {
        drv_iic_scl_output(DRV_IIC_LOW);
        app_delay_us(2);
        drv_iic_scl_output(DRV_IIC_HIGH);
        receive <<= 1;
        receive |= drv_iic_sda_read;
        app_delay_us(1);
    }

    drv_iic_scl_output(DRV_IIC_LOW);
    drv_iic_sda_config_output();
    drv_iic_sda_output(ack ? DRV_IIC_LOW : DRV_IIC_HIGH);
    app_delay_us(2);
    drv_iic_scl_output(DRV_IIC_HIGH);
    app_delay_us(2);
    drv_iic_scl_output(DRV_IIC_LOW);

    return receive;
}

/*!*****************************************************************************
\brief      write data buff to IIC bus

\param[in]    drv_iic_instance_t * instance
\param[in]    uint16_t reg          target register address
\param[in]    uint8_t * buf         data buff to be send
\param[in]    uint8_t len           data len to be send
\return     bool        TRUE if success
******************************************************************************/
bool drv_iic_write(drv_iic_instance_t* instance, uint16_t reg, uint8_t* buf, uint8_t len)
{
    bool ok = false;

    drv_iic_start(instance);

    if (!drv_iic_send_byte(instance, instance->addr))
    {
        drv_iic_stop(instance);
        return false;
    }

    if (instance->reg_addr_16bit)
    {
        ok = (drv_iic_send_byte(instance, reg >> 8) && drv_iic_send_byte(instance, reg));
    }
    else
    {
        ok = drv_iic_send_byte(instance, reg);
    }

    if (!ok)
    {
        drv_iic_stop(instance);
        return false;
    }

    while (len--)
    {
        if (!drv_iic_send_byte(instance, *buf++))
        {
            drv_iic_stop(instance);
            return    false;
        }
    }
    drv_iic_stop(instance);
    return true;
}

/*!*****************************************************************************
\brief      read data from IIC bus

\param[in]    drv_iic_instance_t * instance
\param[in]    uint16_t reg          target register address
\param[in]    uint8_t * buf         data buff for receive
\param[in]    uint8_t len           data len to be read
\return     bool        TRUE if success
******************************************************************************/
bool drv_iic_read(drv_iic_instance_t* instance, uint16_t reg, uint8_t* buf, uint8_t len)
{
    bool ok = false;

    drv_iic_start(instance);
    if (!drv_iic_send_byte(instance, instance->addr))
    {
        drv_iic_stop(instance);
        return false;
    }

    if (instance->reg_addr_16bit)
    {
        ok = (drv_iic_send_byte(instance, reg >> 8) && drv_iic_send_byte(instance, reg));
    }
    else
    {
        ok = drv_iic_send_byte(instance, reg);
    }

    if (!ok)
    {
        drv_iic_stop(instance);
        return false;
    }


    drv_iic_start(instance);
    if (!drv_iic_send_byte(instance, instance->addr | 1))
    {
        drv_iic_stop(instance);
        return false;
    }

    while (len--)
    {
        *buf++ = drv_iic_read_byte(instance, len);
    }
    drv_iic_stop(instance);
    return true;
}

/*!*****************************************************************************
\brief      try to find a device

\param[in]    drv_iic_instance_t * instance
\return     bool        TRUE if found
******************************************************************************/
bool drv_iic_address(drv_iic_instance_t* instance)
{
    bool ack;

    drv_iic_start(instance);

    ack = drv_iic_send_byte(instance, instance->addr);
    drv_iic_stop(instance);
    return ack;
}




#endif // DRV_IIC_C

