#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include<QObject>
#include<QSerialPort>
#include<iostream>
#include<thread>
class Rcommunication:public QObject
{
   Q_OBJECT
public:
    QSerialPort *port;//串口通信
    static volatile int distance[2];//两颗雷达
    ~Rcommunication();
    void Rconnect();
    void RAlert();
private:
    static std::thread updateDistanceThread;
signals:
    void Rread();
private slots:
    void Rreceive();
};

#endif // COMMUNICATION_H
