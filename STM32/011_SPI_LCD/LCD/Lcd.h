#ifndef __LCD_H__
#define __LCD_H__

#include "main.h"
#include "stdlib.h"

//LCD重要参数集
typedef struct  
{										    
	uint16_t width;			//LCD 宽度
	uint16_t height;			//LCD 高度
	uint16_t id;				  //LCD ID
	uint8_t  dir;			  //横屏还是竖屏控制：0，竖屏；1，横屏。	
	uint16_t	 wramcmd;		//开始写gram指令
	uint16_t  setxcmd;		//设置x坐标指令
	uint16_t  setycmd;		//设置y坐标指令	
	uint8_t   xoffset;    
	uint8_t	 yoffset;
}_lcd_dev;

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数
/////////////////////////////////////用户配置区///////////////////////////////////	 
#define USE_HORIZONTAL  	 0 //定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转
//////////////////////////////////////////////////////////////////////////////////	  
//定义LCD的尺寸
#define LCD_W 128
#define LCD_H 160
////////////////////////////////////////////////////////////////////
//-----------------LCD端口定义---------------- 
#define GPIO_TYPE  GPIOB  //GPIO组类型
#define LED      10        //背光控制引脚    BLK脚    PB9
#define LCD_CS   11       //片选引脚            PB11
#define LCD_RS   12       //寄存器/数据选择引脚 PB10 （DC-data_cmd）
#define LCD_RST  14       //复位引脚            PB12
//QDtech全系列模块采用了三极管控制背光亮灭，用户也可以接PWM调节背光亮度

//#define	LCD_LED PBout(LED) //LCD背光        BLK脚	 PB9

//如果使用官方库函数定义下列底层，速度将会下降到14帧每秒，建议采用我司推荐方法
//以下IO定义直接操作寄存器，快速IO操作，刷屏速率可以达到28帧每秒！ 

//GPIO置位（拉高）
#define	LCD_CS_SET  GPIO_TYPE->BSRR=1<<LCD_CS    //片选端口  	PB11
#define	LCD_RS_SET	GPIO_TYPE->BSRR=1<<LCD_RS    //数据/命令  PB10	  
#define	LCD_RST_SET	GPIO_TYPE->BSRR=1<<LCD_RST   //复位			  PB12

//GPIO复位（拉低）							    
#define	LCD_CS_CLR  GPIO_TYPE->BRR=1<<LCD_CS     //片选端口  	PB11
#define	LCD_RS_CLR	GPIO_TYPE->BRR=1<<LCD_RS     //数据/命令  PB10	 
#define	LCD_RST_CLR	GPIO_TYPE->BRR=1<<LCD_RST    //复位			  PB12

#define LCD_LED_ON GPIO_TYPE->BSRR=1<<LED

//****************************************************************************
//画笔颜色
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define GREEN       	0x001F  
#define RED         0xF800
#define BLUE       0x07E0
#define PINK      0xFFE0
#define PURPLE  			0X8430 //灰色
#define GRAY0       0xEF7D       //白色
#define GRAY1       0x8410      	//灰色1      00000 000000 00000
#define GRAY2       0x4208 
//GUI颜色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
#define LIGHTGREEN     	0X841F //浅绿色
#define LIGHTGRAY     0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 		0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE      	0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)

//鉴于他给的颜色有一些问题，我参照RGB565协议加了一些自己的
//经过测试，感觉它的颜色显示不太符合
#define LJX_WHITE       0xFFFF //
#define LJX_BLACK      	0x0000	 // 
#define LJX_BLUE       	0x01cF  //浅蓝
#define LJX_RED        0Xd8a7//浅绿色
#define LJX_GREEN			 	0Xd79c//黄色
#define LJX_YELLOW		 	0XFFE0//粉色
#define LJX_PURPLE       0x8010//黑色
#define LJX_PINK       	 0xFe19 //橙色

//****************************************************************************
//TFTLCD部分外要调用的函数		   
extern uint16_t  POINT_COLOR;//默认红色    
extern uint16_t  BACK_COLOR; //背景颜色.默认为白色

//写命令函数
void LCD_WR_REG(uint8_t data);

//写入数据值函数
void LCD_WR_DATA(uint8_t data);
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
void LCD_WriteRAM_Prepare(void);
void Lcd_WriteData_16Bit(uint16_t Data);

//设置LCD的显示窗口，X、YStar是起始坐标，X、YEnd是终止坐标
void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);

//设置像素点的坐标，用于画个点？
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_DrawPoint(uint16_t x,uint16_t y);

//清屏函数，此处Color为WHITE则为清屏
void LCD_Clear(uint16_t Color);

//初始化液晶屏的GPIO
void LCD_GPIOInit(void);

//重置LCD屏幕
void LCD_RESET(void);

//设置液晶屏显示的旋转角度
void LCD_direction(uint8_t direction);

//初始化液晶屏幕
void LCD_Init(void);

#endif  
