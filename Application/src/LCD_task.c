#include "LCD_task.h"


xSemaphoreHandle  LCD_Handle;

/**
* @brief LCDˢ���߳�
*/
void LCD_FLUSH_Task(void const * argument)
{
	while(1)
	{	
		lcd_show();
		vTaskDelay(10);
	}
}


/**
* @brief ��̬�ַ�ˢ��
*/
void trends_word_task(void const * argument)
{
		static int count;
		while(1)
		{
			xSemaphoreTake( LCD_Handle, portMAX_DELAY );
			{
				count++;
				lcd_num(count ,30 ,30);
			}
			xSemaphoreGive( LCD_Handle );
			vTaskDelay(1);
		}
}

/**
* @brief ��̬ͼ��ˢ��
*/
void trends_gemetry_task(void const * argument)
{
		static int count1,count2,flag = 1;
		while(1)
		{
			
					if(flag == 1)
					{
						count1++;
						if(count1 > 70)
						{
							count2 = 0;
							flag = -flag;
						}
						xSemaphoreTake( LCD_Handle, portMAX_DELAY );
						lcd_color_fill_int(20,20, 40+count1 ,40+count1,0xffff);
						xSemaphoreGive( LCD_Handle );

					}
					else if(flag == -1)
					{
						count2++;
						if(count2 > 70)
						{
							count1 = 0;
							flag = -flag;
						}	
						xSemaphoreTake( LCD_Handle, portMAX_DELAY );					
						lcd_color_fill_int(20,20, 40+count2 ,40+count2,0);		
						xSemaphoreGive( LCD_Handle );
						
					}
			
				vTaskDelay(1);
		}
}
