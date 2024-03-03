/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
 uint8_t brake=0;
 int16_t last_expect;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
	int16_t GetData;//编码器数值
	uint8_t Direction;//编码器方向
	
	#define MAX_OUTPUT 65535
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int16_t get_speed()
{
	int16_t speed=(int16_t)__HAL_TIM_GET_COUNTER(&htim2);
	speed-=50;
	Direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2);
	__HAL_TIM_SET_COUNTER(&htim2,50);
	return speed;
}

typedef struct 
{
	float kp;
	float ki;
	float kd;
	int32_t output;
	int16_t current;
	int16_t last;
	int16_t expect;
	float I;
}pid_t;

pid_t pid_motor1;


void pid_calc(pid_t* T) //
{
	float P,I,D;
	P=T->kp*(T->expect-T->current);
	T->I+=T->ki*(T->expect-T->current);
	D=T->kd*(T->current-T->last);
	
	T->output=(int32_t)(P+T->I+D);
}

void turn(int32_t input)
{
	
	if(input>0&&(!brake))
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,0);
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,1);
		TIM3->CCR4=(uint16_t)input;
	}
	else if(!brake)
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,1);
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,0);
		TIM3->CCR4=(uint16_t)(-input);
	}
	else if(brake)
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,1);
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,1);
		TIM3->CCR4=0;
	}
}



void PID_Cal(pid_t* T) //增量式
{
	short Error = T->expect - T->current;
	static short Error_last = 0,Error_prev = 0;
	short pwm_add=0;
	pwm_add = T->kp*(Error - Error_last) + T->ki*Error + T->kd*(Error-2.0f*Error_last+Error_prev);
	T->I+=T->ki*Error;
	
	Error_prev = Error_last;	  	    // 保存上上次误差
  Error_last = Error;	              // 保存上次偏差
	
	T->output=pwm_add;
}
//blog.csdn.net/QWQ_DIODA/article/details/116519580
int32_t Main_output=0;


void motor_task()
{
		GetData = get_speed();
	//如果数据剧烈跳变，对错误数据进行滤波
//		if(GetData*pid_motor1.expect<0)
//			pid_motor1.current=pid_motor1.last;
//		else
			pid_motor1.current=GetData;
		
		PID_Cal(&pid_motor1);
		Main_output+=pid_motor1.output;
		
	
		
		if(Main_output>MAX_OUTPUT) Main_output=MAX_OUTPUT;
		else if(Main_output<-MAX_OUTPUT) Main_output=-MAX_OUTPUT;
		//当方向相反，刹车100ms
		if(pid_motor1.expect*last_expect<0) brake+=5;
		if(brake) brake--;
	
		//更新状态值
		last_expect=pid_motor1.expect;
		pid_motor1.last=pid_motor1.current;
	
		turn(Main_output);
}


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	
  HAL_TIM_Base_Start_IT(&htim4);
	
	HAL_TIM_PWM_Start (&htim3,TIM_CHANNEL_4 );

	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,1);
	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);
  TIM3->CCR4=0;
	
	pid_motor1.kp=800;
	pid_motor1.ki=100;
	pid_motor1.kd=0;
	pid_motor1.expect=15;
	
	
	

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

		
		HAL_Delay(9);
		
		//turn(pid_motor1.output);
		
	  //pid_motor1.last=GetData;

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
