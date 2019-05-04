#ifndef TYNECOMMUNICATION_H
#define TYNECOMMUNICATION_H

#define TINYCARORDERLENGTH 10
#define FRAMEHEADFIRST 0xFF
#define FRAMEHEADSECOND 0xFE
#include "PreDefinition.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "AbstractCommunication.h"
class TinyCarCommunication:public AbstractCommunication
{
    Q_OBJECT
private:
    QSerialPort* serialPort;
    void initConfig();
    void sendInfo(const unsigned char* info,int len);
    void sendInfo(const QString &info);
    char convertCharToHex(char ch);
    void convertStringToHex(const QString &str, QByteArray &byteData);
public:
    TinyCarCommunication();//波特率
    ~TinyCarCommunication();//波特率
    QString dataBits;//数据位
    QString parity;//奇偶校验位
    QString ptopBit;//设置停止位
    QString flowBit;//流控);
    QSerialPort* getSerialPort();
    bool connect();
    void sendMessage(const unsigned char*);
    void receiveMessage();
    bool close();
    //void setSerialPort(QSerialPort *);
};

#endif // TYNECOMMUNICATION_H
