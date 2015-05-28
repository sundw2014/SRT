/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：串口1(USART1)向电脑的超级终端以1s为间隔打印当前ADC1的转换电压值         
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
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


float ThrottlePulseProp;//油门舵量到PWM_PULSE的比例值
float PitchPulseProp;	 //一号副翼舵量到PWM_PULSE的比例值
float RollPulseProp;	 //二号副翼舵量到PWM_PULSE的比例值
u8 status;

// 软件延时
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
	 
	/*检测NRF模块与MCU的连接*/
   	status = NRF_Check(); 

	/*判断连接状态*/  
   if(status == SUCCESS)	   
   		 printf("\r\n successed \r\n");  
   else	  
   	   printf("\r\n failed \r\n");

	 
	 
	 NRF_RX_Mode();
	 
	while(1)
	{
		/*等待接收数据*/
	status = NRF_Rx_Dat(CommandBuf);

	   /*判断接收状态*/
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
