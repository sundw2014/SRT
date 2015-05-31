#include "stm32f10x_it.h"
#include "usart1.h"
#include "filter.h"
#include "CommandCalc.h"
char SendFlag=0;
void DMA1_Channel1_IRQHandler(void) 

{
	
  if(DMA_GetITStatus(DMA1_IT_TC1) != RESET) 

   {  
		  ADC_SoftwareStartConvCmd(ADC1, DISABLE);
	    filter();  
	    //printf("DMA");
			
//     DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, DISABLE);
//		 for(x=0;x<2;x++)
//			{
//		    for(y=0;y<32;y++)
//					printf("%d,,,",ADC_ConvertedValue[y][x]);
//				printf("----------------------------------------------------\n"); 
//			}
//		 DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);					
	}
	 DMA_ClearITPendingBit(DMA1_IT_TC1);
}


void TIM1_UP_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM1,TIM_FLAG_Update) != RESET) 
	{
		TIM_SetCompare1(TIM3,ThrottlePulseOffset);
		TIM_SetCompare2(TIM3,Flap1PulseOffset);
		TIM_SetCompare3(TIM3,Flap2PulseOffset);
		
		TIM_SetCompare4(TIM2,10000);
		/*disable	TIM1_IT*/
		TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
	}
	
	TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
}
