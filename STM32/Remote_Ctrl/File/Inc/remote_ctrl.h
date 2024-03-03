#ifndef REMOTE
#define REMOTE

#include "main.h"
#include "adc.h"
#include "nrf24L01.h"
#include "usart.h"
#include "string.h"
#include "menu.h"

uint8_t CheckSum(uint8_t *Buf, uint8_t Len);
void remote_ctrl_();
void button_check();

typedef struct
{
	uint16_t rocker[4];
	uint8_t button[2];
	uint8_t status;
	float data[3];
	uint8_t checksum;
}remote_t;

extern remote_t remote;
extern uint8_t buttonL;
extern uint8_t buttonR;
extern uint8_t up_button;
extern uint8_t down_button;

#endif