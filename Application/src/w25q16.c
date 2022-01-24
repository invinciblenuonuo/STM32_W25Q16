#include "w25q16.h"


void WriteEnable(void)
{ 
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&hspi2 ,&W25X_WriteEnable ,1 ,50000);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

}

void WriteDisable(void)
{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&hspi2,&W25X_WriteDisable ,1 ,50000);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

}

// ���ܣ���ȡW25Q16оƬ��״̬��
// ����ֵ��״̬�Ĵ��������ֽ�
// ע��W25X16�ڲ�״̬�Ĵ�����0λ=0��ʾ���У�0λ=1��ʾæ��
unsigned char W25Q16_ReadStatus()
{
    unsigned char status=0;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

		HAL_SPI_Transmit(&hspi2,&W25X_ReadStatus ,1 ,50000);
		HAL_SPI_Receive(&hspi2 , &status , 1 , 1000);
	
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

    return status;
}  

// ���ܣ�дW25Q16оƬ��״̬�Ĵ�����
// ֻ��SPR��TB��BP2��BP1��BP0 (bit7��5��4��3��2)����д��
// ע��W25X16�ڲ�״̬�Ĵ�����0λ=0��ʾ���У�0λ=1��ʾæ��
void W25Q16_WriteStatus(unsigned char Status)
{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

		HAL_SPI_Transmit(&hspi2,&W25X_WriteStatus ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,&Status ,1 ,50000);
	
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

}
//��Ƭ����
void W25Q16_EMPTY()
{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&hspi2,&W25X_C_Erase ,1 ,50000);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

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
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	
		HAL_SPI_Transmit(&hspi2,&W25X_Writepage ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,Addr ,3 ,50000);	
		HAL_SPI_Transmit(&hspi2,pbuf ,Len ,50000);
	
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

    while(W25Q16_ReadStatus()&0x01);   //�ȴ�д�����   
	

}
//�޼���дSPI FLASH
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ����
//��ָ����ַ��ʼд��ָ�����ȵ�����
//pbuf:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//Len:Ҫд����ֽ���(���65535)
void SPI_Flash_Write_NoCheck(u8 * pbuf,u32 WriteAddr,u16 Len)
{
    u16 PageLen;                  // ҳ��д���ֽڳ���
    PageLen=256 - WriteAddr%256;    // ��ҳʣ����ֽ��� ����ҳʣ��ռ䣩
    if(Len<=PageLen) PageLen=Len; // ������256 ���ֽ�
    while(1)
    {
        W25X_Flash_Write_Page(pbuf,WriteAddr,PageLen);
        if(PageLen==Len)break;   // д�������
        else
        {
            pbuf+=PageLen;
            WriteAddr+=PageLen;
            Len-=PageLen;              //  ��ȥ�Ѿ�д���˵��ֽ���
            if(Len>256)PageLen=256;   // һ�ο���д��256 ���ֽ�
            else PageLen=Len;          // ����256 ���ֽ���
        }
    }
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
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	
    HAL_SPI_Transmit(&hspi2,&W25X_ReadDATA8 ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,Addr ,3 ,50000);	
  	HAL_SPI_Receive(&hspi2 , pbuf , Len , 1000);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

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
    Addr3=Addr24;    
	// �ѵ�ַ����  
    while(W25Q16_ReadStatus()&0x01);   // �ж��Ƿ�æ   
    WriteEnable();                     // д����
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

	  HAL_SPI_Transmit(&hspi2,&W25X_B_Erase ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,&Addr3 ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,&Addr2 ,1 ,50000);
		HAL_SPI_Transmit(&hspi2,&Addr1 ,1 ,50000);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	
    while(W25Q16_ReadStatus()&0x01);   // �ȴ��������

}


void W25Q16_WRITE(u8* pData, u32 WriteAddr, u32 Size)
{
		uint8_t cmd[4];
    uint32_t end_addr, current_size, current_addr;
    //uint32_t tickstart = HAL_GetTick();
	
	  current_addr = 0;
	  while(current_addr <= WriteAddr)
		{
				current_addr += 0x100;
		}
		current_size = current_addr - WriteAddr; //�������ǰҳ����д�Ŀռ�
		
		if(current_size > Size)
		{
			current_size = Size;
		}

	  current_addr = WriteAddr;
		end_addr = WriteAddr + Size;
		
		do
		{
				cmd[0] = 0x02;
				cmd[1] = (uint8_t)(current_addr >> 16);
				cmd[2] = (uint8_t)(current_addr >> 8);
				cmd[3] = (uint8_t)current_addr ;
				
				while(W25Q16_ReadStatus()&0x01);    //�ж��Ƿ�æ
				WriteEnable();                  //SET WEL 
			
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
				HAL_SPI_Transmit(&hspi2 ,cmd , 4 , 5000);
				HAL_SPI_Transmit(&hspi2 ,pData , current_size , 5000);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
			
				current_addr += current_size;
				pData += current_size;
				current_size = ((current_addr + 0x100) > end_addr) ? (end_addr - current_addr) : 0x100;
		}
		while(current_addr < end_addr);
		
		


}


void BSP_W25Qx_Erase_Block(uint32_t Address)
{
	u8 cmd[4];
	cmd[0] = W25X_S_Erase;
	cmd[1] = (uint8_t)(Address >> 16);
	cmd[2] = (uint8_t)(Address >> 8);
	cmd[3] = (uint8_t)Address ;
	WriteEnable();                  //SET WEL 
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, cmd, 4, 5000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
		
}











