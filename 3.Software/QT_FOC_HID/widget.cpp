#include "widget.h"
#include "ui_widget.h"
#include<QComboBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("ValentineHP");

    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(page_switch(int)));

    foc_hid_scan_timer.start(500);

    connect(&foc_hid_scan_timer,&QTimer::timeout,this,&Widget::foc_hid_scan);

    connect(&foc_hid,&Foc_Hid::recvReady,this,&Widget::recvHID_Data);
}

Widget::~Widget()
{
    delete ui;
}


//界面切换
void Widget::page_switch(int index){
    ui->stackedWidget->setCurrentIndex(index);
}


//扫描foc hid 设备
void Widget::foc_hid_scan(){
    static int foc_hid_scan_time = 1;
    bool status = foc_hid.scan_foc_connect();
    if( status == 1){
       ui->label_6->setText("已连接");
       status = 1;
       unsigned char data[9] = {0,0xef,2,3,4,5,6,7,0xab};
       qDebug() << "foc hid device connect";
       foc_hid.usb_hid_write(data);
       qDebug() << "foc hid device connect";
    }
    else{
        foc_hid_scan_time+=1;
        if( foc_hid_scan_time == 7)
            foc_hid_scan_time = 0;
        QString dd;
        if( foc_hid_scan_time == 1)  dd =      ".     ";
        else if( foc_hid_scan_time == 2)  dd = "..    ";
        else if( foc_hid_scan_time == 3)  dd = "...   ";
        else if( foc_hid_scan_time == 4)  dd = "....  ";
        else if( foc_hid_scan_time == 5)  dd = "..... ";
        else dd = "......";

        ui->label_6->setText("连接中" + dd);
        status = 0;
        qDebug() << "foc hid device not connect";
    }
}

//接收HID发送过来的信息
void Widget::recvHID_Data(QVector<unsigned char> data){
    qDebug() << data;
}
