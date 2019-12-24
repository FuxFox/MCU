/*******************************************************************************
 * Module: md_m26
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/09/05 14:05          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     md_m26.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/09/05
  *******************************************************************************/
#ifndef MD_M26_C
#define MD_M26_C

#include "md_m26.h"

static error_handler m_error_handler = NULL;
/*!*****************************************************************************
\brief      initialize
\details
\param[in]    void
\return     bool    TRUE if success
******************************************************************************/
bool md_m26_init(error_handler handler)
{
    m_error_handler = handler;

    if (!drv_m26_init(handler))
    {
        return false;
    }

    return md_m26_reinit();
}

/*!*****************************************************************************
\brief      re-initialize
\details
\param[in]    void
\return     bool TRUE if success
******************************************************************************/
bool md_m26_reinit(void)
{
    if (!drv_m26_reinit())
    {
        return false;
    }

    md_m26_configure();

    while (!md_m26_check_ready())
    {
        drv_m26_reboot();
        if (!drv_m26_reinit())
        {
            return false;
        }
        md_m26_configure();
    };
    return true;
}
/*!*****************************************************************************
\brief      send command and check ACK
\details
\param[in]    const char * str      AT command string
\param[in]    const char * ack      expectant ACK string
\param[in]    uint32_t wait_ms      max waiting time, in ms
\return     bool TRUE if success
******************************************************************************/
bool md_m26_send_check_ack_ms(const char* str, const char* ack, uint32_t wait_ms)
{
    char buff[32];

    nrf_delay_ms(10);

    drv_m26_TxRx(str, buff, strlen(ack) + 2, wait_ms);
    return strstr(buff, ack);
}

/*!*****************************************************************************
\brief      send command and get ACK
\details
\param[in]    const char * str      AT command string
\param[in]    const char * ack      Buffer to receive ACK
\param[in]    uint32_t wait_ms      max waiting time, in ms
\return     void
******************************************************************************/
void md_m26_send_and_get_ack(const char* str, char* ack, uint32_t len, uint32_t wait_ms)
{
    nrf_delay_ms(10);
    drv_m26_TxRx(str, ack, len + 2, wait_ms);
}

/*!*****************************************************************************
\brief      M26 module configure
            echo off,
            baud rate 115200,
            disable NITZ
\details
\param[in]    void
\return     void
******************************************************************************/
static void md_m26_configure(void)
{
    md_m26_send_check_ack("ATE0\r", "ATE0\r\nOK");
    md_m26_send_check_ok("AT+IPR=115200\r");
    md_m26_send_check_ok("AT+QNITZ=0\r");//disable NITZ
}


/*!*****************************************************************************
\brief      configure and check Internet connection
\details
\param[in]    void
\return     bool : TRUE if success
******************************************************************************/
static bool md_m26_check_ready(void)
{
    md_m26_send_check_ok("AT+QREFUSECS=1,1\r"); //reject phone call and SMS
    md_m26_send_check_ack_ms("AT+CPIN?\r", "+CPIN: READY", 5000);//SIM unlock
    md_m26_send_check_ack("AT+QINISTAT\r", "+QINISTAT: x");// initialization check

    md_m26_send_check_ok("AT+QIFGCNT=0\r"); //set foreground dialog
    md_m26_send_check_ok("AT+QICSGP=1,\"CMNET\"\r"); //set AP

    while (md_m26_send_check_ack("AT+CREG?\r", "+CREG: 0,2")) nrf_delay_ms(3000); //query register info
    if (!md_m26_send_check_ack("AT+CREG?\r", "+CREG: 0,1"))
        return false;

    md_m26_send_check_ack("AT+CSQ\r", "+CSQ: xx,xx");

    while (md_m26_send_check_ack("AT+CGREG?\r", "+CGREG: 0,2")) nrf_delay_ms(3000);//query GPRS register information
    if (!md_m26_send_check_ack("AT+CGREG?\r", "+CGREG: 0,1"))
        return false;

    md_m26_send_check_ok("AT+QIREGAPP\r"); //Register to TCP/IP stack

    char ack[18];
    md_m26_send_and_get_ack("AT+QIACT\r", ack, 16, 30000);//Activate GPRS PDP context.
    if (!strstr(ack, "OK"))
    {
        return false;
    }

    md_m26_send_check_ack("AT+QILOCIP\r", "xxx.xxx.xxx.xxx");//Query the local IP address.
    md_m26_send_check_ack("AT+QISTAT\r", "OK\r\n\r\nSTATE: IP STATUS");//query connection state

    return true;
}

/*!*****************************************************************************
\brief      set HTTP url
\details
\param[in]    void
\return     void
******************************************************************************/
bool md_m26_http_set_url(const char* url)
{
    char str[20];

    snprintf(str, sizeof(str), "AT+QHTTPURL=%d,2\r", strlen(url));
    md_m26_send_check_ack_ms(str, "CONNECT", 500);
    return md_m26_send_check_ack_ms(url, "OK", 2000);
}

/*!*****************************************************************************
\brief      HTTP get request
\details
\param[out]    char* response   buffer to receive response from server
\param[in]    size_t resp_size       size of receive buffer
\return     size_t              actually size of received data
\note
        The response return from M26 is start with "CONNECT"
******************************************************************************/
size_t md_m26_http_get(char* url, char* response, size_t resp_size)
{
    char str[24];

    snprintf(str, sizeof(str), "AT+QHTTPGET=60,61,%d\r", resp_size);
    md_m26_send_check_ack_ms(str, "OK", 60000);

    return drv_m26_TxRx("AT+QHTTPREAD=30\r", response, resp_size, 30000);
}

/*!*****************************************************************************
\brief      HTTP post and get response
\details
\param[in]    char * post       POST data
\param[in]    char * response   buffer to receive response from server
\param[in]    size_t size       size of response received buffer
\return     size_t            actually size of received data
\note
        The response return from M26 is start with "CONNECT"
******************************************************************************/
size_t md_m26_http_post(char* url, char* post, char* response, size_t resp_size)
{
    char str[24];

    snprintf(str, sizeof(str), "AT+QHTTPPOST=%d,60,60\r", strlen(post));
    if (!md_m26_send_check_ack_ms(str, "CONNECT", 60000))
    {
        md_m26_send_check_ack("+++\r", "");
        if (!md_m26_send_check_ack_ms(str, "CONNECT", 60000))
        {
            m_error_handler(NULL);
        }
    }
    if (!md_m26_send_check_ack_ms(post, "OK", 60000))
    {
        *response = '\0';
        return 0;
    }

    return drv_m26_TxRx("AT+QHTTPREAD=40\r", response, resp_size, 30000);
}

/*!*****************************************************************************
\brief      get local time from M26. Format£ºyy/mm/dd, hh:mm:ss+zz
\details
\param[in]    char * time       receive buffer, size > 22
\return     bool TRUE if success
******************************************************************************/
bool md_m26_get_time(char* time)
{
    char buff[32];
    char* src;

    for (uint8_t i = 0; i < 5; i++)
    {
        md_m26_send_check_ok("AT+QNITZ=1\r");//enable NITZ
        nrf_delay_ms(3000);
        drv_m26_TxRx("AT+QLTS\r", buff, 30, MD_M26_RX_WAIT_TIME_MAX);//+QLTS: "04/05/06,22:10:00+08,0"
        if (strlen(buff) > 20)
        {
            md_m26_send_check_ok("AT+QNITZ=0\r");//disable NITZ
            src = strstr(buff, "+QLTS");
            if (src)
            {
                strcpy(time, src + 8);
                return true;
            }
        }
    }

    return false;
}

/*!*****************************************************************************
\brief      GET M26 IMEI
\details        15 digit number
\param[in]    uint8_t * res         a buffer to receive IMEI, size >= 16
\return     bool   TRUE if success
******************************************************************************/
bool md_m26_get_IMEI(char* res)
{
    char tmp[24];

    drv_m26_TxRx("AT+GSN\r", tmp, 23, MD_M26_RX_WAIT_TIME_MAX);
    *(res + 15) = '\0';
    if (strstr(tmp, "OK"))
    {
        memcpy(res, tmp + 2, 15);
        return true;
    }
    return false;
}
#endif // MD_M26_C
