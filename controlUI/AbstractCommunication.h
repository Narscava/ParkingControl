#ifndef ABSTRACTCOMMUNICATION_H
#define ABSTRACTCOMMUNICATION_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
class AbstractCommunication:public QObject
{
public:
    AbstractCommunication(){}
    virtual bool connect()=0;
    virtual void sendMessage(const unsigned char*)=0;
    virtual void receiveMessage()=0;
    virtual bool close()=0;
};

#endif // ABSTRACTCOMMUNICATION_H
