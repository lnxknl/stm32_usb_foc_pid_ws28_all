#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QMatrix4X4>
#include <QVector2D>
#include <QVector3D>
#include <gl/gl.h>

#include<QTimerEvent>
#include <QTimer>
class OpenGLWidget : public QOpenGLWidget , public QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    void timerEvent(QTimerEvent *event);
    void loadobj(QString fileName, QVector<float>& vPoints);
protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;
signals:

private:
    QVector<float> m_vPoints;
    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;
    QMatrix4x4 m_model;


    QTimer timer;
    float angle = 0;
private:
    QOpenGLShaderProgram *m_program;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer            m_vbo;


    QOpenGLTexture *m_texture;
};

#endif // OPENGLWIDGET_H
