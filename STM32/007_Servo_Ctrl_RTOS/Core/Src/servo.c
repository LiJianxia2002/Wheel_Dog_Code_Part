#include <servo.h>


extern uint8_t servos[14];
uint8_t tmp[12];
uint16_t PWM_value[12];
uint16_t turn=0;

void Servo_data_rec()
{
	int i;
	turn=0; //��turn����λ��0
	
	if(servos[0]==0x30&&servos[13]==0x31)
	{
		for(i=0;i<12;i++)
		{
			if(servos[i+1]!=tmp[i]) 
			{
				tmp[i]=servos[i+1];
				turn|=(1<<i);
			}
		}
 //����׼ȷ������£���������
		
		for(i=0;i<12;i++) //��ӡ���ĵĶ��ֵ
		{
			if(turn&(1<<i))
				printf("servo %u turn to %u\r\n",i+1,tmp[i]);
		}
	}
	else
		printf("data error!\r\n");
}


void Servo_calc()
{
	uint8_t i;
	for(i=0;i<12;i++)
	{
		if(turn&(1<<i)&&tmp[i]<200)
			PWM_value[i]=(uint16_t)(500+11.1*tmp[i]);
	}
	
	TIM2->CCR1=PWM_value[0];
	TIM2->CCR2=PWM_value[1];
	TIM2->CCR3=PWM_value[2];
	TIM2->CCR4=PWM_value[3];
}


void Servo_init()
{
	static uint8_t i;
	
	TIM2->CCR1=1500;
	TIM2->CCR2=1500;
	TIM2->CCR3=1500;
	TIM2->CCR4=1500;
	
	for(i=0;i<12;i++)
	{
		PWM_value[i]=1500;
		tmp[i]=90;
	}
}