#ifndef SERIESCOMMUNICATION_H
#define SERIESCOMMUNICATION_H

#include <QObject>
#include<QTimer>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
class SeriesCommunication : public QObject
{
    Q_OBJECT
public:
    explicit SeriesCommunication(QObject *parent = nullptr);

signals:
    void recvReady(QVector<unsigned char>data);
public slots:
    void DataReceived();

public:
    bool scan_foc_seriers_connect();
    void series_foc_write( char *data);
private:
    QTimer time;
    QSerialPort     serial;                            // 定义全局的串口对象（第三步）
};

#endif // SERIESCOMMUNICATION_H
