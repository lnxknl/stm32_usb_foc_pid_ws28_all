//
// Created by Valentina_HP on 2023/3/19.
//

#include "FOC.h"
#include "math.h"
#include "USB_HIDCommunication.h"
#include "electricity_get.h"
FOC_Parameter FOC_Parameter_M0;

//Uq = 3  open_loop_speed = 1.2
//Uq = 1.5  open_loop_speed = 0.2
//初始化FOC的一些参数
void foc_init(void){

	
	
	FOC_Parameter_M0.Desire_Ud =0;
	FOC_Parameter_M0.Desire_Uq = 2;
	
	FOC_Parameter_M0.Ts = 1.0;
	FOC_Parameter_M0.Polar_Pair = 11;
	FOC_Parameter_M0.Udc = 12;
	
	
	FOC_Parameter_M0.open_loop_direction = 180;
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

void cal_angle_sincos(){
	float angle = FOC_Parameter_M0.angle  * 0.0174532922222;
	FOC_Parameter_M0.cosVal =  cos(angle);
	FOC_Parameter_M0.sinVal =  sin(angle);
}

void Clarke(){
	FOC_Parameter_M0.Ialpha =  FOC_Parameter_M0.currU;
	FOC_Parameter_M0.Ibeta  = (FOC_Parameter_M0.currU + 2*FOC_Parameter_M0.currV) *  0.5773502692f;
}
void Park(){
	FOC_Parameter_M0.Id = FOC_Parameter_M0.Ialpha *  FOC_Parameter_M0.cosVal;// + FOC_Parameter_M0.Ibeta *  FOC_Parameter_M0.sinVal;
	FOC_Parameter_M0.Iq = -FOC_Parameter_M0.Ialpha * FOC_Parameter_M0.sinVal;// +  FOC_Parameter_M0.Ibeta *  FOC_Parameter_M0.cosVal;
}

void InvPark() {
    FOC_Parameter_M0.Ualpha = FOC_Parameter_M0.Desire_Ud * FOC_Parameter_M0.cosVal - FOC_Parameter_M0.Desire_Uq * FOC_Parameter_M0.sinVal;
    FOC_Parameter_M0.Ubeta  = FOC_Parameter_M0.Desire_Ud * FOC_Parameter_M0.sinVal + FOC_Parameter_M0.Desire_Uq * FOC_Parameter_M0.cosVal;
}

//将机械角度，转化为电角度，并且归一化0-360
float to_electrical_angle(float Mechanical_Angle){
	float angle = Mechanical_Angle * FOC_Parameter_M0.Polar_Pair;
	while(angle > 360)
		angle = angle - 360;
	return angle;
}

void update_currUV(void){
	FOC_Parameter_M0.currU = get_adc_u_value();
	FOC_Parameter_M0.currV = get_adc_v_value();
}

float get_M_Iq(){
	return FOC_Parameter_M0.Iq;
}
float get_M_Id(){
	return FOC_Parameter_M0.Id;
}
void set_foc_open_loop_direction(unsigned char direction){
	if(direction > 0) direction = 0;
	else	direction = 1;
	FOC_Parameter_M0.open_loop_direction = direction * 180.0;
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
	float angle = read_as5600_angle();
//	hid_send_angle(angle);
//	hid_send_speed(read_as5600_speed());
	angle = to_electrical_angle(angle +FOC_Parameter_M0.open_loop_direction );
	FOC_Parameter_M0.angle = angle;
	cal_angle_sincos();
	update_currUV();
	Clarke();
    Park();
    InvPark();
    Generate_Sector_Time();
    Generate_SVPWM();
}
//位置控制
void positioning_control(void){
	float angle = read_as5600_angle();
	//hid_send_angle(angle);
	if( abs((int)angle - (int)FOC_Parameter_M0.positioning_angle) < 1.5 || (360 - angle + FOC_Parameter_M0.positioning_angle) < 1.5 )  //判断是否达到期望位置
	{	
		pwm_halt();
		return ;
	}
	float dangle = 0;
	if( abs((int)angle - (int)FOC_Parameter_M0.positioning_angle) <= 180){
		if( FOC_Parameter_M0.positioning_angle < angle)
			dangle = 180;
		else
			dangle = 0;
	
	}
	else{
		if( FOC_Parameter_M0.positioning_angle < angle)
			dangle = 0;
		else
			dangle = 180;
	}
	
	angle = to_electrical_angle(angle + dangle);
	FOC_Parameter_M0.angle = angle;
	cal_angle_sincos();
    InvPark();
    Generate_Sector_Time();
    Generate_SVPWM();
}
