

#include "common_inc.h"
#include "PWM.h"
#include "FOC.h"
#include "electricity_get.h"
#include "USB_HIDCommunication.h"
#include "AS5600.h"
int flag;

int RUNNING_MODE;
int speed_send_flag = 0;
int keyboard_send_cnt = 0;
int keyboard_status = 0;
int nextsong_send_flag = 0;
int revioussong_send_flag = 0;


#define Idle_Mode			0		//空闲
#define Open_Loop_Mode		1		//开环
#define Location_Mode		2		//位置环
#define Moment_Forece_Mode	3		//力矩(电流环)
#define Speed_Mode			4		//速度环
#define HID_KeyBoard_Mode	5		//HID键盘模式(电机为位置环)

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *hitm){// @NOTE 
	
	if( hitm == &htim1 )  //更新频率25Khz
	{
		if( flag == 1){
			flag = 0;
			if( RUNNING_MODE == Idle_Mode)
			{	
				pwm_halt();
				return;
			}
			else if(RUNNING_MODE == Open_Loop_Mode)
				open_loop_control();
			else if(RUNNING_MODE == Location_Mode)
				positioning_control();
			else if( RUNNING_MODE == Speed_Mode){
			}
			else if( RUNNING_MODE == HID_KeyBoard_Mode){
					
			}
			 
		}
		else{
			start_adc();
			flag = 1;
		}
			
	}
	if( hitm == &htim3 )  //50khz
	{
		// start_adc();
	}
}
void AppMain(void){
	RUNNING_MODE = Idle_Mode;
	pwm_init();
	foc_init();
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	while(1){
		hid_recv_data();
		hid_keyboard_nextsong_send();// @NOTE 
		HAL_Delay(20);
		hid_send_Iq(get_M_Iq());
		HAL_Delay(20);
//		hid_send_Id(get_M_Id());
//		HAL_Delay(1);
//		hid_send_angle(get_as5600_angle());
//		HAL_Delay(1);
//		speed_send_flag += 1;
//		if(speed_send_flag == 15)
//		{
//			speed_send_flag = 0;
//			hid_send_speed(read_as5600_speed());
//		}
//		HAL_Delay(1);
	

}
	
}
