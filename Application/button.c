#include "button.h"

xSemaphoreHandle   KEY_1_Handle;
xSemaphoreHandle   KEY_2_Handle;

/**
* @brief �����������
*/
void Button_detect_TASK(void const * argument)
{
	  while(1)
		{
//			vTaskDelay(100);
//			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_5); //���ڼ�������Ƿ���������
			
			xSemaphoreTake( KEY_1_Handle, portMAX_DELAY ); 
			vTaskDelay(3);
			if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == GPIO_PIN_RESET)
			{
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
			}
		}
}

/**
* @brief �����ⲿ�жϷ�����
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	static portBASE_TYPE xHigherPriorityTaskWoken;
		xHigherPriorityTaskWoken = pdFALSE;
	
		switch(GPIO_Pin)
		{
			case GPIO_PIN_3 :  xSemaphoreGiveFromISR( KEY_1_Handle , &xHigherPriorityTaskWoken );break;
			case GPIO_PIN_4 :  break;
			default : break;			
		}
}




