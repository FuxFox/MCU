/*******************************************************************************
* LICENSE : Apache 2.0
*           
* History:
*    <author>         <time>             <version>             <desc>
*      FuxFox	      2020/08/13 16:24          V1.0             build this file
*
*******************************************************************************/
#ifndef APP_MACRO_H
#define APP_MACRO_H

/**
* @defgroup app_macro
* @ingroup lib
* @brief
* @details 
* @{ */

/**
* @brief Concatenates two parameters.
*
* It realizes two level expansion to make it sure that all the parameters
* are actually expanded before gluing them together.
*
* @param p1 First parameter to concatenating
* @param p2 Second parameter to concatenating
*
* @return Two parameters glued together.
*         They have to create correct C mnemonic in other case
*         preprocessor error would be generated.
*
* @sa CONCAT_3
*/
#define CONCAT_2(p1, p2)      CONCAT_2_(p1, p2)
/** Auxiliary macro used by @ref CONCAT_2 */
#define CONCAT_2_(p1, p2)     p1##p2

/**
* @brief Concatenates three parameters.
*
* It realizes two level expansion to make it sure that all the parameters
* are actually expanded before gluing them together.
*
* @param p1 First parameter to concatenating
* @param p2 Second parameter to concatenating
* @param p3 Third parameter to concatenating
*
* @return Three parameters glued together.
*         They have to create correct C mnemonic in other case
*         preprocessor error would be generated.
*
* @sa CONCAT_2
*/
#define CONCAT_3(p1, p2, p3)  CONCAT_3_(p1, p2, p3)
/** Auxiliary macro used by @ref CONCAT_3 */
#define CONCAT_3_(p1, p2, p3) p1##p2##p3

#define STRINGIFY_(val) #val
/** Converts a macro argument into a character constant. */
#define STRINGIFY(val)  STRINGIFY_(val)

/** Counts number of elements inside the array */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

/**
* upper_32_bits - return bits 32-63 of a number
* @n: the number we're accessing
*
* A basic shift-right of a 64- or 32-bit quantity.  Use this to suppress
* the "right shift count >= width of type" warning when that quantity is
* 32-bits.
*/
#define UPPER_32_BITS(n) ((uint32_t)(((n) >> 16) >> 16))
#define UPPER_16_BITS(n) ((uint16_t)(((n) >> 8) >> 8))
#define UPPER_8_BITS(n) ((uint8_t)((n) >> 8))

/**
* lower_32_bits - return bits 0-31 of a number
* @n: the number we're accessing
*/
#define LOWER_32_BITS(n) ((uint32_t)(n))
#define LOWER_16_BITS(n) ((uint16_t)(n))
#define LOWER_8_BITS(n) ((uint8_t)(n))

#define GET_BYTE(w, n)	((uint8_t)((w) >> (n << 3)))

/** 获取结构体成员在结构体内的地址偏移量 */
#define offsetof(TYPE, MEMBER) ((uint32_t) &((TYPE *)0)->MEMBER)

/** 获取ptr指针所指结构体成员所在的结构体实例的指针 */
#define container_of(ptr, type, member) ((type*)((char*)ptr - offsetof(type, member)))

/* Clear unused warnings for actually unused variables */
#define UNUSED(x) (void)(x)


/** @}*/ //end of group app_macro
#endif // APP_MACRO_H
