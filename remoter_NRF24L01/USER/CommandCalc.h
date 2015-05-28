#ifndef _COMMANDCALC_H
#define _COMMANDCALC_H

#include "math.h"
#include "usart1.h"
#include "stm32f10x_tim.h"
#define PI 3.1415927
#define ThrottlePulseMAX 2000
#define Flap1PulseMAX 2000
#define Flap2PulseMAX 2000
#define ThrottlePulseOffset 1000
#define Flap1PulseOffset 1000
#define Flap2PulseOffset 1000

extern float ThrottlePulseProp;//油门舵量到PWM_PULSE的比例值
extern float PitchPulseProp;	 //一号副翼舵量到PWM_PULSE的比例值
extern float RollPulseProp;	 //二号副翼舵量到PWM_PULSE的比例值
extern unsigned char CommandBuf[24];

void CommandCalc(int Thro,int Ptch,int Roll);

#endif
