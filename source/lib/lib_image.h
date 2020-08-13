/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/08/13 16:26          V1.0             build this file
 *
 *******************************************************************************/
#ifndef LIB_IMAGE_H
#define LIB_IMAGE_H

/*! \defgroup lib_image
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
