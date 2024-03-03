
#include "control.h"
#include "filter.h"
#include "mpu6050.h"
#include "math.h"

short x_nAcc,y_nAcc,z_nAcc;//���ٶ�x�ᡢy�ᡢz���ʼ����
short x_nGyro,y_nGyro,z_nGyro;//������x�ᡢy�ᡢz���ʼ����
float x_fAcc,y_fAcc,z_fAcc;

float g_fAccAngle_pitch;//���ٶȴ���������atan2()����õ��ĽǶ�
float g_fGyroAngleSpeed_pitch;//�����ǽ��ٶ�
float g_fCarAngle_pitch;//С�����

float g_fAccAngle_yaw;//���ٶȴ���������atan2()����õ��ĽǶ�
float g_fGyroAngleSpeed_yaw;//�����ǽ��ٶ�
float g_fCarAngle_yaw;//С�����

float g_fAccAngle_roll;//���ٶȴ���������atan2()����õ��ĽǶ�
float g_fGyroAngleSpeed_roll;//�����ǽ��ٶ�
float g_fCarAngle_roll;//С�����

float dt = 0.005;//�����˲�����������

unsigned char g_ucMainEventCount;//���¼��������������ж���

void GetMpuData(void)
{
	MPU_Get_Accelerometer(&x_nAcc,&y_nAcc,&z_nAcc);//��ȡMPU6050���ٶ�����
	MPU_Get_Gyroscope(&x_nGyro,&y_nGyro,&z_nGyro); //��ȡMPU6050����������
}

void AngleCalculate(void)
{
	//-------���ٶ����ݴ���--------------------------
	//����Ϊ��2gʱ�������ȣ�16384 LSB/g
	x_fAcc = x_nAcc / 16384.0;
	y_fAcc = y_nAcc / 16384.0;
  z_fAcc = z_nAcc / 16384.0;
	
  g_fAccAngle_pitch = atan2(y_fAcc,z_fAcc) * 180.0 / 3.14;

  g_fAccAngle_roll = atan2(x_fAcc,z_fAcc) * 180.0 / 3.14;
	//-------���������ݴ���-------------------------
	//��ΧΪ2000deg/sʱ�������ϵ��16.4 LSB/(deg/s)
  g_fGyroAngleSpeed_pitch = x_nGyro / 16.4;  //������ٶ�ֵ			 
  g_fGyroAngleSpeed_yaw = z_nGyro / 16.4;  //������ٶ�ֵ		
	g_fGyroAngleSpeed_roll = y_nGyro / 16.4;  //������ٶ�ֵ		
	
	//-------�����˲�---------------
  g_fCarAngle_pitch = ComplementaryFilter(g_fAccAngle_pitch, g_fGyroAngleSpeed_pitch, dt);
  
	if(!(z_nGyro<200&&z_nGyro>-200)){
	      
		g_fCarAngle_yaw += g_fGyroAngleSpeed_yaw*0.005;
}
		
   if(g_fCarAngle_yaw>=180) g_fCarAngle_yaw-=360.0;
   else if(g_fCarAngle_yaw<=-180) g_fCarAngle_yaw+=360.0;
  
  g_fCarAngle_roll = ComplementaryFilter(g_fAccAngle_roll, g_fGyroAngleSpeed_roll, dt);
}
