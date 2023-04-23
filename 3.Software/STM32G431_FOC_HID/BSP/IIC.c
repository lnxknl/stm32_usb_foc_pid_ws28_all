//
// Created by Valentina_HP on 2023/3/17.
//

#include "IIC.h"



void _iic_delay(void){
    int time = 500;
    while( time --);
}

void _SDA_Out(void){
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    /*Configure GPIO pin Output Level */
//    HAL_GPIO_WritePin(_GPIO_SDA, _GPIO_Pin_SDA, GPIO_PIN_SET);


//    GPIO_InitStruct.Pin =_GPIO_Pin_SDA;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

//    HAL_GPIO_Init(_GPIO_SDA, &GPIO_InitStruct);
}
void _SDA_In(void){
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    /*Configure GPIO pin Output Level */
//    HAL_GPIO_WritePin(_GPIO_SDA, _GPIO_Pin_SDA, GPIO_PIN_SET);


//    GPIO_InitStruct.Pin =_GPIO_Pin_SDA;
//    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

//    HAL_GPIO_Init(_GPIO_SDA, &GPIO_InitStruct);
}

void _SDA_High(void){
    HAL_GPIO_WritePin(_GPIO_SDA,_GPIO_Pin_SDA,GPIO_PIN_SET);
}
void _SDA_Low(void){
    HAL_GPIO_WritePin(_GPIO_SDA,_GPIO_Pin_SDA,GPIO_PIN_RESET);
}
void _SCL_High(void){
    HAL_GPIO_WritePin(_GPIO_CLK,_GPIO_Pin_CLK,GPIO_PIN_SET);
}
void _SCL_Low(void){
    HAL_GPIO_WritePin(_GPIO_CLK,_GPIO_Pin_CLK,GPIO_PIN_RESET);
}
uint8_t _SDA_Read(void){
    return HAL_GPIO_ReadPin(_GPIO_SDA,_GPIO_Pin_SDA);
}
void _IIC_Start(void){
    _SDA_Out();
    _SDA_High();
    _SCL_High();
    _iic_delay();
    _SDA_Low();
    _iic_delay();
}
void _IIC_Stop(void){
    _SDA_Out();
    _SCL_Low();
    _iic_delay();
    _SDA_Low();
    _iic_delay();
    _SCL_High();
    _iic_delay();
    _SDA_High();
    _iic_delay();
}
void _IIC_Write(uint8_t data){
    unsigned char i;

    _SDA_Out();
    for( i = 0 ; i < 8 ; i++)
    {
        _SCL_Low();
        _iic_delay();
        _iic_delay();
        if(data & 0x80)
            _SDA_High();
        else
            _SDA_Low();

        data = data << 1;
        _iic_delay();
        _SCL_High();
        _iic_delay();
    }
    _SCL_Low();
}
uint8_t _IIC_Read(void){
    unsigned char i,data = 0x00;
    _SDA_In();
    _iic_delay();
    for( i =0 ; i < 8 ; i++ )
    {
        data <<= 1;
        _SCL_High();
        _iic_delay();
        data |= _SDA_Read();
        _SCL_Low();
        _iic_delay();
    }
    return data;
}

uint8_t _IIC_Ack(void){
    unsigned int time = 0xfff;

    _SDA_Out();
    _SCL_Low();
    _iic_delay();
    _SDA_High();

    _SDA_In();
    _iic_delay();
    _SCL_High();
    _iic_delay();
    while(time)
    {
        if(_SDA_Read() == 0)   //读取成功
        {
            _iic_delay();
            _SCL_Low();
	
            return 1;
        }
        time--;
    }
		 _iic_delay();
    _SCL_Low();
		
    return 0; //读取错误
}

void iic_write_data(unsigned char device,unsigned char registers, unsigned char value){
    _IIC_Start();
    _IIC_Write(device);
    _IIC_Ack();
    //   ESP_LOGI("iic test1","%d %d\r\n", mpu6050_iic_read_ack(), gpio_get_level(0));
    _IIC_Write(registers);
    _IIC_Ack();
    //  ESP_LOGI("iic test1","%d %d\r\n", mpu6050_iic_read_ack(), gpio_get_level(0));
    _IIC_Write(value);
    _IIC_Ack();
    // ESP_LOGI("iic test1","%d %d\r\n", mpu6050_iic_read_ack(), gpio_get_level(0));
    _IIC_Stop();
}
uint8_t iic_read_data(unsigned char device,unsigned char registers){
    unsigned char data;
    _IIC_Start();
    _IIC_Write(device);
    _IIC_Ack();
    _IIC_Write(registers);
    _IIC_Ack();
    _IIC_Start();
    _IIC_Write(device+0x01);
    _IIC_Ack();
    data = _IIC_Read();
    _IIC_Ack();
    _IIC_Stop();
    return data;
}
