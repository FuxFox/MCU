/*!*****************************************************************************
* @file     app_config.h
* @brief    User application configure for nrf52832
* @author   FuxFox
* @version  V1.0
* @date     2019/05/21
*******************************************************************************/
#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/**
* @defgroup app_config app_config
* @ingroup config
* @brief User application configure for nrf52832
* @details
* @{ */

#ifdef __cplusplus
extern "C" {
#endif

#include "custom_board.h"

/*=========================== Standard header ================================*/
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*=========================== SDK ============================================*/
#include "nordic_common.h"

#include "nrf.h"
#include "nrf_drv_clock.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_pwm.h"
#include "nrf_drv_rtc.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_power.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_sdh_soc.h"
#include "nrf_soc.h"
#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif

#include "nrf_fstorage.h"
#include "nrf_fstorage_sd.h"
#include "fds.h"

#include "nrf_bootloader_info.h"
#include "nrf_dfu_ble_svci_bond_sharing.h"
#include "nrf_svci_async_function.h"
#include "nrf_svci_async_handler.h"

#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#include "ble.h"
#include "ble_gatt.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "ble_conn_state.h"
#include "ble_dfu.h"
#include "ble_err.h"
#include "ble_hci.h"
#include "ble_srv_common.h"

#include "peer_manager.h"
#include "peer_manager_handler.h"

#include "mem_manager.h"

#include "app_button.h"
#include "app_error.h"
#include "app_pwm.h"
#include "app_timer.h"
#include "app_util.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


/*=========================== Drver config ===================================*/
#define CFG_LCD_SPI_INSTANCE    0        /**< SPI instance index. */

/*=========================== Module config ==================================*/

//=================== md_battery ===========================
#define CFG_BATTERY_CHARGING_SUPPORT               1
#define CFG_BATTERY_VOLTAGE_SAMPLE_RATE            6
#define CFG_BATTERY_SAMPLE_INTERVAL_MS             10000    
#define CFG_BATTERY_DETECT_ADC_CHANNEL             0
#define CFG_BATTERY_FULL_VOLTAGE                   420        /*!< max voltage(4.2V)，unit: 10mV */
#define CFG_BATTERY_LEAST_VOLTAGE                  340
#define CFG_BATTERY_ALERT_PERCENT                  10         /*!< low power alert when battery low then 10% */
#define CFG_BATTERY_SHUTDOWN_PERCENT               1          /*!< low power shutdown, when battery low then 1% */
#define CFG_BATTERY_CAPABILITY                     6000       /*!< battery capability, in mAh */                    
#define CFG_BATTERY_CHARGING_CURRENT               450        /*!< battery charging current, in mA */                    
#define CFG_BATTERY_CHARGING_VOLTAGE_CALIBRATE    (-20)       /*!< voltage calibrate value while charging for ADC detection */
#define CFG_BATTERY_CHARGE_DETECT_PIN              BAT_CHARG_IN
#define CFG_BATTERY_CHARGE_FULL_PIN                BAT_CHARG_FULL

//=================== md_led_pwm ===========================
#define CFG_LED_PWM_ID							0	    /*!< PWM id */
#define CFG_LED_PWM_FREQ_HZ						100		/*!< PWM frequency, unit: Hz , recommend [50~1000]*/
#define CFG_LED_PWM_BREATH_STEP_INTERVAL		120		/*!< breathing lamp step interval , in ms*/
#define CFG_LED_PWM_FAST_BLINK_INTERVAL			200		/*!< fast blink, half of period, in ms */
#define CFG_LED_PWM_SLOWLY_BLINK_INTERVAL		500		/*!< slowly blink, half of period, in ms */


//=================== md_store ===========================
#define CFG_STOER_FLASH_START_ADDR         0x72000
#define CFG_STORE_FLASH_END_ADDR           0x74FFF
#define CFG_STORE_DATA_VALID_FLAG          0x5A            /*!< flash 内容有效标志 */

#define CFG_STORE_MOTOR_CONFIG_ADDR        0x73000

#define CFG_STORE_DEVICE_NAME_ADDR         0x72000
#define CFG_STORE_DEVICE_NAME_LEN          20                

#define CFG_STORE_PWR_DOWN_FLAG_ADDR       0x74000         /*!< exception power down flag address */


/*=========================== ui config ======================================*/

#define CFG_BUTTON_DETECTION_DELAY          (10)                     /**< Delay from a GPIOTE event until a button is reported as pushed (in number of timer ticks). */
#define CFG_BUTTON_LONG_PRESS_DETECT_DELAY    (3000)


/*=========================== CMSIS Configure Wizard =========================*/


// <<< Use Configuration Wizard in Context Menu >>>\n


// <s> DEVICE_NAME - Name of device. Will be included in the advertising data.
#define DEVICE_NAME             "hello world"                         
// <s> MANUFACTURER_NAME
#define MANUFACTURER_NAME        "hello world"
// <s> FIRMWARE_VERSION
#define FIRMWARE_VERSION        "v0.8.0"



// <h> APP_BLE_CFG
//==========================================================

#define APP_BLE_OBSERVER_PRIO           3                                       /**< Application's BLE observer priority. You shouldn't need to modify this value. */
#define APP_BLE_CONN_CFG_TAG            1                                       /**< A tag identifying the SoftDevice BLE configuration. */

// <h> ADVERTISING_PARAM
//==========================================================

// <e> APP_ADV_FAST_ENABLE - enable fast advertising
//==========================================================
#define APP_ADV_FAST_ENABLE        1

// <o> APP_ADV_FAST_INTERVAL - The advertising interval in ms
#define APP_ADV_FAST_INTERVAL               MSEC_TO_UNITS(25, UNIT_0_625_MS)                                     /**< Fast advertising interval (in units of 0.625 ms. This value corresponds to 25 ms.). */

// <o> APP_ADV_FAST_DURATION - The advertising time-out (in ms).
// <i> When set to <0 = BLE_GAP_ADV_TIMEOUT_GENERAL_UNLIMITED>, we will never time out.
// <0-180000>
#define APP_ADV_FAST_DURATION               MSEC_TO_UNITS(30000, UNIT_10_MS)                                       /**< The advertising duration of fast advertising in units of 10 milliseconds. */

// </e> 
//==========================================================

// <e> APP_ADV_SLOW_ENABLE - enable slow advertising
//==========================================================
#define APP_ADV_SLOW_ENABLE        1

// <o> APP_ADV_SLOW_INTERVAL - The advertising interval in ms
#define APP_ADV_SLOW_INTERVAL               MSEC_TO_UNITS(2000, UNIT_0_625_MS)                 /**< Slow advertising interval (in units of 0.625 ms. This value corrsponds to 2 seconds). */

// <o> APP_ADV_SLOW_DURATION - The advertising time-out (in ms).
// <i> When set to <0 = BLE_GAP_ADV_TIMEOUT_GENERAL_UNLIMITED>, we will never time out.
// <0-180000>
#define APP_ADV_SLOW_DURATION               MSEC_TO_UNITS(0, UNIT_10_MS)                /**< The advertising duration of slow advertising in units of 10 milliseconds. */

// </e> 
//==========================================================
// </h>
//==========================================================

// <h> CONNECT_PARAM
//==========================================================

//<o> MIN_CONN_INTERVAL - Minimum acceptable connection interval
#define MIN_CONN_INTERVAL               MSEC_TO_UNITS(100, UNIT_1_25_MS)        /**< Minimum acceptable connection interval (0.5 seconds). */
//<o> MAX_CONN_INTERVAL - Maximum acceptable connection interval
#define MAX_CONN_INTERVAL               MSEC_TO_UNITS(800, UNIT_1_25_MS)        /**< Maximum acceptable connection interval (1 second). */
//<o> SLAVE_LATENCY - Slave latency.
#define SLAVE_LATENCY                   0                                       
//<o> CONN_SUP_TIMEOUT - Connection supervisory time-out
#define CONN_SUP_TIMEOUT                MSEC_TO_UNITS(4000, UNIT_10_MS)         /**< Connection supervisory time-out (4 seconds). */

//<o> FIRST_CONN_PARAMS_UPDATE_DELAY - in ms
//<i> Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called
#define FIRST_CONN_PARAMS_UPDATE_DELAY  APP_TIMER_TICKS(5000)                  /**<  (15 seconds). */
//<o> NEXT_CONN_PARAMS_UPDATE_DELAY - in ms
//<i> Time between each call to sd_ble_gap_conn_param_update after the first call
#define NEXT_CONN_PARAMS_UPDATE_DELAY   APP_TIMER_TICKS(30000)                   /**< Time between each call to sd_ble_gap_conn_param_update after the first call (5 seconds). */
//<o> MAX_CONN_PARAMS_UPDATE_COUNT
//<i> Number of attempts before giving up the connection parameter negotiation
#define MAX_CONN_PARAMS_UPDATE_COUNT    3    

// </h>
//==========================================================

// <h> SECURITY_PARAM
//==========================================================

//<q> SEC_PARAM_BOND
#define SEC_PARAM_BOND                  0                                           /**< Perform bonding. */
//<q> SEC_PARAM_MITM - Man In The Middle protection.
#define SEC_PARAM_MITM                  0                                           
//<q> SEC_PARAM_LESC - LE Secure Connections
#define SEC_PARAM_LESC                  0                                           /**<  not enabled. */
//<q> SEC_PARAM_KEYPRESS - Keypress notifications
#define SEC_PARAM_KEYPRESS              0                                           /**<  not enabled. */

//<o> SEC_PARAM_IO_CAPABILITIES - I/O capabilities.
//<0x00=> Display Only
//<0x01=> Display and Yes/No entry
//<0x02=> Keyboard Only
//<0x03=> No I/O capabilities(default)
//<0x04=> Keyboard and Display
#define SEC_PARAM_IO_CAPABILITIES       0x03                        /**< No  */

//<q> SEC_PARAM_OOB - Out Of Band data enable
#define SEC_PARAM_OOB                   0                                           /**<  not available. */
//<o> SEC_PARAM_MIN_KEY_SIZE - Minimum encryption key size
#define SEC_PARAM_MIN_KEY_SIZE          7                                           
//<o> SEC_PARAM_MAX_KEY_SIZE - Maximum encryption key size
#define SEC_PARAM_MAX_KEY_SIZE          16


// </h>
//==========================================================

#define DEAD_BEEF                       0xDEADBEEF                              /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */

// </h>
//==========================================================

//<q> UNIT_TEST_ENABLE
#define TEST_ENABLE        0

// <<< end of configuration section >>>
//==================================================
typedef enum
{
        OFF = 0,
        ON = 1
}SWITCH_enum;


#ifdef __cplusplus
}
#endif

/** @}*/ //end of group MingShanGlasses_BoardConfig
#endif // MINGSHANGLASSES_H
