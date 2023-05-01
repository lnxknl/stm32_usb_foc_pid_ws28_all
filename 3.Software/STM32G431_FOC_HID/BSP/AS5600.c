//
// Created by Valentina_HP on 2023/3/17.
//

#include "AS5600.h"
#include "math.h"


#define RESOLUTION_RATIO  0.087890625		//角度分辨率

float last_angle = 0;
float speed = 0.0;
float last_speed = 0.0;
float last_speed_d0 = 0.0;
float dt = 0.002;  // 20us // 50Khz

float pangle = 0.0;
float flag_10 = 0;
//10  350
//350 - 10 - 360


//350 10

//10 - 350 + 360
float read_as5600_angle(){
    uint8_t angle_l = iic_read_data(0x6c,0x0f);  // 0x6c,0x0f
    uint8_t angle_h = iic_read_data(0x6c,0x0e);  //0e
	
    float angle =  ((float)((angle_h << 8) + angle_l)) * RESOLUTION_RATIO;
	
	if( angle < ANGLE_OFFSET)
		angle = ANGLE_OFFSET - angle;
	else
		angle = ANGLE_OFFSET + (360 - angle);
	float error = 0;
	
	
	if( flag_10 == 10){
		flag_10 = 0;
		error = angle - last_angle;
		if( error  > 280)
			error = error - 360;
		else if( error < -280)
			error = 360 + error;
		speed = -error;
		last_speed_d0 = last_speed;
		last_speed = speed;
	
	}
	else if( flag_10 == 0){
		last_angle = angle;
		flag_10 += 1;
	}
	else
		flag_10 += 1;
	last_angle = angle;
	pangle = angle;
    return angle; // 归一化到0-360
}


//读取速度
float read_as5600_speed(){
	return (speed + last_speed+ last_speed_d0) / 3.0;
}


float get_as5600_angle(){
	return pangle;
}