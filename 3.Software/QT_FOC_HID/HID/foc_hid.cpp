#include "foc_hid.h"
#include<QDebug>
Foc_Hid::Foc_Hid(QObject *parent) : QObject(parent)
{
    status = 0;
    read_time.start(500);
    connect(&read_time , &QTimer::timeout , this , &Foc_Hid::read_scan);

}







//扫描hid设备
bool Foc_Hid::scan_foc_connect(){
    hid_device_info *hid_info;//usb链表
    hid_info = hid_enumerate(0x10c4,0x82cd);
    if(status == 1)
        return 1;
    for(;hid_info != nullptr;hid_info = hid_info->next){
            qDebug("设备接口号:%d",hid_info->interface_number);
            qDebug("厂商字符串:%ls",hid_info->manufacturer_string);
            qDebug("设备字符串:%ls",hid_info->product_string);
            qDebug("版本号:%d",hid_info->release_number);
            qDebug("地址:%s",hid_info->path);
            if( hid_info->interface_number == 0 )
            {
                hid_path = hid_info->path;
                handle = hid_open_path(hid_path);

                status = 1;
                return 1;
            }

        }
    status = 0;
    handle = NULL;
    /*释放链表*/
    hid_free_enumeration(hid_info);
    return 0;
}

//获取hid路径
char *Foc_Hid::get_hid_path(){
    return hid_path;
}

//发送数据
void Foc_Hid::usb_hid_write(unsigned char *data){
    if( status == 0)
        return;
    int res;
    if(handle == NULL )
        return ;
    res = hid_write(handle, data, TXRX_MAXSIZE + 1);
    if(res < 0){
       /*返回值查看*/
       qDebug("err_string = %ls\n",hid_error(handle));
    }
}

void Foc_Hid::usb_hid_read(){
    if( status == 0)
        return ;
    int res;
    qDebug() << "ab c";
    if(handle == NULL )
    {
        handle = hid_open_path(hid_path);
        qDebug() << "abasd c";
        return ;
    }
    qDebug() << "ab c";
    //hid_set_nonblocking(handle, 1);
    res = hid_read(handle, recvbuf, TXRX_MAXSIZE + 1);
    if(res < 0){
       /*返回值查看*/
       qDebug("err_string = %ls\n",hid_error(handle));
    }
//    for(int i = 0;i<8;i++){
//           qDebug("buf[%d]:%02x",i,recvbuf[i]);
//       }
    return ;
}



void Foc_Hid::read_scan(){

    if( status == 0)
        return ;
    unsigned char *data;
    usb_hid_read();
//    for(int i = 0;i<8;i++){
//           qDebug("buf[%d]:%02x",i,recvbuf[i]);
//       }
   //  qDebug("err_string = %02x %02x\n",recvbuf[0],recvbuf[7]);
    if( recvbuf[0] == 0xef && recvbuf[7] == 0xab)
    {
      //  qDebug() << "recvbuf[0]";
        recvbuf[0] = 0x00;
        recvData.clear();
        recvData.push_back(recvbuf[1]);
        recvData.push_back(recvbuf[2]);
        recvData.push_back(recvbuf[3]);
        recvData.push_back(recvbuf[4]);
        recvData.push_back(recvbuf[5]);
        recvData.push_back(recvbuf[6]);
        emit recvReady(recvData);
    }

}
