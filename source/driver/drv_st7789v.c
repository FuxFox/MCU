/*******************************************************************************
 * Module: drv_st7789v
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/09/24 13:48          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_st7789v.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/09/24
  *******************************************************************************/
#ifndef DRV_ST7789V_C
#define DRV_ST7789V_C

#include "drv_st7789v.h"

#define drv_st7789v_cs_deselect()     app_gpio_pin_set(DRV_ST7789V_SPI_CS)
#define drv_st7789v_cs_select()       app_gpio_pin_clear(DRV_ST7789V_SPI_CS)


static const nrf_drv_spi_t m_drv_st7789v_spi = NRF_DRV_SPI_INSTANCE(DRV_ST7789V_SPI_INSTANCE);  /**< SPI instance. */

static bool m_backlight_on = false;

/*!*****************************************************************************
\brief      initialize
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_st7789v_init(void)
{
    app_gpio_cfg_output(DRV_ST7789V_BACK_LIGHT_EN);
    app_gpio_cfg_output(DRV_ST7789V_RST);
    app_gpio_cfg_output(DRV_ST7789V_RS);
    app_gpio_pin_set(DRV_ST7789V_RST);

    drv_st7789v_spi_init();

    drv_st7789v_reset();
    drv_st7789v_config();
}

/*!*****************************************************************************
\brief      st7789v SPI initialize
\details
\param[in]    void
\return     void
******************************************************************************/
static void drv_st7789v_spi_init(void)
{
    nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
    spi_config.mosi_pin = DRV_ST7789V_SPI_SDA;
    spi_config.sck_pin = DRV_ST7789V_SPI_SCK;
    APP_ERROR_CHECK(nrf_drv_spi_init(&m_drv_st7789v_spi, &spi_config, NULL, NULL));

    app_gpio_cfg_output(DRV_ST7789V_SPI_CS);    // pin confige out 
    drv_st7789v_cs_deselect();
}


/*!*****************************************************************************
\brief      send data sequence
\details
\param[in]    uint8_t * data
\param[in]    uint8_t len
\return     void
******************************************************************************/
static void drv_st7789v_send_dataSeqEx(const uint8_t* data, uint8_t len)
{
    app_gpio_pin_set(DRV_ST7789V_RS);
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&m_drv_st7789v_spi, data, len, NULL, 0));
}

/*!*****************************************************************************
\brief      send a byte of cmd
\details
\param[in]    uint8_t cmd
\return     void
******************************************************************************/
static void drv_st7789v_send_cmd(uint8_t cmd)
{
    drv_st7789v_cs_select();
    app_gpio_pin_clear(DRV_ST7789V_RS);
    nrf_drv_spi_transfer(&m_drv_st7789v_spi, &cmd, 1, NULL, 0);
    drv_st7789v_cs_deselect();
}

/*!*****************************************************************************
\brief      send a byte of data
\details
\param[in]    uint8_t cmd
\return     void
******************************************************************************/
static void drv_st7789v_send_data(uint8_t data)
{
    drv_st7789v_cs_select();
    app_gpio_pin_set(DRV_ST7789V_RS);
    nrf_drv_spi_transfer(&m_drv_st7789v_spi, &data, 1, NULL, 0);
    drv_st7789v_cs_deselect();
}

/*!*****************************************************************************
\brief      Send command, use for continuous communication
\details
\param[in]    uint8_t cmd
\return     void
******************************************************************************/
static void drv_st7789v_send_cmdEx(uint8_t cmd)
{
    app_gpio_pin_clear(DRV_ST7789V_RS);
    nrf_drv_spi_transfer(&m_drv_st7789v_spi, &cmd, 1, NULL, 0);
}

/*!*****************************************************************************
\brief      Send data, use for continuous communication
\details
\param[in]    uint8_t cmd
\return     void
******************************************************************************/
static void drv_st7789v_send_dataEx(uint8_t data)
{
    app_gpio_pin_set(DRV_ST7789V_RS);
    nrf_drv_spi_transfer(&m_drv_st7789v_spi, &data, 1, NULL, 0);
}

/*!*****************************************************************************
\brief      reset
\details
\param[in]    void
\return     void
******************************************************************************/
static void drv_st7789v_reset(void)
{
    app_gpio_pin_clear(DRV_ST7789V_RST);
    app_delay_ms(1);//10
    app_gpio_pin_set(DRV_ST7789V_RST);
    app_delay_ms(120);//500
}

/*!*****************************************************************************
\brief      st7789v configure
\details
\param[in]    void
\return     void
******************************************************************************/
static void drv_st7789v_config(void)
{
    const uint8_t frame_rate_setting[5] = { 0x0c, 0x0c, 0x00, 0x33, 0x33 };
    const uint8_t gamma_setting_1[14] = { 0xd0, 0x04, 0x0d, 0x11, 0x13, 0x2b, 0x3f, 0x54, 0x4c, 0x18, 0x0d, 0x0b, 0x1f, 0x23 };
    const uint8_t gamma_setting_2[14] = { 0xd0, 0x04, 0x0c, 0x11, 0x13, 0x2c, 0x3f, 0x44, 0x51, 0x2f, 0x1f, 0x1f, 0x20, 0x23 };

    drv_st7789v_cs_select();
    //----------------------------------Display Setting-----------------------------------------------//
    drv_st7789v_send_cmdEx(0x36);
    drv_st7789v_send_dataEx(0x00);

    drv_st7789v_send_cmdEx(0x3a);
    drv_st7789v_send_dataEx(0x05);//0x55-16bit  0x05-8bit 
    //--------------------------------ST7789V Frame rate setting----------------------------------//
    drv_st7789v_send_cmdEx(0xb2);
    drv_st7789v_send_dataSeqEx(frame_rate_setting, sizeof(frame_rate_setting));

    drv_st7789v_send_cmdEx(0xb7);
    drv_st7789v_send_dataEx(0x35); //VGH=13V, VGL=-10.4V
    //----------------------------------------------------------------------------------------------------//
    drv_st7789v_send_cmdEx(0xbb);
    drv_st7789v_send_dataEx(0x19);

    drv_st7789v_send_cmdEx(0xc0);
    drv_st7789v_send_dataEx(0x2c);

    drv_st7789v_send_cmdEx(0xc2);
    drv_st7789v_send_dataEx(0x01);

    drv_st7789v_send_cmdEx(0xc3);
    drv_st7789v_send_dataEx(0x12);

    drv_st7789v_send_cmdEx(0xc4);
    drv_st7789v_send_dataEx(0x20);

    drv_st7789v_send_cmdEx(0xc6);
    drv_st7789v_send_dataEx(0x0f);

    drv_st7789v_send_cmdEx(0xd0);
    drv_st7789v_send_dataEx(0xa4);
    drv_st7789v_send_dataEx(0xa1);
    //----------------------------------------------------------------------------------------------------//
    drv_st7789v_send_cmdEx(0xe0); //gamma setting
    drv_st7789v_send_dataSeqEx(gamma_setting_1, sizeof(gamma_setting_1));
    drv_st7789v_send_cmdEx(0xe1);
    drv_st7789v_send_dataSeqEx(gamma_setting_2, sizeof(gamma_setting_2));

    drv_st7789v_send_cmdEx(0x11);

    drv_st7789v_cs_deselect();

    app_delay_ms(120);
    drv_st7789v_send_cmd(0x29); //display on
}


/*!*****************************************************************************
\brief  	set coordinate
\param[in]	uint16_t x1       Top left x coordinate, starting from 0
\param[in]	uint16_t y1       Top left y coordinate, starting from 0
\param[in]	uint16_t x2       Bottom right x coordinate, starting from 0
\param[in]	uint16_t y2       Bottom right y coordinate, starting from 0
\return     void
******************************************************************************/
void drv_st7789v_set_addressEx(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    drv_st7789v_send_cmdEx(0x2a);
    drv_st7789v_send_dataEx(x1 >> 8);
    drv_st7789v_send_dataEx(x1);
    drv_st7789v_send_dataEx(x2 >> 8);
    drv_st7789v_send_dataEx(x2);

    drv_st7789v_send_cmdEx(0x2b);
    drv_st7789v_send_dataEx(y1 >> 8);
    drv_st7789v_send_dataEx(y1);
    drv_st7789v_send_dataEx(y2 >> 8);
    drv_st7789v_send_dataEx(y2);

    drv_st7789v_send_cmdEx(0x2C);    /* Enable RAM write*/
}

/*!*****************************************************************************
\brief  	draw a dot
\param[in]	uint16_t x      Top left x coordinate of the dot, starting from 0
\param[in]	uint16_t y      Top left y coordinate of the dot, starting from 0
\param[in]	uint16_t color  The dot color
\return     void
******************************************************************************/
void drv_st7789v_draw_dot(uint16_t x, uint16_t y, uint16_t color)
{
    if ((x >= DRV_ST7789V_LCD_WIDTH) || (y >= DRV_ST7789V_LCD_HEIGHT))
    {
        return;
    }

    drv_st7789v_cs_select();

    drv_st7789v_set_addressEx(x, y, x, y);
    drv_st7789v_send_dataEx(color >> 8);
    drv_st7789v_send_dataEx(color);

    drv_st7789v_cs_deselect();
}


/*!*****************************************************************************
\brief      fill rectangle
\details
\param[in]    uint16_t x            Top left x coordinate of the rectangle, starting from 0
\param[in]    uint16_t y            Top left y coordinate of the rectangle, starting from 0
\param[in]    uint16_t width        rectangle width
\param[in]    uint16_t height       rectangle height
\param[in]    uint16_t color        
\return     void
******************************************************************************/
void drv_st7789v_fill_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    uint32_t i = width * height;

    if ((x + width > DRV_ST7789V_LCD_WIDTH) || (y + height > DRV_ST7789V_LCD_HEIGHT))
    {
        width = DRV_ST7789V_LCD_WIDTH - x;
        height = DRV_ST7789V_LCD_HEIGHT - y;
    }

    drv_st7789v_cs_select();

    drv_st7789v_set_addressEx(x, y, x + width - 1, y + height - 1);

    while (i--)
    {
        drv_st7789v_send_dataEx(color >> 8);
        drv_st7789v_send_dataEx(color);
    }

    drv_st7789v_cs_deselect();
}

/*!*****************************************************************************
\brief  	ST7789V control interface
\param[in]	drv_st7789v_ctrl_cmd_t cmd          control command
\param[in]	uint32_t param1                     as parameter if command support parameter, 
                                                    or NULL if command has no parameter
\return     uint32_t    as return value if command support has return value,
                         or NULL if command has no return value
******************************************************************************/
uint32_t drv_st7789v_ctrl(drv_st7789v_ctrl_cmd_t cmd, uint32_t param1)
{
    switch (cmd)
    {
    case DRV_ST7789V_CTRL_BACKLIGHT:
        if (param1)
        {
            nrf_gpio_pin_set(DRV_ST7789V_BACK_LIGHT_EN);
            m_backlight_on = true;
        }
        else
        {
            nrf_gpio_pin_clear(DRV_ST7789V_BACK_LIGHT_EN);
            m_backlight_on = false;
        }
        break;
    case DRV_ST7789V_IS_BACKLIGHT_ON:
        return m_backlight_on;
    case DRV_ST7789V_CTRL_DISPLAY:
        drv_st7789v_send_cmd(param1 ? 0x29 : 0x28);
        break;
    default:
        break;
    }

    return NULL;
}


#endif // DRV_ST7789V_AML_C
