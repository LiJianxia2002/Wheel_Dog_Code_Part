#include "servo_ctrl.h"



uint8_t servos[15];
int8_t drive_height;

void servos_data_init()
{
	uint8_t i;
	for(i=0;i<12;i++)
	{
		servos[i+1]=90;
	}
  servos[2]=45;
	servos[4]=135;
	servos[6]=45;
	servos[8]=135;	
	
	
	servos[0]=0x51;
	servos[13]=0;
	servos[14]=0x50;
}

void servos_data_init_lie()
{
	uint8_t i;
	for(i=0;i<8;i++)
		servos[i+1]=90;
		
  servos[0]=0x51;
	servos[13]=0;
	servos[14]=0x50;
}

void drive_mode()
{
	servos[1]=90;
	servos[3]=90;
	servos[5]=90;
	servos[7]=90;
	servos[2]=45-drive_height;
	servos[4]=135+drive_height;
	servos[6]=45-drive_height;
	servos[8]=135+drive_height;
}
