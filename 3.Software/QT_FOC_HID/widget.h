#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "foc_hid.h"
#include<QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private  slots:
    void page_switch(int index);

    void recvHID_Data(QVector<unsigned char> data);
private  slots:
    void foc_hid_scan();
private:
    Ui::Widget *ui;

    QTimer  foc_hid_scan_timer;
    Foc_Hid foc_hid;
    bool status;  //是否已连接
};
#endif // WIDGET_H
