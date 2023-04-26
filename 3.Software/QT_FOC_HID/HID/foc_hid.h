#ifndef FOC_HID_H
#define FOC_HID_H

#include <QObject>
#include <windows.h>
#include "hidapi.h"
#include <QTimer>

#define TXRX_MAXSIZE  8
class Foc_Hid : public QObject
{
    Q_OBJECT
public:
   explicit Foc_Hid(QObject *parent = nullptr);

    bool scan_foc_connect();

    void  usb_hid_write(unsigned char *data);
    void  usb_hid_read();

    char *get_hid_path();
signals:
    void recvReady(QVector<unsigned char> data);
private slots:
    void read_scan();
private:
    char *hid_path = NULL;
    hid_device *handle = NULL;//usb句柄
    QTimer read_time;
    int status;

    QVector<unsigned char> recvData;
    unsigned char recvbuf[TXRX_MAXSIZE+1];
};

#endif // FOC_HID_H
