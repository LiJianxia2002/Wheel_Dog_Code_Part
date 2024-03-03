#ifndef TRANSMIT
#define TRANSMIT


#include "main.h"

//Э������

typedef struct    //��16�ֽ�
{
	uint8_t head;
	int16_t speed[2];
	uint8_t change;
	uint8_t servo_mode_and_height;  
	uint8_t messages[8];
	uint8_t CRC_check;
}message_between_boards;

//0ſ�ش��� 1-5��·�ٶ� 10-40������ʻ�߶�(25Ϊ��)

extern message_between_boards main_board;
extern message_between_boards auxilliary_board;
void connect_with_board();
void receieve_from_board();
void main_data_parse();
#endif