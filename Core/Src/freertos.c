/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

#include <string.h>
#include <stdio.h>
#include <usart.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define MAX_LENGTH_OF_LINE_RECEIVED_BY_USART 20

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task2_UsartReceiving */
osThreadId_t Task2_UsartReceivingHandle;
const osThreadAttr_t Task2_UsartReceiving_attributes = {
  .name = "Task2_UsartReceiving",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task3_CommandDetection */
osThreadId_t Task3_CommandDetectionHandle;
const osThreadAttr_t Task3_CommandDetection_attributes = {
  .name = "Task3_CommandDetection",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for Queue1_Commands */
osMessageQueueId_t Queue1_CommandsHandle;
const osMessageQueueAttr_t Queue1_Commands_attributes = {
  .name = "Queue1_Commands"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void UsartReceiving(void *argument);
void CommandDetection(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

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

  /* Create the queue(s) */
  /* creation of Queue1_Commands */
  Queue1_CommandsHandle = osMessageQueueNew (10, 20, &Queue1_Commands_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Task2_UsartReceiving */
  Task2_UsartReceivingHandle = osThreadNew(UsartReceiving, NULL, &Task2_UsartReceiving_attributes);

  /* creation of Task3_CommandDetection */
  Task3_CommandDetectionHandle = osThreadNew(CommandDetection, NULL, &Task3_CommandDetection_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_UsartReceiving */
/**
* @brief Function implementing the Task2_UsartReceiving thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UsartReceiving */
void UsartReceiving(void *argument)
{
  /* USER CODE BEGIN UsartReceiving */
	static char line_buffer[MAX_LENGTH_OF_LINE_RECEIVED_BY_USART + 1];
	static uint32_t line_length;
	static uint8_t value;

    static char receivedLine[MAX_LENGTH_OF_LINE_RECEIVED_BY_USART + 1]; // +1 for null terminator


  /* Infinite loop */
  for(;;)
  {

	  if (HAL_UART_Receive(&huart2, &value, 1, 0) == HAL_OK){
	  		if (value == '\r' || value == '\n') {
	  			// end of line character received
	  			if (line_length > 0){
	  				// if the buffer is not empty, we add the \0 character at the end of the line
	  				line_buffer[line_length] = '\0';
	  				// passing the buffer to CommendDetection Task by queue
	  			    strncpy(receivedLine, line_buffer, line_length);
	  			    receivedLine[line_length] = '\0'; // Ensure null termination
	  				osMessageQueuePut(Queue1_CommandsHandle, receivedLine, 0, 200);
	  				int x = osMessageQueueGetCapacity(Queue1_CommandsHandle);
	  				int y = osMessageQueueGetMsgSize(Queue1_CommandsHandle);
	  				// starting data collection again
	  				line_length = 0;
	  			}
	  		}
	  		else {
	  			if (line_length >= MAX_LENGTH_OF_LINE_RECEIVED_BY_USART) {
	  				// too much data, we delete what we have collected so far
	  				line_length = 0;
	  			}
	  			// we add the value to the buffer
	  			line_buffer[line_length++] = value;
	  		}
	  	}

    osDelay(1);
  }
  /* USER CODE END UsartReceiving */
}

/* USER CODE BEGIN Header_CommandDetection */
/**
* @brief Function implementing the Task3_CommandDetection thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CommandDetection */
void CommandDetection(void *argument)
{
  /* USER CODE BEGIN CommandDetection */
	char ReceivedValue[MAX_LENGTH_OF_LINE_RECEIVED_BY_USART + 1];
	  /* Infinite loop */
	  for(;;){

		 osMessageQueueGet(Queue1_CommandsHandle, ReceivedValue, 0, osWaitForever);
		  //ReceivedValue = osMessageGet(Queue1_CommandsHandle, osWaitForever)
		  if (strcmp(ReceivedValue, "led_on") == 0){
			  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		  }else if (strcmp(ReceivedValue, "led_off") == 0) {
			  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		  } else {
			  printf("Nieznane polecenie: %s\n", ReceivedValue);
		  }

	    osDelay(1);
	  }
  /* USER CODE END CommandDetection */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

