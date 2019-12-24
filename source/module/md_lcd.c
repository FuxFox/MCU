/*******************************************************************************
 * Module: md_lcd
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/09/24 16:27          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     md_lcd.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/09/24
  *******************************************************************************/
#ifndef MD_LCD_C
#define MD_LCD_C

#include "md_lcd.h"

  /*!*****************************************************************************
  \brief      initialize
  \details
  \param[in]    void
  \return     void
  ******************************************************************************/
void md_lcd_init(void)
{
    drv_lcd_clear(MD_LCD_BACKGRAUND_COLOR);
    drv_lcd_backlight_on();
    md_lcd_show_string(10, 10, "hello");
}

/*!*****************************************************************************
\brief        draw a char
\details
\param[in]    uint16_t x £º x coordinate
\param[in]    uint16_t y £º y coordinate
\param[in]    uint8_t chr : ascii char
\param[in]    md_lcd_font_enum font £º
\param[in]    bool draw_background £º
\return       void
******************************************************************************/
void md_lcd_show_charEx(uint16_t x, uint16_t y, uint8_t chr, md_lcd_font_enum font_size, bool draw_background)
{
    uint8_t temp, mask, i, font_height;
    uint16_t y0 = y;
    const uint8_t* font_map;

    switch (font_size)
    {
    case MD_LCD_FONT_1608:
        font_map = (const uint8_t*)asc2_1608;
        font_height = 16;
        break;
//         case MD_LCD_FONT_2412:
//                 font_map = (const uint8_t *)asc2_2412;
//                 font_height = 24;
//                 break;
    case MD_LCD_FONT_3216:
        font_map = (const uint8_t*)asc2_3216;
        font_height = 32;
        break;
    case MD_LCD_FONT_4824:
        font_map = (const uint8_t*)asc2_4824;
        font_height = 48;
        break;
    default:
        return;
    }

    chr -= ' ';    /* £¨ASCII font is start at space(' '), minus ' ' to get the index in font of this char £© */

    for (i = 0; i < font_size; i++)    /*print all pix */
    {
        temp = font_map[chr * font_size + i];

        for (mask = 0x80; mask; mask >>= 1)    /* print a pix */
        {
            if (temp & mask)
            {
                drv_lcd_draw_point(x, y, MD_LCD_FONT_COLOR);
            }
            else if (draw_background)
            {
                drv_lcd_draw_point(x, y, MD_LCD_BACKGRAUND_COLOR);
            }
            y++;

            if ((y >= DRV_LCD_HEIGHT) || ((y - y0) == font_height))
            {
                y = y0;
                x++;
                if (x >= DRV_LCD_WIDTH)
                {
                    return;    /* out of region */
                }
                break;
            }
        }
    }
}

/*!*****************************************************************************
\brief      show string
\details
\param[in]    uint16_t x,y :    start coordinate
\param[in]    uint8_t * str £º  string to be printed.(must end with '\0')
\param[in]    md_lcd_font_enum font £º
\param[in]    bool draw_background £º if true, renew background
\return     void
******************************************************************************/
void md_lcd_show_stringEx(uint16_t x, uint16_t y, char* str, md_lcd_font_enum font, bool draw_background)
{
    uint16_t x0 = x;
    uint8_t font_height;

    switch (font)
    {
    case MD_LCD_FONT_1608:
        font_height = 16;
        break;
    case MD_LCD_FONT_2412:
        font_height = 24;
        break;
    case MD_LCD_FONT_3216:
        font_height = 32;
        break;
    case MD_LCD_FONT_4824:
        font_height = 48;
        break;
    default:
        return;
    }

    while (*str)
    {
        if (*str == '\n')
        {
            x = x0;
            y += font_height;
            str++;
            continue;
        }

        if (x >= DRV_LCD_WIDTH)
        {
            x = x0;
            y += font_height;
        }

        if (y >= DRV_LCD_HEIGHT)
        {
            break;
        }
        md_lcd_show_charEx(x, y, *str, font, draw_background);
        //                NRF_LOG_DEBUG("put char:%c at %d,%d", *str, x, y);
        x += font_height / 2;
        str++;
    }
}

/*!*****************************************************************************
\brief      show bitmap icon
\details
\param[in]    uint16_t x    x coordinate
\param[in]    uint16_t y    y coordinate
\param[in]    lib_image_struct * image
\param[in]    bool draw_background  If true, renew background
\return     void
******************************************************************************/
void md_lcd_show_image(uint16_t x, uint16_t y, const lib_image_struct* image, bool draw_background)
{
    uint8_t temp, mask, i;
    uint16_t y0 = y;

    for (i = 0; i < image->size; i++)
    {
        temp = image->data[i];

        for (mask = 0x80; mask; mask >>= 1)
        {
            if (temp & mask)
            {
                drv_lcd_draw_point(x, y, MD_LCD_FONT_COLOR);
            }
            else if (draw_background)
            {
                drv_lcd_draw_point(x, y, MD_LCD_BACKGRAUND_COLOR);
            }
            y++;

            if ((y >= DRV_LCD_HEIGHT) || ((y - y0) >= image->height))
            {
                y = y0;
                x++;
                if (x >= DRV_LCD_WIDTH)
                {
                    return;
                }
                break;
            }
        }
    }
}

/*!*****************************************************************************
\brief      print number
\details
\param[in]    uint16_t x
\param[in]    uint16_t y
\param[in]    int number
\param[in]    md_lcd_font_enum font
\param[in]    bool draw_background      If true, renew background
\return     void
******************************************************************************/
void md_lcd_show_numberEx(uint16_t x, uint16_t y, int number, md_lcd_font_enum font, bool draw_background)
{
    char str[12];

    snprintf(str, 12, "%d", number);
    md_lcd_show_stringEx(x, y, str, font, draw_background);
}



#endif // MD_LCD_C
