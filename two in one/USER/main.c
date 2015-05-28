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

float ThrottlePulseProp;//���Ŷ�����PWM_PULSE�ı���ֵ
float PitchPulseProp;	 //һ�Ÿ��������PWM_PULSE�ı���ֵ
float RollPulseProp;	 //���Ÿ��������PWM_PULSE�ı���ֵ

// �����ʱ
void Delay(__IO uint32_t nCount);

/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */

int main(void)
{	
	int Throttle_m,Pitch_m, Roll_m;        //�е�ֵ
	int Throttle_MAX=4000,Pitch_MAX=4000,Roll_MIN=100,Roll_MAX=4000;  //����ֵ�г�
	
	int Throttle_ActValue=0,Pitch_ActValue=0,Roll_ActValue=0;;			//������е�ֵ�Ķ�����
	
	/* enable adc1 and config adc1 to dma mode */
	ADC1_Init();
	GPIO_Config();
	Delay(0xfffff);//�ȴ�У׼
	
	/*ҡ��У׼*/ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(!FilterFlag);
	Throttle_m=After_filter[0];
	Pitch_m=After_filter[1];
	Roll_m=After_filter[2];
	ThrottlePulseProp=(float)(ThrottlePulseMAX-ThrottlePulseOffset)/(Throttle_MAX-Throttle_m);
	PitchPulseProp=(float)(Flap1PulseMAX-Flap1PulseOffset+Flap2PulseMAX-Flap2PulseOffset)/(2*(Pitch_MAX-Pitch_m));
	RollPulseProp=(float)(Flap1PulseMAX-Flap1PulseOffset+Flap2PulseMAX-Flap2PulseOffset)/(Roll_MAX-Roll_MIN);
	
	/*NRF24L01 Init*/
	SPI_NRF_Init();
	/* USART1 config */
	USART1_Config();
	/* TIM1 config */
	TIM1_Config();
	//printf("x_m=%d,y_m=%d,COMValue_Prop=%f\r\n",x_m,y_m,ComValue_Prop);
	while(1)
	{
		//printf("main+++");
		if (!USARTFlag)
				continue;
		USARTFlag=0;
		if(FilterFlag)
		{
			FilterFlag=0;
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);
			
			Throttle_ActValue=After_filter[0]-Throttle_m;
			Pitch_ActValue=After_filter[1]-Pitch_m;
			Roll_ActValue=After_filter[2]-Roll_m;
			
			CommandCalc(Throttle_ActValue,Pitch_ActValue,Roll_ActValue);
			//printf("%d,%d\r\n",After_filter[0],After_filter[1]);
		}
	}
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
