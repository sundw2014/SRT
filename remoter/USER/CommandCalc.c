#include "CommandCalc.h"
int myABS(int a)
{
	if(a<0)
		a=-a;
	return a;
}
void CommandCalc(int x,int y)
{
		float Angle;
		int Speed;
		char rot='N';
	if((myABS(x)>50)||(myABS(y)>50))
	{
		
		if(x>0)
		{
			if(y<0)
				Angle=atan((float)y/x)+2*PI;
			else
					Angle=atan((float)y/x);
		}
		else if(x<0)
			Angle=atan((float)y/x)+PI;
		else if(y>0)
			Angle=PI/2;
		else if(y<0)
			Angle=3*PI/2;
		else
			Angle=0;
		Speed=(int)(sqrt(x*x+y*y)*ComValue_Prop);
		if(Speed>CAR_SpeedMAX)
			Speed=CAR_SpeedMAX;
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5))
			rot='A';
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6))
			rot='C';
		Angle=180*(Angle/PI);
		//printf("xComvalue=%d,y=%d\r\n",x,y);
		printf("com%c,,,%d,,,%fend\r\n",rot,Speed,Angle);
		//printf("+++++++++++++++++++++++\r\n");
	}
	else
	{
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5))
			rot='A';
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6))
			rot='C';
		printf("com%c,,,%d,,,%fend\r\n",rot,0,0.0);
	}
}
