#ifndef _COMMANDCALC_H
#define _COMMANDCALC_H

#include "math.h"
#include "usart1.h"
#define PI 3.1415927
#define CAR_SpeedMAX 140
extern float ComValue_Prop;//舵量到速度的比例值
void CommandCalc(int x,int y);

#endif
