/*!*****************************************************************************
* \file     md_battery.h
* \brief    
* \author   FuxFox
* \version  V1.0
* \date  	2019/07/26
*******************************************************************************/
#ifndef MD_BATTERY_H
#define MD_BATTERY_H

/**
* @defgroup md_battery
* @ingroup module
* @brief      The battery detection module implemented base on NRF52832.The charging chip is SLM6600.
* @details 
*           During charging, the voltage is pull up about 0.4V, we use MD_BATTERY_CHARGING_VOLTAGE_CALIBRATE to reduce error.
*           During charging, we consider MD_BATTERY_CHARGING_CURRENT and MD_BATTERY_CAPABILITY to calculate the percent of battery.
* @{ */

#include "app_config.h"


/*================================= Module Config ============================*/
#define MD_BATTERY_CHARGING_SUPPORT			CFG_BATTERY_CHARGING_SUPPORT	        /*!< Whether charging is supported, true -> support*/
#define MD_BATTERY_CHARGING_VOLTAGE_CALIBRATE	CFG_BATTERY_CHARGING_VOLTAGE_CALIBRATE	/*!< The calibrate value of voltage during charging */
#define MD_BATTERY_CHARGE_DETECT_PIN			CFG_BATTERY_CHARGE_DETECT_PIN           
#define MD_BATTERY_CHARGE_FULL_PIN				CFG_BATTERY_CHARGE_FULL_PIN
#define MD_BATTERY_CAPABILITY					CFG_BATTERY_CAPABILITY                 /*!< The max capability of battery, unit: mah */
#define MD_BATTERY_CHARGING_CURRENT			CFG_BATTERY_CHARGING_CURRENT           /*!< Charging current, unit: mah */

#define MD_BATTERY_DETECT_SAMPLE_RATE			CFG_BATTERY_VOLTAGE_SAMPLE_RATE		/*!< sample rate, use to calculate average */
#define MD_BATTERY_SAMPLE_INTERVAL_MS			CFG_BATTERY_SAMPLE_INTERVAL_MS	        /*!< ADC sample interval, unit: ms */

#define MD_BATTERY_DETECT_ADC_CHANNEL			CFG_BATTERY_DETECT_ADC_CHANNEL         /*!< The number of ADC channel */

#define MD_BATTERY_FULL_VOLTAGE				CFG_BATTERY_FULL_VOLTAGE		        /*!< The max voltage of battery, unit: 10mv */
#define MD_BATTERY_LEST_VOLTAGE				CFG_BATTERY_LEAST_VOLTAGE		        /*!< The least voltage of battery, unit: 10mv */

/*================================= Data Type ================================*/

/**
* The callback function will be call when battery value change 1%
* @param battery_percent  : current battery percent
*/
typedef void (*battery_change_callback)(uint8_t battery_percent);

/*================================= Public Interface =========================*/

/*!*****************************************************************************
* @brief  	battery voltage level detect initialize
* @param[in]	battery_change_callback	 : Will be call if battery voltage change greater than 1%.
*                                          Can be NULL.
* @return     void
*******************************************************************************/
void md_battery_init(battery_change_callback callback);

/*!*****************************************************************************
* @brief  	get average voltage
* @param[in]	void
* @return     uint16_t	voltage, unit: 10mV
*******************************************************************************/
uint16_t md_battery_get_voltage(void);

/*!*****************************************************************************
* @brief  	get battery percent
* @param[in]	void
* @return
*******************************************************************************/
uint8_t md_battery_get_percent(void);

/*!*****************************************************************************
* @brief  	is charging?
* @param[in]	void
* @return     bool TRUE£ºcharging£¬FALSE£ºno charging
*******************************************************************************/
bool md_battery_is_charging(void);

/** @}*/ //end of group md_battery
#endif // MD_BATTERY_H
