#ifndef SPEED
#define SPEED


#include "main.h"
//������
int16_t get_speed(TIM_HandleTypeDef* htim);

void speed_meter_init();



//������
extern int16_t motor_speed[4];


#endif