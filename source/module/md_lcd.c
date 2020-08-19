/*!****************************************************************************
* @file     md_lcd.c
* @brief
* @author   FuxFox
* @version  V1.0
* @date     2019/09/24
*******************************************************************************/
#ifndef MD_LCD_C
#define MD_LCD_C

#include "md_lcd.h"

void md_lcd_init(void)
{
    drv_lcd_clear(MD_LCD_BACKGRAUND_COLOR);
    drv_lcd_backlight_on();
    md_lcd_show_string(10, 10, "hello");
}

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

void md_lcd_show_numberEx(uint16_t x, uint16_t y, int number, md_lcd_font_enum font, bool draw_background)
{
    char str[12];

    snprintf(str, 12, "%d", number);
    md_lcd_show_stringEx(x, y, str, font, draw_background);
}



#endif // MD_LCD_C
