#include "walk.h"
#include "math.h"
#include "main.h"
#include "servo_ctrl.h"

#define LEG 61.74
#define LL  80.0   //大小腿长度
#define Ts  1 //时间周期
#define fai 0.5  //占空比

#define xs  -80.0
#define xf  -10.0
#define xf2 -xs
#define xs2 -xf //x位置的start和final，由于前腿和后退运动轨迹为镜像，因此为相反数

#define height  40.0    //抬腿高度
#define zs  -115.0	//地面到机体距离

#define pi 3.1416


float z_exp[4];
float x_exp[4];


float LEG_degree[4];
float LOWER_LEG_degree[4];
float tmod=0.0;


 
float abs_float(float num)
{
	if(num<-0.00001)
		num=-num;
	return num;
}

void walk_speed_set(float step)
{
		tmod+=step;
		if(tmod>=1.0) tmod=0.0;
		else if(tmod<=-0.0001) tmod=1.0;
}

void Servo_Degree_calc_walk()
{

		static float sigma;
		static float phai[4];
		static float sita_LL[4];
		static float sita_L[4];	
	
	
		if(tmod<0.5&&tmod>=0)  //0,2抬腿相;1,3支撑相
		{
			sigma=2*pi*tmod/fai/Ts;
			z_exp[0]=height*(1-cos(sigma))/2+zs;
			z_exp[1]=zs;
			z_exp[2]=z_exp[0];
			z_exp[3]=zs;
			
			x_exp[0]=(xf-xs)*(sigma-sin(sigma))/(2*pi)+xs;
			x_exp[1]=(xs-xf)*(sigma-sin(sigma))/(2*pi)+xf;
			x_exp[2]=(xf2-xs2)*(sigma-sin(sigma))/(2*pi)+xs2;
			x_exp[3]=(xs2-xf2)*(sigma-sin(sigma))/(2*pi)+xf2;
		}
		else if(tmod>0.5&&tmod<1)	//相反
		{
			sigma=2*pi*(tmod-(Ts*fai))/fai/Ts;
      z_exp[0]=zs;
			z_exp[1]=height*(1-cos(sigma))/2+zs;
			z_exp[2]=zs;
			z_exp[3]=z_exp[1];
			
      x_exp[0]=(xs-xf)*(sigma-sin(sigma))/(2*pi)+xf;
			x_exp[1]=(xf-xs)*(sigma-sin(sigma))/(2*pi)+xs;
      x_exp[2]=(xs2-xf2)*(sigma-sin(sigma))/(2*pi)+xf2;
			x_exp[3]=(xf2-xs2)*(sigma-sin(sigma))/(2*pi)+xs2;
		}

    //腿1的算法
		phai[0]= acos((x_exp[0]*x_exp[0] + z_exp[0]*z_exp[0] + LEG*LEG - LL*LL) /(2 *LEG*sqrt(x_exp[0]*x_exp[0] + z_exp[0]*z_exp[0])));
		sita_LL[0] = 2*pi - acos((x_exp[0]*x_exp[0] + z_exp[0]*z_exp[0] - LEG*LEG - LL*LL) / (2 * LEG * LL));
		
		sita_L[0]=pi-abs_float(atan(z_exp[0]/x_exp[0]))-phai[0];
		
		LEG_degree[0]=sita_L[0]*57.29;
		LOWER_LEG_degree[0]=360-sita_LL[0]*57.29;		
		
		//腿0的算法
		phai[1]= acos((x_exp[1]*x_exp[1] + z_exp[1]*z_exp[1] + LEG*LEG - LL*LL) /(2 *LEG*sqrt(x_exp[1]*x_exp[1] + z_exp[1]*z_exp[1])));
		sita_LL[1] = 2*pi - acos((x_exp[1]*x_exp[1] + z_exp[1]*z_exp[1] - LEG*LEG - LL*LL) / (2 * LEG * LL));
		
		sita_L[1]=pi-abs_float(atan(z_exp[1]/x_exp[1]))-phai[1];
		
		LEG_degree[1]=180-sita_L[1]*57.29;
		LOWER_LEG_degree[1]=sita_LL[1]*57.29-180;	
		
		
		//接下来是前腿,唯一区别是
		//腿2算法
		phai[2]= acos((x_exp[2]*x_exp[2] + z_exp[2]*z_exp[2] + LEG*LEG - LL*LL) /(2 *LEG*sqrt(x_exp[2]*x_exp[2] + z_exp[2]*z_exp[2])));
		sita_LL[2] = 2*pi - acos((x_exp[2]*x_exp[2] + z_exp[2]*z_exp[2] - LEG*LEG - LL*LL) / (2 * LEG * LL));
		
		sita_L[2]=abs_float(atan(z_exp[2]/x_exp[2])) +phai[2];  
		
		LEG_degree[2]=180-sita_L[2]*57.29;
		LOWER_LEG_degree[2]=360-sita_LL[2]*57.29;	

		//腿3算法
		phai[3]= acos((x_exp[3]*x_exp[3] + z_exp[3]*z_exp[3] + LEG*LEG - LL*LL) /(2 *LEG*sqrt(x_exp[3]*x_exp[3] + z_exp[3]*z_exp[3])));
		sita_LL[3] = 2*pi - acos((x_exp[3]*x_exp[3] + z_exp[3]*z_exp[3] - LEG*LEG - LL*LL) / (2 * LEG * LL));
		
		sita_L[3]=abs_float(atan(z_exp[3]/x_exp[3])) +phai[3];  
		
		LEG_degree[3]=sita_L[3]*57.29;
		LOWER_LEG_degree[3]=sita_LL[3]*57.29-180;	
		
		servos[1]=(uint8_t)LEG_degree[0];
		servos[2]=(uint8_t)LOWER_LEG_degree[0];
		servos[3]=(uint8_t)LEG_degree[1];
		servos[4]=(uint8_t)LOWER_LEG_degree[1];
		servos[5]=(uint8_t)LEG_degree[2];
		servos[6]=(uint8_t)LOWER_LEG_degree[2];
		servos[7]=(uint8_t)LEG_degree[3];
		servos[8]=(uint8_t)LOWER_LEG_degree[3];
}







