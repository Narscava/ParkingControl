#include "gpsSerialPort.h"
GPSSerialPortCommunication::GPSSerialPortCommunication(GpsRingBuffer *gpsRingBuffer)
{
    using namespace std;
    if(gpsRingBuffer==0)
    {
        gpsRingBuffer=new GpsRingBuffer;
    }
    port1RingBuffer=new CharRingBuffer();
    port2RingBuffer=new CharRingBuffer();
    port3RingBuffer=new CharRingBuffer();

    //开启三个写入ringbuffer的线程
    GpsBufferWriteThread1=new GpsBufferWriteThread(port1RingBuffer,gpsRingBuffer,this,QStringLiteral("GPS 第1路"));
    GpsBufferWriteThread1->start();

    GpsBufferWriteThread2=new GpsBufferWriteThread(port2RingBuffer,gpsRingBuffer,this,QStringLiteral("GPS 第2路"));
    GpsBufferWriteThread2->start();

    GpsBufferWriteThread3=new GpsBufferWriteThread(port3RingBuffer,gpsRingBuffer,this,QStringLiteral("GPS 第3路"));
    GpsBufferWriteThread3->start();

    //第一个串口相关的初始化
    portName1="COM6";
    baudRate1=115200;
    databits1=QSerialPort::Data8;
    parity1=QSerialPort::NoParity;
    stopBits1=QSerialPort::OneStop;
    flowControl1=QSerialPort::NoFlowControl;
    fillSerialPortInfo(serialPort1,portName1,baudRate1,databits1,parity1,stopBits1,flowControl1);

    //第二个串口
    portName2="COM7";
    baudRate2=115200;
    databits2=QSerialPort::Data8;
    parity2=QSerialPort::NoParity;
    stopBits2=QSerialPort::OneStop;
    flowControl2=QSerialPort::NoFlowControl;
    fillSerialPortInfo(serialPort2,portName2,baudRate2,databits2,parity2,stopBits2,flowControl2);

    //第三个串口
    portName3="COM8";
    baudRate3=115200;
    databits3=QSerialPort::Data8;
    parity3=QSerialPort::NoParity;
    stopBits3=QSerialPort::OneStop;
    flowControl3=QSerialPort::NoFlowControl;
    fillSerialPortInfo(serialPort3,portName3,baudRate3,databits3,parity3,stopBits3,flowControl3);
//TODO:修BUG
    connect(this,&GPSSerialPortCommunication::serialPort1ContentChanged,this,&GPSSerialPortCommunication::serialPort1ContentUpdate);
    connect(this,&GPSSerialPortCommunication::serialPort2ContentChanged,this,&GPSSerialPortCommunication::serialPort2ContentUpdate);
    connect(this,&GPSSerialPortCommunication::serialPort3ContentChanged,this,&GPSSerialPortCommunication::serialPort3ContentUpdate);

    //开始开启串口并连接
    if(this->openSerialPort(serialPort1,port1RingBuffer))
    {
        cout<<"port 1 Opened"<<endl;
    }
    else {
        cout<<"port 1 failed to open"<<endl;
    }
    if(this->openSerialPort(serialPort2,port2RingBuffer))
    {
        cout<<"port 2 Opened"<<endl;
    }
    else {
        cout<<"port 2 failed to open"<<endl;
    }
    if(this->openSerialPort(serialPort3,port3RingBuffer))
    {
        cout<<"port 3 Opened"<<endl;
    }
    else {
        cout<<"port 3 failed to open"<<endl;
    }

}
GPSSerialPortCommunication::~GPSSerialPortCommunication()
{
    delete  port1RingBuffer;
    delete  port2RingBuffer;
    delete  port3RingBuffer;
    delete  serialPort1;
    delete  serialPort2;
    delete  serialPort3;
    delete  GpsBufferWriteThread1;
    delete  GpsBufferWriteThread2;
    delete  GpsBufferWriteThread3;

}
void GPSSerialPortCommunication::fillSerialPortInfo(QSerialPort *qSerialport,
                                                    const QString &portName, const int &baudRate,
                                                    const QSerialPort::DataBits &databits, const QSerialPort::Parity &parity,
                                                    const QSerialPort::StopBits &stopBits, const QSerialPort::FlowControl &flowcontrol)
{
    qSerialport->setPortName(portName);
    qSerialport->setBaudRate(baudRate);
    qSerialport->setDataBits(databits);
    qSerialport->setParity(parity);
    qSerialport->setStopBits(stopBits);
    qSerialport->setFlowControl(flowcontrol);
}

bool GPSSerialPortCommunication::openSerialPort(QSerialPort *serialPort, CharRingBuffer *ringBuffer)
{
    if(serialPort->open(QSerialPort::OpenModeFlag::ReadOnly)){
        qDebug()<<serialPort->portName()<<"open success!!";
    }else{
        qDebug()<<serialPort->portName()<<"open fail!!";
        return false;
    }
    disconnect(serialPort,&QSerialPort::readyRead,0,0);
    connect(serialPort,&QSerialPort::readyRead,[this,serialPort,ringBuffer](){
        readCom(serialPort,ringBuffer);
    });
    return true;
}

void GPSSerialPortCommunication::readCom(QSerialPort* serialPort,CharRingBuffer* ringBuffer)
{
    QByteArray temp = serialPort->readAll();
    send(temp,serialPort);
    foreach (char var, temp) {
        ringBuffer->push(var);
    }
}

void GPSSerialPortCommunication::closeSerialPort(QSerialPort* serialPort,CharRingBuffer* ringBuffer){
    if(serialPort->isOpen()){
        serialPort->clear();
        serialPort->close();
        qDebug()<<serialPort->portName()<<"has been closed";
    }
    char temp=NULL;
    while(!ringBuffer->pop(temp)){
        if(temp==NULL)
            break;
    }
}
void GPSSerialPortCommunication::send(QByteArray content,const QSerialPort* serialPort){
    if(serialPort==serialPort1)
        emit serialPort1ContentChanged(content);
    else if(serialPort==serialPort2){
        emit serialPort2ContentChanged(content);
    }else if(serialPort==serialPort3){
        emit serialPort3ContentChanged(content);
    }
}
void GPSSerialPortCommunication::serialPort1ContentUpdate(const QString&)
{

}
void GPSSerialPortCommunication::serialPort2ContentUpdate(const QString&)
{

}
void GPSSerialPortCommunication::serialPort3ContentUpdate(const QString&)
{

}
