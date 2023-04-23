#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

OpenGLWidget::~OpenGLWidget(){

}


void OpenGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3,0.4,0.23,0.2);
}

void OpenGLWidget::resizeGL(int w, int h){

}

void OpenGLWidget::paintGL(){

}
