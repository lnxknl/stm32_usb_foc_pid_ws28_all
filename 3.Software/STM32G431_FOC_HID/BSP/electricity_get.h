
#ifndef __ELECTRICITY_GET_H_
#define __ELECTRICITY_GET_H_


#include "common_inc.h"




int calculate_current_I(uint32_t voltage);

void start_adc();
int get_adc_value();



#endif