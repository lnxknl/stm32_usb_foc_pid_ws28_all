#include "openglwidget.h"
#include <QFile>
#include <QDataStream>
#include <algorithm>
#include <QDebug>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

    loadobj("F:\\Gitee\\STM32G431CBT6\\4008_FOC_HID\\3.Software\\QT_FOC_HID\\model\\motor.obj",m_vPoints);
    angle = 0;
    startTimer(1000 / 60);

}
void OpenGLWidget::timerEvent(QTimerEvent *event)
{
    angle += 1 ;
    if (angle >= 360)
        angle = 0;
    m_model.setToIdentity();
    m_model.rotate(angle, 0,0, 1);
    m_model.scale(1.25);
    repaint();

}

OpenGLWidget::~OpenGLWidget(){

}


void OpenGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.94,0.94,0.94,1);

    m_vao.create();
    m_vbo.create();
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex ,"F:\\Gitee\\STM32G431CBT6\\4008_FOC_HID\\3.Software\\QT_FOC_HID\\OPENGL\\vertex.shader");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,"F:\\Gitee\\STM32G431CBT6\\4008_FOC_HID\\3.Software\\QT_FOC_HID\\OPENGL\\fragment.shader");
    m_program->link();


    m_vao.bind();
    m_vbo.bind();

    m_vbo.allocate(m_vPoints.data(),sizeof (float)*m_vPoints.size());
    m_program->bind();
    m_program->setAttributeBuffer("vPos",GL_FLOAT,0*sizeof (float),3,0);
    m_program->enableAttributeArray("vPos");
    m_program->setAttributeBuffer("vTexture",GL_FLOAT,0*sizeof (float),2,3*sizeof(float));
    m_program->enableAttributeArray("vTexture");

    // 绑定变换矩阵
    m_view.setToIdentity();
    m_view.lookAt(QVector3D(0, -5, 5), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
    m_model.setToIdentity();
    m_model.rotate(90, 0, 0, 0);

    m_texture = new QOpenGLTexture(QImage("F:\\Gitee\\STM32G431CBT6\\4008_FOC_HID\\3.Software\\QT_FOC_HID\\model\\tup.png").mirrored());
    m_program->release();
    m_vbo.release();
}

void OpenGLWidget::resizeGL(int w, int h){
    m_projection.setToIdentity();
    m_projection.perspective(30, (float)w / h, 0.001, 1000);
}

void OpenGLWidget::paintGL(){

glEnable(GL_CULL_FACE);
    m_texture->bind();
    m_vao.bind();
    m_program->bind();


    m_program->setUniformValue("projection", m_projection);
    m_program->setUniformValue("view", m_view);
    m_program->setUniformValue("model", m_model);

    glDrawArrays(GL_TRIANGLES, 0, m_vPoints.size()/3);
    m_vao.release();
    m_texture->release();
    m_program->release();

}



void OpenGLWidget::loadobj(QString fileName, QVector<float>& vPoints){
    if (fileName.mid(fileName.lastIndexOf('.')) != ".obj" && fileName.mid(fileName.lastIndexOf('.')) != ".OBJ")
       {
           qDebug() << "file is not a obj file.";
          return;
       }
       QFile objFile(fileName);
       if (!objFile.open(QIODevice::ReadOnly))
       {
           qDebug() << "open" << fileName << "failed";
           return ;
       }
       else
       {
           qDebug() << "open" << fileName << "success!";
       }
       while (!objFile.atEnd())
       {
           QByteArray lineData = objFile.readLine();

           QList<QByteArray> strValues = lineData.trimmed().split(' ');
           QString dataType = strValues.takeFirst();
           if( dataType == 'v'){
               float x= strValues[0].toFloat() /100.0;
               float y= strValues[1].toFloat() /90.0;
               float z= strValues[2].toFloat() /90.0;

               vPoints.push_back(x -0.2);
               vPoints.push_back(y + 0.3);
               vPoints.push_back(z);
              // qDebug() << x <<  y << z;
           }
        }


}
