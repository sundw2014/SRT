#include "stm32f10x_it.h"
#include "usart1.h"
#include "filter.h"
char USARTFlag=0;
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
		//printf("into TIM1_interript\n");
		USARTFlag=1;
	}
	
	TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
}