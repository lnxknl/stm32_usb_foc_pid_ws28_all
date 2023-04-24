


#include "electricity_get.h"



uint32_t ADC_VALUE = 0;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)  //���жϻص������ж�ȡ
{
    ADC_VALUE = HAL_ADC_GetValue(&hadc1);  //�������Բ��˷���Դ����Ȼ�����������ж�ȡҲ��

}


//����ѹת��Ϊ����,��λma
int calculate_current_I(uint32_t voltage){
	//return (((float)(voltage/4096.0)*5.0) / 0.05) / 50.0;  �������ʽ
	return (int)((float)(voltage/2048.0) * 1000);  
}


//��ȡ����ֵ
int get_adc_value(){
	return calculate_current_I(ADC_VALUE);
}

//��ʼadc����
void start_adc(){
	HAL_ADC_Start_IT(&hadc1);
}
	 