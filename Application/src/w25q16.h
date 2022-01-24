#ifndef  _W25Q16_H_
#define  _W25Q16_H_

#include "spi.h"
#include "stm32f1xx_hal.h"

#define W25Q128FV_PAGE_SIZE   256
	
#define W25X_FastRead         0x0B      //���_����
#define W25X_DualOutput       0x3B      //���_˫���
#define W25X_S_Erase          0x20      //��������4KB
#define W25X_PowerDown        0xB9      //����
#define W25X_PowerON_ID       0xAB      //�������Ƕ�ID
#define W25X_JEDEC_ID         0x9F      //ʮ��λ��JEDEC_ID
#define W25Qx_ERROR           0xff
#define W25Qx_TIMEOUT_VALUE   1000
#define W25Qx_BUSY            0x01
#define W25Qx_TIMEOUT         111
#define W25Qx_OK              0xee

static u8  W25X_WriteDisable = 0x04;
static u8  W25X_WriteEnable  = 0x06;
static u8  W25X_ReadStatus   = 0x05;
static u8  W25X_WriteStatus  = 0x01;
static u8  W25X_Writepage  = 0x02;
static u8  W25X_ReadDATA8  = 0x03;
static u8  W25X_B_Erase  = 0xD8;
static u8  W25X_C_Erase   =   0xC7;      //��Ƭ��ʽ��

unsigned char W25Q16_ReadStatus(void);
void W25X_Flash_Write_Page(u8* pbuf,u32 WriteAddr,u16 Len);
void SPI_Flash_Read(u8 * pbuf,u32 ReadAddr,u16 Len); 
void W25X_BlockErase(unsigned long Addr24);  //��������ͼʾ��64KB�ռ�
void W25Q16_EMPTY(void);
void SPI_Flash_Write_NoCheck(u8 * pbuf,u32 WriteAddr,u16 Len);
void W25Q16_WRITE(u8* pData, u32 WriteAddr, u32 Size);
void BSP_W25Qx_Erase_Block(uint32_t Address);


#endif
