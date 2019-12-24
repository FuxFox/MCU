/*******************************************************************************
 *
 * Module: md_battery
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2019/07/26 15:32          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     md_battery.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date  	 2019/07/26
 *******************************************************************************/
#ifndef MD_BATTERY_H
#define MD_BATTERY_H

/*! \defgroup md_battery_public Public
\ingroup md_battery
\brief      The battery detection module implemented base on NRF52832.The charging chip is SLM6600.
            During charging, the voltage is pull up about 0.4V, we use MD_BATTERY_CHARGING_VOLTAGE_CALIBRATE to reduce error.
            During charging, we consider MD_BATTERY_CHARGING_CURRENT and MD_BATTERY_CAPABILITY to calculate the percent of battery.
            
\details 
* @{ */

#include "app_config.h"


//********************************* Module Config *******************************/
#define MD_BATTERY_CHARGING_SUPPORT				CFG_BATTERY_CHARGING_SUPPORT	        /*!< Whether charging is supported, true -> support*/
#define MD_BATTERY_CHARGING_VOLTAGE_CALIBRATE	CFG_BATTERY_CHARGING_VOLTAGE_CALIBRATE	/*!< The calibrate value of voltage during charging */
#define MD_BATTERY_CHARGE_DETECT_PIN			CFG_BATTERY_CHARGE_DETECT_PIN           
#define MD_BATTERY_CHARGE_FULL_PIN				CFG_BATTERY_CHARGE_FULL_PIN
#define MD_BATTERY_CAPABILITY					CFG_BATTERY_CAPABILITY                  /*!< The max capability of battery, unit: mah */
#define MD_BATTERY_CHARGING_CURRENT				CFG_BATTERY_CHARGING_CURRENT            /*!< Charging current, unit: mah */

#define MD_BATTERY_DETECT_SAMPLE_RATE			CFG_BATTERY_VOLTAGE_SAMPLE_RATE			/*!< sample rate, use to calculate average */
#define MD_BATTERY_SAMPLE_INTERVAL_MS			CFG_BATTERY_SAMPLE_INTERVAL_MS	        /*!< ADC sample interval, unit: ms */

#define MD_BATTERY_DETECT_ADC_CHANNEL			CFG_BATTERY_DETECT_ADC_CHANNEL          /*!< The number of ADC channel */

#define MD_BATTERY_FULL_VOLTAGE					CFG_BATTERY_FULL_VOLTAGE		        /*!< The max voltage of battery, unit: 10mv */
#define MD_BATTERY_LEST_VOLTAGE					CFG_BATTERY_LEAST_VOLTAGE		        /*!< The least voltage of battery, unit: 10mv */

//********************************* Data Type ***********************************/

/*! The callback function will be call when battery value change 1%
@param battery_percent  : current battery percent
*/
typedef void (*battery_change_callback)(uint8_t battery_percent);
//********************************* Public Interface ****************************/


void md_battery_init(battery_change_callback callback);

uint16_t md_battery_get_voltage(void);
uint8_t md_battery_get_percent(void);
bool md_battery_is_charging(void);

//********************************* Private Interface ***************************/
void md_battery_adc_config(void);
static void md_battery_get_first_data(void);
uint16_t md_battery_GetAverageVoltage(void);
static void md_battery_detect_TimerHandler(void* context);
static uint16_t md_battery_get_sample(void);
static uint8_t md_battery_get_percentEx(void);
/*! @}*/ //end of group md_battery
#endif // MD_BATTERY_H
