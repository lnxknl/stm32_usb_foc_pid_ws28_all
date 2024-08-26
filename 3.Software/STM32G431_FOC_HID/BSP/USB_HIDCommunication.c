

#include "USB_HIDCommunication.h"
#include "FOC.h"


unsigned char USB_Recive_Buffer[8]; //USB接收缓存
unsigned char USB_Received_Count = 0;//USB接收数据计数



extern USBD_HandleTypeDef hUsbDeviceFS; //外部声明USB发送函数


void data_send(uint8_t* Buf, uint16_t Len){
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,Buf,Len);
}
//发送Uq
void hid_send_Uq(float uq){
	Message_Struct message;
	
	message.head = Communication_head;
	message.function = 0x14;
	message.data1 = 0x2a;
	message.data2.float_t = uq;
	message.tail = Communication_tail;

	data_send((unsigned char *)&message, 8);
}
void hid_send_Ud(float ud){
	Message_Struct message;
	
	message.head = Communication_head;
	message.function = 0x14;
	message.data1 = 0x2b;
	message.data2.float_t = ud;
	message.tail = Communication_tail;

	data_send((unsigned char *)&message, 8);
}
void hid_send_Iq(float iq){
	Message_Struct message;
	
	message.head = Communication_head;
	message.function = 0x14;
	message.data1 = 0x2e;
	message.data2.float_t = iq;
	message.tail = Communication_tail;

	data_send((unsigned char *)&message, 8);
}
void hid_send_Id(float id){
	Message_Struct message;
	
	message.head = Communication_head;
	message.function = 0x14;
	message.data1 = 0x2f;
	message.data2.float_t = id;
	message.tail = Communication_tail;
	data_send((unsigned char *)&message, 8);
}
 //发送角度
void hid_send_angle(float angle){
	
	Message_Struct message;
	
	message.head = Communication_head;
	message.function = 0x14;
	message.data1 = 0x2d;
	message.data2.float_t = angle;
	message.tail = Communication_tail;
	data_send((unsigned char *)&message, 8);
}

//发送速度
void hid_send_speed(float speed){
	
	Message_Struct message;
	
	message.head = Communication_head;
	message.function = 0x14;
	message.data1 = 0x2c;
	message.data2.float_t = speed;
	message.tail = Communication_tail;
	data_send((unsigned char *)&message, 8);
}



void hid_recv_data(void){
	if( USB_Received_Count == 0 )  //没有接收到数据// @NOTE 
		return; 
	if(USB_Recive_Buffer[0] != Communication_head || USB_Recive_Buffer[7] != Communication_tail)// @NOTE 
		return ;
	if( USB_Recive_Buffer[1] == 0x12)   //公共参数
		Common_Parameters_Parsing(); 
	else if( USB_Recive_Buffer[1] == 0x22)  //位置环参数
		Position_Parameters_Parsing();
	else if( USB_Recive_Buffer[1] == 0x32)  //开环参数
		Open_Loop_Parameters_Parsing();
	USB_Received_Count = 0;	
}
extern int RUNNING_MODE;
//公共参数接收，解析
void Common_Parameters_Parsing(void){
	
	//模式切换
	if( USB_Recive_Buffer[2] == 0x20 ){
		RUNNING_MODE = USB_Recive_Buffer[6];
	}
	//更新Uq
	else if(  USB_Recive_Buffer[2] == 0x2a ){
		float_union new_uq;
		new_uq.ca[0] = USB_Recive_Buffer[3];
		new_uq.ca[1] = USB_Recive_Buffer[4];
		new_uq.ca[2] = USB_Recive_Buffer[5];
		new_uq.ca[3] = USB_Recive_Buffer[6];
		set_foc_uq(new_uq.float_t);
	}
	//更新Ud
	else if(  USB_Recive_Buffer[2] == 0x2b ){
		float_union new_ud;
		new_ud.ca[0] = USB_Recive_Buffer[3];
		new_ud.ca[1] = USB_Recive_Buffer[4];
		new_ud.ca[2] = USB_Recive_Buffer[5];
		new_ud.ca[3] = USB_Recive_Buffer[6];
		set_foc_ud(new_ud.float_t);
	}
	
	//更新速度
	else if(  USB_Recive_Buffer[2] == 0x2c ){
		
	}
}
//位置控制参数
void Position_Parameters_Parsing(void){
	if( USB_Recive_Buffer[2] == 0x1a ){
		uint16_t angle = (USB_Recive_Buffer[5] << 8 ) + USB_Recive_Buffer[6];
		set_positioning_angle(angle);
	}
			
}
//开环控制参数
void Open_Loop_Parameters_Parsing(void){
	//设置正反转
	if( USB_Recive_Buffer[2] == 0x1a ){
		set_foc_open_loop_direction(USB_Recive_Buffer[6]);
	}
}




void hid_keyboard_nextsong_send(void){
	uint8_t keyboard_buf[8] = {0,0,0,0,0,0,0,0};
	
	keyboard_buf[0] = 0x05;////0x5;  //ctrl + alt
	keyboard_buf[2] = 0x4F;//0x4F; //left
	
	USBD_KEYBOADR_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&keyboard_buf,8);  //发送按下
	HAL_Delay(15);
	keyboard_buf[0] = 0x00;  //ctrl + alt
	keyboard_buf[2] = 0x00; //left
	USBD_KEYBOADR_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&keyboard_buf, 8);
	HAL_Delay(15);
	
}
void hid_keyboard_previoussong_send(void){
	uint8_t keyboard_buf[8] = {0,0,0,0,0,0,0,0};
	
	keyboard_buf[0] = 0x05;  //ctrl + alt
	keyboard_buf[2] = 0x50; //left
	
	data_send((unsigned char *)&keyboard_buf, 8);
	HAL_Delay(5);
	keyboard_buf[0] = 0x0;  //ctrl + alt
	keyboard_buf[2] = 0x0; //left
	data_send((unsigned char *)&keyboard_buf, 8);
	HAL_Delay(5);
}
