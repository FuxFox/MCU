/*!*****************************************************************************
* @file     module.c
* @brief
* @author   FuxFox
* @version  V1.0
* @date     2019/07/26
*******************************************************************************/
#ifndef MODULE_C
#define MODULE_C

#include "module.h"
#include "driver.h"
#include "md_battery.h"

static bool md_shutdown_handler(nrf_pwr_mgmt_evt_t event);
static void module_battery_change_callback(uint8_t battery_percent);

void module_init(void)
{

}

/*!*****************************************************************************
* @brief     Handler for shutdown preparation.
* @details During shutdown procedures, this function will be called at a 1 second interval
*          untill the function returns true. When the function returns true, it means that the
*          app is ready to reset to DFU mode.
* @param[in] nrf_pwr_mgmt_evt_t event : Power manager event.
* @return    bool
* @retval   True if shutdown is allowed by this power manager handler, otherwise false.
*******************************************************************************/
static bool md_shutdown_handler(nrf_pwr_mgmt_evt_t event)
{
    switch (event)
    {
    case NRF_PWR_MGMT_EVT_PREPARE_DFU:
        NRF_LOG_INFO("Power management wants to reset to DFU mode.");

        if (0)
        {
            return false;
        }
        else
        {
            // Device ready to enter
            uint32_t err_code;
            err_code = nrf_sdh_disable_request();
            APP_ERROR_CHECK(err_code);
            err_code = app_timer_stop_all();
            APP_ERROR_CHECK(err_code);
            return true;
        }
        //break;
    case NRF_PWR_MGMT_EVT_PREPARE_WAKEUP:
        NRF_LOG_INFO("Power management wants to prepare wakeup mechanism.");
        return false;
    case NRF_PWR_MGMT_EVT_PREPARE_SYSOFF:
        NRF_LOG_INFO("Power management wants to Shutdown.");
        return false;
    case NRF_PWR_MGMT_EVT_PREPARE_RESET:
        NRF_LOG_INFO("Power management wants to reset.");
        return false;
    default:
        break;
    }

    NRF_LOG_INFO("Power management allowed to reset to DFU mode.");
    return true;
}

//lint -esym(528, m_app_shutdown_handler)
/**
* @brief Register application shutdown handler with priority 0.
*/
NRF_PWR_MGMT_HANDLER_REGISTER(md_shutdown_handler, 0);


/*!*****************************************************************************
* @brief      battery change callback handler
* @param[in]    void
* @return     void
*******************************************************************************/
static void module_battery_change_callback(uint8_t battery_percent)
{

}
#endif // module_C
