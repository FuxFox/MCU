/*******************************************************************************
 * Module: md_store
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/30 11:31          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     md_store.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/30
  *******************************************************************************/
#ifndef MD_STORE_C
#define MD_STORE_C

#include "md_store.h"

DRV_AT24Cxx_INSTANCE(eeprom_at24c02, CFG_EEPROM_SDA, CFG_EEPROM_SCL, CFG_EEPROM_ADDR, CFG_EEPROM_TYPE);

/*!*****************************************************************************
\brief      initialize
\details
\param[in]    void
\return     void
******************************************************************************/
void md_store_init(void)
{
    drv_at24cxx_init(&eeprom_at24c02);
}

/*!*****************************************************************************
\brief      write storage
\details
\param[in]    uint32_t addr
\param[in]    uint8_t * data
\param[in]    uint16_t len
\return     void
******************************************************************************/
void md_store_write(uint32_t addr, uint8_t* data, uint16_t len)
{
    drv_at24cxx_write(&eeprom_at24c02, addr, data, len);
}

/*!*****************************************************************************
\brief      read storage
\details
\param[in]    uint32_t addr
\param[in]    uint8_t * data
\param[in]    uint16_t len
\return     void
******************************************************************************/
void md_store_read(uint32_t addr, uint8_t* data, uint16_t len)
{
    drv_at24cxx_read(&eeprom_at24c02, addr, data, len);
}


#endif // MD_STORE_C
