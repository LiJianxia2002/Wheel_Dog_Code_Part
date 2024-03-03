#include "menu.h"

extern const unsigned char gImage_qq[3200];

uint8_t menu[10]="MENU!";
uint8_t four_wheel[12]="WHEELS_mode";
uint8_t four_leg[12]="LEGS_mode";
uint8_t settings[15]="PARM_set";
uint8_t ok[5]="ok";
uint8_t return_[8]="return";
uint8_t engineer[15]="AUTHOR";

uint8_t menu1_to_menu2=0;
uint8_t setting_to_menu3=0;

#define BG LJX_YELLOW  //背景颜色

void menu_init()
{
	LCD_Init();
	HAL_Delay(500);
	LCD_Clear(LJX_YELLOW);
//	Gui_Drawbmp16(45,80,gImage_qq);
}

void menu_dynamic_test()
{
	LCD_ShowNum(40,50,(uint32_t)remote.rocker[0],4,20);
	LCD_ShowNum(40,20,(uint32_t)buttonL,3,20);
}

extern uint8_t jianke[64];

void hanzi_test()
{
	GUI_DrawFont16(50,5,0,DARKBLUE,jianke,0);
}

uint8_t return_count;

uint8_t double_press_quit_menu()
{
	if(buttonL==1&&return_count==0)
		{
			return_count=20;
			buttonL=2;
		}
		else if(return_count&&buttonL!=1)
		{
			return_count--;
		}
		else if(buttonL==1&&return_count>1)  //return
		{
			LCD_Clear(LJX_YELLOW);
			buttonL=2;
			return_count=0;
			return 1;
		}
		return 0;
}

uint8_t WHEEL_MODE[15]="WHEEL_MODE";
uint8_t main_menu()
{
	 uint8_t item=0;
	static uint8_t i;
	static uint16_t color[5];
	remote.status=0;
	
	color[0]=0;
	for(i=0;i<3;i++)
	{
		color[i+1]=BG;
	}
	

	Show_Str(40,5,BLUE,BG,menu,24,0);
	Show_Str(30,25,GREEN,color[0],four_wheel,12,0);
	Show_Str(30,40,GREEN,color[1],four_leg,12,0);
	Show_Str(30,55,GREEN,color[2],settings,12,0);
	Show_Str(30,70,GREEN,color[3],engineer,12,0);
	Show_Str(5,115,GREEN,BG,return_,12,0);
	Show_Str(110,115,GREEN,BG,ok,12,0);
	Gui_Drawbmp16(45,88,gImage_qq);
	
	
	while(1)
	{
					if(up_button==1)
				{
					if(item)
						item--;
					else
						item=3;
					  up_button=2;
				}
				
				if(down_button==1)
				{
					if(item==3)
						item=0;
					else
						item++;	
						down_button=2;				
				}
				
				if(buttonR==1)  //ok
				{
					LCD_Clear(BG);
					buttonR=2;
					return(item);		
				}
				
				if(buttonL==1)  //return
				{
					LCD_Clear(BG);
					buttonL=2;
					return 4;
					
				}
				
				for(i=0;i<4;i++)
				{
					if(i==item)
						color[i]=0;
					else
						color[i]=BG;		
				}
				
	Show_Str(30,25,GREEN,color[0],four_wheel,12,0);
	Show_Str(30,40,GREEN,color[1],four_leg,12,0);
	Show_Str(30,55,GREEN,color[2],settings,12,0);
	Show_Str(30,70,GREEN,color[3],engineer,12,0);
				
		HAL_Delay(50);	
	}

}

uint8_t Horizontal[12]="Horizontal";
uint8_t Forward[12]="Forward";
uint8_t Clockwise[12]="C-Clockwise";
uint8_t Height[10]="Height";
uint8_t quit[28]="double press return to quit";


void wheel_mode()
{
//	LCD_Clear(BG);
	Show_Str(5,25,GREEN,BG,Horizontal,12,0);
	Show_Str(5,48,GREEN,BG,Forward,12,0);
	Show_Str(5,71,GREEN,BG,Clockwise,12,0);
	Show_Str(5,94,GREEN,BG,Height,12,0);
	Show_Str(4,115,BLUE,BG,quit,12,0);
	Show_Str(20,5,BLUE,BG,WHEEL_MODE,24,0);
	remote.status=1;
	
	while(1)
	{
		LCD_ShowNum(70,25,(uint32_t)remote.rocker[0],4,20);
		LCD_ShowNum(70,48,(uint32_t)(4096-remote.rocker[1]),4,20);
		LCD_ShowNum(70,71,(uint32_t)remote.rocker[2],4,20);
		LCD_ShowNum(70,94,(uint32_t)(4096-remote.rocker[3]),4,20);
	
		if(double_press_quit_menu()==1)
			break;
		HAL_Delay(20);
	}
	
}

uint8_t bilibili[15]="Bilibili:";
uint8_t author[15]="JianKe114514";
uint8_t arrow[2]="^";
uint8_t straight[2]="|";
uint8_t zhongwen[25]="Chinese of Swordman";

void Author()
{
	
	Show_Str(4,115,BLUE,BG,quit,12,0);
	Show_Str(5,30,GREEN,BG,bilibili,12,0);
	Show_Str(15,45,BLUE,BG,author,16,0);
	
	Show_Str(25,60,GREEN,BG,arrow,16,0);
	Show_Str(25,65,GREEN,BG,straight,16,0);
	Show_Str(10,80,BLUE,BG,zhongwen,12,0);
	
	while(1)
	{
		if(double_press_quit_menu()==1)
			break;	
		HAL_Delay(20);
	}
}


uint8_t PPP[15]="Wheel_P_Set";
uint8_t III[15]="Wheel_I_Set";
uint8_t Speedset[20]="Speed_ctrl_ratio";



uint8_t Setting_mode()
{

		uint8_t item_set=0;
		static uint8_t i;
		static uint16_t color[4];
		
		for(i=0;i<3;i++)
	 {
			color[i]=BG;
	 }
	 color[0]=0;
	 
		Show_Str(40,5,GREEN,BG,settings,16,0);
		Show_Str(30,40,GREEN,color[0],PPP,12,0);
		Show_Str(30,55,GREEN,color[1],III,12,0);
		Show_Str(30,70,GREEN,color[2],Speedset,12,0);
	 	Show_Str(5,115,GREEN,BG,return_,12,0);
		Show_Str(110,115,GREEN,BG,ok,12,0);
		
		while(1)
		{
				if(up_button==1)
				{
					if(item_set)
						item_set--;
					else
						item_set=3;
					  up_button=2;
				}
				
				if(down_button==1)
				{
					if(item_set==3)
						item_set=0;
					else
						item_set++;	
						down_button=2;				
				}
				
				if(buttonR==1)  //ok
				{
					LCD_Clear(BG);
					buttonR=2;
					return item_set;	
				}
				
				if(buttonL==1)  //return
				{
					LCD_Clear(BG);
					buttonL=2;
					return 4;
					
				}
				
				for(i=0;i<4;i++)
				{
					if(i==item_set)
						color[i]=0;
					else
						color[i]=BG;		
				}
				
		Show_Str(30,40,GREEN,color[0],PPP,12,0);
		Show_Str(30,55,GREEN,color[1],III,12,0);
		Show_Str(30,70,GREEN,color[2],Speedset,12,0);
			
		}
}


uint8_t walk_forward[10]="forward!";
uint8_t walk_backward[10]="backward!";
uint8_t walk_right[15]="turn_right!";
uint8_t walk_left[15]="turn_left!";
uint8_t steady[10]="steady";
uint8_t LEG_MODE[10]="LEG_MODE";

void walk_mode()
{
	
	while(1)
	{
		LCD_Clear(BG);
		Show_Str(20,5,BLUE,BG,LEG_MODE,24,0);
	  Show_Str(4,115,BLUE,BG,quit,12,0);
		
		if(remote.rocker[1]>4000) 
		{
			Show_Str(30,90,GREEN,BG,walk_backward,16,0);
			remote.status=4;
		}
		
		else if(remote.rocker[1]<500)
		{
			Show_Str(30,40,GREEN,BG,walk_forward,16,0);
			remote.status=2;
		}
		else 
		{
			remote.status=3;	
		}
		
		if(remote.rocker[0]>4000)
			Show_Str(3,64,GREEN,BG,walk_left,16,0);
		
		if(remote.rocker[0]<500)
			Show_Str(40,64,GREEN,BG,walk_right,16,0);
		
		if(double_press_quit_menu()==1)
			break;
		
		HAL_Delay(200);
	}
	

}

float ctrl_P=20.0;
float ctrl_I=1.5;
float ctrl_ratio=2.0;

void P_SET() //设置界面下的子菜单
{
	Show_Str(25,5,BLUE,BG,PPP,16,0);
	Show_Str(5,115,GREEN,BG,return_,12,0);
	Show_Str(110,115,GREEN,BG,ok,12,0);
	while(1)
	{
		 if(buttonL==1)
	 {
		 buttonL=2;
		 LCD_Clear(BG);
		 break;
	 }
	 if(up_button==1)
	 {
			up_button=2;
		 if(ctrl_P<30.0) ctrl_P+=0.5;
	 }
	 	if(down_button==1)
	 {
			down_button=2;
		 if(ctrl_P>0.50001) ctrl_P-=0.5;
	 }
	 LCD_ShowfloatNum(40,60,ctrl_P,3,20);
	 HAL_Delay(20);
	}
}

void I_SET()
{
	Show_Str(25,5,BLUE,BG,III,16,0);
	Show_Str(5,115,GREEN,BG,return_,12,0);
	Show_Str(110,115,GREEN,BG,ok,12,0);
	while(1)
	{
		 if(buttonL==1)
	 {
		 buttonL=2;
		 LCD_Clear(BG);
		 break;
	 }
	 if(up_button==1)
	 {
			up_button=2;
		 if(ctrl_I<10.0) ctrl_I+=0.2;
	 }
	 	if(down_button==1)
	 {
			down_button=2;
		 if(ctrl_P>0.200001) ctrl_I-=0.2;
	 }
	 LCD_ShowfloatNum(40,60,ctrl_I,3,20);
	 HAL_Delay(20);
	}

}

void Ratio_set()
{
		Show_Str(15,5,BLUE,BG,Speedset,16,0);
		Show_Str(5,115,GREEN,BG,return_,12,0);
	  Show_Str(110,115,GREEN,BG,ok,12,0);
	while(1)
	{
		 if(buttonL==1)
	 {
		 buttonL=2;
		 LCD_Clear(BG);
		 break;
	 }
	 if(up_button==1)
	 {
			up_button=2;
		 if(ctrl_ratio<3.0) ctrl_ratio+=0.1;
	 }
	 	if(down_button==1)
	 {
			down_button=2;
		 if(ctrl_ratio>0.100001) ctrl_ratio-=0.1;
	 }
	 LCD_ShowfloatNum(40,60,ctrl_ratio,5,20);
	 HAL_Delay(20);
	}

}


