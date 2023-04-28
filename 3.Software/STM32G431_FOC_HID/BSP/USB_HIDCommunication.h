

#ifndef __USB_HIDCommunication_H__
#define __USB_HIDCommunication_H__


#include "common_inc.h"

extern unsigned char USB_Recive_Buffer[8];
extern unsigned char USB_Received_Count;

#define Communication_head  0xef
#define Communication_tail  0xab


typedef union float_union{
    float float_t;
    unsigned char ca[4];
}float_union;
#pragma pack(1)
typedef struct message{
    unsigned char head;
    unsigned char function;
	unsigned char data1;
    float_union   data2;
    unsigned char tail;
}Message_Struct;
#pragma pack()

//接收
void hid_recv_data(void);
void Common_Parameters_Parsing(void);

//发送
void hid_send_Uq(float uq);
void hid_send_Ud(float ud);
void hid_send_Iq(float iq);
void hid_send_Id(float id);
void hid_send_angle(unsigned int angle);  //发送角度

#endif