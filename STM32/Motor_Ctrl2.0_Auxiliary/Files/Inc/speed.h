#ifndef SPEED
#define SPEED


#include "main.h"

void speed_meter_init();
int16_t get_speed(TIM_HandleTypeDef* htim);
#endif