/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ������1(USART1)����Եĳ����ն���1sΪ�����ӡ��ǰADC1��ת����ѹֵ         
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "usart1.h"
#include "filter.h"
#include "adc.h"
#include "timer.h"
#include "CommandCalc.h"
#include "myGPIO.h"
#include "SPI_NRF.h"

extern char SendFlag;


float ThrottlePulseProp;//���Ŷ�����PWM_PULSE�ı���ֵ
float PitchPulseProp;	 //һ�Ÿ��������PWM_PULSE�ı���ֵ
float RollPulseProp;	 //���Ÿ��������PWM_PULSE�ı���ֵ
u8 status;

// �����ʱ
void Delay(__IO uint32_t nCount);

/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */

int main(void)
{	
	int ThroPulse=0,Flap1Pulse=0,Flap2Pulse=0;
	
	GPIO_Config();
	
	/*NRF24L01 Init*/
	SPI_NRF_Init();
	/* USART1 config */
	USART1_Config();
	/* TIM3 config */
  TIM3_Config();
	 
	/*���NRFģ����MCU������*/
   	status = NRF_Check(); 

	/*�ж�����״̬*/  
   if(status == SUCCESS)	   
   		 printf("\r\n successed \r\n");  
   else	  
   	   printf("\r\n failed \r\n");

	 
	 
	 NRF_RX_Mode();
	 
	while(1)
	{
		/*�ȴ���������*/
	status = NRF_Rx_Dat(CommandBuf);

	   /*�жϽ���״̬*/
	if(status == RX_DR)
	{
		sscanf(CommandBuf,"com%d,,,%d,,,%dend",&ThroPulse,&Flap1Pulse,&Flap2Pulse);
		TIM_SetCompare1(TIM3,ThroPulse);
		TIM_SetCompare2(TIM3,Flap1Pulse);
		TIM_SetCompare3(TIM3,Flap2Pulse);
//		printf("%s\r\n");
//		printf("%d|%d|%d\r\n",ThroPulse,Flap1Pulse,Flap2Pulse);
	} 
	else
	{
		TIM_SetCompare1(TIM3,ThrottlePulseOffset);
		TIM_SetCompare2(TIM3,Flap1PulseOffset);
		TIM_SetCompare3(TIM3,Flap2PulseOffset);
	} 
	}
		
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
