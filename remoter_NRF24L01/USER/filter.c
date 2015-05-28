#include "stm32f10x.h"
#define N 32
int After_filter[3];
char FilterFlag=0;
extern vu16 ADC_ConvertedValue[32][3];

void filter(void) 
{ 
	vu32 sum= 0; int count,i; 
	for(i=0;i<3;i++) 
	{
		for ( count=0;count<N;count++) 
		{
			sum += ADC_ConvertedValue[count][i]; 
		}
	After_filter[i]=sum>>5; 
	sum=0;
	}	
  FilterFlag=1;	
}
