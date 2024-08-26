#include "seriescommunication.h"
#include<QDebug>
SeriesCommunication::SeriesCommunication(QObject *parent) : QObject(parent)
{
    time.start(500);



    serial.setBaudRate(QSerialPort::Baud115200);
    serial.setParity(QSerialPort::NoParity);
    serial.setDataBits(QSerialPort::Data8);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    scan_foc_seriers_connect();



    connect(&serial,&QSerialPort::readyRead,this,&SeriesCommunication::DataReceived);      // 接收数据
}

void SeriesCommunication::DataReceived(){
    char *data =  serial.read(8).data();
    if((unsigned char)data[0] != 0xef || (unsigned char)data[7] != 0xab)// @NOTE 
        return;
    QVector<unsigned char> d;
    d.push_back(data[1]);
    d.push_back(data[2]);
    d.push_back(data[3]);
    d.push_back(data[4]);
    d.push_back(data[5]);
    d.push_back(data[6]);
    qDebug() << d;
    emit recvReady(d);
}


bool SeriesCommunication::scan_foc_seriers_connect(){

    if(serial.isOpen())
        return 1;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
       {
          // qDebug() << info.portName();
          // if(info.portName() == "COM3"){
               serial.setPort(info);
               if(serial.open(QIODevice::ReadWrite))      // 以读写方式打开串口
               {
                   return 1;
                   qDebug() << "串口打开成功，请重试";
               } else
               {
                   return 0;
                   qDebug() << "串口打开失败，请重试";
               }
           //}
       }

    return 0;
}


void SeriesCommunication::series_foc_write(char *data){
    if(!serial.isOpen())
        return;
    serial.write(data,8);
}
