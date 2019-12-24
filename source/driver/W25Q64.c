/*******************************************************************************
 * Module: W25Q64
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2018/10/22 22:08          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     W25Q64.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2018/10/22
  *******************************************************************************/
#ifndef W25Q64_C
#define W25Q64_C

#include "global.h"

#define SECTOR_SIZE 4096
#define PAGE_SIZE    256

#define W25Q64_CS() GPIO_WriteBit(SPI2_CS_PORT, SPI2_CS_PIN, Bit_RESET)
#define W25Q64_NCS() GPIO_WriteBit(SPI2_CS_PORT, SPI2_CS_PIN, Bit_SET)


uint8_t TempBuff[SECTOR_SIZE];

/*!*****************************************************************************
\brief  忙检测
\param    void
\return void
*******************************************************************************/
uint8_t W25Q64_IsBusy(void)
{
    uint8_t statusValue;
    uint32_t timeCount = 0;
    do
    {
        timeCount++;
        if (timeCount > 0xEFFFFFFF) //等待超时
        {
            return 1;
        }
        W25Q64_CS(); //使能器件
        SPI2_ReadWriteByte(0x05); //发送读取状态寄
        statusValue = SPI2_ReadWriteByte(0xFF); //读取一个字节
        W25Q64_NCS(); //取消片选
    } while ((statusValue & 0x01) == 0x01); // 等待 BUSY 位清空
    return 0;
}

/*!*****************************************************************************
\brief  读取芯片ID
\param    void
\return void
*******************************************************************************/
uint16_t W25Q64_ReadID(void)
{
    uint16_t id;

    if (W25Q64_IsBusy())
    {
        return 0;
    }

    W25Q64_CS();

    SPI2_ReadWriteByte(0x90);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    id = SPI2_ReadWriteByte(0xFF);
    id <<= 8;
    id |= SPI2_ReadWriteByte(0xFF);
    W25Q64_NCS();

    return id;
}
/*!*****************************************************************************
\brief  读取芯片JEDECID
\param    void
\return void
*******************************************************************************/
uint32_t W25Q64_ReadJEDECID(void)
{
    uint32_t id;

    if (W25Q64_IsBusy())
    {
        return 0;
    }

    W25Q64_CS();

    SPI2_ReadWriteByte(0x9F);
    id = SPI2_ReadWriteByte(0xFF);
    id <<= 8;
    id |= SPI2_ReadWriteByte(0xFF);
    id <<= 8;
    id |= SPI2_ReadWriteByte(0xFF);
    W25Q64_NCS();

    return id;
}
/*!*****************************************************************************
\brief  读数据
\param    void
\return void
*******************************************************************************/
void W25Q64_ReadData(uint8_t* buf, uint32_t addr, uint16_t len)
{
    SPI2_SetSpeed(SPI_BaudRatePrescaler_2);

    W25Q64_IsBusy();

    W25Q64_CS();

    SPI2_ReadWriteByte(0x03);
    SPI2_ReadWriteByte(addr >> 16);
    SPI2_ReadWriteByte(addr >> 8);
    SPI2_ReadWriteByte(addr);

    while (len--)
    {
        *buf++ = SPI2_ReadWriteByte(0xFF);
    };

    W25Q64_NCS();
}

/*!*****************************************************************************
\brief  写使能
\param    void
\return void
*******************************************************************************/
void W25Q64_EnableWrite(void)
{
    W25Q64_CS();

    SPI2_ReadWriteByte(0x06);

    W25Q64_NCS();
}
/*!*****************************************************************************
\brief  擦除一个扇区
\param    void
\return void
*******************************************************************************/
void W25Q64_EraseSector(uint32_t addr)
{
    W25Q64_IsBusy();
    W25Q64_EnableWrite();

    W25Q64_CS();

    SPI2_ReadWriteByte(0x20);
    SPI2_ReadWriteByte(addr >> 16);
    SPI2_ReadWriteByte(addr >> 8);
    SPI2_ReadWriteByte(addr);

    W25Q64_NCS();
}

/*!*****************************************************************************
\brief  页写
\param    void
\return void
*******************************************************************************/
void W25Q64_PageWrite(uint8_t* buff, uint32_t addr, uint16_t len)
{
    uint16_t i;
    uint8_t j = 1;

    while (j)
    {
        if (len >= PAGE_SIZE)
        {
            i = PAGE_SIZE;
        }
        else
        {
            i = len;
            j = 0;
        }

        W25Q64_IsBusy();
        W25Q64_EnableWrite();

        W25Q64_CS();

        SPI2_ReadWriteByte(0x02);
        SPI2_ReadWriteByte(addr >> 16);
        SPI2_ReadWriteByte(addr >> 8);
        SPI2_ReadWriteByte(addr);

        while (i--)
        {
            SPI2_ReadWriteByte(*buff++);
        }

        W25Q64_NCS();

        addr += PAGE_SIZE;
        len -= PAGE_SIZE;
    }
}

/*!*****************************************************************************
\brief  任意写入
\param    void
\return void
*******************************************************************************/
void W25Q64_Write(uint8_t* Buff, uint32_t writeAddr, uint16_t len)
{
    uint32_t sectorIndex;
    uint16_t offsetInSector, sectorLastSize;
    uint16_t i;

    sectorIndex = writeAddr / SECTOR_SIZE;
    offsetInSector = writeAddr & (SECTOR_SIZE - 1);
    sectorLastSize = SECTOR_SIZE - offsetInSector;


    while (len)
    {
        if (sectorLastSize >= len)
        {
            sectorLastSize = len;
        }
        W25Q64_ReadData(TempBuff, sectorIndex * SECTOR_SIZE, SECTOR_SIZE);
        for (i = 0; i < sectorLastSize; i++)
        {
            if (TempBuff[offsetInSector + i] != 0xFF)
            {
                break;
            }
        }

        if (i < sectorLastSize)
        {
            W25Q64_EraseSector(sectorIndex);
            for (i = 0; i < sectorLastSize; i++)
            {
                TempBuff[offsetInSector + i] = Buff[i];
            }
            W25Q64_PageWrite(TempBuff, sectorIndex * SECTOR_SIZE, SECTOR_SIZE);
        }
        else
        {
            W25Q64_PageWrite(Buff, sectorIndex * SECTOR_SIZE, SECTOR_SIZE);
        }
        writeAddr += sectorLastSize;
        Buff += sectorLastSize;
        len -= sectorLastSize;
        sectorIndex++;
        sectorLastSize = SECTOR_SIZE;
        offsetInSector = 0;
    }

}
#endif // W25Q64_C
