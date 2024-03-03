#ifndef __LCD_H__
#define __LCD_H__

#include "main.h"
#include "stdlib.h"

//LCD��Ҫ������
typedef struct  
{										    
	uint16_t width;			//LCD ���
	uint16_t height;			//LCD �߶�
	uint16_t id;				  //LCD ID
	uint8_t  dir;			  //���������������ƣ�0��������1��������	
	uint16_t	 wramcmd;		//��ʼдgramָ��
	uint16_t  setxcmd;		//����x����ָ��
	uint16_t  setycmd;		//����y����ָ��	
	uint8_t   xoffset;    
	uint8_t	 yoffset;
}_lcd_dev;

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
/////////////////////////////////////�û�������///////////////////////////////////	 
#define USE_HORIZONTAL  	 0 //����Һ����˳ʱ����ת���� 	0-0����ת��1-90����ת��2-180����ת��3-270����ת
//////////////////////////////////////////////////////////////////////////////////	  
//����LCD�ĳߴ�
#define LCD_W 128
#define LCD_H 160
////////////////////////////////////////////////////////////////////
//-----------------LCD�˿ڶ���---------------- 
#define GPIO_TYPE  GPIOB  //GPIO������
#define LED      10        //�����������    BLK��    PB9
#define LCD_CS   11       //Ƭѡ����            PB11
#define LCD_RS   12       //�Ĵ���/����ѡ������ PB10 ��DC-data_cmd��
#define LCD_RST  14       //��λ����            PB12
//QDtechȫϵ��ģ������������ܿ��Ʊ��������û�Ҳ���Խ�PWM���ڱ�������

//#define	LCD_LED PBout(LED) //LCD����        BLK��	 PB9

//���ʹ�ùٷ��⺯���������еײ㣬�ٶȽ����½���14֡ÿ�룬���������˾�Ƽ�����
//����IO����ֱ�Ӳ����Ĵ���������IO������ˢ�����ʿ��Դﵽ28֡ÿ�룡 

//GPIO��λ�����ߣ�
#define	LCD_CS_SET  GPIO_TYPE->BSRR=1<<LCD_CS    //Ƭѡ�˿�  	PB11
#define	LCD_RS_SET	GPIO_TYPE->BSRR=1<<LCD_RS    //����/����  PB10	  
#define	LCD_RST_SET	GPIO_TYPE->BSRR=1<<LCD_RST   //��λ			  PB12

//GPIO��λ�����ͣ�							    
#define	LCD_CS_CLR  GPIO_TYPE->BRR=1<<LCD_CS     //Ƭѡ�˿�  	PB11
#define	LCD_RS_CLR	GPIO_TYPE->BRR=1<<LCD_RS     //����/����  PB10	 
#define	LCD_RST_CLR	GPIO_TYPE->BRR=1<<LCD_RST    //��λ			  PB12

#define LCD_LED_ON GPIO_TYPE->BSRR=1<<LED

//****************************************************************************
//������ɫ
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define GREEN       	0x001F  
#define RED         0xF800
#define BLUE       0x07E0
#define PINK      0xFFE0
#define PURPLE  			0X8430 //��ɫ
#define GRAY0       0xEF7D       //��ɫ
#define GRAY1       0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2       0x4208 
//GUI��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
#define LIGHTGREEN     	0X841F //ǳ��ɫ
#define LIGHTGRAY     0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 		0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE      	0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE          0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

//������������ɫ��һЩ���⣬�Ҳ���RGB565Э�����һЩ�Լ���
//�������ԣ��о�������ɫ��ʾ��̫����
#define LJX_WHITE       0xFFFF //
#define LJX_BLACK      	0x0000	 // 
#define LJX_BLUE       	0x01cF  //ǳ��
#define LJX_RED        0Xd8a7//ǳ��ɫ
#define LJX_GREEN			 	0Xd79c//��ɫ
#define LJX_YELLOW		 	0XFFE0//��ɫ
#define LJX_PURPLE       0x8010//��ɫ
#define LJX_PINK       	 0xFe19 //��ɫ

//****************************************************************************
//TFTLCD������Ҫ���õĺ���		   
extern uint16_t  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern uint16_t  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//д�����
void LCD_WR_REG(uint8_t data);

//д������ֵ����
void LCD_WR_DATA(uint8_t data);
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
void LCD_WriteRAM_Prepare(void);
void Lcd_WriteData_16Bit(uint16_t Data);

//����LCD����ʾ���ڣ�X��YStar����ʼ���꣬X��YEnd����ֹ����
void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);

//�������ص�����꣬���ڻ����㣿
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_DrawPoint(uint16_t x,uint16_t y);

//�����������˴�ColorΪWHITE��Ϊ����
void LCD_Clear(uint16_t Color);

//��ʼ��Һ������GPIO
void LCD_GPIOInit(void);

//����LCD��Ļ
void LCD_RESET(void);

//����Һ������ʾ����ת�Ƕ�
void LCD_direction(uint8_t direction);

//��ʼ��Һ����Ļ
void LCD_Init(void);

#endif  
