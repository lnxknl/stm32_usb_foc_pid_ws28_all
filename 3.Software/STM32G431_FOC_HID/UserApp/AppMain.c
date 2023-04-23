

#include "common_inc.h"
#include "PWM.h"
#include "FOC.h"
uint16_t ADC_convert_result;
int I;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *hitm){
	
	if( hitm == &htim2)  //����Ƶ��25Khz
	{
		open_loop_control();

		//positioning_control();
		ADC_convert_result = HAL_ADC_GetValue(&hadc1);	//��ȡADCת�����ݣ�16λ���ݣ�
		I = calculate_current_I(ADC_convert_result);
		usb_printf("%d,\n",I);
	}
	if( hitm == &htim3 )  //���������ɼ�
	{
		HAL_ADC_Start(&hadc1);	//����ADCת��
	}
     
 
}

void AppMain(void){
	
	pwm_init();
	foc_init();
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	
	float angle;
	while(1){
//		//angle = read_as5600_angle();
//		//printf("%d\r\n",(int)angle);
//		
//	    uint16_t ADC_Value[2];
//   
//		HAL_ADC_Start(&hadc1);    //����ADCת��
//		HAL_ADC_PollForConversion(&hadc1,0x10);  //�ȴ�ת�����
//		ADC_Value[1] = HAL_ADC_GetValue(&hadc1);	//��ȡת��ֵ
	//	usb_printf("%d,\n",I);

		
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
