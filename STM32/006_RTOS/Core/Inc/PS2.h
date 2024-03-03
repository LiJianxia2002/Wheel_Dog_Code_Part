// PS2.h
#ifndef __PS2_H__
#define __PS2_H__

#include "main.h"
#define DAT HAL_GPIO_ReadPin(PS2_DAT_GPIO_Port,PS2_DAT_Pin)

#define CMD_H HAL_GPIO_WritePin(PS2_CMD_GPIO_Port,PS2_CMD_Pin,GPIO_PIN_SET)
#define CMD_L HAL_GPIO_WritePin(PS2_CMD_GPIO_Port,PS2_CMD_Pin,GPIO_PIN_RESET)

#define CS_H HAL_GPIO_WritePin(PS2_CS_GPIO_Port,PS2_CS_Pin,GPIO_PIN_SET)
#define CS_L HAL_GPIO_WritePin(PS2_CS_GPIO_Port,PS2_CS_Pin,GPIO_PIN_RESET)

#define CLK_H HAL_GPIO_WritePin(PS2_CLK_GPIO_Port,PS2_CLK_Pin,GPIO_PIN_SET)
#define CLK_L HAL_GPIO_WritePin(PS2_CLK_GPIO_Port,PS2_CLK_Pin,GPIO_PIN_RESET)


//These are our button constants
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2        	9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16
#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      26

//These are stick values
#define PSS_RX 5                //右摇杆X轴数据
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8

typedef __packed struct
{
	__packed struct
	{
		uint8_t PS2_LX;
		uint8_t PS2_LY;
		uint8_t PS2_RX;
		uint8_t PS2_RY;
	}RC;
				
	uint8_t PS2_KEY;    
} RC_ctrl_t;
	
void delay_us(uint32_t);

void PS2_Init(void);//手柄设置初始化
void PS2_ReadData(void);
void PS2_Cmd(uint8_t CMD);		  //
uint8_t PS2_DataKey(void);		  //键值读取
uint8_t PS2_AnologData(uint8_t button); //得到一个摇杆的模拟量
void PS2_ClearData(void);	  //清除数据缓冲区

void PS2_ShortPoll(void);//short poll
void PS2_EnterConfing(void);//进入设置
void PS2_TurnOnAnalogMode(void);//保存并完成设置
void PS2_VibrationMode(void);
void PS2_ExitConfing(void);//保存并完成设置
void PS2_Init(void);//手柄设置初始化
void PS2_Vibration(uint8_t motor1 ,uint8_t motor2);

void PS2_Receive(RC_ctrl_t*);
#endif
;
