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

float ComValue_Prop;//�������ٶȵı���ֵ

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */

int main(void)
{	
	int x_m,y_m;        //�е�ֵ
	int x_max=4000,x_min=100,y_max=4000,y_min=100;   //����ֵ�г�
	
	int x_ComValue=0,y_ComValue=0;
	
	/* enable adc1 and config adc1 to dma mode */
	ADC1_Init();
	GPIO_Config();
	Delay(0xfffff);//�ȴ�У׼
	
	/*ҡ��У׼*/ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(!FilterFlag);
	x_m=After_filter[0];
	y_m=After_filter[1];
	ComValue_Prop=4*(float)(CAR_SpeedMAX)/(x_max-x_min+y_max-y_min);
	
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
			x_ComValue=After_filter[0]-x_m;
			y_ComValue=After_filter[1]-y_m;
			CommandCalc(x_ComValue,y_ComValue);
			//printf("%d,%d\r\n",After_filter[0],After_filter[1]);
		}
	}
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
