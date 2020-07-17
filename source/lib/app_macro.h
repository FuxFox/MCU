/*******************************************************************************
 *
 * Module: app_interface_remap
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/07/12 14:44          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     app_common_head.h
  * \brief    
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/07/12
  *******************************************************************************/
#ifndef APP_INTERFACE_REMAP_H
#define APP_INTERFACE_REMAP_H

/**************************** define *******************/



/**************************** common macro *******************/

/**@brief Concatenates two parameters.
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

/**@brief Concatenates three parameters.
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
/** Converts a macro argument into a character constant.
 */
#define STRINGIFY(val)  STRINGIFY_(val)

 /** Counts number of elements inside the array
  */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


/**************************** Standard *********************************/




#endif // APP_COMMON_HEAD_H
