#include "w25q16.h"


void WriteEnable(void)
{ 
		HAL_SPI_Transmit(&hspi2 ,&W25X_WriteEnable ,1 ,50000);
}

void WriteDisable(void)
{
		HAL_SPI_Transmit(&hspi2,&W25X_WriteDisable ,1 ,50000);
}

// 功能：读取W25Q16芯片的状态。
// 返回值：状态寄存器数据字节
// 注：W25X16内部状态寄存器第0位=0表示空闲，0位=1表示忙。
unsigned char W25Q16_ReadStatus()
{
    unsigned char status=0;
		HAL_SPI_Transmit(&hspi2,&W25X_ReadStatus ,1 ,50000);
		HAL_SPI_Receive(&hspi2 , &status , 1 , 1000);
    return status;
}  

// 功能：写W25Q16芯片的状态寄存器。
// 只有SPR、TB、BP2、BP1、BP0 (bit7、5、4、3、2)可以写、
// 注：W25X16内部状态寄存器第0位=0表示空闲，0位=1表示忙。
void W25Q16_WriteStatus(unsigned char Status)
{
		HAL_SPI_Transmit(&hspi2,&W25X_WriteStatus ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,&Status ,1 ,50000);
}

//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pbuf:数据存储区
//WriteAddr:开始写入的地址(24bit)
//Len:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!  
void W25X_Flash_Write_Page(u8* pbuf,u32 WriteAddr,u16 Len)
{
		u8 Addr[3];
		Addr[0] =  (u8)((WriteAddr)>>16);
		Addr[1] =  (u8)((WriteAddr)>>8);
		Addr[2] =  (u8)(WriteAddr);

    while(W25Q16_ReadStatus()&0x01);    //判断是否忙
		WriteEnable();                  //SET WEL      
		HAL_SPI_Transmit(&hspi2,&W25X_Writepage ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,Addr ,3 ,50000);	
		HAL_SPI_Transmit(&hspi2,pbuf ,Len ,50000);
    while(W25Q16_ReadStatus()&0x01);   //等待写入结束   
}

//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pbuf:数据存储区
//ReadAddr:开始读取的地址(24bit)
//Len:要读取的字节数(最大65535)
void SPI_Flash_Read(u8 * pbuf,u32 ReadAddr,u16 Len)   
{
		u8 Addr[3];
	
		Addr[0] =  (u8)((ReadAddr)>>16);
		Addr[1] =  (u8)((ReadAddr)>>8);
		Addr[2] =  (u8)(ReadAddr);	
    while(W25Q16_ReadStatus()&0x01);      // 判断是否忙
	
    HAL_SPI_Transmit(&hspi2,&W25X_ReadDATA8 ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,Addr ,3 ,50000);	
  	HAL_SPI_Receive(&hspi2 , pbuf , Len , 1000);

}  


void W25X_BlockErase(unsigned long Addr24)  //擦除资料图示的64KB空间
{
    unsigned char Addr1;       // 最低地址字节
    unsigned char Addr2;       // 中间地址字节
    unsigned char Addr3;       // 最高地址字节  
    Addr1=Addr24;
    Addr24=Addr24>>8;
    Addr2=Addr24;
    Addr24=Addr24>>8;
    Addr3=Addr24;                      // 把地址拆开来  
    while(W25Q16_ReadStatus()&0x01);   // 判断是否忙   
    WriteEnable();                     // 写允许
	  HAL_SPI_Transmit(&hspi2,&W25X_B_Erase ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,&Addr3 ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,&Addr2 ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,&Addr1 ,1 ,50000);
	
    while(W25Q16_ReadStatus()&0x01);   // 等待擦除完成
}


