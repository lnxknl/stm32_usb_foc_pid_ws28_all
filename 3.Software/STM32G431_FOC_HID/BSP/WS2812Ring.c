//
// Created by Valentina_HP on 2023/3/16.
//

#include "WS2812Ring.h"
WS2812Ring::WS2812Ring(){

}

void WS2812Ring::mode_1(){
    unsigned char i;
    for( i = 0;i < 12;i++) {

        WS2812_WriteRGB(0xff, 0x00, 0x00);
        WS2812_WriteRGB(0x00, 0xff, 0x00);
        WS2812_WriteRGB(0x00, 0x00, 0xff);
    }
   // WS2812_Reset();
}
void WS2812Ring::mode_1_shift(uint8_t datar,uint8_t datag,uint8_t datab){
//    unsigned char i;
//    WS2812_WriteRGB(datar, datag, datab);
//    WS2812_Reset();
    unsigned char i;
    for( i = 0;i < 8;i++) {
        datar = datar + datag;
        datag = datag + datab;
        datab = datar + datag;
        WS2812_WriteRGB(datar, 0xfa, 0x31);
        WS2812_WriteRGB(0xa3, 0xbc, datab);
        WS2812_WriteRGB(0xf4, datag, 0xae);
    }
}
void WS2812Ring::mode_2(){

}


void WS2812Ring::WS2812_Write_H(){
    HAL_GPIO_WritePin(Dout_GPIO_Port,Dout_Pin,GPIO_PIN_SET);


    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    HAL_GPIO_WritePin(Dout_GPIO_Port,Dout_Pin,GPIO_PIN_RESET);

    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
}
void WS2812Ring::WS2812_Write_L(){
    HAL_GPIO_WritePin(Dout_GPIO_Port,Dout_Pin,GPIO_PIN_SET);
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    HAL_GPIO_WritePin(Dout_GPIO_Port,Dout_Pin,GPIO_PIN_RESET);
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
}

void WS2812Ring::WS2812_WriteRGB(uint8_t R,uint8_t G,uint8_t B){// @NOTE 
   uint8_t i;
   for( i = 0 ;i < 8 ;i++){
       if( G & 0x80)
           WS2812_Write_H();
       else
           WS2812_Write_L();
       G <<= 1;
   }
  //  HAL_GPIO_WritePin(Dout_GPIO_Port,Dout_Pin,GPIO_PIN_SET);
    for( i = 0 ;i < 8 ;i++){
        if( R & 0x80)
            WS2812_Write_H();
        else
            WS2812_Write_L();
        R <<= 1;
    }
   // HAL_GPIO_WritePin(Dout_GPIO_Port,Dout_Pin,GPIO_PIN_SET);
    for( i = 0 ;i < 8 ;i++){
        if( B  & 0x80)
            WS2812_Write_H();
        else
            WS2812_Write_L();
        B <<= 1;
    }
 //   HAL_GPIO_WritePin(Dout_GPIO_Port,Dout_Pin,GPIO_PIN_SET);
}

void WS2812Ring::WS2812_Reset(){
    HAL_GPIO_WritePin(Dout_GPIO_Port,Dout_Pin,GPIO_PIN_RESET);
    HAL_Delay(1);
}
