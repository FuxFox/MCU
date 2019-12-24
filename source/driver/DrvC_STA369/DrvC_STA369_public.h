/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2018/05/09 10:07          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     DrvC_STA369_public.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2018/05/09
  *******************************************************************************/
#ifndef DRVC_STA369_PUBLIC_H
#define DRVC_STA369_PUBLIC_H

/*! \defgroup drv_sta369_public Public
\ingroup drv_sta369
\brief 
\details 
* @{ */

//********************************* Module Config *******************************/
	
#define STA369_I2C_ADDR    (0x38>>1)        /*!< STA369器件地址 */

/*!< STA369 功放输入检测 使用的GPIO端口和引脚 */
#ifdef NEW_MAIN_BOARD
#define STA369_CHECKIN_PORT        GPIO_P8
#define STA369_CHECKIN_BIT        GPIO_BIT_7
#else
#define STA369_CHECKIN_PORT        GPIO_P5
#define STA369_CHECKIN_BIT        GPIO_BIT_9
#endif // SDP20


#define STA369_VOL_OFF            0xFF    //!< mute
#define STA369_VOL_ALL_DEF        0x00    //总音量(0-255，值越大音量越小，反之音量越大)
#define STA369_SPK_VOL_PERCENT    87        //喇叭音量的百分数
#define STA369_PHONE_VOL_PERCENT    82        //耳机音量的百分数
#define STA369_VOL_SPK_DEF        (255 - 255*STA369_SPK_VOL_PERCENT/100) //喇叭音量 (255 - 255*x/100) x为音量的百分数
#define STA369_VOL_PHONE_DEF    (255 - 255*STA369_PHONE_VOL_PERCENT/100)//0x39    //耳机音量 通道音量110，功放（耳机）音量0x39，可以调小音量，切勿随便再增大音量





//********************************* Data Type ***********************************/

/*! STA369 MSG structure */
typedef struct
{
    uint16_t  regAddr;        /*!< device register address */
    uint16_t* pBuffer;        /*!< buffer to be send */
    uint16_t  bufSize;        /*!< data size to be send */
}stSTA369_MSG_INFO, *stSTA369_MSG_INFO_P;

/*! 音量寄存器枚举 */
typedef enum        
{
    STA369_REG_ALL_VOL = 0x07, 
    STA369_REG_SPKL_VOL,
    STA369_REG_SPKR_VOL,
    STA369_REG_PHONE_VOL,

}emSTA369_REG;




//********************************* Public Interface ****************************/


//initialize
extern void DrvC_STA369_Init(void);

//功放输入检测
extern uint16_t DrvC_STA369_CheckIn(void);

//发送数据
extern void DrvC_STA369_SendData(stSTA369_MSG_INFO_P msgInfo);





//********************************* Private Interface ***************************/





/*! @}*/ //end of group drv_sta369
#endif // DRVC_STA369_PUBLIC_H
