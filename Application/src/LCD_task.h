#ifndef _LCD_TASK_H_
#define _LCD_TASK_H_

#include "st7735s.h"
#include "led.h"
extern xSemaphoreHandle  LCD_Handle;

/**
* @brief LCD刷新线程
*/
void LCD_FLUSH_Task(void const * argument);
/**
* @brief 动态字符刷新
*/
void trends_word_task(void const * argument);
/**
* @brief 动态图形刷新
*/
void trends_gemetry_task(void const * argument);


#endif