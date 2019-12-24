/*******************************************************************************
 *
 * Module: drv_spi
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/17 09:59          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_spi.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/17
  *******************************************************************************/
#ifndef DRV_SPI_C
#define DRV_SPI_C

#include "drv_spi.h"

/*!*****************************************************************************
\brief      initialize
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_spi_init(drv_spi_instance_struct* instance)
{
    instance->delay_time = 1000 / instance->speed_kHz / 2 - 1;

    if (instance->miso_pin)
    {
        app_gpio_cfg_input(instance->miso_pin, APP_GPIO_PULLUP);
    }
    if (instance->mosi_pin)
    {
        app_gpio_cfg_output(instance->mosi_pin);
        app_gpio_pin_write(instance->mosi_pin, GPIO_PIN_SET);
    }
    if (instance->cs_pin)
    {
        app_gpio_cfg_output(instance->cs_pin);
        app_gpio_pin_write(instance->cs_pin, (GPIO_PinState)instance->cs_level);
    }
    if (instance->sck_pin)
    {
        app_gpio_cfg_output(instance->sck_pin);
        app_gpio_pin_write(instance->sck_pin, (instance->mode <= DRV_SPI_MODE_1) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    }

}

/*!*****************************************************************************
\brief      SPI transmit
\details
\param[in]    const drv_spi_instance_struct *   spi_instance
\param[in]    const uint8_t * tx_buff           Tx buffer, can be null if you want to send nothing
\param[in]    uint32_t tx_len                   Tx data length, can be null if you want to send nothing
\param[in]    const uint8_t * rx_buff           Rx buffer, can be null if you want to send nothing
\param[in]    uint32_t rx_len                   Rx data length,can be null if you want to send nothing                    
\return     void
******************************************************************************/
void drv_spi_TxRx(drv_spi_instance_struct* spi_instance, const uint8_t* tx_buff, uint32_t tx_len, uint8_t* rx_buff, uint32_t rx_len)
{
    uint8_t tx_byte, rx_byte, mask;

    if (!((spi_instance->mosi_pin && tx_buff && tx_len) || (spi_instance->miso_pin && rx_buff && rx_len)))
    {
        return;
    }

    if (spi_instance->cs_pin)
    {
        app_gpio_pin_write(spi_instance->cs_pin, (GPIO_PinState)spi_instance->cs_level);
    }

    if (spi_instance->mode & DRV_SPI_CPHA_MASK)
    {
        app_gpio_pin_toggle(spi_instance->sck_pin);
    }

    while (tx_len || rx_len)
    {
        if (tx_len)
        {
            tx_byte = *tx_buff++;
        }
        rx_byte = 0;

        for (mask = 0x80; mask; mask >>= 1)
        {
            if (tx_len)
            {
                app_gpio_pin_write(spi_instance->mosi_pin, (GPIO_PinState)(tx_byte & mask));
            }
#if (DRV_SPI_MAX_SPEED_MODE == 0)
            app_delay_us(spi_instance->delay_time);
#endif
            app_gpio_pin_toggle(spi_instance->sck_pin);
#if (DRV_SPI_MAX_SPEED_MODE == 0)
            app_delay_us(spi_instance->delay_time);
#endif
            if (rx_len)
            {
                rx_byte |= app_gpio_pin_read(spi_instance->miso_pin) ? mask : 0;
            }
            app_gpio_pin_toggle(spi_instance->sck_pin);
        }

        if (tx_len)
        {
            tx_len--;
        }
        if (rx_len)
        {
            *rx_buff++ = rx_byte;
            rx_len--;
        }
    }

#if (DRV_SPI_MAX_SPEED_MODE == 0)
    if (spi_instance->mode & DRV_SPI_CPHA_MASK)
    {
        app_delay_us(spi_instance->delay_time);
    }
#endif
    app_gpio_pin_write(spi_instance->sck_pin, (spi_instance->mode & DRV_SPI_CPOL_MASK) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    if (spi_instance->miso_pin)
    {
        app_gpio_pin_write(spi_instance->miso_pin, GPIO_PIN_SET);
    }
    if (spi_instance->mosi_pin)
    {
        app_gpio_pin_write(spi_instance->mosi_pin, GPIO_PIN_SET);
    }
    if (spi_instance->cs_pin)
    {
        app_gpio_pin_write(spi_instance->cs_pin, (GPIO_PinState)(!spi_instance->cs_level));
    }
}
#endif // DRV_SPI_C
