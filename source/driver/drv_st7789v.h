/*******************************************************************************
 * Module: drv_st7789v
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/09/24 13:48          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     drv_st7789v.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/09/24
 *******************************************************************************/
#ifndef DRV_ST7789V_H
#define DRV_ST7789V_H

/*! \defgroup drv_st7789v_public Public
\ingroup drv_st7789v
\brief 
        AML280V15002-A TFT-LCD driver, base on ST7789V driver chip.
        This driver implemented base on NRF52832 base on hardware SPI, you can modify the driver
        to use software SPI(or your MCU's hardware SPI) to use for another MCU.

\note 
    see also \ref drv_spi.h to modify the software SPI interface
    and ../app_interface_remap.h to remap the GPIO interface.
* @{ */

//#include "app_common_head.h"
#include "app_globle.h"

//********************************* Module Config *******************************/

#define DRV_ST7789V_SPI_INSTANCE    CFG_LCD_SPI_INSTANCE /**< SPI instance index for nrf52832. */
    
#define DRV_ST7789V_SPI_SDA            LCD_SPI_DI
#define DRV_ST7789V_SPI_SCK            LCD_SPI_CLK
#define DRV_ST7789V_SPI_CS             LCD_SPI_CS
#define DRV_ST7789V_RS                 LCD_RS
#define DRV_ST7789V_BACK_LIGHT_EN      LCD_BACKLIGHT
#define DRV_ST7789V_RST                LCD_RST




#define DRV_ST7789V_LCD_HEIGHT    320
#define DRV_ST7789V_LCD_WIDTH    240
//********************************* Data Type ***********************************/

/*! st7789v control command list */
typedef enum
{
   DRV_ST7789V_CTRL_BACKLIGHT,      /*!< Back light control. Param1: TRUE -> back light ON; FALSE -> back light OFF */
   DRV_ST7789V_IS_BACKLIGHT_ON,     /*!< Query back light state, has return value: TRUE if back light ON, FALSE if back light OFF */
   DRV_ST7789V_CTRL_DISPLAY,        /*!< Display control. Param1: TRUE -> display ON; FALSE -> display OFF */
}drv_st7789v_ctrl_cmd_t;



//********************************* Public Interface ****************************/

void drv_st7789v_init(void);

void drv_st7789v_set_addressEx(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void drv_st7789v_draw_dot(uint16_t x, uint16_t y, uint16_t color);
void drv_st7789v_fill_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
uint32_t drv_st7789v_ctrl(drv_st7789v_ctrl_cmd_t cmd, uint32_t param1);

#define drv_st7789v_clear(color)         drv_st7789v_fill_rectangle(0, 0, DRV_ST7789V_LCD_WIDTH, DRV_ST7789V_LCD_HEIGHT, color)
//********************************* Private Interface ***************************/


static void drv_st7789v_spi_init(void);
static void drv_st7789v_send_dataSeqEx(const uint8_t* data, uint8_t len);
static void drv_st7789v_send_cmd(uint8_t cmd);
static void drv_st7789v_send_data(uint8_t data);
static void drv_st7789v_send_cmdEx(uint8_t cmd);
static void drv_st7789v_send_dataEx(uint8_t data);
static void drv_st7789v_reset(void);
static void drv_st7789v_config(void);



/*! @}*/ //end of group drv_st7789v
#endif // DRV_ST7789V_AML_H
