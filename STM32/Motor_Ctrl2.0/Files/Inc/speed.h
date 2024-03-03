#ifndef SPEED
#define SPEED


#include "main.h"
//函数区
int16_t get_speed(TIM_HandleTypeDef* htim);

void speed_meter_init();



//变量区
extern int16_t motor_speed[4];


#endif