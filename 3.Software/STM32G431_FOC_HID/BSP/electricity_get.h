
#ifndef __ELECTRICITY_GET_H_
#define __ELECTRICITY_GET_H_


#include "common_inc.h"




float calculate_current_I(uint32_t voltage);

void start_adc();
float get_adc_u_value();
float get_adc_v_value();


#endif