/*******************************************************************************
 *
 * Module: drv_cs1237
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/28 15:31          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_cs1237.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/28
  *******************************************************************************/
#ifndef DRV_CS1237_H
#define DRV_CS1237_H

/*! \defgroup drv_cs1237_public Public
\ingroup drv_cs1237
\brief      CHIPSEA CS1237 24-bit Sigma-Delta ADC Driver

    example:
        DRV_CS1237_INSTANCE(weight_bucket_1, PIN_BUCKET_WEIGHT_1_DIN, PIN_BUCKET_WEIGHT_1_SCK);
        DRV_CS1237_INSTANCE(weight_bucket_2, PIN_BUCKET_WEIGHT_2_DIN, PIN_BUCKET_WEIGHT_2_SCK);

        void md_weight_sensor_init(void)
        {
            drv_cs1237_init(&weight_bucket_1);
            drv_cs1237_init(&weight_bucket_2);
        }

* @{ */

#include "app_config.h"

#include "app_delay.h"
#include "drv_spi.h"
  //********************************* Module Config *******************************/

#define DRV_CS1237_CMD_READ_CFG         (0x56 << 1)
#define DRV_CS1237_CMD_WRITE_CFG        (0x65 << 1)
#define DRV_CS1237_CFG_VALUE            0x0C

//********************************* Data Type ***********************************/

typedef drv_spi_instance_struct drv_cs1237_instance_t;

//********************************* Public Interface ****************************/

/*!*****************************************************************************
\brief  Use this macro to quickly define a CS1237 instance.

\param	_name       :   name of instance
\param	_sda_pin    :   The pin number of MCU that connected to the SDA pin of CS1237
\param	_sck_pin    :   The pin number of MCU that connected to the SCL pin of CS1237
*******************************************************************************/
#define DRV_CS1237_INSTANCE(_name, _sda_pin, _sck_pin) \
        DRV_SPI_INSTANCE(_name, NULL, _sda_pin, _sck_pin, NULL, NULL, DRV_SPI_MODE_1)

void drv_cs1237_init(drv_cs1237_instance_t* instance);
bool drv_cs1237_get_value(drv_cs1237_instance_t* instance, int32_t* value);

//********************************* Private Interface ***************************/

bool drv_cs1237_is_ready(drv_cs1237_instance_t* instance);




/*! @}*/ //end of group drv_cs1237
#endif // DRV_CS1237_H
