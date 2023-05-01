#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "foc_hid.h"
#include<QTimer>
#include<QChart>
#include<QtCharts>
#include<QChartView>
#include<QSplineSeries>
#include<QDateTimeAxis>
#include<QValueAxis>

#include<seriescommunication.h>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


typedef union
{
    float a;
    unsigned char b[4];
}float_uchar_Data;


#define Communication_head  0xef
#define Communication_tail  0xab

#define Common_Parameters   0x14
#define Position_Parameters 0x24
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


    void foc_write(char *data);
    void charInit();
    void updateSeries0(float data);
    void updateSeries1(float data);


    void Common_Parameters_Parsing(QVector<unsigned char> data);
    void Position_Parameters_Parsing(QVector<unsigned char> data);
private  slots:
    void page_switch(int index);

    void recvHID_Data(QVector<unsigned char> data);

private slots:
    void common_para_Uq_send();
    void common_para_Ud_send();
    void common_para_Speed_send();

private slots:
    void open_loop_para_direct_send(bool en);
private slots:
    void position_para_Angle_send();

private  slots:
    void foc_hid_scan();
private:
    Ui::Widget *ui;

    QTimer  foc_hid_scan_timer;
    Foc_Hid foc_hid;
    SeriesCommunication series;
    bool status;  //是否已连接
private:
     QChartView *charView;
     QChart *chart;                           //画布
     QSplineSeries *series0;                     //线
     QSplineSeries *series1;                     //线
     QValueAxis *axisX;                    //轴
     QValueAxis *axisY;
     QVector<float> seriers0_data;
     QVector<float> seriers1_data;


};
#endif // WIDGET_H
