/*******************************************************************************
 * Module: md_store
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/30 11:31          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     md_store.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/10/30
 *******************************************************************************/
#ifndef MD_STORE_H
#define MD_STORE_H

/*! \defgroup md_store_public Public
\ingroup md_store
\brief 
\details 
* @{ */

#include "app_config.h"

#include "driver.h"
//********************************* Module Config *******************************/
                                




//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/

void md_store_init(void);
void md_store_write(uint32_t addr, uint8_t* data, uint16_t len);
void md_store_read(uint32_t addr, uint8_t* data, uint16_t len);



//********************************* Private Interface ***************************/





/*! @}*/ //end of group md_store
#endif // MD_STORE_H
