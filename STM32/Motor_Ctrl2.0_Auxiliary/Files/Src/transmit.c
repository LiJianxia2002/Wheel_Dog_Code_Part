#include "transmit.h"
#include "usart.h"
#include "string.h"
#include "servo_ctrl.h"
#include "crc.h"
extern float walk_speed;

message_between_boards main_board;  //定义的原则为数据来源
message_between_boards auxilliary_board;

uint8_t OK;

uint8_t CheckSum(uint8_t *Buf, uint8_t Len)
{
  uint8_t i = 0;
  uint8_t sum = 0;
  uint8_t checksum = 0;
 
 
  for(i=0; i<Len; i++)
  {
    sum += *Buf++;
  }
 
  checksum = sum & 0xff;
  return checksum;
}


void connect_with_board()
{
	static uint8_t buffer[30];
	auxilliary_board.change++;
	
	memcpy(buffer,&auxilliary_board ,15);
	
	auxilliary_board.CRC_check = CheckSum(buffer,15);
	memcpy(buffer,&auxilliary_board ,sizeof(auxilliary_board ));

	HAL_UART_Transmit(&huart2,buffer,sizeof(auxilliary_board ),4);

}


void receieve_from_board()
{
	static uint8_t buffer[30];
	uint8_t CRC_test;
	
	CRC_test=CheckSum(buffer,15);
	if(buffer[0]==0x51)
		memcpy(&main_board,buffer,sizeof(main_board)); 
	
	if(CRC_test==main_board.CRC_check&&main_board.head==0x51)
		OK=1;
	else OK=0;
	//串口只能接收字符型数组，不能用结构体直接接收
	HAL_UART_Receive_IT(&huart2,buffer,sizeof(main_board));
}


void main_data_parse()
{
	//servo_mode_and_height字节解算
	if(main_board.servo_mode_and_height ==0)
	{
		servos_data_init_lie();
		walk_speed=-11;
		drive_height=0;
	}
	else if(main_board.servo_mode_and_height==1)
	{
		drive_height=0;
		walk_speed=0.0;
	}
	else if(main_board.servo_mode_and_height >1&&main_board.servo_mode_and_height <=5)
	{
		drive_height=0;
		walk_speed=0.005f*(float)main_board.servo_mode_and_height;
	}
	else if(main_board.servo_mode_and_height >5&&main_board.servo_mode_and_height <9)
	{
		drive_height=0;
		walk_speed=-0.005f*(float)(5-main_board.servo_mode_and_height);
	}
	else if(main_board.servo_mode_and_height >=10&&main_board.servo_mode_and_height <=40)
	{
		walk_speed=-11;
		drive_height=main_board.servo_mode_and_height -25;
		if(drive_height==0) drive_height=1;
	}
	else
	{
		servos_data_init();
		drive_height=0;
		walk_speed=-11;
	}
}