/*******************************************************************************
 * Module: md_yaohe
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/09/16 14:10          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     md_yaohe.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/09/16
  *******************************************************************************/
#ifndef MD_YAOHE_C
#define MD_YAOHE_C

#include "md_yaohe.h"

static uint32_t md_MedicationPlanVer = 0;
static char m_serial_number[16];
static char m_plan_content[MD_YAOHE_MEDICATION_PLAN_BUFF_SIZE];
/*! SSL certificate
static const char m_ca_certificat[] =
"-----BEGINCERTIFICATE-----\r\n\
MIIHBDCCBeygAwIBAgIQDs3JQm23/Ixt/LtiPRjccDANBgkqhkiG9w0BAQsFADBN\r\n\
MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMScwJQYDVQQDEx5E\r\n\
aWdpQ2VydCBTSEEyIFNlY3VyZSBTZXJ2ZXIgQ0EwHhcNMTkwNzIyMDAwMDAwWhcN\r\n\
MjEwNzIyMTIwMDAwWjByMQswCQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3Rv\r\n\
bjEQMA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0\r\n\
aW9uMRwwGgYDVQQDDBMqLmF6dXJld2Vic2l0ZXMubmV0MIIBIjANBgkqhkiG9w0B\r\n\
AQEFAAOCAQ8AMIIBCgKCAQEA6076mOnIVWGdh6m190uQuSKaCKXt7fuiZIBTX5af\r\n\
m/XJIuNBlJdDqABvlk4D8ieprbqQ/C28piMPoVkW6MzI+rkrQA1b3XmtCb+d0pLC\r\n\
ZNoZDHjzeM7A5m7AHZkDa2mjw6yG+9/PGJby/ewandoXWvbwREgJmEagMTPI4qos\r\n\
r5rBnq67sv1nDPfvLwa9YvP6mhGxLA8nsfZBpUaWYd2eepjxyPB+Zuo+qYedVD5q\r\n\
38kUpAmyIva+42k9Yz0kDhV3SxE0RWtfRwANpRAKEmpxw487ttA4dC3A64WX0bVO\r\n\
0Y4EFhbbgJ5+6HDGIiLsU9eLb2Aw0qw/ehpuspROn6HuOQIDAQABo4IDuTCCA7Uw\r\n\
HwYDVR0jBBgwFoAUD4BhHIIxYdUvKOeNRji0LOHG2eIwHQYDVR0OBBYEFL0c1S2M\r\n\
vkFZ78FyY67l8HWKYJnaMHwGA1UdEQR1MHOCEyouYXp1cmV3ZWJzaXRlcy5uZXSC\r\n\
Fyouc2NtLmF6dXJld2Vic2l0ZXMubmV0ghcqLnNzby5henVyZXdlYnNpdGVzLm5l\r\n\
dIISKi5henVyZS1tb2JpbGUubmV0ghYqLnNjbS5henVyZS1tb2JpbGUubmV0MA4G\r\n\
A1UdDwEB/wQEAwIFoDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwawYD\r\n\
VR0fBGQwYjAvoC2gK4YpaHR0cDovL2NybDMuZGlnaWNlcnQuY29tL3NzY2Etc2hh\r\n\
Mi1nNi5jcmwwL6AtoCuGKWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9zc2NhLXNo\r\n\
YTItZzYuY3JsMEwGA1UdIARFMEMwNwYJYIZIAYb9bAEBMCowKAYIKwYBBQUHAgEW\r\n\
HGh0dHBzOi8vd3d3LmRpZ2ljZXJ0LmNvbS9DUFMwCAYGZ4EMAQICMHwGCCsGAQUF\r\n\
BwEBBHAwbjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQuY29tMEYG\r\n\
CCsGAQUFBzAChjpodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGlnaUNlcnRT\r\n\
SEEyU2VjdXJlU2VydmVyQ0EuY3J0MAwGA1UdEwEB/wQCMAAwggF9BgorBgEEAdZ5\r\n\
AgQCBIIBbQSCAWkBZwB1AKS5CZC0GFgUh7sTosxncAo8NZgE+RvfuON3zQ7IDdwQ\r\n\
AAABbBfAhlgAAAQDAEYwRAIgOLHaVNpfaAG62D44LRcuLNCrkoUVDPgtOYKcZVuq\r\n\
iDECIEoH/JXVzgFakDsUcDkutq8JpyDnWUyTBXJYX98BkMDZAHYAh3W/51l8+IxD\r\n\
mV+9827/Vo1HVjb/SrVgwbTq/16ggw8AAAFsF8CGpAAABAMARzBFAiB8SrDuQuRM\r\n\
95TqVZ9Out4BKKEaAg3N+5lDIChftzBa+gIhAIvmg4lpdQT3fJJv1ek8dVJ7TfL3\r\n\
l+EtoALYxrcMOf77AHYARJRlLrDuzq/EQAfYqP4owNrmgr7YyzG1P9MzlrW2gagA\r\n\
AAFsF8CFrgAABAMARzBFAiAKx2hKozj/lcKFoDpwAg1v0GLvEPZI/RNpfCQz3rH+\r\n\
iwIhAIfiAwYYyaxd5468YD3cASrA6piX5V/swwnbCyFYaNzlMA0GCSqGSIb3DQEB\r\n\
CwUAA4IBAQBD7ldn73TIk2MVKXCrru5SXIuYmDkcs76fGBFsOdqFb9QwZSllzjz9\r\n\
jjSz0y1LJUzIXTgzrvHLT5gyKLzp+OYMIWOIdhL1NUVeay7ZCGTm5lMak7Bf2vTi\r\n\
MfgN8wuYMeu4fjTTwnA0sJzzxzXLy7AyZTjETZgCf8U6x8T1hkws3t6wzwwwefTm\r\n\
3RSiUG0Cqoar0ejI8wmTx35ficRJ/LSPskDnpfcGRM6Jw7U7wZBP+TRgVYTzxpA8\r\n\
/4Tb+dqwZ4l5a4uUtxeUW1Tv9lovrdZnwKIhVo0bIRh98G86zk79jgVz4O67K7hA\r\n\
fLdFsNsahoXJ16hSyUqGq4zEDc+lmGsX\r\n\
-----ENDCERTIFICATE-----\r\n";
 */


 /*!*****************************************************************************
 \brief      initialize
 \details
 \param[in]    void
 \return    TRUE if success
 ******************************************************************************/
bool md_yaohe_init()
{
    //        md_yaohe_https_config();
    md_m26_http_set_url(MD_YAOHE_POST_URL);
    if (!md_m26_get_IMEI(m_serial_number))
    {
        if (!md_m26_get_IMEI(m_serial_number))
        {
            return false;
        }
    }

    if (!md_yaohe_server_handshake())
    {
        if (!md_yaohe_server_handshake())
        {
            return false;
        }
    }

    return true;
}

/*!*****************************************************************************
\brief      get serial number
\details
\param[in]    void
\return     char*
******************************************************************************/
char* md_yaohe_get_serial_number(void)
{
    return m_serial_number;
}
/*!*****************************************************************************
\brief      HTTPS configure
\details
\param[in]    void
\return     void
******************************************************************************/
static void md_yaohe_https_config(void)
{
    //        md_m26_send_check_ack_ms("AT+QSECWRITE=\"RAM:ca_cert.pem\",2530\r", "CONNECT", 300);//upload ca certificate
    //        md_m26_send_check_ack_ms(m_ca_certificat, "+QSECWRITE: 2530,2964\r\nOK", 300);//upload ca certificate

    md_m26_send_check_ok("AT+QSSLCFG=\"sslversion\",0,3\r"); //Configure SSL version.
    md_m26_send_check_ok("AT+QSSLCFG=\"seclevel\",0,1\r"); //Configure Server authentication and client authentication.
    md_m26_send_check_ok("AT+QSSLCFG=\"ciphersuite\",0,\"0X003D\"\r");
    md_m26_send_check_ok("AT+QSSLCFG=\"cacert\",0,\"RAM:ca_cert.pem\"\r");
    md_m26_send_check_ok("AT+QSSLCFG=\"httpsctxi\",0\r"); //set https context index
    md_m26_send_check_ok("AT+QSSLCFG=\"https\",1\r"); //Enable HTTPS function.
//         md_m26_send_check_ack_ms("AT+QSSLCFG=\"smtpstyle\"\r", "+QSSLCFG=\"smtpstyle\",1 OK\r", 300); 
//         md_m26_send_check_ack_ms("AT+QSSLCFG=\"smtpsctxi\"\r", "+QSSLCFG=\"smtpsctxi\",1 OK\r", 300); 

}
/*!*****************************************************************************
\brief      handshake with server
\details
\param[in]    void
\return     0 if failure
******************************************************************************/
bool md_yaohe_server_handshake(void)
{
    char post[160];

    snprintf(post, sizeof(post),
        "{\"senderId\":\"%s\",\"cmd\":\"handshake\",\"timeStamp\":\"%d000\",\"data\":{\"systemVer\":\"%s\",\"medicationPlanVersion\":\"%d\"}}",
        m_serial_number, md_clock_timestamp_get(), FIRMWARE_VERSION, md_MedicationPlanVer);

    return md_yaohe_send_post_waite_succeed(post);
    /*
    POST:
    {
            "senderId":"xxxx-xxx-xx",
            "cmd" : "handshake",
            "timeStamp" : "xxx"
            "data" : {
                    "systemVer":"xxx"
                    "medicationPlanVersion" : "xxx"
            }
    }

    RESPONSE:
    {
            "status":"succeeded",
            "serverTime":1575336773035,
            "message":""
    }
    */
}

/*!*****************************************************************************
\brief      sync
\details
\param[in]    void
\return     void
******************************************************************************/
void md_yaohe_medication_plans_sync(void)
{
    char* remindertimerId, * ptr_position, data[80];
    uint8_t hour, minute;
    time_t timestamp;

    snprintf(data, sizeof(data), "{\"senderId\":\"%s\",\"cmd\":\"getplan\",\"timeStamp\":\"%d000\"}", m_serial_number, md_clock_timestamp_get());
    if (!md_yaohe_send_post_and_recieve(data, m_plan_content, 4096))
    {
        NRF_LOG_DEBUG("yaohe plan no succeeded");
        ble_log("getplan:failure");
        return;
    }

    memset(data, 0, sizeof(data));

    //get version of plan
    ptr_position = strstr(m_plan_content, "version");
    ptr_position = strstr(ptr_position, ":") + 1;
    strncpy(data, ptr_position, strstr(ptr_position, ",") - ptr_position);
    if (atoi(data) < md_MedicationPlanVer)
    {
        NRF_LOG_DEBUG("yaohe plan invalid version");
        ble_log("getplan:invalid");
        return;
    }
    md_MedicationPlanVer = atoi(data);

    //sync time
    ptr_position = strstr(m_plan_content, "serverTime");
    ptr_position = strstr(ptr_position, ":") + 1;
    strncpy(data, ptr_position, 10);
    data[10] = '\0';
    timestamp = atoi(data) + 8 * 60 * 60;
    md_clock_time_sync(localtime(&timestamp));

    //set alarm
    md_clock_alarm_delete_all();
    if (!strstr(m_plan_content, "Active"))
    {
        NRF_LOG_DEBUG("yaohe plan no active");
        ble_log("getplan:no active");
        return;// plan is not active
    }

    data[2] = '\0';
    ptr_position = m_plan_content;
    while (ptr_position = strstr(ptr_position, "reminderTimeId"))
    {
        remindertimerId = strstr(ptr_position, ":") + 2;
        ptr_position = strstr(remindertimerId, "when");
        ptr_position = strstr(ptr_position, ":") + 2;

        strncpy(data, ptr_position, 2);
        hour = atoi(data);
        strncpy(data, ptr_position + 3, 2);
        minute = atoi(data);
        md_clock_alarm_add(remindertimerId, hour, minute);
    }

    /*
    POST:
    {
            "senderId": "xxxx - xxx - xx",
            "cmd" : "getplan",
            "timeStamp" : "xxx",
            "data" : {}
    }
    RESPONSE:
    {
    "status":"succeeded",
    "serverTime":1575336773035,
    "message":"",
    "data":{"reminderId":"783e9123-9ce9-e911-a32d-7cd30aeb129f","code":null,"remindingFor":"Medicine",
    "schedule":[
            {"reminderTimeId":"4e02a990-d1ea-45e4-97a8-efd5b51c1422","code":null,"when":"09:20","type":"Time",
            "items":[
                    {"reminderItemId":"9fe17d18-3a7c-4a6a-9a5a-1e41e2fbeefe","name":"¸´·½Í·æß¿ËÂå½ºÄÒ","message":"1Á£"},
                    {"reminderItemId":"1265a1e0-3213-4400-9f41-8d61787bc20c","name":"Í·æß°±ÜÐ½ºÄÒ","message":"1Á£"},
                    {"reminderItemId":"9d81e3b3-8fd8-4e21-b653-907f43dbf45a","name":"Í·æß±ûÏ©Æ¬","message":"1Á£"},
                    {"reminderItemId":"48b585c1-9e46-4966-a0f4-facc8ce45e30","name":"Í·æß±ûÏ©½ºÄÒ","message":"1Á£"}],
            "completedForToday":false},
            {"reminderTimeId":"4ed035e7-1c97-4ac0-8a61-648309f07319","code":null,"when":"13:20","type":"time",
            "items":[
                    {"reminderItemId":"92c8ae79-6b36-490e-bcfc-844fc23f2779","name":"ÑÎËáÁÖ¿ÉÃ¹ËØ½ºÄÒ","message":"1Á£"},
                    {"reminderItemId":"d0b34aa7-a61c-4db8-9a30-9970531d4b1b","name":"´×ËáÇâ»¯¿ÉµÄËÉÆ¬","message":"1Á£"},
                    {"reminderItemId":"b8583744-4a8c-4b2d-a940-d818660eff29","name":"ÑÎËá¿ÉÀÖ¶¨Æ¬","message":"1Á£"},
                    {"reminderItemId":"9c4f26e5-9ead-4ce1-b3bd-e33f2def4186","name":"Äá¿ÉµØ¶ûÆ¬","message":"1Á£"}],
            "completedForToday":false},
            {"reminderTimeId":"459c6011-8f40-43de-83c0-e6f4594d35ca","code":null,"when":"16:21","type":"time",
            "items":[
                    {"reminderItemId":"5f5f8c80-3a74-4940-8285-051f3c847cb4","name":"°¢±½´ïßòÆ¬","message":"1Á£"},
                    {"reminderItemId":"5585aab7-40ec-4b33-ad4e-1af5e66c91d4","name":"°¢µÂ¸£Î¤õ¥Æ¬","message":"1Á£"},
                    {"reminderItemId":"baacec92-42b3-4b65-a040-3fd11504cd4f","name":"°¢µÂ¸£Î¤õ¥½ºÄÒ","message":"1Á£"},
                    {"reminderItemId":"acbd3adc-0cf5-498e-be8d-e0040c513ec3","name":"°¢·¨¹Ç»¯´¼Æ¬","message":"1Á£"}],
            "completedForToday":false},
            {"reminderTimeId":"818a24a6-8b49-4cdf-8105-d4be832dcd09","code":null,"when":"23:03","type":"time",
            "items":[
                    {"reminderItemId":"9b5689a2-fdbb-441e-9ebc-0b7ee1213015","name":"¶÷Ìæ¿¨Î¤½ºÄÒ","message":"9Á£"},
                    {"reminderItemId":"d7d01463-ad2d-476b-8133-42f050e831fe","name":"¶÷Ìæ¿¨Î¤·ÖÉ¢Æ¬","message":"8Á£"}],
            "completedForToday":false}
            ],
    "userId":"e1339fa2-b85e-4d44-8e21-98c63388c063",
    "userName":"18867058346",
    "status":"Active",
    "version":14,
    "createdDateTime":"1570519244413",
    "lastModified":"1570521134710",
    "completedForToday":false}
    }
    */

}

/*!*****************************************************************************
\brief      notify alarm event to server
\details
\param[in]    void
\return     void
******************************************************************************/
bool md_yaohe_alarm_notify(md_yaohe_msg_enum msg, char* id, uint8_t hour, uint8_t min)
{
    char* cmd, post[200];

    switch (msg)
    {
    case MD_YAOHE_MSG_ALARMAUDIT:
        cmd = "reminderAudit";
        break;
    case MD_YAOHE_MSG_COMFIRM:
        cmd = "confirm";
        break;
    case MD_YAOHE_MSG_COMFIRMDELAY:
        cmd = "confirmDelay";
        break;
    default:
        break;
    }
    snprintf(post, sizeof(post),
        "{\"senderId\":\"%s\",\"cmd\":\"%s\",\"timeStamp\":\"%d000\",\"data\":{\"medicationPlanVersion\":\"%d\",\"reminderTimeId\":\"%s\",\"reminderTime\":\"%d:%d\"}}",
        m_serial_number, cmd, md_clock_timestamp_get(), md_MedicationPlanVer, id, hour, min);

    return md_yaohe_send_post_waite_succeed(post);
    /*
    POST:
    {
            "senderId":"xxxx-xxx-xx",
            "cmd" : "reminderAudit", /"confirm"/"confirmDelay"
            "timeStamp" : "xxx"
            "data" : {
                    "medicationPlanVersion":"xxx",
                    "reminderTimeId" : "xxx",
                    "reminderTime" : "hh:mm"
            }
    }
    RECIEVE:
    {
            "status":"suceeded",
            "serverTime":1575336773035,
            "message":""
    }
    */

}

/*!*****************************************************************************
\brief      notify door action
\details
\param[in]    md_yaohe_door_action_enum msg
\return     void
******************************************************************************/
bool md_yaohe_door_action_notify(md_yaohe_door_action_enum msg)
{
    char* cmd, post[95];

    switch (msg)
    {
    case MD_YAOHE_DOOR_ACTION_CLOSE:
        cmd = "close";
        break;
    case MD_YAOHE_DOOR_ACTION_OPEN:
        cmd = "open";
        break;
    default:
        break;
    }
    snprintf(post, sizeof(post),
        "{\"senderId\":\"%s\",\"cmd\":\"%s\",\"timeStamp\":\"%d000\",\"data\":{\"door\":1}}",
        m_serial_number, cmd, md_clock_timestamp_get());
    return md_yaohe_send_post_waite_succeed(post);

    /*
    POST:
    {
            "senderId":"xxxx-xxx-xx",
            "cmd" : "open",/"close"
            "timeStamp" : "xxx"
            "data" : {
                    "door": x
            }
    }
    RECIEVE:
    {
            "status":"suceeded",
            "serverTime":1575336773035,
            "message":""
    }
    */

}


/*!*****************************************************************************
\brief      POST and get response
\details
\param[in]    char * post       POST buffer
\param[in]    char * response   Receive buffer
\param[in]    size_t rx_size    Expectant size to receive
\return     bool  Not zero if success
******************************************************************************/
static bool md_yaohe_send_post_and_recieve(char* post, char* response, size_t rx_size)
{
    if (!md_m26_http_post(MD_YAOHE_POST_URL, post, response, rx_size))
    {
        NRF_LOG_DEBUG("post failse")
            md_m26_http_post(MD_YAOHE_POST_URL, post, response, rx_size);        //try again        
    }

    return strstr(response, "succeeded");
}

/*!*****************************************************************************
\brief      sent post and wait success
\details
\param[in]    char *post POST buffer
\return     bool Not zero if success
******************************************************************************/
static bool md_yaohe_send_post_waite_succeed(char* post)
{
    char response[64];

    if (!md_m26_http_post(MD_YAOHE_POST_URL, post, response, sizeof(response)))
    {
        md_m26_http_post(MD_YAOHE_POST_URL, post, response, sizeof(response));        //try again        
    }

    return strstr(response, "succeeded");

}
#endif // MD_YAOHE_C
