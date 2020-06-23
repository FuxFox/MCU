/*******************************************************************************
 *
 * Module: app_error
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/21 15:31          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     app_error.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/11/21
  *******************************************************************************/
#ifndef APP_ERROR_C
#define APP_ERROR_C

#include "app_error.h"
#include "app_log.h"

  /*!*****************************************************************************
  \brief      initialize
  \details
  \param[in]    void
  \return     void
  ******************************************************************************/
void app_error_init(void)
{
    //currently nothing
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void app_error_assert(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,*/
    LOG_ERROR("Wrong parameters value: file %s on line %d\r\n", file, line);
    while (1);
}
#endif /* USE_FULL_ASSERT */

void app_error_handler(uint32_t error_code, uint8_t* file, uint32_t line)
{
    LOG_ERROR("Error 0x%x occurred at: file %s on line %d\r\n", error_code, file, line);
    while (1);
}



#endif // APP_ERROR_C
