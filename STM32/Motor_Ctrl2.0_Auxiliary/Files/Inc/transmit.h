#ifndef TRANSMIT
#define TRANSMIT


#include "main.h"

//协议内容

typedef struct    //共16字节
{
	uint8_t head;
	int16_t speed[2];
	uint8_t change;
	uint8_t servo_mode_and_height;  
	uint8_t messages[8];
	uint8_t CRC_check;
}message_between_boards;

//0趴地待机 1-5走路速度 10-40调整行驶高度(25为中)

extern message_between_boards main_board;
extern message_between_boards auxilliary_board;
void connect_with_board();
void receieve_from_board();
void main_data_parse();
#endif