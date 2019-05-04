#ifndef GPSSERIALPORT_H
#define GPSSERIALPORT_H

#include "RingBuffer.h"
#include "GpsBufferWriteThread.h"
#include "GpsBufferReadThread.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <iostream>
#include <QDebug>
class GPSSerialPortCommunication:public QObject
{
    Q_OBJECT
signals:
    void serialPort1ContentChanged(const QString&);
    void serialPort2ContentChanged(const QString&);
    void serialPort3ContentChanged(const QString&);

public slots:
    void serialPort1ContentUpdate(const QString&);
    void serialPort2ContentUpdate(const QString&);
    void serialPort3ContentUpdate(const QString&);

public:
    GPSSerialPortCommunication(GpsRingBuffer *gpsRingBuffer);
    ~GPSSerialPortCommunication();

    //数据存储环形链表
    CharRingBuffer * port1RingBuffer;
    CharRingBuffer * port2RingBuffer;
    CharRingBuffer * port3RingBuffer;

    //串口部分
    QSerialPort* serialPort1;
    QSerialPort* serialPort2;
    QSerialPort* serialPort3;

    //端口号部分
    QString portName1;
    QString portName2;
    QString portName3;

    //波特率部分
    int baudRate1;
    int baudRate2;
    int baudRate3;

    //数据位部分
    QSerialPort::DataBits databits1;
    QSerialPort::DataBits databits2;
    QSerialPort::DataBits databits3;

    //奇偶检验位部分
    QSerialPort::Parity parity1;
    QSerialPort::Parity parity2;
    QSerialPort::Parity parity3;

    //停止位部分
    QSerialPort::StopBits stopBits1;
    QSerialPort::StopBits stopBits2;
    QSerialPort::StopBits stopBits3;

    //流控部分
    QSerialPort::FlowControl flowControl1;
    QSerialPort::FlowControl flowControl2;
    QSerialPort::FlowControl flowControl3;

    GpsBufferWriteThread* GpsBufferWriteThread1;
    GpsBufferWriteThread* GpsBufferWriteThread2;
    GpsBufferWriteThread* GpsBufferWriteThread3;



private:
    void fillSerialPortInfo(QSerialPort* qSerialport,const QString & portName,
                            const int& baudRate,const QSerialPort::DataBits& databits,const QSerialPort::Parity& parity,
                            const QSerialPort::StopBits& stopBits,const QSerialPort::FlowControl &flowcontrol );
    void send(QByteArray,const QSerialPort*);
    void closeSerialPort(QSerialPort*,CharRingBuffer*);
    void readCom(QSerialPort*,CharRingBuffer*);
    bool openSerialPort(QSerialPort*,CharRingBuffer*);//通过槽函数实现，未开启线程


};

#endif // GPSSERIALPORT_H
