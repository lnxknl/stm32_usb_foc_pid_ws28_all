#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "foc_hid.h"
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

private:
    Ui::Widget *ui;


    Foc_Hid foc_hid;
};
#endif // WIDGET_H
