#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "foc_hid.h"
#include<QTimer>
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


    void Common_Parameters_Parsing(QVector<unsigned char> data);
    void Position_Parameters_Parsing(QVector<unsigned char> data);
private  slots:
    void page_switch(int index);

    void recvHID_Data(QVector<unsigned char> data);

private slots:
    void common_para_Uq_send();
    void common_para_Ud_send();
    void common_para_Speed_send();
private  slots:
    void foc_hid_scan();
private:
    Ui::Widget *ui;

    QTimer  foc_hid_scan_timer;
    Foc_Hid foc_hid;
    bool status;  //是否已连接
};
#endif // WIDGET_H
