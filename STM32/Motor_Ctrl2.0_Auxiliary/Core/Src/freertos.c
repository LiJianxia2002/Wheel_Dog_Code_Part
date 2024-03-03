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
#include "transmit.h"
#include "servo_ctrl.h"
#include "usart.h"
#include "walk.h"
#include "speed.h"
#include "tim.h"
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
float walk_speed=0.025;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for connect_with_ma */
osThreadId_t connect_with_maHandle;
const osThreadAttr_t connect_with_ma_attributes = {
  .name = "connect_with_ma",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Servo_ctrl */
osThreadId_t Servo_ctrlHandle;
const osThreadAttr_t Servo_ctrl_attributes = {
  .name = "Servo_ctrl",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh7,
};
/* Definitions for Walk */
osThreadId_t WalkHandle;
const osThreadAttr_t Walk_attributes = {
  .name = "Walk",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void connect_with_main(void *argument);
void Servo_ctrl_task(void *argument);
void Walk_task(void *argument);

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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of connect_with_ma */
  connect_with_maHandle = osThreadNew(connect_with_main, NULL, &connect_with_ma_attributes);

  /* creation of Servo_ctrl */
  Servo_ctrlHandle = osThreadNew(Servo_ctrl_task, NULL, &Servo_ctrl_attributes);

  /* creation of Walk */
  WalkHandle = osThreadNew(Walk_task, NULL, &Walk_attributes);

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

/* USER CODE BEGIN Header_connect_with_main */
/**
* @brief Function implementing the connect_with_ma thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_connect_with_main */
void connect_with_main(void *argument)
{
  /* USER CODE BEGIN connect_with_main */
	auxilliary_board.head=0x51;
	receieve_from_board();
	/* Infinite loop */
  for(;;)
  {	
		auxilliary_board.speed[0]=-get_speed(&htim2);
		auxilliary_board.speed[1]=-get_speed(&htim1);
		auxilliary_board.servo_mode_and_height=main_board.servo_mode_and_height+1;
		
		connect_with_board();
    osDelay(10);
  }
  /* USER CODE END connect_with_main */
}

/* USER CODE BEGIN Header_Servo_ctrl_task */
/**
* @brief Function implementing the Servo_ctrl thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Servo_ctrl_task */
void Servo_ctrl_task(void *argument)
{
  /* USER CODE BEGIN Servo_ctrl_task */
	servos_data_init();
	uint8_t i;

	for(i=0;i<6;i++)
	{	
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		osDelay(500);
	}
	
	
	
  /* Infinite loop */
  for(;;)
  {
		main_data_parse();
		
		if(drive_height)
			drive_mode();
		
		HAL_UART_Transmit(&huart3,servos,15,3);
    osDelay(50);
		
		i+=1;
		if(i==10)
		{
			i=0;
			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		}
  }
  /* USER CODE END Servo_ctrl_task */
}

/* USER CODE BEGIN Header_Walk_task */
/**
* @brief Function implementing the Walk thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Walk_task */
void Walk_task(void *argument)
{
  /* USER CODE BEGIN Walk_task */
  /* Infinite loop */
  for(;;)
  {
		if(walk_speed>-10)
		{
			walk_speed_set(walk_speed);
			Servo_Degree_calc_walk();
		}
    osDelay(30);
  }
  /* USER CODE END Walk_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)//串口接收完成回调函数
{
	if(huart->Instance == USART2)
	{ 
   receieve_from_board();
	}
}
/* USER CODE END Application */

