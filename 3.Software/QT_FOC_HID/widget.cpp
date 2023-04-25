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


}

Widget::~Widget()
{
    delete ui;
}


//界面切换
void Widget::page_switch(int index){
    ui->stackedWidget->setCurrentIndex(index);
}
