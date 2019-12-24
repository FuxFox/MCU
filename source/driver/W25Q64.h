/*******************************************************************************
 * Module: W25Q64
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2018/10/22 22:09          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     W25Q64.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2018/10/22
 *******************************************************************************/
#ifndef W25Q64_H
#define W25Q64_H

/*! \defgroup W25Q64_public Public
\ingroup W25Q64
\brief 
\details 
* @{ */


extern uint16_t W25Q64_ReadID(void);
extern void W25Q64_ReadData(uint8_t *buf, uint32_t addr, uint16_t len);
extern void W25Q64_Write(uint8_t *Buff, uint32_t writeAddr, uint16_t len);
extern uint32_t W25Q64_ReadJEDECID(void);







/*! @}*/ //end of group W25Q64
#endif // W25Q64_H
