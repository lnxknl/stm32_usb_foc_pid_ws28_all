//
// Created by Valentina_HP on 2023/3/19.
//

#ifndef FOC_FOC_H
#define FOC_FOC_H

#include "common_inc.h"
#include "PWM.h"
#include "AS5600.h"


#define ROOT_SIGN_3		1.732050807568877

typedef struct FOC_Parameter{
	
	
	
	  //期望的Ud和Uq
    float Desire_Ud;
	float Desire_Uq;   
	
	
	float currU;
	float currV;
	
	float Ualpha;
	float Ubeta;
	
	float Ialpha;
	float Ibeta;
	
	float Iq;
	float Id;
	
	float sinVal;
	float cosVal;
	
	float angle;
	float Polar_Pair; //电机极对数
    float Udc; //母线电压
    float Ts;  //矢量作用总时长
	
	
	  //扇区和以及扇区对应矢量作用时间
    uint8_t sector;
    float T0;
    float T1;
    float T2;
    float T3;
    float T4;
    float T5;
    float T6;
    float T7;
	
	
	//开环
	float open_loop_direction; //开环方向 0 -顺时针   1 - 逆时针
	float open_loop_speed; //开环速度
	
	//位置
	uint16_t positioning_angle; //期望角度
		
}FOC_Parameter;



void foc_init(void);


float to_electrical_angle(float Mechanical_Angle);
void Sector_Determination(float u1 , float u2 ,float u3);
void Generate_Sector_Time(void);
void Generate_SVPWM(void);

void cal_angle_sincos();

void Clarke();
void Park();
void InvPark();

void update_currUV(void);

float get_M_Iq();
float get_M_Id();

void set_foc_open_loop_direction(unsigned char direction);
void set_foc_ud(float new_ud);
void set_foc_uq(float new_uq);
void set_open_loop_speed(float new_speed);
void set_positioning_angle(uint16_t new_angle);

void open_loop_control(void);   //开环控制
void positioning_control(void);  //位置控制


#endif //FOC_FOC_H
