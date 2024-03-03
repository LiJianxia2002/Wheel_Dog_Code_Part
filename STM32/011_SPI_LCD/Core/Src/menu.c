#include <menu.h>
#include "Pic.h"


extern uint8_t remote[7];

uint8_t string[20]="WoShi_ShuaiGehh";
uint8_t menu[5]="MENU";
uint8_t PID[10]="PID_SET";
uint8_t Color[6]="COLOR";
uint8_t Settings[15]="Settings";
uint8_t Games[15]="Games";
uint8_t Kp[3]="P";
uint8_t Ki[3]="I";
uint8_t Kd[3]="D";

uint16_t count=0;

uint8_t up_button=0;
uint8_t down_button=0;
uint8_t ok_button=0;
uint8_t return_button=0;

uint16_t color[4];


uint8_t item1=0;
uint8_t item2=0;
uint8_t item3=0;

uint8_t menu2=0;
uint8_t menu3=0;

uint8_t i;



uint8_t menu1()
{
	//≥ı ºªØ
	
		color[0]=0;
	  for(i=0;i<3;i++)
		{
			color[i+1]=BG;
		}
		
	  Show_Str(50,10,BLUE,BG,menu,16,0);
		Show_Str(45,40,GREEN,color[0],PID,12,0);
		Show_Str(45,55,GREEN,color[1],Color,12,0);
		Show_Str(45,70,GREEN,color[2],Settings,12,0);
		Show_Str(45,85,GREEN,color[3],Games,12,0);
		Gui_Drawbmp16(45,105,gImage_qq);
	
		while(1)
		{
				if(up_button)
				{
					if(item1)
						item1--;
					else
						item1=3;
					up_button=0;
				}
				
				if(down_button)
				{
					if(item1==3)
						item1=0;
					else
						item1++;	
					down_button=0;				
				}
				
				if(ok_button)
				{
					ok_button=0;
					LCD_Clear(LIGHTBLUE);
					return(item1);		
				}
				if(return_button)
				{
					return_button=0;		
				}
				
				for(i=0;i<4;i++)
				{
					if(i==item1)
						color[i]=0;
					else
						color[i]=BG;		
				}
				
		Show_Str(45,40,GREEN,color[0],PID,12,0);
		Show_Str(45,55,GREEN,color[1],Color,12,0);
		Show_Str(45,70,GREEN,color[2],Settings,12,0);
		Show_Str(45,85,GREEN,color[3],Games,12,0);			
		}
}


uint8_t menu_PID()
{
	color[0]=0;
	color[1]=BG;
	color[2]=BG;
	
	Show_Str(30,10,BLUE,BG,PID,16,0);
	Show_Str(45,55,GREEN,color[0],Kp,12,0);
	Show_Str(45,70,GREEN,color[1],Ki,12,0);
	Show_Str(45,85,GREEN,color[2],Kd,12,0);
	Gui_Drawbmp16(45,105,gImage_qq);
	
	while(1)
	{
				if(up_button)
				{
					if(item2)
						item2--;
					else
						item2=2;
					up_button=0;
				}
				
				if(down_button)
				{
					if(item2==2)
						item2=0;
					else
						item2++;	
					down_button=0;				
				}
				
				if(ok_button)
				{
					ok_button=0;
					LCD_Clear(LIGHTBLUE);
					return(item2);		
				}
				if(return_button)
				{
					return_button=0;
					LCD_Clear(LIGHTBLUE);
					return 10;
				}
			for(i=0;i<3;i++)
			{
				if(i==item2)
					color[i]=0;
				else
					color[i]=BG;	
			}
	Show_Str(45,55,GREEN,color[0],Kp,12,0);
	Show_Str(45,70,GREEN,color[1],Ki,12,0);
	Show_Str(45,85,GREEN,color[2],Kd,12,0);
	 
	 HAL_Delay(1);
	}

}

uint8_t menu_Settings()
{
	Show_Str(30,10,BLUE,BG,Settings,20,0);
	
	while(1)
	{
	 if(return_button)
	 {
		 return_button=0;
		 LCD_Clear(LIGHTBLUE);
		 return 0;
	 }
	 HAL_Delay(1);
	}
}


uint8_t PPP()
{
	Show_Str(50,10,BLUE,BG,Kp,20,0);
	static uint8_t kp;
	while(1)
	{
	 if(return_button)
	 {
		 return_button=0;
		 LCD_Clear(LIGHTBLUE);
		 return 0;
	 }
	 if(up_button)
	 {
			up_button=0;
		 if(kp<250) kp+=10;
	 }
	 	if(down_button)
	 {
			down_button=0;
		 if(kp>0) kp-=10;
	 }
	 
	 LCD_ShowNum(40,80,kp,3,20);
	 
	 HAL_Delay(1);
	}

}

uint8_t III()
{
	Show_Str(50,10,BLUE,BG,Ki,20,0);
	
	while(1)
	{
	 if(return_button)
	 {
		 return_button=0;
		 LCD_Clear(LIGHTBLUE);
		 return 0;
	 }
	 HAL_Delay(1);
	}

}

uint8_t DDD()
{
	Show_Str(50,10,BLUE,BG,Kd,20,0);
	
	while(1)
	{
	 if(return_button)
	 {
		 return_button=0;
		 LCD_Clear(LIGHTBLUE);
		 return 0;
	 }
	 HAL_Delay(1);
	}

}

void remote_ctrl()
{
	if(remote[0]==0xA5)
	{
		if(remote[1]==10)  up_button=1;
		else if(remote[2]==20) down_button=1;
		else if(remote[3]==30) ok_button=1;
		else if(remote[4]==40) return_button=1;
		
		memset(remote,0x00,7);
	}
	
	
	HAL_UART_Receive_IT(&huart1,remote,7);

}




