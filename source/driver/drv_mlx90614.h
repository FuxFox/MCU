/*******************************************************************************
 *
 * Module: drv_mlx90614
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/28 19:47          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_mlx90614.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/28
  *******************************************************************************/
#ifndef DRV_MLX90614_H
#define DRV_MLX90614_H

  /*! \defgroup drv_mlx90614_public Public
  \ingroup drv_mlx90614
  \brief
  \details
          mlx90614 Infrared temperature sensor driver
    example:
        #include "mlx90614.h"
        DRV_MLX90614_INSTANCE(water_temp, PIN_WATER_TEMP_I2C_SDA, PIN_WATER_TEMP_I2C_SCK, 0x00);
        
        void module_layer_init(void)
        {      
             drv_mlx90614_init(&water_temp);
             printf("temp: %d", drv_mlx90614_get_temp(&water_temp, DRV_MLX90614_TEMP_OBJ1));//unit: 0.1¡æ
        }


  * @{ */

#include "app_config.h"

#include "drv_iic.h"
  //********************************* Module Config *******************************/





  //********************************* Data Type ***********************************/

#define DRV_MLX90614_TEMP_ERROR            (0x7FFF)

typedef drv_iic_instance_t drv_mlx90614_instance_t;

/*! Device register address and command list */
typedef enum
{        //RAM are read only
    DRV_MLX90614_RAM_RAW_DATA_IR_CHANNEL_1 = 0x04,
    DRV_MLX90614_RAM_RAW_DATA_IR_CHANNEL_2 = 0x05,
    DRV_MLX90614_RAM_TEMP_AMBIENT          = 0x06,    /*!< Environment temperature */
    DRV_MLX90614_RAM_TEMP_OBJ1             = 0x07,    /*!< Target temperature */
    DRV_MLX90614_RAM_TEMP_OBJ2             = 0x08,

    DRV_MLX90614_EEPROM_TEMP_OBJ_MAX       = 0x20,
    DRV_MLX90614_EEPROM_TEMP_OBJ_MIN       = 0x21,
    DRV_MLX90614_EEPROM_PWM_CTRL           = 0x22,
    DRV_MLX90614_EEPROM_TEMP_AMBIENT_RANGE = 0x23,    /*!< Environment temperature range , writeable*/
    DRV_MLX90614_EEPROM_OBJ_IR_Emissivity  = 0x24,    /*!< The IR Emissivity factor of target, writeable, default value 0xFFFF*/
    DRV_MLX90614_EEPROM_CFG                = 0x25,    /*!< Configuration register, writeable */
    DRV_MLX90614_EEPROM_DEVICE_ADDR        = 0x2E,    /*!< Device address, writeable */
    DRV_MLX90614_EEPROM_DEVICE_ID_1        = 0x3C,    /*!< Device ID read only */
    DRV_MLX90614_EEPROM_DEVICE_ID_2        = 0x3D,    /*!< Device ID read only */
    DRV_MLX90614_EEPROM_DEVICE_ID_3        = 0x3E,    /*!< Device ID read only */
    DRV_MLX90614_EEPROM_DEVICE_ID_4        = 0x3F,    /*!< Device ID read only */

    DRV_MLX90614_CMD_READ_FLAG             = 0xF0,    /*!< command: read flag */
    DRV_MLX90614_CMD_SLEEP                 = 0xFF,    /*!< command: sleep */
}drv_mlx90614_reg_t;

/*! Device flag mask */
typedef enum
{
    DRV_MLX90614_FLAG_EEBUSY     = 0x80,            /*!< EEPROM busy */
    DRV_MLX90614_FLAG_EEDEAD     = 0x20,            /*!< EEPROM dead */
    DRV_MLX90614_FLAG_INIT       = 0x10,            /*!< Initialize done */

    DRV_MLX90614_FLAG_TEMP_ERROR = 0x8000           /*!< Temperature error flag */
}drv_mlx90614_flag_mask_t;

/*! Temperature type enum */
typedef enum
{
    DRV_MLX90614_TEMP_AMBIENT = DRV_MLX90614_RAM_TEMP_AMBIENT,         /*!< Environment  */
    DRV_MLX90614_TEMP_OBJ1    = DRV_MLX90614_RAM_TEMP_OBJ1,            /*!< Target temperature 1 */
    DRV_MLX90614_TEMP_OBJ2    = DRV_MLX90614_RAM_TEMP_OBJ2,            /*!< Target temperature 2 */
}drv_mlx90614_temp_type_t;

//********************************* Public Interface ****************************/

/*!*****************************************************************************
\brief  	Use this macro to quickly define a MLX90614 instance

\param[in]	_name       name of instance
\param[in]	_sda_pin    chip pin number of MCU that connected to mlx90614 SDA pin
\param[in]	_scl_pin    chip pin number of MCU that connected to mlx90614 SCL pin
\param[in]	_addr       mlx90614 IIC address, 8bit , LSB(R/W) must be 0
*******************************************************************************/
#define DRV_MLX90614_INSTANCE(_name, _sda_pin, _scl_pin, _addr)    \
    drv_mlx90614_instance_t _name = {                              \
        .sda_pin = _sda_pin,                                       \
        .scl_pin = _scl_pin,                                       \
        .addr     = _addr,                                         \
        .reg_addr_16bit = false                                    \
}

bool drv_mlx90614_init(drv_mlx90614_instance_t* instance);
int16_t drv_mlx90614_get_temp(drv_mlx90614_instance_t* instance, drv_mlx90614_temp_type_t temp_type);
uint16_t drv_mlx90614_read_reg(drv_mlx90614_instance_t* instance, drv_mlx90614_reg_t reg);
//********************************* Private Interface ***************************/





/*! @}*/ //end of group drv_mlx90614
#endif // DRV_MLX90614_H
