//
// Created by Valentina_HP on 2023/3/17.
//

#include "AS5600.h"
#include "math.h"


#define RESOLUTION_RATIO  0.087890625		//角度分辨率
float read_as5600_angle(){
    uint8_t angle_l = iic_read_data(0x6c,0x0f);  // 0x6c,0x0f
    uint8_t angle_h = iic_read_data(0x6c,0x0e);  //0e
	
    float angle =  ((float)((angle_h << 8) + angle_l)) * RESOLUTION_RATIO;
	
	if( angle < ANGLE_OFFSET)
		angle = ANGLE_OFFSET - angle;
	else
		angle = ANGLE_OFFSET + (360 - angle);
    return angle; // 归一化到0-360
}
