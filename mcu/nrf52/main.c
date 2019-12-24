/*******************************************************************************
 * Module: main
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/07/26 14:49          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     main.c
  * \brief      main for nrf52832
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/07/26
  *******************************************************************************/
#ifndef MAIN_C
#define MAIN_C

#include "main.h"

  /**@brief Function for application main entry.
   */
int main(void)
{
    // Initialize.
    main_nrf_preinit();

    driver_init();
    module_init();
    ui_init();

    //        test_run();

    ble_module_init();

    // Start execution.
    NRF_LOG_INFO("system started.");

    while (1)
    {
        idle_state_handle();
    }
}



/*!*****************************************************************************
\brief      nrf pre-initialize
\details
\param[in]    void
\return     void
******************************************************************************/
static void main_nrf_preinit(void)
{
    log_init();
    timers_init();

    power_management_init();

}

/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module.
 */
static void timers_init(void)
{
    // Initialize timer module, making it use the scheduler
    ret_code_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);
}


static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

/**@brief Function for initializing power management.
 */
static void power_management_init(void)
{
    ret_code_t err_code;
    err_code = nrf_pwr_mgmt_init();
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for handling the idle state (main loop).
 *
 * @details If there is no pending log operation, then sleep until next the next event occurs.
 */
static void idle_state_handle(void)
{
    if (NRF_LOG_PROCESS() == false)
    {
        nrf_pwr_mgmt_run();
    }
}

/**@brief Function for assert macro callback.
 *
 * @details This function will be called in case of an assert in the SoftDevice.
 *
 * @warning This handler is an example only and does not fit a final product. You need to analyze
 *          how your product is supposed to react in case of Assert.
 * @warning On assert from the SoftDevice, the system can only recover on reset.
 *
 * @param[in] line_num    Line number of the failing ASSERT call.
 * @param[in] p_file_name File name of the failing ASSERT call.
 */
void assert_nrf_callback(uint16_t line_num, const uint8_t* p_file_name)
{
    app_error_handler(DEAD_BEEF, line_num, p_file_name);
}

#endif // MAIN_C
