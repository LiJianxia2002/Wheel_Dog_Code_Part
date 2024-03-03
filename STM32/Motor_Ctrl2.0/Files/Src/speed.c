#include "speed.h"
#include "tim.h"

int16_t motor_speed[4];

void speed_meter_init()
{
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
}


int16_t get_speed(TIM_HandleTypeDef* htim)
{
	int16_t speed=(int16_t)__HAL_TIM_GET_COUNTER(htim);
	//Direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2);
	__HAL_TIM_SET_COUNTER(htim,0);
	return speed;
}