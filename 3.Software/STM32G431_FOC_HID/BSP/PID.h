

#ifndef __PID_H_
#define __PID_H_



#include "common_inc.h"

//�ٶ� λ�� PID�ṹ��
typedef struct PID_Struct{
	float kp;
	float ki;
	float kd;
	
	float bias;
	float lastBias;
	float desier_value;
	float outMax;
}PID_Struct;









#endif