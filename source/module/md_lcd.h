/*!****************************************************************************
* @file     md_lcd.h
* @brief
* @author   FuxFox
* @version  V1.0
* @date     2019/09/24
*******************************************************************************/
#ifndef MD_LCD_H
#define MD_LCD_H

/**
* @defgroup md_lcd
* @ingroup module
* @brief      This is a generic(?) LCD module in module layer.
* @note       You need to confirm whether the interface of LCD driver matches.
* @{ */

#include "app_globle.h"

#include "drv_lcd.h"
#include "lib_font.h"
#include "lib_image.h"
/*================================= Module Config ============================*/

/* color */
#define MD_LCD_WHITE              0xFFFF
#define MD_LCD_BLACK              0x0000      
#define MD_LCD_BLUE               0x001F  
#define MD_LCD_BRED               0XF81F
#define MD_LCD_GRED               0XFFE0
#define MD_LCD_GBLUE              0X07FF
#define MD_LCD_RED                0xF800
#define MD_LCD_MAGENTA            0xF81F
#define MD_LCD_GREEN              0x07E0
#define MD_LCD_CYAN               0x7FFF
#define MD_LCD_YELLOW             0xFFE0
#define MD_LCD_BROWN              0XBC40
#define MD_LCD_BRRED              0XFC07
#define MD_LCD_GRAY               0X8430

#define MD_LCD_BACKGRAUND_COLOR MD_LCD_BLACK
#define MD_LCD_FONT_COLOR        MD_LCD_GREEN
/*================================= Public Interface =========================*/

/** font list */
typedef enum
{
    MD_LCD_FONT_1608 = FONT_CHAR_SIZE_1608,
    MD_LCD_FONT_2412 = FONT_CHAR_SIZE_2412,
    MD_LCD_FONT_3216 = FONT_CHAR_SIZE_3216,
    MD_LCD_FONT_4824 = FONT_CHAR_SIZE_4824,
}md_lcd_font_enum;

#define MD_LCD_FONT_DEF    MD_LCD_FONT_4824     /**< default font */
#define MD_LCD_FONT_DEF_WIDTH     24
#define MD_LCD_FONT_DEF_HEIGHT    48

/*================================= Public Interface =========================*/

/*!*****************************************************************************
* @brief      initialize
* @details
* @param[in]    void
* @return     void
*******************************************************************************/
void md_lcd_init(void);

/*!*****************************************************************************
* @brief        draw a char
* @param[in]    uint16_t x £º x coordinate
* @param[in]    uint16_t y £º y coordinate
* @param[in]    uint8_t chr : ascii char
* @param[in]    md_lcd_font_enum font £º
* @param[in]    bool draw_background £º
* @return       void
*******************************************************************************/
void md_lcd_show_charEx(uint16_t x, uint16_t y, uint8_t chr, md_lcd_font_enum font_size, bool draw_backgraund);

/*!*****************************************************************************
* @brief      show string
* @param[in]    uint16_t x,y :    start coordinate
* @param[in]    uint8_t * str £º  string to be printed.(must end with '* @0')
* @param[in]    md_lcd_font_enum font £º
* @param[in]    bool draw_background £º if true, renew background
* @return     void
*******************************************************************************/
void md_lcd_show_stringEx(uint16_t x, uint16_t y, char* str, md_lcd_font_enum font, bool draw_backgraund);

/*!*****************************************************************************
* @brief      show bitmap icon
* @param[in]    uint16_t x    x coordinate
* @param[in]    uint16_t y    y coordinate
* @param[in]    lib_image_struct * image
* @param[in]    bool draw_background  If true, renew background
* @return     void
*******************************************************************************/
void md_lcd_show_image(uint16_t x, uint16_t y, const lib_image_struct* image, bool draw_backgraund);

/*!*****************************************************************************
* @brief      print number
* @param[in]    uint16_t x
* @param[in]    uint16_t y
* @param[in]    int number
* @param[in]    md_lcd_font_enum font
* @param[in]    bool draw_background      If true, renew background
* @return     void
*******************************************************************************/
void md_lcd_show_numberEx(uint16_t x, uint16_t y, int number, md_lcd_font_enum font, bool draw_backgraund);

#define md_lcd_show_number(x, y, num) md_lcd_show_numberEx(x, y, num, MD_LCD_FONT_DEF, true)
#define md_lcd_claer_area(x, y, width, height)         drv_lcd_fill_retangle(x, y, width, height, MD_LCD_BACKGRAUND_COLOR)
#define md_lcd_show_string(x, y, str)    md_lcd_show_stringEx(x, y, str, MD_LCD_FONT_DEF, false)
#define md_lcd_show_string_bg(x, y, str)    md_lcd_show_stringEx(x, y, str, MD_LCD_FONT_DEF, true)
#define md_lcd_show_char(x, y, chr)        md_lcd_show_charEx(x, y, chr, MD_LCD_FONT_DEF, true)


/** @}*/ //end of group md_lcd
#endif // MD_LCD_H
