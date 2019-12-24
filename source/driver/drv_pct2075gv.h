/*******************************************************************************
 *
 * Module: drv_pct2075gv
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/15 17:33          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_pct2075gv.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/15
  *******************************************************************************/
#ifndef DRV_PCT2075GV_H
#define DRV_PCT2075GV_H

/*! \defgroup drv_pct2075gv_public Public
\ingroup drv_pct2075gv
\brief
        PCT2075GV temperature sensor driver.

    example:
        #include "drv_pct2075gv.h"

        DRV_PCT2057GV_INSTANCE(temp_board, CFG_PCT2075GV_SDA, CFG_PCT2075GV_SCL, CFG_PCT2075GV_ADDR);

        void module_layer_init(void)
        {
             drv_pct2075gv_init(&temp_board);
             printf("temp: %d", drv_pct2075gv_get_temp(&temp_board));//unit: 1¡æ
        }
* @{ */

#include "app_config.h"
#include "drv_iic.h"

//********************************* Module Config *******************************/


//********************************* Data Type ***********************************/
/*! Device register address */
typedef enum
{
    DRV_PCT2075GV_REG_TEMP,            /*!< Temperature register: contains two 8-bit data bytes; to store the measured Temp data. */
    DRV_PCT2075GV_REG_CONF,            /*!< Configuration register: contains a single 8-bit data byte; to set the device operating condition; default = 0. */
    DRV_PCT2075GV_REG_THYST,           /*!< Hysteresis register: contains two 8-bit data bytes; to store the hysteresis Thys limit; default = -10 ¡æ(0xF600). */
    DRV_PCT2075GV_REG_TOS,             /*!< Overtemperature shutdown threshold register: contains two 8-bit data bytes; to store the overtemperature shutdown Tots limit; default = -5 ¡æ(0xFB00) */
    DRV_PCT2075GV_REG_TIDLE,           /*!< Temperature conversion cycle, default to 100 ms. */
}drv_pct2057gv_reg_enum;

/*! PCT2075GV driver instance structure */
typedef struct
{
    drv_iic_instance_t driver;
    uint8_t sample_interval;        /*!< Sample interval, unit: 100ms, valid range [1 - 31], default value: 1 */
    bool is_sleep;                  /*!< Is device sleeping */
}drv_pct2057_instance_t;


//********************************* Public Interface ****************************/

/*!*****************************************************************************
\brief  	Use this macro to quickly define a PCT2057GV instance .

\param[in]	_name        : The name of the instance.
\param[in]	_sda_pin     : The pin number of MCU that connected to the SDA pin of PCT2057GV.
\param[in]	_scl_pin     : The pin number of MCU that connected to the SCL pin of PCT2057GV.
\param[in]	_iic_addr    : The device's IIC addr.
*******************************************************************************/
#define DRV_PCT2057GV_INSTANCE(_name, _sda_pin, _scl_pin, _iic_addr)    \
    static drv_pct2057_instance_t _name ={    \
        {.sda_pin = _sda_pin,    .scl_pin = _scl_pin,    .addr = _iic_addr}    \
};

bool drv_pct2075gv_init(drv_pct2057_instance_t* instance);

int8_t drv_pct2075gv_get_temp(drv_pct2057_instance_t* instance);
int16_t drv_pct2075gv_get_tempEx(drv_pct2057_instance_t* instance);
float drv_pct2075gv_get_tempExf(drv_pct2057_instance_t* instance);

bool drv_pct2075gv_set_measurement_interval(drv_pct2057_instance_t* instance, uint8_t nX100ms);
bool drv_pct2075gv_go_sleep(drv_pct2057_instance_t* instance);
bool drv_pct2075gv_awake(drv_pct2057_instance_t* instance);

//********************************* Private Interface ***************************/





/*! @}*/ //end of group drv_pct2075gv
#endif // DRV_PCT2075GV_H
