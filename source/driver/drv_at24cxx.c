/*******************************************************************************
 *
 * Module: drv_at24cxx
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/16 11:17          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_at24cxx.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/16
  *******************************************************************************/
#ifndef DRV_AT24CXX_C
#define DRV_AT24CXX_C

#include "drv_at24cxx.h"


/*!*****************************************************************************
\brief  	initialize
\param[in]	drv_at24cxx_instance_t * instance       The parameter '_name' of DRV_AT24Cxx_INSTANCE()
\return     bool    TRUE if found the device
******************************************************************************/
bool drv_at24cxx_init(drv_at24cxx_instance_t* instance)
{
    instance->driver.reg_addr_16bit = (instance->device_type > AT24C02);

    if (instance->device_type == AT24C01)             instance->page_size = 8;
    else if (instance->device_type <= AT24C16)        instance->page_size = 16;
    else if (instance->device_type <= AT24C64)        instance->page_size = 32;
    else if (instance->device_type <= AT24C256)       instance->page_size = 64;

    return drv_iic_init(&instance->driver);
}


/*!*****************************************************************************
\brief      is device ready ?
\details
\param[in]    drv_at24cxx_instance_t * instance
\return     bool TRUE if ready.
******************************************************************************/
bool drv_at24cxx_is_ready(drv_at24cxx_instance_t* instance)
{
    return drv_iic_address(&instance->driver);
}

/*!*****************************************************************************
\brief  	wait device standby
\param[in]	drv_at24cxx_instance_t * instance
\return     bool  return not zero if device ready, return zero if timeout
******************************************************************************/
bool drv_at24cxx_wait_ready(drv_at24cxx_instance_t* instance)
{
    uint8_t i = 120;

    while ((i-- > 0) && !drv_iic_address(&instance->driver));

    return i;
}

/*!*****************************************************************************
\brief  	read
\param[in]	drv_at24cxx_instance_t * instance
\param[in]	uint16_t ptr        The pointer of device memory to be read
\param[in]	uint8_t * buf       The buffer to receive data
\param[in]	uint16_t len        The number of bytes to read
\return     bool    TRUE if success.
******************************************************************************/
bool drv_at24cxx_read(drv_at24cxx_instance_t* instance, uint16_t ptr, uint8_t* buf, uint16_t len)
{
    if (drv_at24cxx_wait_ready(instance))
    {
        return drv_iic_read(&instance->driver, ptr, buf, len);
    }

    return false;
}

/*!*****************************************************************************
\brief  	write, support page write
\param[in]	drv_at24cxx_instance_t * instance
\param[in]	uint16_t ptr        The pointer of device memory to be write
\param[in]	uint8_t * buf       The buffer of data to be write
\param[in]	uint16_t len        The number of bytes to be write
\return     bool    TRUE if success
******************************************************************************/
bool drv_at24cxx_write(drv_at24cxx_instance_t* instance, uint16_t ptr, uint8_t* buf, uint16_t len)
{
    if (drv_at24cxx_wait_ready(instance))
    {
        return false;
    }

    while (len)
    {
        if (len >= instance->page_size)
        {

            if (!drv_iic_write(&instance->driver, ptr, buf, instance->page_size))
            {
                return false;
            }

            len -= instance->page_size;
            ptr += instance->page_size;
            buf += instance->page_size;
        }
        else
        {
            return drv_iic_write(&instance->driver, ptr, buf, len);
        }
        app_delay_ms(20);
    }
    return true;
}




#endif // DRV_AT24CXX_C
