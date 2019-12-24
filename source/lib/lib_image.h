/*******************************************************************************
 * Module: lib_image
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/11 13:42          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     lib_image.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/11
  *******************************************************************************/
#ifndef LIB_IMAGE_H
#define LIB_IMAGE_H

  /*! \defgroup lib_image_public Public
  \ingroup lib_image
  \brief
  \details
  * @{ */

#include "app_globle.h"


//********************************* Module Config *******************************/




//********************************* Data Type ***********************************/

/*! picture data structure*/
typedef struct
{
    uint16_t width;         /*!< picture width in pix */
    uint16_t height;        /*!< picture height in pix */
    uint16_t size;          /*!< picture size */
    const uint8_t* data;    /*!< pointer to picture data */
}lib_image_struct;



//********************************* Public Interface ****************************/

extern const lib_image_struct lib_image_battery;
extern const lib_image_struct lib_image_bluetooth;



//********************************* Private Interface ***************************/





/*! @}*/ //end of group lib_image
#endif // LIB_IMAGE_H
