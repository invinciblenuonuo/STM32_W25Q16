#include "led.h"


/**
* @brief LED��˸����
*/
void LED_FLASH_TASK(void const * argument)
{
		static int i;

	  while(1)
		{
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_5);
			vTaskDelay(500);
		}
}






