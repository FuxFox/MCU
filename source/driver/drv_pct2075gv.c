/*******************************************************************************
 *
 * Module: drv_pct2075gv
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/15 17:32          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_pct2075gv.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/15
  *******************************************************************************/
#ifndef DRV_PCT2075GV_C
#define DRV_PCT2075GV_C

#include "drv_pct2075gv.h"

  /*!*****************************************************************************
  \brief      initialize
  \details
  \param[in]    void
  \return     void
  ******************************************************************************/
bool drv_pct2075gv_init(drv_pct2057_instance_t* instance)
{
    instance->driver.reg_addr_16bit = false;
    instance->is_sleep = false;
    instance->sample_interval = 1;

    return drv_iic_init(&instance->driver);
}


/*!*****************************************************************************
\brief          Get temperature, int8
\details        unit: 1¡æ, resolution: 1¡æ, 8bit
\param[in]      drv_pct2057_instance_t* instance
\return     int8_t      Return temperature(¡æ) if success or 0 if failure
******************************************************************************/
int8_t drv_pct2075gv_get_temp(drv_pct2057_instance_t* instance)
{
    uint8_t temp;

    if (drv_iic_read(&instance->driver, DRV_PCT2075GV_REG_TEMP, &temp, 1))
    {
        return (int8_t)temp;
    }

    return 0;
}


/*!*****************************************************************************
\brief       Get temperature, int16
\details     Temperature unit: 0.01¡æ
             Temperature resolution: 0.25¡æ, 10bits
\note        The max resolution of the chip is 11bits(0.125¡æ).Here only use 10bits.
\param[in]   drv_pct2057_instance_t* instance
\return     int16_t     Return temperature(¡æ) if success or 0 if failure
******************************************************************************/
int16_t drv_pct2075gv_get_tempEx(drv_pct2057_instance_t* instance)
{
    uint8_t* temp[2];
    uint16_t resault;

    if (drv_iic_read(&instance->driver, DRV_PCT2075GV_REG_TEMP, temp, 2))
    {
        resault = temp[0] * 100 + (temp[1] >> 5) * 25;
        return resault;
    }

    return 0;
}

/*!*****************************************************************************
\brief       Get temperature, float
\details     Temperature unit: 1¡æ
             Temperature resolution: 0.125¡æ, 11bits
\note        The max resolution of the chip is 11bits(0.125¡æ).
\param[in]   drv_pct2057_instance_t* instance
\return     float     Return temperature(¡æ) if success or 0 if failure
******************************************************************************/
float drv_pct2075gv_get_tempExf(drv_pct2057_instance_t* instance)
{
    uint8_t temp[2];

    if (drv_iic_read(&instance->driver, DRV_PCT2075GV_REG_TEMP, temp, 2))
    {
        return ((int8_t)temp[0] + (temp[1] >> 5) * 0.125);
    }

    return 0;
}

/*!*****************************************************************************
\brief      Set measurement interval
\details        range [100ms - 3.1s]
\param[in]    uint8_t nX100ms Sample interval, unit: 100ms, valid range [1 - 31], reset value: 1
\return     void
******************************************************************************/
bool drv_pct2075gv_set_measurement_interval(drv_pct2057_instance_t* instance, uint8_t nX100ms)
{
    if (drv_iic_write(&instance->driver, DRV_PCT2075GV_REG_TIDLE, &nX100ms, 1))
    {
        instance->sample_interval = nX100ms;
        return true;
    }

    return false;
}

/*!*****************************************************************************
\brief      go sleep, current <1uA
\details        Stop measurement, IIC interface still valid
\param[in]    void
\return     void
******************************************************************************/
bool drv_pct2075gv_go_sleep(drv_pct2057_instance_t* instance)
{
    uint8_t conf;

    if (!instance->is_sleep)
    {
        drv_iic_read(&instance->driver, DRV_PCT2075GV_REG_CONF, &conf, 1);
        conf |= 1;
        if (!drv_iic_write(&instance->driver, DRV_PCT2075GV_REG_CONF, &conf, 1))
        {
            return false;
        }

        instance->is_sleep = true;
    }

    return true;
}

/*!*****************************************************************************
\brief      Wake up
\details        resum measurement
\param[in]    void
\return     void
******************************************************************************/
bool drv_pct2075gv_awake(drv_pct2057_instance_t* instance)
{
    uint8_t conf;

    if (instance->is_sleep)
    {
        drv_iic_read(&instance->driver, DRV_PCT2075GV_REG_CONF, &conf, 1);

        conf &= ~0x01;
        if (!drv_iic_write(&instance->driver, DRV_PCT2075GV_REG_CONF, &conf, 1))
        {
            return false;
        }
        instance->is_sleep = false;
    }

    return true;
}
#endif // DRV_PCT2075GV_C
