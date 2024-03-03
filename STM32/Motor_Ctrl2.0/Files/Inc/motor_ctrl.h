#ifndef MOTOR_H	
#define MOTOR_H

#include "main.h"

typedef struct 
{
	int16_t output;
	int16_t current;
	int16_t expect;
	short Error_prev;
	short Error_last;
	float I;
}pid_t;

typedef struct
{
	uint16_t rocker[4];
	uint8_t button[2];
	uint8_t status;

	uint8_t checksum;
}remote_t;

extern remote_t remote;

void motor_ctrl_at_TB6612();
void PID_Init();
void PID_Cal(pid_t* T);
void remote_recieve();

extern int16_t expect_speed[4];
extern pid_t motor[4];
extern int16_t X_expect;
extern int16_t Y_expect;
extern int16_t Z_expect;
extern int16_t height_expect;












#endif