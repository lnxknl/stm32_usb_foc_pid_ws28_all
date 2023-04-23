//
// Created by Valentina_HP on 2023/3/19.
//

#include "FOC.h"
#include "math.h"


FOC_Parameter FOC_Parameter_M0;

//Uq = 3  open_loop_speed = 1.2
//Uq = 1.5  open_loop_speed = 0.2
//初始化FOC的一些参数
void foc_init(void){

	
	
	FOC_Parameter_M0.Desire_Ud = 0.0;
	FOC_Parameter_M0.Desire_Uq = 2;
	
	FOC_Parameter_M0.Ts = 1.0;
	FOC_Parameter_M0.Polar_Pair = 11;
	FOC_Parameter_M0.Udc = 12;
	
	
	FOC_Parameter_M0.open_loop_angle = 0;
	FOC_Parameter_M0.open_loop_speed = 0.5;
	
	
	FOC_Parameter_M0.positioning_angle = 0;
}

void Sector_Determination(float u1 , float u2 ,float u3){
    uint8_t  A , B , C , N;
		
		if( u3 > 0 ) A = 1;
	  else A = 0;
		if( u2 > 0 ) B = 1;
	  else B = 0;
		if( u1 > 0 ) C = 1;
	  else C = 0;
    N = 4*C + B * 2 + A;
    if( N == 5)
        FOC_Parameter_M0.sector = 1;
    else if( N == 4)
        FOC_Parameter_M0.sector = 2;
    else if( N == 6)
        FOC_Parameter_M0.sector = 3;
    else if( N == 2)
        FOC_Parameter_M0.sector = 4;
    else if( N == 3)
        FOC_Parameter_M0.sector = 5;
    else
        FOC_Parameter_M0.sector = 6;
}

void Generate_Sector_Time(void){
    float K = ROOT_SIGN_3 * FOC_Parameter_M0.Ts / FOC_Parameter_M0.Udc;
    float U1,U2,U3;

    U1 = FOC_Parameter_M0.Ubeta;
    U2 = -0.8660254037844386 * FOC_Parameter_M0.Ualpha - FOC_Parameter_M0.Ubeta/2;
    U3 =  0.8660254037844386* FOC_Parameter_M0.Ualpha - FOC_Parameter_M0.Ubeta/2;
    Sector_Determination(U1 , U2 ,U3);
    if( FOC_Parameter_M0.sector == 1){
        FOC_Parameter_M0.T4 = K * U3;
        FOC_Parameter_M0.T6 = K * U1;
        if( FOC_Parameter_M0.T4 + FOC_Parameter_M0.T6 > FOC_Parameter_M0.Ts){
            float k = FOC_Parameter_M0.Ts /(FOC_Parameter_M0.T4+ FOC_Parameter_M0.T6) ;
            FOC_Parameter_M0.T4 = k * FOC_Parameter_M0.T4;
            FOC_Parameter_M0.T6 = k * FOC_Parameter_M0.T6;
        }
        FOC_Parameter_M0.T0 = (FOC_Parameter_M0.Ts - FOC_Parameter_M0.T4 - FOC_Parameter_M0.T6) / 2;
        FOC_Parameter_M0.T7 = (FOC_Parameter_M0.Ts - FOC_Parameter_M0.T4 - FOC_Parameter_M0.T6) / 2;
    }
    else if(FOC_Parameter_M0.sector == 2 ){
        FOC_Parameter_M0.T2 = -K * U3;
        FOC_Parameter_M0.T6 = -K * U2;
        if( FOC_Parameter_M0.T2 + FOC_Parameter_M0.T6 > FOC_Parameter_M0.Ts){
            float k = FOC_Parameter_M0.Ts /(FOC_Parameter_M0.T2+ FOC_Parameter_M0.T6) ;
            FOC_Parameter_M0.T2 = k * FOC_Parameter_M0.T2;
            FOC_Parameter_M0.T6 = k * FOC_Parameter_M0.T6;
        }
        FOC_Parameter_M0.T0 = (FOC_Parameter_M0.Ts - FOC_Parameter_M0.T2 - FOC_Parameter_M0.T6) / 2;
        FOC_Parameter_M0.T7 = (FOC_Parameter_M0.Ts - FOC_Parameter_M0.T2 - FOC_Parameter_M0.T6) / 2;
    }
    else if(FOC_Parameter_M0.sector == 3){
        FOC_Parameter_M0.T2 = K * U1;
        FOC_Parameter_M0.T3 = K * U2;
        if( FOC_Parameter_M0.T2 + FOC_Parameter_M0.T3 > FOC_Parameter_M0.Ts){
            float k = FOC_Parameter_M0.Ts /(FOC_Parameter_M0.T2+ FOC_Parameter_M0.T3) ;
            FOC_Parameter_M0.T2 = k * FOC_Parameter_M0.T2;
            FOC_Parameter_M0.T3 = k * FOC_Parameter_M0.T3;
        }
        FOC_Parameter_M0.T0 = (FOC_Parameter_M0.Ts - FOC_Parameter_M0.T2 - FOC_Parameter_M0.T3) / 2;
        FOC_Parameter_M0.T7 = (FOC_Parameter_M0.Ts - FOC_Parameter_M0.T2 - FOC_Parameter_M0.T3) / 2;
    }
    else if(FOC_Parameter_M0.sector == 4){
        FOC_Parameter_M0.T1 = -K * U1;
        FOC_Parameter_M0.T3 = -K * U3;
        if( FOC_Parameter_M0.T1 + FOC_Parameter_M0.T3 > FOC_Parameter_M0.Ts){
            float k = FOC_Parameter_M0.Ts /(FOC_Parameter_M0.T1+ FOC_Parameter_M0.T3) ;
            FOC_Parameter_M0.T1 = k * FOC_Parameter_M0.T1;
            FOC_Parameter_M0.T3 = k * FOC_Parameter_M0.T3;
        }
        FOC_Parameter_M0.T0 = (FOC_Parameter_M0.Ts - FOC_Parameter_M0.T1 - FOC_Parameter_M0.T3) / 2;
        FOC_Parameter_M0.T7 = (FOC_Parameter_M0.Ts - FOC_Parameter_M0.T1 - FOC_Parameter_M0.T3) / 2;
    }
    else if(FOC_Parameter_M0.sector == 5){
        FOC_Parameter_M0.T1 = K * U2;
        FOC_Parameter_M0.T5 = K * U3;
        if( FOC_Parameter_M0.T1 + FOC_Parameter_M0.T5 > FOC_Parameter_M0.Ts){
            float k = FOC_Parameter_M0.Ts /(FOC_Parameter_M0.T1+ FOC_Parameter_M0.T5) ;
            FOC_Parameter_M0.T1 = k * FOC_Parameter_M0.T1;
            FOC_Parameter_M0.T5 = k * FOC_Parameter_M0.T5;
        }
        FOC_Parameter_M0.T0 = (FOC_Parameter_M0.Ts - FOC_Parameter_M0.T1 - FOC_Parameter_M0.T5) / 2;
        FOC_Parameter_M0.T7 = (FOC_Parameter_M0.Ts - FOC_Parameter_M0.T1 - FOC_Parameter_M0.T5) / 2;
    }
    else {
        FOC_Parameter_M0.T4 = -K * U2;
        FOC_Parameter_M0.T5 = -K * U1;
        if( FOC_Parameter_M0.T4 + FOC_Parameter_M0.T5 > FOC_Parameter_M0.Ts){
            float k = FOC_Parameter_M0.Ts /(FOC_Parameter_M0.T4+ FOC_Parameter_M0.T5) ;
            FOC_Parameter_M0.T4 = k *FOC_Parameter_M0. T4;
            FOC_Parameter_M0.T5 = k *FOC_Parameter_M0.T5;
        }
        FOC_Parameter_M0.T0 = (FOC_Parameter_M0.Ts - FOC_Parameter_M0.T4 - FOC_Parameter_M0.T5) / 2;
        FOC_Parameter_M0.T7 = (FOC_Parameter_M0.Ts - FOC_Parameter_M0.T4 - FOC_Parameter_M0.T5) / 2;
    }

}
void Generate_SVPWM(void){
	float Ta , Tb , Tc;
    if( FOC_Parameter_M0.sector == 1){
        Ta = FOC_Parameter_M0.T4 + FOC_Parameter_M0.T6 + FOC_Parameter_M0.T7;
        Tb = FOC_Parameter_M0.T6 + FOC_Parameter_M0.T7;
        Tc = FOC_Parameter_M0.T7;
    }
    else if( FOC_Parameter_M0.sector == 2){
        Ta = FOC_Parameter_M0.T6 + FOC_Parameter_M0.T7;
        Tb = FOC_Parameter_M0.T2 + FOC_Parameter_M0.T6 + FOC_Parameter_M0.T7;
        Tc = FOC_Parameter_M0.T7;
    }
    else if( FOC_Parameter_M0.sector == 3){
        Ta = FOC_Parameter_M0.T7;
        Tb = FOC_Parameter_M0.T2 + FOC_Parameter_M0.T3 + FOC_Parameter_M0.T7;
        Tc = FOC_Parameter_M0.T3 + FOC_Parameter_M0.T7;
    }
    else if( FOC_Parameter_M0.sector == 4){
        Ta = FOC_Parameter_M0.T7;
        Tb = FOC_Parameter_M0.T3 + FOC_Parameter_M0.T7;
        Tc = FOC_Parameter_M0.T1 + FOC_Parameter_M0.T3 + FOC_Parameter_M0.T7;
    }
    else if( FOC_Parameter_M0.sector == 5){
        Ta = FOC_Parameter_M0.T5 + FOC_Parameter_M0.T7;
        Tb = FOC_Parameter_M0.T7;
        Tc = FOC_Parameter_M0.T1 + FOC_Parameter_M0.T5 + FOC_Parameter_M0.T7;
    }
    else{
        Ta = FOC_Parameter_M0.T4 + FOC_Parameter_M0.T5 + FOC_Parameter_M0.T7;
        Tb = FOC_Parameter_M0.T7;
        Tc = FOC_Parameter_M0.T5 + FOC_Parameter_M0.T7;
    }
    pwm_update(Ta,Tb,Tc);
}

void Clarke(float *Ialpha , float *Ibeta){

}
void Park(float *Iq,float *Id){

}

void InvPark(float angle) {
    FOC_Parameter_M0.Ualpha = FOC_Parameter_M0.Desire_Ud * cos(angle  * 0.0174532922222) - FOC_Parameter_M0.Desire_Uq * sin(angle * 0.0174532922222);
    FOC_Parameter_M0.Ubeta  = FOC_Parameter_M0.Desire_Ud * sin(angle  * 0.0174532922222) + FOC_Parameter_M0.Desire_Uq * cos(angle * 0.0174532922222);
}

//将机械角度，转化为电角度，并且归一化0-360
float to_electrical_angle(float Mechanical_Angle){
	float angle = Mechanical_Angle * FOC_Parameter_M0.Polar_Pair;
	while(angle > 360)
		angle = angle - 360;
	return angle;
}



//将电压转换为电流,单位ma
int calculate_current_I(uint16_t voltage){
	//return (((float)(voltage/4096.0)*5.0) / 0.05) / 50.0;  完整表达式
	return (int)((float)(voltage/2048.0) * 1000);  
}

//设置foc期望 Ud
void set_foc_ud(float new_ud){
	FOC_Parameter_M0.Desire_Ud = new_ud;
}

//设置foc期望 Uq
void set_foc_uq(float new_uq){
	FOC_Parameter_M0.Desire_Uq = new_uq;
}
//设置开环速度 new_speed°/ 40us
void set_open_loop_speed(float new_speed){
	FOC_Parameter_M0.open_loop_speed = new_speed;
}
//设置位置角度值
void set_positioning_angle(uint16_t new_angle){
	FOC_Parameter_M0.positioning_angle = new_angle;
}
 //开环控制 
void open_loop_control(void){   
	FOC_Parameter_M0.open_loop_angle += FOC_Parameter_M0.open_loop_speed;
	if( FOC_Parameter_M0.open_loop_angle > 360)
		FOC_Parameter_M0.open_loop_angle = 0;

    InvPark(FOC_Parameter_M0.open_loop_angle);
    Generate_Sector_Time();
    Generate_SVPWM();
	
}
//位置控制
void positioning_control(void){
	set_foc_uq(2.0);
	set_foc_ud(0.5);
	float angle = read_as5600_angle();
	if( abs((int)angle - (int)FOC_Parameter_M0.positioning_angle) < 7)  //判断是否达到期望位置
	{	

		pwm_halt();
		return ;
	}
	angle = to_electrical_angle(angle+10.9);
    InvPark(angle);
    Generate_Sector_Time();
    Generate_SVPWM();
}
void foc_test(float angle) {
	angle = to_electrical_angle(angle);
    InvPark(angle);
    Generate_Sector_Time();
    Generate_SVPWM();
}
