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
	
#define STA369_I2C_ADDR    (0x38>>1)        /*!< STA369������ַ */

/*!< STA369 ���������� ʹ�õ�GPIO�˿ں����� */
#ifdef NEW_MAIN_BOARD
#define STA369_CHECKIN_PORT        GPIO_P8
#define STA369_CHECKIN_BIT        GPIO_BIT_7
#else
#define STA369_CHECKIN_PORT        GPIO_P5
#define STA369_CHECKIN_BIT        GPIO_BIT_9
#endif // SDP20


#define STA369_VOL_OFF            0xFF    //!< mute
#define STA369_VOL_ALL_DEF        0x00    //������(0-255��ֵԽ������ԽС����֮����Խ��)
#define STA369_SPK_VOL_PERCENT    87        //���������İٷ���
#define STA369_PHONE_VOL_PERCENT    82        //���������İٷ���
#define STA369_VOL_SPK_DEF        (255 - 255*STA369_SPK_VOL_PERCENT/100) //�������� (255 - 255*x/100) xΪ�����İٷ���
#define STA369_VOL_PHONE_DEF    (255 - 255*STA369_PHONE_VOL_PERCENT/100)//0x39    //�������� ͨ������110�����ţ�����������0x39�����Ե�С�����������������������





//********************************* Data Type ***********************************/

/*! STA369 MSG structure */
typedef struct
{
    uint16_t  regAddr;        /*!< device register address */
    uint16_t* pBuffer;        /*!< buffer to be send */
    uint16_t  bufSize;        /*!< data size to be send */
}stSTA369_MSG_INFO, *stSTA369_MSG_INFO_P;

/*! �����Ĵ���ö�� */
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

//����������
extern uint16_t DrvC_STA369_CheckIn(void);

//��������
extern void DrvC_STA369_SendData(stSTA369_MSG_INFO_P msgInfo);





//********************************* Private Interface ***************************/





/*! @}*/ //end of group drv_sta369
#endif // DRVC_STA369_PUBLIC_H
