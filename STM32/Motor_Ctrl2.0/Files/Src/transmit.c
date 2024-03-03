#include "transmit.h"
#include "usart.h"
#include "string.h"

message_between_boards main_board;
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
	main_board.change++;
	
	memcpy(buffer,&main_board ,15);
	
	main_board.CRC_check = CheckSum(buffer,15);
	memcpy(buffer,&main_board ,sizeof(main_board ));

	HAL_UART_Transmit(&huart2,buffer,sizeof(main_board),4);

}

extern uint8_t CRC_test;

void receieve_from_board()
{
	static uint8_t buffer[30];
	
	
	CRC_test=CheckSum(buffer,15);
	if(buffer[0]==0x51)
		memcpy(&auxilliary_board,buffer,sizeof(auxilliary_board)); 
	
	if(CRC_test==auxilliary_board.CRC_check&&auxilliary_board.head==0x51)
		OK=1;
	else OK=0;
	//串口只能接收字符型数组，不能用结构体直接接收
	HAL_UART_Receive_IT(&huart2,buffer,sizeof(auxilliary_board));
}

