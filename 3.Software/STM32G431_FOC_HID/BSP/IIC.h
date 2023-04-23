//
// Created by Valentina_HP on 2023/3/17.
//

#ifndef FOC_IIC_H
#define FOC_IIC_H

#include "common_inc.h"

#define _GPIO_CLK  AS5600_SCL_GPIO_Port
#define _GPIO_SDA  AS5600_SDA_GPIO_Port
#define _GPIO_Pin_CLK AS5600_SCL_Pin
#define _GPIO_Pin_SDA AS5600_SDA_Pin
// class IIC {
// public:

//     void Init(GPIO_TypeDef *GPIO_CLK, GPIO_TypeDef *GPIO_SDA,uint16_t GPIO_Pin_CLK,uint16_t GPIO_Pin_SDA);


void iic_write_data(unsigned char device,unsigned char registers, unsigned char value);
uint8_t iic_read_data(unsigned char device,unsigned char registers);

// private:

void _iic_delay(void);
void _SDA_Out(void);
void _SDA_In(void);
void _SCL_High(void);
void _SCL_Low(void);
uint8_t _SDA_Read(void);

void _SDA_High(void);
void _SDA_Low(void);
void _IIC_Start(void);
void _IIC_Stop(void);
void _IIC_Write(uint8_t data);
uint8_t _IIC_Read(void);
uint8_t _IIC_Ack(void);
// private:
//     GPIO_TypeDef *_GPIO_CLK;
//     GPIO_TypeDef *_GPIO_SDA;
//     uint16_t     _GPIO_Pin_CLK;
//     uint16_t     _GPIO_Pin_SDA;

// };


#endif //FOC_IIC_H
