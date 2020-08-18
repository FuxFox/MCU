/*!*****************************************************************************
* @file     custom_board.h
* @brief    Customer board pin define for nrf52832
* @author   FuxFox
* @version  V1.0
* @date     2019/08/01
*******************************************************************************/
#ifndef CUSTOM_BOARD_H
#define CUSTOM_BOARD_H

/**
* @defgroup custom_board
* @ingroup config
* @details  GPIO pin allocation
* @{ */

#define LED_START      30
#define LED_GREEN      30
#define LED_RED        31

#define LEDS_ACTIVE_STATE 0  //LOW level led on
#define LEDS_INV_MASK  LEDS_MASK

#define LEDS_LIST { LED_GREEN, LED_RED}


#define BUTTON_PWR        20            //key_pwr

#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP
#define BUTTONS_ACTIVE_STATE 0

#define BUTTONS_LIST {BUTTON_PWR}

//====================== key matrix ============================
#define KEY_COLUMN_CNT    5
#define KEY_ROW_CNT        4

#define KEY_COLUMN_1     11
#define KEY_COLUMN_2     12
#define KEY_COLUMN_3     13
#define KEY_COLUMN_4     14
#define KEY_COLUMN_5     15
#define KEY_ROW_1        16
#define KEY_ROW_2        17
#define KEY_ROW_3        18
#define KEY_ROW_4        19

#define KEY_COLUMN_PULL    NRF_GPIO_PIN_PULLUP
#define KEY_ROW_PULL    NRF_GPIO_PIN_PULLDOWN
#define KEY_ACTIVE_STATE 0
//======================

#define POWER_CTRL         29
#define BAT_CHARG_IN       26
#define BAT_CHARG_FULL     25
#define BAT_DETECT         2
#define BAT_CHARG_PULL    NRF_GPIO_PIN_PULLUP

#define UART_TXD_PIN       3
#define UART_RXD_PIN       4

#define LCD_RST            5
#define LCD_SPI_CS         6
#define LCD_RS             7
#define LCD_SPI_CLK        8
#define LCD_SPI_DI         9
#define LCD_BACKLIGHT      10        //high for ON

#define AUDIO_BUSY         24
#define AUDIO_DATA         23
#define AUDIO_SPK_EN       22

#define IN1_D              28
#define IN2_D              27
/** @}*/ //end of group custom_board
#endif // CUSTOM_BOARD_H
