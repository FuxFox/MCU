/*******************************************************************************
 * Module: DrvC_STA369
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2018/05/09 10:07          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     DrvC_STA369_prc.c
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2018/05/09
 *******************************************************************************/
#ifndef DRVC_STA369_PRC_C
#define DRVC_STA369_PRC_C

#define STA369_INIT_TAB_NB        (82*2)    //除了音量外的参数数量
 //sta369initialize表
const uint16_t sta369_init_tab[STA369_INIT_TAB_NB] = {//寄存器地址，数据
    0x00,    0x63,
    0x01,   0x80,
    0x02,   0x97,
    0x03,   0x40,
    0x04,   0xC2,

    0x05,   0xdc,                    //设置输出方式：2.0
    0x06,   0x50,                    //设置输出方式：Line output variable - channel 3 volume effects line output, no EQ
    0x07,   0xff,                    //总音量，值越小，音量越大                                                                                    
    0x08,   STA369_VOL_SPK_DEF,        //1/L通道音量，值越小，音量越大
    0x09,   STA369_VOL_SPK_DEF,        //2/R通道音量，值越小，音量越大
    0x0a,   STA369_VOL_PHONE_DEF,    //3/L通道音量，值越小，音量越大(耳机总音量)

    0x0B,   0x80,
    0x0C,   0x00,
    0x0E,   0x00,
    0x0F,   0x40,
    0x10,   0x80,
    0x11,   0x77,
    0x12,   0x6A,
    0x13,   0x69,
    0x14,   0x6A,
    0x15,   0x69,
    0x16,   0x00,
    0x17,   0x00,
    0x18,   0x00,
    0x19,   0x00,
    0x1A,   0x00,
    0x1B,   0x00,
    0x1C,   0x00,
    0x1D,   0x00,
    0x1E,   0x00,
    0x1F,   0x00,
    0x20,   0x00,
    0x21,   0x00,
    0x22,   0x00,
    0x23,   0x00,
    0x24,   0x00,
    0x25,   0x00,
    0x26,   0x00,
    0x27,   0x1A,
    0x28,   0xC0,
    0x29,   0xF3,
    0x2A,   0x33,
    0x2B,   0x00,
    0x2C,   0x0C,
    0x2D,   0x7F,
    0x31,   0x00,
    0x32,   0x30,
    0x33,   0x30,
    0x34,   0x30,
    0x35,   0x30,
    0x36,   0x00,
    0x37,   0x00,
    0x38,   0x00,
    0x39,   0x01,
    0x3A,   0xEE,
    0x3B,   0xFF,
    0x3C,   0x7E,
    0x3D,   0xC0,
    0x3E,   0x26,
    0x3F,   0x00,
    0x46,   0xFF,
    0x48,   0x00,
    0x49,   0x00,
    0x4A,   0x00,
    0x4B,   0x04,
    0x4C,   0x00,
    0x4D,   0x32,
    0x4E,   0x00,
    0x4F,   0x5E,
    0x60,   0x00,
    0x61,   0x00,
    0x62,   0x00,
    0x63,   0x00,
    0x64,   0x00,
    0x65,   0x00,
    0x66,   0x00,
    0x67,   0x00,
    0x68,   0x00,
    0x69,   0x00,
    0x6A,   0x00,
    0x6B,   0x00,
    0x6C,   0x44,
};



/*!*****************************************************************************
\brief  initialize
\details

\param    none
\return none

\author        FuxFox 2018/5/9 10:07
*******************************************************************************/
void DrvC_STA369_Init(void)
{
    uint16_t i;

    DrvC_GPIO_ConfigToGpio(STA369_CHECKIN_PORT, STA369_CHECKIN_BIT);

    DrvC_GPIO_ConfigDir(STA369_CHECKIN_PORT, STA369_CHECKIN_BIT, GPIO_BIT_IN);

    //STA369参数initialize
    for(i=0; i<STA369_INIT_TAB_NB; i+=2)                  
    {
        DrvC_I2C_WriteAdata(STA369_I2C_ADDR, sta369_init_tab[i],sta369_init_tab[i+1]);    
    }
}

/*!*****************************************************************************
\brief      功放输入检测
\details

\param        none

\return     uint16_t
\retval        

\author        FuxFox 2018/05/16 10:36
*******************************************************************************/
uint16_t DrvC_STA369_CheckIn(void)
{
    return DrvC_GPIO_ReadLevel(STA369_CHECKIN_PORT, STA369_CHECKIN_BIT);
}

/*!*****************************************************************************
\brief      向STA369发送数据
\details

\param[in] msgInfo :待发送数据信息

\return     none
\retval        

\author        FuxFox 2018/05/16 11:31
*******************************************************************************/
void DrvC_STA369_SendData(stSTA369_MSG_INFO_P msgInfo)
{
    DrvC_I2C_Write(STA369_I2C_ADDR, msgInfo->regAddr, msgInfo->pBuffer, msgInfo->bufSize);
}
#endif // DRVC_STA369_PRC_C