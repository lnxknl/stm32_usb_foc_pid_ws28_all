//
// Created by Valentina_HP on 2023/3/16.
//

#ifndef WS2812RING_H
#define WS2812RING_H

#include "common_inc.h"

class WS2812Ring{
public:
    WS2812Ring();

public:
    void mode_1();
    void mode_1_shift(uint8_t datar,uint8_t datag,uint8_t datab);
    void mode_2();
public:
    void WS2812_WriteRGB(uint8_t R,uint8_t G,uint8_t B);
    void WS2812_Reset();
private:
    void WS2812_Write_H();
    void WS2812_Write_L();


};


#endif //BOTTOM_MCU_CONTROL_WS2812RING_H
