/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/08/13 16:50          V1.0             build this file
 *
 *******************************************************************************/
#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/*! \defgroup  Application_Config
\brief 
\details
* @{ */

#ifdef __cplusplus
extern "C" {
#endif
/**************************** Macro ************************************/
#include "app_macro.h"
#include "custom_board.h"

/**************************** Standard header *********************************/
#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


/**************************** SDK **************************************/


/**************************** CMSIS Configure Wizard *******************/

// <<< Use Configuration Wizard in Context Menu >>>\n

// <s> DEVICE_NAME - Name of device. Will be included in the advertising data.
#ifndef DEVICE_NAME
#define DEVICE_NAME             "Machine"    
#endif
// <s> MANUFACTURER_NAME
#define MANUFACTURER_NAME        "FuxFox"
// <s> FIRMWARE_VERSION
#define FIRMWARE_VERSION        "v0.0.0"

// <h> USER_DRIVER
//==========================================================


// </h>
//==========================================================


// <h> APP_LIBARY
//==========================================================

// <e> APP_LOG_ENABLE
//==========================================================
#ifndef CFG_LOG_ENABLE
#define CFG_LOG_ENABLE 1
#endif

// <o> APP_LOG_LEVEL - log display level
// <0=> NONE 
// <1=> ERROR 
// <2=> WARNING 
// <3=> INFO 
// <4=> DEBUG 
#ifndef CFG_LOG_LEVEL
#define CFG_LOG_LEVEL 4
#endif

// <e> APP_LOG_TAG_ENABLE
#ifndef CFG_LOG_TAG_ENABLE
#define CFG_LOG_TAG_ENABLE 0
#endif
// </e> 

// <e> APP_LOG_TIMESTAMP_ENABLE
#ifndef CFG_LOG_TIMESTAMP_ENABLE
#define CFG_LOG_TIMESTAMP_ENABLE 0
#endif
// </e> 

// <e> APP_LOG_COLORS_ENABLE
#ifndef CFG_LOG_COLORS_ENABLE
#define CFG_LOG_COLORS_ENABLE 0
#endif
// </e> 

// <e> APP_LOG_ASSERT_ENALBLE
#ifndef CFG_LOG_ASSERT_ENALBLE
#define CFG_LOG_ASSERT_ENALBLE 0
#endif
// </e> 

// <o> APP_LOG_BAUDRATE - set baud rate if use UART to print log
#define CFG_LOG_BAUDRATE 2400

// <o> APP_LOG_ASSERT_ENABLE
#define CFG_LOG_ASSERT_ENABLE 0

// </e> 
//==========================================================

// <e> APP_BUTTON_ENABLE
//==========================================================
#define APP_BUTTON_ENABLE        1

//<o> APP_BUTTON_SCAN_INTERVAL - button scan interval in ms
#define CFG_BUTTON_SCAN_INTERVAL                50

//<o> APPG_BUTTON_DETECTION_DELAY - Shake off delay in ms
#define CFG_BUTTON_DETECTION_DELAY                20

//<o> APP_BUTTON_LONG_PRESS_DETECT_DELAY - long press detect
#define CFG_BUTTON_LONG_PRESS_DETECT_DELAY        200

//<o> APP_BUTTON_LONGLONG_PRESS_TIME_MS - long press detect
#define CFG_BUTTON_LONGLONG_PRESS_TIME_MS        5000

//<q> APP_BUTTON_REALTIME_MODE
//<i> if true, key scanned in interrupt as real time
//<i> if false, key scanned in main loop, not real time.
#define CFG_BUTTON_REALTIME_MODE    0        


// <e> APP_BUTTON_LINEAR_ENABLE - enable linear keyboard
#define APP_BUTTON_LINEAR_ENABLE 0
// </e> 

// <e> APP_BUTTON_MATRIX_ENABLE - enable matrix keyboard
#define CFG_BUTTON_MATRIX_ENABLE 1

//<o> APP_BUTTON_MATRIX_INPUT_BANDWIDE - number of pins used as input
#define CFG_BUTTON_MATRIX_INPUT_BANDWIDE	5

//<o> APP_BUTTON_MATRIX_OUTPUT_BANDWIDE - number of pins used as output
#define CFG_BUTTON_MATRIX_OUTPUT_BANDWIDE	5

// <e> APP_BUTTON_MATRIX_ALLOW_GND_AS_OUTPUT_LINE
//<i> If enable this, you are allowed to connect an output line to GND.
//<i> It can extend the matrix keyboard to use more keys (additional output line).
//<i> ATTENTION: When a key on GND line is pressed, other keys on the same input line can not be scanned.* /
#define CFG_BUTTON_MATRIX_ALLOW_GND_AS_OUTPUT_LINE 1
// </e> 

/*
// <e> APP_BUTTON_MATRIX_COMBINATION_SUPPORT
#define CFG_BUTTON_MATRIX_COMBINATION_SUPPORT	1
// </e> 
*/

// </e> 

// </e> 
//==========================================================


// <e> APP_TIMER_ENABLE - the software timer
//==========================================================
#define APP_TIMER_ENABLE 1

//<o> APP_TIMER_NUM_MAX - the max quantity of soft timer 
#define CFG_APP_TIMER_NUM_MAX 7    

/*
// <e> APP_TIMER_CHAIN_LIST_SUPPORT
//<i> You can use chain list, if you are allowed to use malloc()
#define CFG_APP_TIMER_CHAIN_LIST_SUPPORT 0
// </e> 
*/

// </e> 
//==========================================================

// </h> 
//==========================================================

// <<< end of configuration section >>>



/********************************* drver config ***************************************/




/********************************* module config ***************************************/


#ifdef __cplusplus
}
#endif

/*! @}*/ //end of group BoardConfig
#endif // app_config_H
