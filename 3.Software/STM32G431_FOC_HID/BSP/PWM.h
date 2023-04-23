//
// Created by Valentina_HP on 2023/3/19.
//

#ifndef FOC_PWM_H
#define FOC_PWM_H

#include "common_inc.h"



void pwm_init(void);
void pwm_update(float Ta , float Tb , float Tc);
void pwm_halt(void);



#endif //FOC_PWM_H
