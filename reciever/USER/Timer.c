#include "timer.h"
#include "misc.h"
void TIM1_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);          
  TIM_TimeBaseStructure.TIM_Prescaler = (7200-1);                 //10KHZ                        
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    
  TIM_TimeBaseStructure.TIM_Period = 1000;                        //0.1s interrupt            
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;                                       
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure); 
	
	
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM1, ENABLE);	
}
void TIM3_Config(void)  
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  
   
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  
	
    /* Time base configuration */   
		TIM_TimeBaseStructure.TIM_Prescaler = (72-1);  
    TIM_TimeBaseStructure.TIM_Period =(20000-1);  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                                //????????:???  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                 //????????  
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  
	
    /* PWM1 Mode configuration: Channel1 */  
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           //???PWM??1  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
    TIM_OCInitStructure.TIM_Pulse = 0;                                       //?????,???????????,??????  
    TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;                    //?????????CCR1?????  
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);                                    //????1      
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	
    /* PWM1 Mode configuration: Channel2 */  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
    TIM_OCInitStructure.TIM_Pulse =0;                                       //????2??????,??????????PWM  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                    //?????????CCR2????? 
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);                                    //????2  
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  
		
		/* PWM1 Mode configuration: Channel3 */  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
    TIM_OCInitStructure.TIM_Pulse =0;                                       //????2??????,??????????PWM  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                    //?????????CCR2????? 
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);                                    //????2  
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  
		
    TIM_ARRPreloadConfig(TIM3, ENABLE);                                         //??TIM3?????ARR  
    /* TIM3 enable counter */  
    TIM_Cmd(TIM3, ENABLE);                                                      //??TIM3   
} 
