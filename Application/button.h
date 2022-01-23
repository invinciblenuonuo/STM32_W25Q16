#ifndef _BUTTON_H_
#define _BUTTON_H_


#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "led.h"

extern xSemaphoreHandle   KEY_1_Handle;
extern xSemaphoreHandle   KEY_2_Handle;


/**
* @brief °´¼ü¼ì²âÈÎÎñ
*/
void Button_detect_TASK(void const * argument);


#endif
