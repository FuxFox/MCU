/*******************************************************************************
 *
 * Module: drv_iic
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/12 10:58          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_iic.h
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/12
  *******************************************************************************/
#ifndef DRV_IIC_H
#define DRV_IIC_H

  /*! \defgroup drv_iic_public Public
  \ingroup drv_iic
  \details
          This is a software IIC driver. Speed: standard£º100kbps
          Use 8bit slave address, the LSB(R/W) must be 0.
          You can easily modify the code to support 10bit address.
          This driver can be nested into other drivers to simply implement chip driver which used IIC bus.As an example: drv_at24cxx.h
  * @{ */

#include "app_config.h"

#include "app_delay.h"
#include "app_gpio.h"

  //********************************* Module Config *******************************/

#define DRV_IIC_HIGH      GPIO_PIN_SET
#define DRV_IIC_LOW      GPIO_PIN_RESET


//********************************* Data Type ***********************************/

/*! IIC instance */
typedef struct
{
    uint8_t sda_pin;            /*!< The chip pin number, which use as SDA */
    uint8_t scl_pin;            /*!< The chip pin number, which use as SCL */
    uint8_t addr;               /*!< The device's address, 8bit, LSB(R/W) must be 0 */
    bool reg_addr_16bit;        /*!< TRUE if the device use 16bit register address,
                                     FALSE if use 8bit register address*/
}drv_iic_instance_t;



//********************************* Public Interface ****************************/

bool drv_iic_init(drv_iic_instance_t* instance);

bool drv_iic_write(drv_iic_instance_t* instance, uint16_t reg, uint8_t* buf, uint8_t len);
bool drv_iic_read(drv_iic_instance_t* instance, uint16_t reg, uint8_t* buf, uint8_t len);
bool drv_iic_address(drv_iic_instance_t* instance);
//********************************* Private Interface ***************************/

static void drv_iic_start(drv_iic_instance_t* instance);
static void drv_iic_stop(drv_iic_instance_t* instance);
static bool drv_iic_send_byte(drv_iic_instance_t* instance, uint8_t txd);
static uint8_t drv_iic_read_byte(drv_iic_instance_t* instance, bool ack);


/*! @}*/ //end of group drv_iic
#endif // DRV_IIC_H



