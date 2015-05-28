#include "CommandCalc.h"
int myABS(int a)
{
	if(a<0)
		a=-a;
	return a;
}

unsigned char CommandBuf[27];
void CommandCalc(int Thro,int Ptch ,int Roll)
{
	int Pulse;
	
	if(Thro>50)	
			Pulse=ThrottlePulseProp*Thro+ThrottlePulseOffset;
	else
			Pulse=ThrottlePulseOffset;
	sprintf(CommandBuf,"com%4d,,,",Pulse);
	
	
	 
	if(Ptch<0)
		Ptch=0;
	
	Pulse=Flap1PulseOffset+PitchPulseProp*Ptch+RollPulseProp*Roll;		
	if(Pulse>Flap1PulseMAX)
		Pulse=Flap1PulseMAX;
	if(Pulse<0)
		Pulse=0;
	sprintf((CommandBuf+10),"%4d,,,",Pulse);
	
	Pulse=Flap2PulseOffset+PitchPulseProp*Ptch-RollPulseProp*Roll;		
	if(Pulse>Flap1PulseMAX)
		Pulse=Flap1PulseMAX;
	if(Pulse<0)
		Pulse=0;
	sprintf((CommandBuf+17),"%4dend",Pulse);
}
