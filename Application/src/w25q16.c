#include "w25q16.h"


void WriteEnable(void)
{ 
		HAL_SPI_Transmit(&hspi2 ,&W25X_WriteEnable ,1 ,50000);
}

void WriteDisable(void)
{
		HAL_SPI_Transmit(&hspi2,&W25X_WriteDisable ,1 ,50000);
}

// ���ܣ���ȡW25Q16оƬ��״̬��
// ����ֵ��״̬�Ĵ��������ֽ�
// ע��W25X16�ڲ�״̬�Ĵ�����0λ=0��ʾ���У�0λ=1��ʾæ��
unsigned char W25Q16_ReadStatus()
{
    unsigned char status=0;
		HAL_SPI_Transmit(&hspi2,&W25X_ReadStatus ,1 ,50000);
		HAL_SPI_Receive(&hspi2 , &status , 1 , 1000);
    return status;
}  

// ���ܣ�дW25Q16оƬ��״̬�Ĵ�����
// ֻ��SPR��TB��BP2��BP1��BP0 (bit7��5��4��3��2)����д��
// ע��W25X16�ڲ�״̬�Ĵ�����0λ=0��ʾ���У�0λ=1��ʾæ��
void W25Q16_WriteStatus(unsigned char Status)
{
		HAL_SPI_Transmit(&hspi2,&W25X_WriteStatus ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,&Status ,1 ,50000);
}

//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pbuf:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//Len:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!  
void W25X_Flash_Write_Page(u8* pbuf,u32 WriteAddr,u16 Len)
{
		u8 Addr[3];
		Addr[0] =  (u8)((WriteAddr)>>16);
		Addr[1] =  (u8)((WriteAddr)>>8);
		Addr[2] =  (u8)(WriteAddr);

    while(W25Q16_ReadStatus()&0x01);    //�ж��Ƿ�æ
		WriteEnable();                  //SET WEL      
		HAL_SPI_Transmit(&hspi2,&W25X_Writepage ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,Addr ,3 ,50000);	
		HAL_SPI_Transmit(&hspi2,pbuf ,Len ,50000);
    while(W25Q16_ReadStatus()&0x01);   //�ȴ�д�����   
}

//��ȡSPI FLASH  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pbuf:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//Len:Ҫ��ȡ���ֽ���(���65535)
void SPI_Flash_Read(u8 * pbuf,u32 ReadAddr,u16 Len)   
{
		u8 Addr[3];
	
		Addr[0] =  (u8)((ReadAddr)>>16);
		Addr[1] =  (u8)((ReadAddr)>>8);
		Addr[2] =  (u8)(ReadAddr);	
    while(W25Q16_ReadStatus()&0x01);      // �ж��Ƿ�æ
	
    HAL_SPI_Transmit(&hspi2,&W25X_ReadDATA8 ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,Addr ,3 ,50000);	
  	HAL_SPI_Receive(&hspi2 , pbuf , Len , 1000);

}  


void W25X_BlockErase(unsigned long Addr24)  //��������ͼʾ��64KB�ռ�
{
    unsigned char Addr1;       // ��͵�ַ�ֽ�
    unsigned char Addr2;       // �м��ַ�ֽ�
    unsigned char Addr3;       // ��ߵ�ַ�ֽ�  
    Addr1=Addr24;
    Addr24=Addr24>>8;
    Addr2=Addr24;
    Addr24=Addr24>>8;
    Addr3=Addr24;                      // �ѵ�ַ����  
    while(W25Q16_ReadStatus()&0x01);   // �ж��Ƿ�æ   
    WriteEnable();                     // д����
	  HAL_SPI_Transmit(&hspi2,&W25X_B_Erase ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,&Addr3 ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,&Addr2 ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,&Addr1 ,1 ,50000);
	
    while(W25Q16_ReadStatus()&0x01);   // �ȴ��������
}


