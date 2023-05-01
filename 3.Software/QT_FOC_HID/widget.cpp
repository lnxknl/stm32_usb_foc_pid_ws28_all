#include "widget.h"
#include "ui_widget.h"
#include<QComboBox>
#include<QPushButton>
#include<QRadioButton>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("ValentineHP");
    charInit();
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(page_switch(int)));

    foc_hid_scan_timer.start(500);

    connect(&foc_hid_scan_timer,&QTimer::timeout,this,&Widget::foc_hid_scan);


    connect(&foc_hid,&Foc_Hid::recvReady,this,&Widget::recvHID_Data);


    connect(ui->radioButton,&QRadioButton::clicked,this,&Widget::open_loop_para_direct_send);

    //按键
    connect(ui->pushButton,&QPushButton::clicked,this,&Widget::common_para_Uq_send);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&Widget::common_para_Ud_send);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&Widget::common_para_Speed_send);


    //发送角度环角度
    connect(ui->pushButton_4,&QPushButton::clicked,this,&Widget::position_para_Angle_send);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::foc_write(char *data){
    unsigned char datas[9];
    datas[0] = 0x01;
    for(int i = 1 ;i < 9;i++)
        datas[i] = data[i-1];
    foc_hid.usb_hid_write(datas);
}
void Widget::charInit(){
    charView = new QChartView(ui->widget);

    chart = new QChart();
   // chart->setTitle("波形显示");
    charView->setChart(chart);

    series0 = new QSplineSeries;
    series1 = new QSplineSeries;

    series0->setName("波形1");
    series1->setName("波形2");


    chart->addSeries(series0);
    chart->addSeries(series1);


    int cnt=100;
    for(int i=0;i<cnt;i++)
    {
        seriers0_data.append(0);
        seriers1_data.append(0);
        series0->append(i,0);
        series1->append(i,0);
    }

    axisX = new QValueAxis;
    axisX->setRange(0,100);
   // axisX->setTitleText("time(secs)");

    axisY = new QValueAxis;
    axisY->setRange(-5,5);
   // axisY->setTitleText("value");

    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);

    series0->attachAxis(axisX);
    series0->attachAxis(axisY);
    series1->attachAxis(axisX);
    series1->attachAxis(axisY);
    charView->setRenderHint(QPainter::Antialiasing);//防止图形走样


    charView->resize(400,320);

}

//界面切换
void Widget::page_switch(int index){
    ui->stackedWidget->setCurrentIndex(index);

    char data[8];
    data[0] = Communication_head;
    data[1] = 0x12;
    data[2] = 0x20;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    data[6] = 0;
    data[7] = Communication_tail;
    if(ui->comboBox->currentText() == "空闲"){
        data[6] = 0;
        foc_write(data);
    }
    else if( ui->comboBox->currentText() == "开环控制" ){
        data[6] = 1;
        foc_write(data);
    }
    else if( ui->comboBox->currentText() == "位置控制" ){
        data[6] = 2;
        foc_write(data);
    }
    else if( ui->comboBox->currentText() == "力矩控制" ){
        data[6] = 3;
        foc_write(data);
    }
    else if( ui->comboBox->currentText() == "速度控制" ){
        data[6] = 4;
        foc_write(data);
    }
    else if( ui->comboBox->currentText() == "HID键盘控制" ){
        data[6] = 5;
        foc_write(data);
    }
}

//扫描foc hid 设备
void Widget::foc_hid_scan(){


    static int foc_hid_scan_time = 1;
    bool status = foc_hid.scan_foc_connect();//foc_hid.scan_foc_connect();
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


void Widget::updateSeries0(float data){
    seriers0_data.pop_front();
    seriers0_data.append(data);
    series0->clear();
    for(int i=0;i<100;i +=1)
    {
        series0->append(i,seriers0_data[i]);
    }
}
void Widget::updateSeries1(float data){
    seriers1_data.pop_front();
    seriers1_data.append(data);
    series1->clear();
    for(int i=0;i<100;i +=1)
    {
        series1->append(i,seriers1_data[i]);
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
        updateSeries0(fdata.a);
        ui->doubleSpinBox_6->setValue(fdata.a);
    }
    //设置角度
    else if(data.at(1) == 0x2d){
        //updateSeries0(fdata.a);
        ui->openglwidget->set_new_angle(fdata.a);
        ui->spinBox->setValue(fdata.a);
    }
    //设置电流Iq
    else if( data.at(1) == 0x2e){
       // updateSeries0(fdata.a);
        ui->doubleSpinBox_10->setValue(fdata.a);
    }
     //设置电流Id
    else if( data.at(1) == 0x2f){
        //updateSeries1(fdata.a);
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
    char data[8];

    data[0] = Communication_head;
    data[1] = 0x12;
    data[2] = 0x2a;
    data[3] = fdata.b[0];
    data[4] = fdata.b[1];
    data[5] = fdata.b[2];
    data[6] = fdata.b[3];
    data[7] = Communication_tail;
    foc_write(data);
}

void Widget::common_para_Ud_send(){
    float_uchar_Data fdata;
    fdata.a = ui->doubleSpinBox_8->value();
    char data[8];

    data[0] = Communication_head;
    data[1] = 0x12;
    data[2] = 0x2b;
    data[3] = fdata.b[0];
    data[4] = fdata.b[1];
    data[5] = fdata.b[2];
    data[6] = fdata.b[3];
    data[7] = Communication_tail;
    foc_write(data);
}
void Widget::common_para_Speed_send(){
    float_uchar_Data fdata;
    fdata.a = ui->doubleSpinBox_9->value();
    char data[8];

    data[0] = Communication_head;
    data[1] = 0x12;
    data[2] = 0x2c;
    data[3] = fdata.b[0];
    data[4] = fdata.b[1];
    data[5] = fdata.b[2];
    data[6] = fdata.b[3];
    data[7] = Communication_tail;
    foc_write(data);
}


void Widget::open_loop_para_direct_send(bool en){
    char data[9];

    data[0] = Communication_head;
    data[1] = 0x32;
    data[2] = 0x1a;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    data[6] = en;
    data[7] = Communication_tail;
    foc_write(data);
}
void Widget::position_para_Angle_send(){
    uint16_t angle = (uint16_t)ui->spinBox_2->value();

    char data[8];

    data[0] = Communication_head;
    data[1] = 0x22;
    data[2] = 0x1a;
    data[3] = 0;
    data[4] = 0;
    data[5] = (angle >> 8) & 0xff;
    data[6] =  angle  & 0xff;
    data[7] = Communication_tail;

    foc_write(data);
}





