#include "widget.h"
#include <QApplication>
#include <windows.h>
#include "hidapi.h"

#include<QDebug>

#include "openglwidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
//    OpenGLWidget w;
//    w.show();
    return a.exec();

}
