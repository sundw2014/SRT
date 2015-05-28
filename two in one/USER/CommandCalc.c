#include "CommandCalc.h"
int myABS(int a)
{
	if(a<0)
		a=-a;
	return a;
}
void CommandCalc(int Thro,int Ptch ,int Roll)
{
	int Pulse;
	
	if(Thro>50)	
			Pulse=ThrottlePulseProp*Thro+ThrottlePulseOffset;
	else
			Pulse=ThrottlePulseOffset;
	TIM_SetCompare1(TIM3,Pulse);
	
	
	
	if(Ptch<0)
		Ptch=0;
	
	Pulse=Flap1PulseOffset+PitchPulseProp*Ptch+RollPulseProp*Roll;		
	if(Pulse>Flap1PulseMAX)
		Pulse=Flap1PulseMAX;
	if(Pulse<0)
		Pulse=0;
	TIM_SetCompare2(TIM3,Pulse);
	
	Pulse=Flap2PulseOffset+PitchPulseProp*Ptch-RollPulseProp*Roll;		
	if(Pulse>Flap1PulseMAX)
		Pulse=Flap1PulseMAX;
	if(Pulse<0)
		Pulse=0;
	TIM_SetCompare3(TIM3,Pulse);
}
