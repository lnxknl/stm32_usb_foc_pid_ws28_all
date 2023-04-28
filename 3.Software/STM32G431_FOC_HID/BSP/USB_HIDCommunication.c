

#include "USB_HIDCommunication.h"
#include "FOC.h"


unsigned char USB_Recive_Buffer[8]; //USB���ջ���
unsigned char USB_Received_Count = 0;//USB�������ݼ���



extern USBD_HandleTypeDef hUsbDeviceFS; //�ⲿ����USB���ͺ���

//����Uq
void hid_send_Uq(float uq){
	Message_Struct message;
	
	message.head = Communication_head;
	message.function = 0x14;
	message.data1 = 0x2a;
	message.data2.float_t = uq;
	message.tail = Communication_tail;

	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (unsigned char *)&message, sizeof(message));
}
void hid_send_Ud(float ud){
	Message_Struct message;
	
	message.head = Communication_head;
	message.function = 0x14;
	message.data1 = 0x2b;
	message.data2.float_t = ud;
	message.tail = Communication_tail;

	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (unsigned char *)&message, sizeof(message));
}
void hid_send_Iq(float iq){
	Message_Struct message;
	
	message.head = Communication_head;
	message.function = 0x14;
	message.data1 = 0x2e;
	message.data2.float_t = iq;
	message.tail = Communication_tail;

	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (unsigned char *)&message, sizeof(message));
}
void hid_send_Id(float id){
Message_Struct message;
	
	message.head = Communication_head;
	message.function = 0x14;
	message.data1 = 0x2f;
	message.data2.float_t = id;
	message.tail = Communication_tail;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (unsigned char *)&message, sizeof(message));
}
 //���ͽǶ�
void hid_send_angle(unsigned int angle){
	
	Message_Struct message;
	
	message.head = Communication_head;
	message.function = 0x14;
	message.data1 = 0x2d;
	message.data2.ca[0] = 0x00;
	message.data2.ca[1] = 0x00;
	message.data2.ca[2] = (angle >> 8) & 0xFF;
	message.data2.ca[3] = angle & 0xFF;
	message.tail = Communication_tail;

	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (unsigned char *)&message, sizeof(message));
}





void hid_recv_data(void){
	if( USB_Received_Count == 0 )  //û�н��յ�����
		return; 
	if(USB_Recive_Buffer[0] != Communication_head || USB_Recive_Buffer[7] != Communication_tail)
		return ;
	if( USB_Recive_Buffer[1] == 0x12)
		Common_Parameters_Parsing();
			
	USB_Received_Count = 0;	
}
extern int RUNNING_MODE;
//�����������գ�����
void Common_Parameters_Parsing(void){
	
	//ģʽ�л�
	if( USB_Recive_Buffer[2] == 0x20 ){
		RUNNING_MODE = USB_Recive_Buffer[6];
	}
	//����Uq
	else if(  USB_Recive_Buffer[2] == 0x2a ){
		float_union new_uq;
		new_uq.ca[0] = USB_Recive_Buffer[3];
		new_uq.ca[1] = USB_Recive_Buffer[4];
		new_uq.ca[2] = USB_Recive_Buffer[5];
		new_uq.ca[3] = USB_Recive_Buffer[6];
		set_foc_uq(new_uq.float_t);
	}
	//����Ud
	else if(  USB_Recive_Buffer[2] == 0x2b ){
		float_union new_ud;
		new_ud.ca[0] = USB_Recive_Buffer[3];
		new_ud.ca[1] = USB_Recive_Buffer[4];
		new_ud.ca[2] = USB_Recive_Buffer[5];
		new_ud.ca[3] = USB_Recive_Buffer[6];
		set_foc_ud(new_ud.float_t);
	}
	
	//�����ٶ�
	else if(  USB_Recive_Buffer[2] == 0x2c ){
		
	}
}