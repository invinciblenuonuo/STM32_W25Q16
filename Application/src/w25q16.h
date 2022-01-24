#ifndef  _W25Q16_H_
#define  _W25Q16_H_

#include "spi.h"
#include "stm32f1xx_hal.h"

//#define u8 unsigned char
//#define u16 unsigned int
//#define u32 unsigned long
	
//#define W25X_ReadStatus       0x05      //读状态寄存器
//#define W25X_WriteStatus      0x01      //写状态寄存器
//#define W25X_ReadDATA8        0x03      //普读_数据
#define W25X_FastRead         0x0B      //快读_数据
#define W25X_DualOutput       0x3B      //快读_双输出
//#define W25X_Writepage        0x02      //写_数据_0~255个字节
#define W25X_S_Erase          0x20      //扇区擦除4KB
//#define W25X_B_Erase          0xD8      //块区擦除64KB
//#define W25X_C_Erase          0xC7      //整片格式化
#define W25X_PowerDown        0xB9      //待机
#define W25X_PowerON_ID       0xAB      //开机或是读ID
#define W25X_JEDEC_ID         0x9F      //十六位的JEDEC_ID
//#define W25X_WriteEnable      0x06      //写允许
//#define W25X_WriteDisable     0x04      //写禁止

static u8  W25X_WriteDisable = 0x04;
static u8  W25X_WriteEnable  = 0x06;
static u8  W25X_ReadStatus   = 0x05;
static u8  W25X_WriteStatus  = 0x01;
static u8  W25X_Writepage  = 0x02;
static u8  W25X_ReadDATA8  = 0x03;
static u8  W25X_B_Erase  = 0xD8;
static u8  W25X_C_Erase   =   0xC7;      //整片格式化

unsigned char W25Q16_ReadStatus();
void W25X_Flash_Write_Page(u8* pbuf,u32 WriteAddr,u16 Len);
void SPI_Flash_Read(u8 * pbuf,u32 ReadAddr,u16 Len); 
void W25X_BlockErase(unsigned long Addr24);  //擦除资料图示的64KB空间
void W25Q16_EMPTY();


#endif
