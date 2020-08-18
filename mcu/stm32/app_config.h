/*!*****************************************************************************
* @file     app_config.h
* @brief    
* @author   FuxFox
* @version  V1.0
* @date       2019/05/21
*******************************************************************************/
#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/**
* @defgroup  app_config
* @ingroup config
* @brief 
* @details
* @{ */

#ifdef __cplusplus
extern "C" {
#endif

/*=========================== Custom Board ===================================*/
#include "custom_board.h"

/*=========================== Standard header ================================*/
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*=========================== SDK ============================================*/
#include "sdk_config.h"

#include "stm32f103xe.h"
#include "stm32f1xx_hal.h"


typedef enum
{
	OFF = 0,
	ON = 1
}SWITCH_enum;

/*=========================== CMSIS Configure Wizard =========================*/

// <<< Use Configuration Wizard in Context Menu >>>\n

// <s> DEVICE_NAME - Name of device. Will be included in the advertising data.
#define DEVICE_NAME             "Machine"                         
// <s> MANUFACTURER_NAME
#define MANUFACTURER_NAME        "2333"
// <s> FIRMWARE_VERSION
#define FIRMWARE_VERSION        "v0.9.0"

// <h> USER_DRIVER
//==========================================================

// <e> DRV_IRM    - Infrared Receiver Module Driver
//==========================================================
#define DRV_IRM_ENABLE    1

// <o> DRV_IRM_LOG_LEVEL
// <0=> NONE 
// <1=> INFO 
// <2=> ERROR 
// <3=> WARNING 
// <4=> DEBUG 
#define DRV_IRM_LOG_LEVEL 0


// </e> 
//==========================================================



// </h>
//==========================================================


// <h> APP_LIBARY
//==========================================================

// <e> APP_LOG_ENABLE
//==========================================================
#ifndef APP_LOG_ENABLE
#define APP_LOG_ENABLE 1
#endif

// <o> APP_LOG_LEVEL - log display level
// <0=> NONE 
// <1=> INFO 
// <2=> ERROR 
// <3=> WARNING 
// <4=> DEBUG 
#define APP_LOG_LEVEL 4

// </e> 
//==========================================================

// <e> APP_DELAY_ENABLE
//==========================================================
#ifndef APP_DELAY_ENABLE
#define APP_DELAY_ENABLE 1
#endif

//<e> APP_DELAY_USE_HAL_LIB - Use HAL_Delay or other function that use systick
#ifndef APP_DELAY_USE_HAL_LIB
#define APP_DELAY_USE_HAL_LIB 1
#endif

//<o> APP_DELAY_SYSTICK_PRIORITY 
//<i> if use delsy function in intterupt, the systick's priority mast higher than that interrupt's
#ifndef APP_DELAY_SYSTICK_PRIORITY
#define APP_DELAY_SYSTICK_PRIORITY 5
#endif
// </e> 
//==========================================================

// </e> 
//==========================================================


// <e> APP_BUTTON_ENABLE
//==========================================================
#define APP_BUTTON_ENABLE        1

//<o> APP_BUTTON_SCAN_INTERVAL - button scan interval in ms
#define CFG_BUTTON_SCAN_INTERVAL                100

//<o> APPG_BUTTON_DETECTION_DELAY - Ïû¶¶Ê±¼ä£¬ in ms
#define CFG_BUTTON_DETECTION_DELAY                10

//<o> APP_BUTTON_LONG_PRESS_DETECT_DELAY - long press detect
#define CFG_BUTTON_LONG_PRESS_DETECT_DELAY        2000

//<q> APP_BUTTON_REALTIME_MODE
//<i> if true, key scanned in interrupt as real time
//<i> if false, key scanned in main loop, not real time.
#define CFG_BUTTON_REALTIME_MODE    1        

// </e> 
//==========================================================

// <e> APP_GPIO_ENABLE
//==========================================================
#define APP_GPIO_ENABLE 1



// </e> 
//==========================================================


// <e> APP_TIMER_ENABLE - the software timer
//==========================================================
#define APP_TIMER_ENABLE        1
 
//<o> APP_TIMER_NUM_MAX - the max quantity of soft timer 
#define CFG_APP_TIMER_NUM_MAX 10    



// </e> 
//==========================================================

// <e> APP_USART_ENABLE
//==========================================================
#define APP_USART_ENABLE 1



// </e> 
//==========================================================

// </h> 
//==========================================================

// <<< end of configuration section >>>



/*=========================== drver config ===================================*/





//=========================== EEPROM_24c02 =====================================
#define CFG_EEPROM_TYPE            AT24C01
#define CFG_EEPROM_ADDR             0xA0
#define CFG_EEPROM_SDA            PIN_FLASH_I2C_SDA
#define CFG_EEPROM_SCL            PIN_FLASH_I2C_SCL

//=========================== temp_board =======================================
#define CFG_PCT2075GV_SDA        PIN_TEMP_I2C_SDA
#define CFG_PCT2075GV_SCL        PIN_TEMP_I2C_SCL
#define CFG_PCT2075GV_ADDR        0x92

/*=========================== module config ==================================*/

//=========================== weight_sensor ====================================
#define CFG_WEIGHT_SENSOR_CFG_ADDR                0x0
#define CFG_WEIGHT_SENSOR_CFG_VALID_FLAG        0xFA
#define CFG_WEIGHT_SENSOR_UNIT_GRAM                500


#ifdef __cplusplus
}
#endif

/** @}*/ //end of group BoardConfig
#endif // app_config_H
