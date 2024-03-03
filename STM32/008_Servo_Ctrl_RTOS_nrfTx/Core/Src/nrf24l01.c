#include "nrf24L01.h"
#include "spi.h"
#include "main.h"
#include "usart.h"

const uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ
const uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���յ�ַ
 
 
//���NRF24L01�޸�SPI1����
void NRF24L01_SPI_Init(void)
{
    __HAL_SPI_DISABLE(&hspi2);               //�ȹر�SPI1
    hspi2.Init.CLKPolarity=SPI_POLARITY_LOW; //����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
    hspi2.Init.CLKPhase=SPI_PHASE_1EDGE;     //����ͬ��ʱ�ӵĵ�1�������أ��������½������ݱ�����
    HAL_SPI_Init(&hspi2);
    __HAL_SPI_ENABLE(&hspi2);                //ʹ��SPI1
}
 
//��ʼ��24L01��IO��
void NRF24L01_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��

	
	//GPIOA.4��������
		GPIO_Initure.Pin=GPIO_PIN_12;							//PA4
		GPIO_Initure.Mode=GPIO_MODE_INPUT;      	//����
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);     	//��ʼ��
			
//		MX_SPI1_Init();    		              			//��ʼ��SPI1
		NRF24L01_SPI_Init();                			//���NRF���ص��޸�SPI������
		NRF24L01_CE_LOW(); 			            			//ʹ��24L01
		NRF24L01_SPI_CS_DISABLE();			    			//SPIƬѡȡ��	 	

		printf("����һ��NRF24L01 2.4G�������ݴ���ģ�����ʵ��\r\n"); 
	
	
	
		while(NRF24L01_Check())
		{
			printf("Ӳ����Ѱ����NRF24L01����ģ��\r\n"); 
			HAL_Delay(1000);
		}
	
		printf("NRF24L01����ģ��Ӳ����������\r\n");	
}
 
/**
	*SPI�ٶ����ú���
  *SPI�ٶ�=fAPB1/��Ƶϵ��
  *@ref SPI_BaudRate_Prescaler:SPI_BAUDRATEPRESCALER_2~SPI_BAUDRATEPRESCALER_2 256
	*fAPB1ʱ��һ��Ϊ42Mhz��
	*/
static void SPI1_SetSpeed(uint8_t SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
    __HAL_SPI_DISABLE(&hspi2);            //�ر�SPI
    hspi2.Instance->CR1&=0XFFC7;          //λ3-5���㣬�������ò�����
    hspi2.Instance->CR1|=SPI_BaudRatePrescaler;//����SPI�ٶ�
    __HAL_SPI_ENABLE(&hspi2);             //ʹ��SPI
}
 
/**
  * ��������: ������Flash��ȡд��һ���ֽ����ݲ�����һ���ֽ�����
  * �������: byte������������
  * �� �� ֵ: uint8_t�����յ�������
  * ˵    ������
  */
uint8_t SPIx_ReadWriteByte(SPI_HandleTypeDef* hspi,uint8_t byte)
{
  uint8_t d_read,d_send=byte;
  if(HAL_SPI_TransmitReceive(hspi,&d_send,&d_read,1,0xFF)!=HAL_OK)
  {
    d_read=0xFF;
  }
  return d_read; 
}
 
/**
  * ��������: ���24L01�Ƿ����
  * �������: ��
  * �� �� ֵ: 0���ɹ�;1��ʧ��
  * ˵    ������          
  */ 
uint8_t NRF24L01_Check(void)
{
	uint8_t buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uint8_t i;
  
	SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_4); //spi�ٶ�Ϊ8.0Mhz����24L01�����SPIʱ��Ϊ10Mhz,�����һ��û��ϵ��  
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//д��5���ֽڵĵ�ַ.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //����д��ĵ�ַ  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//���24L01����	
	return 0;		 	//��⵽24L01
}	
 
/**
  * ��������: SPIд�Ĵ���
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ����reg:ָ���Ĵ�����ַ
  *           
  */ 
uint8_t NRF24L01_Write_Reg(uint8_t reg,uint8_t value)
{
	uint8_t status;	
  NRF24L01_SPI_CS_ENABLE();                 //ʹ��SPI����
  status =SPIx_ReadWriteByte(&hspi2,reg);   //���ͼĴ����� 
  SPIx_ReadWriteByte(&hspi2,value);         //д��Ĵ�����ֵ
  NRF24L01_SPI_CS_DISABLE();                //��ֹSPI����	   
  return(status);       			//����״ֵ̬
}
 
/**
  * ��������: ��ȡSPI�Ĵ���ֵ
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ����reg:Ҫ���ļĴ���
  *           
  */ 
uint8_t NRF24L01_Read_Reg(uint8_t reg)
{
	uint8_t reg_val;	    
 	NRF24L01_SPI_CS_ENABLE();          //ʹ��SPI����		
  SPIx_ReadWriteByte(&hspi2,reg);   //���ͼĴ�����
  reg_val=SPIx_ReadWriteByte(&hspi2,0XFF);//��ȡ�Ĵ�������
  NRF24L01_SPI_CS_DISABLE();          //��ֹSPI����		    
  return(reg_val);           //����״ֵ̬
}		
 
/**
  * ��������: ��ָ��λ�ö���ָ�����ȵ�����
  * �������: ��
  * �� �� ֵ: �˴ζ�����״̬�Ĵ���ֵ 
  * ˵    ������
  *           
  */ 
uint8_t NRF24L01_Read_Buf(uint8_t reg,uint8_t *pBuf,uint8_t len)
{
	uint8_t status,uint8_t_ctr;	   
  
  NRF24L01_SPI_CS_ENABLE();           //ʹ��SPI����
  status=SPIx_ReadWriteByte(&hspi2,reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
 	for(uint8_t_ctr=0;uint8_t_ctr<len;uint8_t_ctr++)
  {
    pBuf[uint8_t_ctr]=SPIx_ReadWriteByte(&hspi2,0XFF);//��������
  }
  NRF24L01_SPI_CS_DISABLE();       //�ر�SPI����
  return status;        //���ض�����״ֵ̬
}
 
/**
  * ��������: ��ָ��λ��дָ�����ȵ�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ����reg:�Ĵ���(λ��)  *pBuf:����ָ��  len:���ݳ���
  *           
  */ 
uint8_t NRF24L01_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
	uint8_t status,uint8_t_ctr;	    
 	NRF24L01_SPI_CS_ENABLE();          //ʹ��SPI����
  status = SPIx_ReadWriteByte(&hspi2,reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
  for(uint8_t_ctr=0; uint8_t_ctr<len; uint8_t_ctr++)
  {
    SPIx_ReadWriteByte(&hspi2,*pBuf++); //д������	 
  }
  NRF24L01_SPI_CS_DISABLE();       //�ر�SPI����
  return status;          //���ض�����״ֵ̬
}		
 
/**
  * ��������: ����NRF24L01����һ������
  * �������: ��
  * �� �� ֵ: �������״��
  * ˵    ����txbuf:�����������׵�ַ
  *           
  */ 
uint8_t NRF24L01_TxPacket(uint8_t *txbuf)
{
	uint8_t sta;
	SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_8); //spi�ٶ�Ϊ4.0Mhz��24L01�����SPIʱ��Ϊ10Mhz�� 
	NRF24L01_CE_LOW();
  NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д���ݵ�TX BUF  32���ֽ�
 	NRF24L01_CE_HIGH();//��������	 
  
	while(NRF24L01_IRQ_PIN_READ()!=0);//�ȴ��������
  
	sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ	   
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	if(sta&MAX_TX)//�ﵽ����ط�����
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//���TX FIFO�Ĵ��� 
		return MAX_TX; 
	}
	if(sta&TX_OK)//�������
	{
		return TX_OK;
	}
	return 0xff;//����ԭ����ʧ��
}
 
/**
  * ��������:����NRF24L01����һ������
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  *           
  */ 
uint8_t NRF24L01_RxPacket(uint8_t *rxbuf)
{
	uint8_t sta;		
  SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_8); //spi�ٶ�Ϊ4.0Mhz��24L01�����SPIʱ��Ϊ10Mhz�� 
	sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ    	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	if(sta&RX_OK)//���յ�����
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//���RX FIFO�Ĵ��� 
		return 0; 
	}	   
	return 1;//û�յ��κ�����
}			
 
/**
  * ��������: �ú�����ʼ��NRF24L01��RXģʽ
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  *           
  */ 
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE_LOW();	  
  NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0F);//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC 
  NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
  NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ  	 
  NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	     //����RFͨ��Ƶ��		  
  NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);//����TX�������,0db����,2Mbps,���������濪��   
  
  NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ�� 	    
    
  NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
	
  NRF24L01_CE_HIGH(); //CEΪ��,�������ģʽ 
  HAL_Delay(1);
}	
 
/**
  * ��������: �ú�����ʼ��NRF24L01��TXģʽ
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  *           
  */ 
void NRF24L01_TX_Mode(void)
{														 
	NRF24L01_CE_LOW();	    
  NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(uint8_t*)TX_ADDRESS,TX_ADR_WIDTH);//дTX�ڵ��ַ 
  NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  
 
  NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
  NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
  NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0xff);//�����Զ��ط����ʱ��:4000us + 86us;����Զ��ط�����:15��
  NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //����RFͨ��Ϊ40
  NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
  NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	NRF24L01_CE_HIGH();//CEΪ��,10us����������
  HAL_Delay(1);
}
 
/**
  * ��������: �ú���NRF24L01����͹���ģʽ
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  *           
  */
void NRF_LowPower_Mode(void)
{
	NRF24L01_CE_LOW();	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x00);		//���ù���ģʽ:����ģʽ
}