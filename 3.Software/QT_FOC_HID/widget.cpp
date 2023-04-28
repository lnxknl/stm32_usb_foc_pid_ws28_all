#include "widget.h"
#include "ui_widget.h"
#include<QComboBox>
#include<QPushButton>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("ValentineHP");
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(page_switch(int)));

    foc_hid_scan_timer.start(500);

    connect(&foc_hid_scan_timer,&QTimer::timeout,this,&Widget::foc_hid_scan);
    connect(&foc_hid,&Foc_Hid::recvReady,this,&Widget::recvHID_Data);


    //按键
    connect(ui->pushButton,&QPushButton::clicked,this,&Widget::common_para_Uq_send);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&Widget::common_para_Ud_send);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&Widget::common_para_Speed_send);
}

Widget::~Widget()
{
    delete ui;
}


//界面切换
void Widget::page_switch(int index){
    ui->stackedWidget->setCurrentIndex(index);

    unsigned char data[9];
    data[0] = 0;
    data[1] = Communication_head;
    data[2] = 0x12;
    data[3] = 0x20;
    data[4] = 0;
    data[5] = 0;
    data[6] = 0;
    data[7] = 0;
    data[8] = Communication_tail;
    if(ui->comboBox->currentText() == "空闲"){
        data[7] = 0;
        foc_hid.usb_hid_write(data);
    }
    else if( ui->comboBox->currentText() == "开环控制" ){
        data[7] = 1;
        foc_hid.usb_hid_write(data);
    }
    else if( ui->comboBox->currentText() == "位置控制" ){
        data[7] = 2;
        foc_hid.usb_hid_write(data);
    }
    else if( ui->comboBox->currentText() == "力矩控制" ){
        data[7] = 3;
        foc_hid.usb_hid_write(data);
    }
    else if( ui->comboBox->currentText() == "HID键盘控制" ){
        data[7] = 4;
        foc_hid.usb_hid_write(data);
    }
}


//扫描foc hid 设备
void Widget::foc_hid_scan(){
    static int foc_hid_scan_time = 1;
    bool status = foc_hid.scan_foc_connect();
    if( status == 1){
       ui->label_6->setText("已连接");
       status = 1;
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

    if( data.at(0) == Common_Parameters){
        Common_Parameters_Parsing(data);
    }
    else if( data.at(0) == Position_Parameters){
        Position_Parameters_Parsing(data);
    }
}


//公共参数接收，解析
void Widget::Common_Parameters_Parsing(QVector<unsigned char> data){
    float_uchar_Data fdata;

    fdata.b[0] = data.at(2);
    fdata.b[1] = data.at(3);
    fdata.b[2] = data.at(4);
    fdata.b[3] = data.at(5);

    //设置Uq
    if( data.at(1) == 0x2a){
        ui->doubleSpinBox_4->setValue(fdata.a);
    }
    //设置Ud
    else if( data.at(1) == 0x2b){
        ui->doubleSpinBox_5->setValue(fdata.a);
    }
    //设置速度
    else if(data.at(1) == 0x2c){
        ui->doubleSpinBox_6->setValue(fdata.a);
    }
    //设置角度
    else if(data.at(1) == 0x2d){
        uint16_t angle = (data.at(4) << 8) + data.at(5);
        ui->spinBox->setValue(angle);
    }
    //设置电流Iq
    else if( data.at(1) == 0x2e){
        ui->doubleSpinBox_10->setValue(fdata.a);
    }
     //设置电流Id
    else if( data.at(1) == 0x2f){
        ui->doubleSpinBox_11->setValue(fdata.a);
    }
}






void Widget::Position_Parameters_Parsing(QVector<unsigned char> data){
    float_uchar_Data fdata;

    fdata.b[0] = data.at(2);
    fdata.b[1] = data.at(3);
    fdata.b[2] = data.at(4);
    fdata.b[3] = data.at(5);

    if( data.at(1) == 0x1b){
        ui->doubleSpinBox_12->setValue(fdata.a);
    }
    else if( data.at(1) == 0x1c){
        ui->doubleSpinBox_13->setValue(fdata.a);
    }
    else if( data.at(1) == 0x1d){
        ui->doubleSpinBox_14->setValue(fdata.a);
    }
}











void Widget::common_para_Uq_send(){
    float_uchar_Data fdata;
    fdata.a = ui->doubleSpinBox_7->value();
    unsigned char data[9];

    data[0] = 0;
    data[1] = Communication_head;
    data[2] = 0x12;
    data[3] = 0x2a;
    data[4] = fdata.b[0];
    data[5] = fdata.b[1];
    data[6] = fdata.b[2];
    data[7] = fdata.b[3];
    data[8] = Communication_tail;
    foc_hid.usb_hid_write(data);
}

void Widget::common_para_Ud_send(){
    float_uchar_Data fdata;
    fdata.a = ui->doubleSpinBox_8->value();
    unsigned char data[9];

    data[0] = 0;
    data[1] = Communication_head;
    data[2] = 0x12;
    data[3] = 0x2b;
    data[4] = fdata.b[0];
    data[5] = fdata.b[1];
    data[6] = fdata.b[2];
    data[7] = fdata.b[3];
    data[8] = Communication_tail;
    foc_hid.usb_hid_write(data);
}
void Widget::common_para_Speed_send(){
    float_uchar_Data fdata;
    fdata.a = ui->doubleSpinBox_9->value();
    unsigned char data[9];

    data[0] = 0;
    data[1] = Communication_head;
    data[2] = 0x12;
    data[3] = 0x2c;
    data[4] = fdata.b[0];
    data[5] = fdata.b[1];
    data[6] = fdata.b[2];
    data[7] = fdata.b[3];
    data[8] = Communication_tail;
    foc_hid.usb_hid_write(data);
}





