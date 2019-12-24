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
  * \file     drv_mlx90614.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/28
  *******************************************************************************/
#ifndef DRV_MLX90614_C
#define DRV_MLX90614_C

#include "drv_mlx90614.h"

  /*!*****************************************************************************
  \brief      initialize
  \details
  \param[in]    void
  \return     void
  ******************************************************************************/
bool drv_mlx90614_init(drv_mlx90614_instance_t* instance)
{
    return drv_iic_init(instance);
}

/*!*****************************************************************************
\brief      get temperature (¡æ)
\details
\param[in]    drv_mlx90614_instance_t * instance
\param[in]    drv_mlx90614_temp_type_t temp_type
\return     int16_t signed value, unit: 0.1¡æ . example: -325 mean -32.5¡æ¡£
                        return -127 if failure
******************************************************************************/
int16_t drv_mlx90614_get_temp(drv_mlx90614_instance_t* instance, drv_mlx90614_temp_type_t temp_type)
{
    uint8_t temp[3];
    uint16_t temp_value;

    if (drv_iic_read(instance, temp_type, temp, 3))
    {
        temp_value = temp[1];
        temp_value <<= 8;
        temp_value |= temp[0];

        if (temp_value & DRV_MLX90614_FLAG_TEMP_ERROR)
        {
            return DRV_MLX90614_TEMP_ERROR;
        }

        return (temp_value / 5 - 2731);//value *0.02 - 273.15
    }

    return DRV_MLX90614_TEMP_ERROR;
}

/*!*****************************************************************************
\brief  	read device register
\param[in]	drv_mlx90614_instance_t * instance
\param[in]	drv_mlx90614_reg_t reg
\return     uint16_t
******************************************************************************/
uint16_t drv_mlx90614_read_reg(drv_mlx90614_instance_t* instance, drv_mlx90614_reg_t reg)
{
    uint8_t temp[3];

    if (drv_iic_read(instance, reg, temp, 3))
    {
        return ((uint16_t)temp[1] << 8 | temp[0]);
    }
    return 0;
}


#endif // DRV_MLX90614_C
