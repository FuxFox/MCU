/*******************************************************************************
 * Module: TFTLCD
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2018/10/21 13:22          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     TFTLCD.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2018/10/21
 *******************************************************************************/
#ifndef TFTLCD_H
#define TFTLCD_H

/*! \defgroup TFTLCD_public Public
\ingroup TFTLCD
\brief 
\details 
* @{ */


#define TFT_XMAX 239
#define TFT_YMAX 399

extern void TFT_Init(void);
extern void TFT_WriteDat(uint16_t dat);
extern void TFT_WriteCmd(uint16_t cmd);





/*! @}*/ //end of group TFTLCD
#endif // TFTLCD_H
