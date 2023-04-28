

#include "common_inc.h"
#include "PWM.h"
#include "FOC.h"
#include "electricity_get.h"
#include "USB_HIDCommunication.h"
int flag;

int RUNNING_MODE;


#define Idle_Mode			0		//����
#define Open_Loop_Mode		1		//����
#define Location_Mode		2		//λ�û�
#define Moment_Forece_Mode	3		//����(������)
#define Speed_Mode			4		//����(������)
#define HID_KeyBoard_Mode	5		//HID����ģʽ(���Ϊλ�û�)

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *hitm){
	
	if( hitm == &htim1 )  //����Ƶ��25Khz
	{
		if( flag == 1){
			
			if( RUNNING_MODE == Idle_Mode)
			{	
				pwm_halt();
				return;
			}
			else if(RUNNING_MODE == Open_Loop_Mode)
				open_loop_control();
			else if(RUNNING_MODE == Location_Mode)
				positioning_control();
			flag = 0;
		}
		else
			flag = 1;
	}
	if( hitm == &htim3 )  //50khz
	{
		 
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
	}
	
}
