/*******************************************************************************
 *
 * Module: app_error
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/21 15:30          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     app_error.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/11/21
 *******************************************************************************/
#ifndef APP_ERROR_H
#define APP_ERROR_H

/*! \defgroup app_error_public Public
\ingroup app_error
\brief      Implement assert macro and error handler
\details 
* @{ */

#include "app_config.h"
//********************************* Module Config *******************************/
                                
#ifdef  USE_FULL_ASSERT

void app_error_assert(uint8_t* file, uint32_t line);
void app_error_handler(uint32_t error_code, uint8_t* file, uint32_t line);

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
#define assert_param(expr) ((expr) ? (void)0U : app_error_assert((uint8_t *)__FILE__, __LINE__))
#define HAL_ERROR_CHECK(err_code)    ((err_code == HAL_OK) ? (void)0U : app_error_handler(err_code, (uint8_t *)__FILE__, __LINE__))
  /* Exported functions ------------------------------------------------------- */
#else
#define assert_param(expr) ((void)0U)
#define HAL_ERROR_CHECK(err_code) ((void)0U)
#endif /* USE_FULL_ASSERT */





//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/





//********************************* Private Interface ***************************/





/*! @}*/ //end of group app_error
#endif // APP_ERROR_H