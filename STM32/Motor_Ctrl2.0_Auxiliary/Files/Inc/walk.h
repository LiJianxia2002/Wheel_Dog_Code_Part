#ifndef WALK
#define WALK

#include "main.h"

extern float LEG_degree[4];
extern float LOWER_LEG_degree[4];


void walk_speed_set(float step);
void Servo_Degree_calc_walk();
#endif