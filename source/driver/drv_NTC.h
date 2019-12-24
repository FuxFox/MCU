/*******************************************************************************
 *
 * Module: drv_NTC
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/20 11:53          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_NTC.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/11/20
  *******************************************************************************/
#ifndef DRV_NTC_H
#define DRV_NTC_H

/*! \defgroup drv_NTC_public Public
\ingroup drv_NTC
\brief            NTC resistor driver, this driver is implemented base on STM32F103xxx with HAL_ADC.
\details        The NTC resistor is MF52A103 F 3950 (A1)(UL:E240991)

\note           You can modify the interface of ADC to make this driver able to use for your MCU.
                You can modify the parameter of NTC to use other NTC resistor.
                This driver uses math.h library.
* @{ */

#include "app_config.h"

#include "app_gpio.h"
  //********************************* Module Config *******************************/

#define DRV_NTC_ADC_ID    1                               /*!< The ADC of STM32 used by this driver, range[1-3] */

#define DRV_NTC_K0        273.15            
#define DRV_NTC_T0        (DRV_NTC_K0 + 25.0)    
#define DRV_NTC_R0        10000                           /*!< Resistance of the NTC resistor , at 25¡æ */
#define DRV_NTC_B         3950                            /*!< The B value of the NTC resistor */
#define DRV_NTC_DIVIDER_RESISTOR        22000             /*!< Voltage divider resistance in Ohm */
#define DRV_NTC_AVERAGE_TIMES           10                /*!< The driver will sample specified times to obtain precise temperature */

//********************************* Data Type ***********************************/

/*! NTC instance */
typedef struct
{
    uint8_t input_pin;        /*!< the pin number of chip */
    uint8_t adc_channel;      /*!< the ADC channel [ADC_CHANNEL_0 - ADC_CHANNEL_17]*/
}drv_NTC_instance_t;


//********************************* Public Interface ****************************/

#define DRV_NTC_INSTANCE(_name, _pin, _channel)    \
    static drv_NTC_instance_t _name = {            \
        .input_pin = _pin,                         \
        .adc_channel = _channel                    \
}


void drv_NTC_init(drv_NTC_instance_t* instance);
float drv_NTC_get_temperature(drv_NTC_instance_t* instance);
//********************************* Private Interface ***************************/

static uint32_t drv_NTC_get_resistance(void);



/*! @}*/ //end of group drv_NTC
#endif // DRV_NTC_H
