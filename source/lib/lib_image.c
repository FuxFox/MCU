/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/08/13 16:26          V1.0             build this file
 *
 *******************************************************************************/
#ifndef LIB_IMAGE_C
#define LIB_IMAGE_C

#include "lib_image.h"

  /*! battery icon */
const static uint8_t img_data_battery[] = {
    0x00,0x00,0x1E,0x00,0x3F,0x00,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,
    0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,
    0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,
    0xFF,0xC0
};
const lib_image_struct lib_image_battery = {
    .width = 25,
    .height = 10,
    .size = sizeof(img_data_battery),
    .data = (const uint8_t*)&img_data_battery
};


/*! Bluetooth icon */
const static uint8_t img_data_bluetooth[] = {
    0x30,0x18,0x18,0x30,0x0C,0x60,0x7F,0xFE,0x61,0x86,0x33,0xCC,0x1E,0x78,0x0C,0x30
};
const lib_image_struct lib_image_bluetooth = {
    .width = 8,
    .height = 16,
    .size = sizeof(img_data_bluetooth),
    .data = (const uint8_t*)&img_data_bluetooth
};
#endif // LIB_IMAGE_C
