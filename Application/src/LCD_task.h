#ifndef _LCD_TASK_H_
#define _LCD_TASK_H_

#include "st7735s.h"
#include "led.h"
extern xSemaphoreHandle  LCD_Handle;

/**
* @brief LCDˢ���߳�
*/
void LCD_FLUSH_Task(void const * argument);
/**
* @brief ��̬�ַ�ˢ��
*/
void trends_word_task(void const * argument);
/**
* @brief ��̬ͼ��ˢ��
*/
void trends_gemetry_task(void const * argument);


#endif