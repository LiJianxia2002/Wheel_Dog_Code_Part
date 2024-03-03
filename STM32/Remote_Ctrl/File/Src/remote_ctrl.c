#include "remote_ctrl.h"
#include "tim.h"

remote_t remote;




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

uint16_t ADC_Read(uint32_t Channel)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = Channel;                                         /* 通道 */
	sConfig.Rank = ADC_REGULAR_RANK_1;                              
	sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;                  /* 采样时间 */
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)             
	{
		Error_Handler();
	}
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	return (uint16_t)HAL_ADC_GetValue(&hadc1);
}



uint8_t tmp_buf[33];  //nrf发送缓冲区


void remote_ctrl_()
{
		static uint8_t i;
		
		remote.rocker[0]=ADC_Read(ADC_CHANNEL_0);
		remote.rocker[1]=ADC_Read(ADC_CHANNEL_1);
		remote.rocker[2]=ADC_Read(ADC_CHANNEL_4);
		remote.rocker[3]=ADC_Read(ADC_CHANNEL_6);
	
		button_check();
		
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1) remote.button[0]=1;
			else remote.button[0]=0;
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1) remote.button[1]=1;
			else remote.button[1]=0;
	
//		remote.data[0]=ctrl_I;
//		remote.data[1]=ctrl_P;
//		remote.data[2]=ctrl_ratio;
	
		remote.checksum=0x51;
		memcpy(tmp_buf,&remote,sizeof(remote));
		
		
	 NRF24L01_TxPacket(tmp_buf);

}

uint8_t buttonL=0;
uint8_t buttonR=0;
uint8_t up_button=0;
uint8_t down_button=0;

void button_check()
{
	
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)&&buttonL==0) buttonL=1;
			else if(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)&&buttonL==2) buttonL=0;
	
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)&&buttonR==0) buttonR=1;
			else if(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)&&buttonR==2) buttonR=0;	
		
		if(remote.rocker[1]>4000&&down_button==0) down_button=1;
			else if(remote.rocker[1]<2500&&down_button==2) down_button=0; 
			
		if(remote.rocker[1]<1000&&up_button==0) up_button=1;
			else if(remote.rocker[1]>1500&&up_button==2) up_button=0; 
}
