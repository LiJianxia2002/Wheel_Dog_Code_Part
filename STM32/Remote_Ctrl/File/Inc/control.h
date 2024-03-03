
#ifndef __CONTROL_H
#define __CONTROL_H

#include "filter.h"

extern unsigned char g_ucMainEventCount;
extern float g_fCarAngle;

void GetMpuData(void);
void AngleCalculate(void);

#endif 
