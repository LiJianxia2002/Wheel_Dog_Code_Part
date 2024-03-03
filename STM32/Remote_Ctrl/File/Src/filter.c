
#include "filter.h"

//互补滤波器
// a = tau / (tau + dt)  
// acc = 加速度传感器数据 
// gyro = 陀螺仪数据 
// dt = 运行周期       
float angle;
float a;

float ComplementaryFilter(float acc, float gyro, float dt) 
{
		a = 0.98;  
		angle = a * (angle + gyro * dt) + (1 - a) * (acc);  
		return angle;  
}
