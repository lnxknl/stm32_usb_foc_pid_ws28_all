


#include "electricity_get.h"



uint32_t ADC_VALUE = 0;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)  //在中断回调函数中读取
{
    ADC_VALUE = HAL_ADC_GetValue(&hadc1);  //这样可以不浪费资源，当然放在主函数中读取也行

}


//将电压转换为电流,单位ma
int calculate_current_I(uint32_t voltage){
	//return (((float)(voltage/4096.0)*5.0) / 0.05) / 50.0;  完整表达式
	return (int)((float)(voltage/2048.0) * 1000);  
}


//获取电流值
int get_adc_value(){
	return calculate_current_I(ADC_VALUE);
}

//开始adc采样
void start_adc(){
	HAL_ADC_Start_IT(&hadc1);
}
	 