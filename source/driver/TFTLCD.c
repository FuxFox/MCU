/*******************************************************************************
 * Module: TFTLCD
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2018/10/21 13:22          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     TFTLCD.c
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2018/10/21
 *******************************************************************************/
#ifndef TFTLCD_C
#define TFTLCD_C

#include "global.h"

typedef struct 
{
    uint16_t CMD;
    uint16_t DAT;
}TFTLCD_TypeDef;

#define LCD_BASE ((uint32_t)(0x6C000000 | 0x000007FE))
#define TFTLCD    ((TFTLCD_TypeDef *)LCD_BASE)



void TFT_FSMC_Init(void);
void TFT_GPIO_Init(void);
void TFT_LCD_Config(void);



/*!*****************************************************************************
\brief  LCD initialize
\param    void
\return void
*******************************************************************************/
void TFT_Init(void)
{
    TFT_GPIO_Init();
    TFT_FSMC_Init();
    TFT_LCD_Config();
}

/*!*****************************************************************************
\brief  LCD GPIO initialize
\param    void
\return void
*******************************************************************************/
void TFT_GPIO_Init(void)
{

    GPIO_InitTypeDef gpioInit;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |RCC_APB2Periph_GPIOG, ENABLE);

    //FSMC_A10(G0),FSME_NE4(CS)(G12)
    gpioInit.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_12;
    gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &gpioInit);

    gpioInit.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15
                        | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_Init(GPIOD, &gpioInit);

    gpioInit.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOE, &gpioInit);
}

/*!*****************************************************************************
\brief  LCD-FSMCinitialize
\param    void
\return void
*******************************************************************************/
void TFT_FSMC_Init(void)
{
    FSMC_NORSRAMInitTypeDef Fsmc_Init;
    FSMC_NORSRAMTimingInitTypeDef stFSMC_ReadWriteTiming;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

    Fsmc_Init.FSMC_Bank = FSMC_Bank1_NORSRAM4;
    Fsmc_Init.FSMC_MemoryType = FSMC_MemoryType_SRAM;
    Fsmc_Init.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    Fsmc_Init.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    Fsmc_Init.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;
    Fsmc_Init.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    Fsmc_Init.FSMC_ReadWriteTimingStruct = &stFSMC_ReadWriteTiming;
    Fsmc_Init.FSMC_WriteTimingStruct = &stFSMC_ReadWriteTiming;

    stFSMC_ReadWriteTiming.FSMC_AccessMode = FSMC_AccessMode_B;
    stFSMC_ReadWriteTiming.FSMC_CLKDivision = 0x01;
    stFSMC_ReadWriteTiming.FSMC_AddressSetupTime = 0x03;
    stFSMC_ReadWriteTiming.FSMC_AddressHoldTime = 0x00;
    stFSMC_ReadWriteTiming.FSMC_DataSetupTime =0x05;
    stFSMC_ReadWriteTiming.FSMC_DataLatency = 0x00;
    stFSMC_ReadWriteTiming.FSMC_BusTurnAroundDuration = 0x00;

    FSMC_NORSRAMInit(&Fsmc_Init);
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);

}

/*!*****************************************************************************
\brief  TFTÐ´ÃüÁî
\param    void
\return void
*******************************************************************************/
void TFT_WriteCmd(uint16_t cmd)
{
    TFTLCD->CMD = cmd;
}

/*!*****************************************************************************
\brief  TFTÐ´Êý¾Ý
\param    void
\return void
*******************************************************************************/
void TFT_WriteDat(uint16_t dat)
{
    TFTLCD->DAT = dat;
}

/*!*****************************************************************************
\brief  TFTLCDÅäÖÃ
\param    void
\return void
*******************************************************************************/
void TFT_LCD_Config(void)
{
    uint16_t i;
    
    Delay_ms(50); 

    TFT_WriteCmd(0x0000);TFT_WriteDat(0x0000);
    TFT_WriteCmd(0x0000);TFT_WriteDat(0x0000);
    TFT_WriteCmd(0x0000);TFT_WriteDat(0x0000);

    TFT_WriteCmd(0x0400);TFT_WriteDat(0x6200); 
    TFT_WriteCmd(0x0008);TFT_WriteDat(0x0808); 


    TFT_WriteCmd(0x0001);TFT_WriteDat(0x0100);
    TFT_WriteCmd(0x0002);TFT_WriteDat(0x0100);
    TFT_WriteCmd(0x0003);TFT_WriteDat(0x1030);
    TFT_WriteCmd(0x0008);TFT_WriteDat(0x0808);
    /*gamma set 20090423 BY LYJ*/

    TFT_WriteCmd(0x0300);TFT_WriteDat(0x000c); 
    TFT_WriteCmd(0x0301);TFT_WriteDat(0x5A0B); 
    TFT_WriteCmd(0x0302);TFT_WriteDat(0x0906); 
    TFT_WriteCmd(0x0303);TFT_WriteDat(0x1017); 
    TFT_WriteCmd(0x0304);TFT_WriteDat(0x2300); 
    TFT_WriteCmd(0x0305);TFT_WriteDat(0x1700); 
    TFT_WriteCmd(0x00307);TFT_WriteDat(0x0c09); 
    TFT_WriteCmd(0x306);TFT_WriteDat(0x6309); 
    TFT_WriteCmd(0x0308);TFT_WriteDat(0x100c); 
    TFT_WriteCmd(0x0309);TFT_WriteDat(0x2232); 
    /*power set*/
    TFT_WriteCmd(0x0010);TFT_WriteDat(0x0014);
    TFT_WriteCmd(0x0011);TFT_WriteDat(0x0101);  
    TFT_WriteCmd(0x0100);TFT_WriteDat(0x0230);//
    //for(i=500; i>0; i--);
    Delay_ms(50);
    TFT_WriteCmd(0x0101);TFT_WriteDat(0x0247);//
    for(i=500; i>0; i--);
    Delay_ms(50);
    TFT_WriteCmd(0x0103);TFT_WriteDat(0x0a00);//Starts VLOUT3,Sets the VREG1OUT.
    for(i=500; i>0; i--);
    Delay_ms(10);
    TFT_WriteCmd(0x0280);TFT_WriteDat(0xf0ff);//VCOMH voltage   //0xcEff
    Delay_ms(50);
    for(i=500; i>0; i--);
    TFT_WriteCmd(0x0102);TFT_WriteDat(0xB1b0);//Starts VLOUT3,Sets the VREG1OUT.
    for(i=500; i>0; i--);
    Delay_ms(50);
    /*window set*/
    TFT_WriteCmd(0x0210);TFT_WriteDat(0x0000);//Window Horizontal RAM Address Start
    TFT_WriteCmd(0x0211);TFT_WriteDat(0x00ef);//Window Horizontal RAM Address End
    TFT_WriteCmd(0x0212);TFT_WriteDat(0x0000);//Window Vertical RAM Address Start
    TFT_WriteCmd(0x0213);TFT_WriteDat(0x018f);//Window Vertical RAM Address End
    TFT_WriteCmd(0x0200);TFT_WriteDat(0x0000);//RAM Address Set (Horizontal Address)
    TFT_WriteCmd(0x0201);TFT_WriteDat(0x0000);//RAM Address Set (Vertical Address)
    TFT_WriteCmd(0x0401);TFT_WriteDat(0x0000);//Base Image Display
    TFT_WriteCmd(0x0007);TFT_WriteDat(0x0100);//Display Control 1
    for(i=500; i>0; i--);
    Delay_ms(50);
    TFT_WriteCmd(0x0202);
}


#endif // TFTLCD_C
