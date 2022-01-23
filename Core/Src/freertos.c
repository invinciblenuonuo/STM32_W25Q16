/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LCD_task.h"
#include "button.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId LEDHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
osThreadId LCD_FLUSHHandle;
osThreadId Button_TaskHHandle;
osThreadId Word_TaskHHandle;
osThreadId Gemetry_TaskHandle;
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void LED_FLASH(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	vSemaphoreCreateBinary( KEY_1_Handle);
	vSemaphoreCreateBinary( KEY_2_Handle);
	LCD_Handle = xSemaphoreCreateMutex();
	
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of LED */
  osThreadDef(LED, LED_FLASH_TASK, osPriorityNormal, 0, 16);
  LEDHandle = osThreadCreate(osThread(LED), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	 osThreadDef( LCD_FLUSH ,
								LCD_FLUSH_Task, 
	              +1, 
								0, 
	              128);
  LCD_FLUSHHandle = osThreadCreate(osThread(LCD_FLUSH), NULL);
	
//	xTaskCreate( Button_detect_TASK , "handle_key",128 ,NULL, 2 ,NULL);
	 osThreadDef( Button_Task ,
								Button_detect_TASK, 
	              osPriorityAboveNormal, 
								0, 
	              32);
  Button_TaskHHandle = osThreadCreate(osThread(Button_Task), NULL);

	 osThreadDef( Word_Task ,
								trends_word_task, 
	              0, 
								0, 
	              32);
  Word_TaskHHandle = osThreadCreate(osThread(Word_Task), NULL);
	
	 osThreadDef( Gemetry_Task ,
								trends_gemetry_task, 
	              osPriorityNormal, 
								0, 
	              32);
  Gemetry_TaskHandle = osThreadCreate(osThread(Gemetry_Task), NULL);
	

//	 osThreadDef(LVGL_FLUSH, LVGL_Fresh_Task, osPriorityNormal, 0, 128);
//	 LVGL_FLUSHHandle = osThreadCreate(osThread(LVGL_FLUSH), NULL);

  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_LED_FLASH */
/**
* @brief Function implementing the LED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED_FLASH */
void LED_FLASH(void const * argument)
{
  /* USER CODE BEGIN LED_FLASH */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END LED_FLASH */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

