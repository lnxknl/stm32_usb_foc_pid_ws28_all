

#include "common_inc.h"
#include "PWM.h"
#include "FOC.h"
#include "electricity_get.h"
#include "usbd_customhid.h"
extern USBD_HandleTypeDef hUsbDeviceFS; //�ⲿ����USB���ͺ���
uint16_t ADC_convert_result;
int I;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *hitm){
	
	if( hitm == &htim2)  //����Ƶ��25Khz
	{
		open_loop_control();

		//positioning_control();
		I = get_adc_value();
	}
	if( hitm == &htim3 )  //���������ɼ�
	{
		start_adc();	//����ADCת��
	}
     
 
}

void AppMain(void){
	
	pwm_init();
	foc_init();
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
	//HAL_TIM_Base_Start_IT(&htim2);
	//HAL_TIM_Base_Start_IT(&htim3);
	
	while(1){
		//int8_t send_buf[8] = {//����һ��USB�ķ���BUFF
       //                  1,2,3,4,5,6,7,8};
//		a
	}
	
	while(1){
			//uint16_t adc;
//		int i;
//		uint16_t ADC_Value[2];
//   
//		HAL_ADC_Start(&hadc1);    //����ADCת��
//		HAL_ADC_PollForConversion(&hadc1,0x10);  //�ȴ�ת�����
//		ADC_Value[1] = HAL_ADC_GetValue(&hadc1);	//��ȡת��ֵ
//		usb_printf("%d,\n",I);

	}
}
