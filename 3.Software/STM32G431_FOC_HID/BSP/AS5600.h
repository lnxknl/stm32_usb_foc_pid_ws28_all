//
// Created by Valentina_HP on 2023/3/17.
//

#ifndef FOC_AS5600_H
#define FOC_AS5600_H

#include "IIC.h"



#define ANGLE_OFFSET	293.6 - 23.6//对应电机的0角度
 
float read_as5600_angle();
float read_as5600_speed();


float get_as5600_angle();
#endif //FOC_AS5600_H
