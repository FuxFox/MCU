/*******************************************************************************
 *
 * Module: drv_at24cxx
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/16 11:16          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_at24cxx.h
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/16
  *******************************************************************************/
#ifndef DRV_AT24CXX_H
#define DRV_AT24CXX_H

  /*! \defgroup drv_at24cxx_public Public
  \ingroup drv_at24cxx
  \details
          This is a driver of AT24CXX serial EEPROM.

    example:
        #include "drv_at24cxx.h"
        #define CFG_EEPROM_TYPE			AT24C01
        #define CFG_EEPROM_ADDR			 0xA0
        #define CFG_EEPROM_SDA			PIN_FLASH_I2C_SDA   //value is 15, see also ../../stm32/custom_board.h
        #define CFG_EEPROM_SCL			PIN_FLASH_I2C_SCL   //value is 16

        DRV_AT24Cxx_INSTANCE(eeprom_at24c02, CFG_EEPROM_SDA, CFG_EEPROM_SCL, CFG_EEPROM_ADDR, CFG_EEPROM_TYPE);

        void md_store_init(void)
        {
            drv_at24cxx_init(&eeprom_at24c02);
        }

        void md_store_write(uint32_t addr, uint8_t* data, uint16_t len)
        {
            drv_at24cxx_write(&eeprom_at24c02, addr, data, len);
        }

  \note     This driver use software IIC, but you can modify the IIC interface to use by your way.
  * @{ */

#include "app_config.h"
#include "drv_iic.h"

//********************************* Module Config *******************************/
/*! supported chip enum */
typedef enum
{
    AT24C01,
    AT24C02,
    AT24C04,
    AT24C08,
    AT24C16,
    AT24C32,
    AT24C64,
    AT24C128,
    AT24C256
}drv_at24cxx_enum;

#define DRV_AT24CXX_SIZE(_device_type)    ((128 * (1 << _device_type)) - 1)

//********************************* Data Type ***********************************/

/*! driver instance structure */
typedef struct
{
    drv_iic_instance_t driver;      /*!< IIC driver instance */
    drv_at24cxx_enum device_type;   /*!< device type */
    uint8_t page_size;              /*!< device page size */
}drv_at24cxx_instance_t;


//********************************* Public Interface ****************************/

/*!*****************************************************************************
\brief  	Use this macro to quickly define a AT24Cxx instance .

\param[in]	_name        : The name of the instance.
\param[in]	_sda_pin     : The pin number of MCU that connected to the SDA pin of AT24CXX.
\param[in]	_scl_pin     : The pin number of MCU that connected to the SCL pin of AT24CXX.
\param[in]	_iic_addr    : The device's IIC addr.
\param[in]	_device_type : The type of device. \ref drv_at24cxx_enum
*******************************************************************************/
#define DRV_AT24Cxx_INSTANCE(_name, _sda_pin, _scl_pin, _iic_addr, _device_type)        \
    static drv_at24cxx_instance_t _name = {                                             \
        {.sda_pin = _sda_pin,    .scl_pin = _scl_pin,    .addr = _iic_addr},            \
        .device_type = _device_type,                                                    \
}


bool drv_at24cxx_init(drv_at24cxx_instance_t* instance);
bool drv_at24cxx_read(drv_at24cxx_instance_t* instance, uint16_t ptr, uint8_t* buf, uint16_t len);
bool drv_at24cxx_write(drv_at24cxx_instance_t* instance, uint16_t ptr, uint8_t* buf, uint16_t len);
bool drv_at24cxx_is_ready(drv_at24cxx_instance_t* instance);
//********************************* Private Interface ***************************/





/*! @}*/ //end of group drv_at24cxx
#endif // DRV_AT24CXX_H
