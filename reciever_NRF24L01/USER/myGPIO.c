#include "myGPIO.h"
void GPIO_Config()
{
			GPIO_InitTypeDef GPIO_InitStructure;
	   
	
      /* GPIOA and GPIOB enable */ 
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);  
     
	
      /*GPIOA Configuration: TIM3 channel 1 and 2 and TIM2 channel 1 as alternate function push-pull */ 
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3| GPIO_Pin_6 | GPIO_Pin_7; 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
      GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
      /*GPIOB Configuration: TIM3 channel 3 and 4 as alternate function push-pull */ 
			GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1; 
		  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}
