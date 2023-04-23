//
// Created by Valentina_HP on 2023/3/19.
//

#include "PWM.h"


//定时器初始化
void pwm_init(void) {
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
    __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,0);
    __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,0);
    __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,0);
}

//更新pwm ,Tx为高电平持续时间
void pwm_update(float Ta , float Tb , float Tc){
		
	 if( Ta > 1) Ta = 1;
	 else Ta = Ta;
	
	 if( Ta < 0) Ta = 0;
	 else Ta = Ta;
	
	 if( Tb > 1) Tb = 1;
	 else Tb = Tb;
	
	 if( Tb < 0) Tb = 0;
	 else Tb = Tb;
	
   if( Tc > 1) Tc = 1;
	 else Tc = Tc;
	
	 if( Tc < 0) Tc = 0;
	 else Tc = Tc;
	
	
	
    __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,Ta * PWM_50KHZ_ARR);
    __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,Tb * PWM_50KHZ_ARR);
    __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,Tc * PWM_50KHZ_ARR);

    //printf("%lf,%lf,%lf\r\n",Ta * TIM_ARR,Tb * TIM_ARR,Tc * TIM_ARR);
}
////暂停，停止PWM输出
void pwm_halt(void){
   __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,0);
   __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,0);
   __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,0);
}