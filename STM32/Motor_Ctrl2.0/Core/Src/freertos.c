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
#include "speed.h"
#include "transmit.h"
#include "motor_ctrl.h"
#include "tim.h"
#include "usart.h"
#include "nrf24L01.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t tmp_buf[33];
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t CRC_test;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Servo_uart_ctrl */
osThreadId_t Servo_uart_ctrlHandle;
const osThreadAttr_t Servo_uart_ctrl_attributes = {
  .name = "Servo_uart_ctrl",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for connect_Aux */
osThreadId_t connect_AuxHandle;
const osThreadAttr_t connect_Aux_attributes = {
  .name = "connect_Aux",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for motor_ctrl */
osThreadId_t motor_ctrlHandle;
const osThreadAttr_t motor_ctrl_attributes = {
  .name = "motor_ctrl",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh1,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Servo_uart_ctrl_task(void *argument);
void connect_Aux_task(void *argument);
void motor_ctrl_task(void *argument);

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

  /* creation of Servo_uart_ctrl */
  Servo_uart_ctrlHandle = osThreadNew(Servo_uart_ctrl_task, NULL, &Servo_uart_ctrl_attributes);

  /* creation of connect_Aux */
  connect_AuxHandle = osThreadNew(connect_Aux_task, NULL, &connect_Aux_attributes);

  /* creation of motor_ctrl */
  motor_ctrlHandle = osThreadNew(motor_ctrl_task, NULL, &motor_ctrl_attributes);

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

/* USER CODE BEGIN Header_Servo_uart_ctrl_task */
/**
* @brief Function implementing the Servo_uart_ctrl thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Servo_uart_ctrl_task */
void Servo_uart_ctrl_task(void *argument)
{
  /* USER CODE BEGIN Servo_uart_ctrl_task */
  /* Infinite loop */
  for(;;)
  {
			if(NRF24L01_RxPacket(tmp_buf)==0) //nrf数据接收
    {
			memcpy(&remote,tmp_buf,sizeof(remote));
		}
    osDelay(20);
  }
  /* USER CODE END Servo_uart_ctrl_task */
}

/* USER CODE BEGIN Header_connect_Aux_task */
/**
* @brief Function implementing the connect_Aux thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_connect_Aux_task */
void connect_Aux_task(void *argument)
{
  /* USER CODE BEGIN connect_Aux_task */
	main_board.head=0x51;
	receieve_from_board();
  /* Infinite loop */
  for(;;)
  {
		connect_with_board();
    osDelay(25);
  }
  /* USER CODE END connect_Aux_task */
}

/* USER CODE BEGIN Header_motor_ctrl_task */
/**
* @brief Function implementing the motor_ctrl thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_motor_ctrl_task */
void motor_ctrl_task(void *argument)
{
  /* USER CODE BEGIN motor_ctrl_task */
	PID_Init();
  /* Infinite loop */
  for(;;)
  {
		motor_speed[0]=-get_speed(&htim2);
		motor_speed[1]=-get_speed(&htim1);		
		motor_speed[2]=auxilliary_board.speed[1];
		motor_speed[3]=auxilliary_board.speed[0];
    remote_recieve();
		
		if(remote.status==1)
			motor_ctrl_at_TB6612();
		
    osDelay(10);
  }
  /* USER CODE END motor_ctrl_task */
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

