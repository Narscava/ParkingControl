#include "communication.h"
#include<QDebug>
int volatile Rcommunication::distance[2];

std::thread Rcommunication::updateDistanceThread;
Rcommunication::~Rcommunication()
{
    port->close();
    delete port;
}
void Rcommunication::Rconnect()
{
    using namespace std;
    distance[0]=3000;
    distance[1]=3000;
    port=new QSerialPort();
    port->setPortName("COM4");   
    port->open(QIODevice::ReadWrite);
    if(port->isOpen()==false)
    {
        cout<<"failed to connect Radars"<<endl;
        exit(0);
    }
    port->setBaudRate(9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    cout<<"connect success"<<endl;
    connect(port,SIGNAL(readyRead()),this,SLOT(Rreceive()));

    /*
    auto lambdaReceive=[this]()->void
    {
        connect(this,SIGNAL(Rread()),this,SLOT(Rreceive()));
        while(true)
        {
            if(port->bytesAvailable()>=10)
            {
                emit Rread();
                distance[0]=2000;
            }
            _sleep(50);
        }
    };

    updateDistanceThread=std::thread(lambdaReceive);
    updateDistanceThread.detach();
    */

}

void Rcommunication::RAlert()
{
    connect(this,SIGNAL(Rread()),this,SLOT(Rreceive()));
    port->waitForReadyRead(100);
    if(port->bytesAvailable()>=10)
    {
        emit Rread();
        distance[0]=2000;
    }


}
void Rcommunication::Rreceive()
{
    using namespace std;
    char buffer[11];
    buffer[10]='\0';   
    port->read(buffer,10);
    if((unsigned char)buffer[0]!=0xff||(unsigned char)buffer[1]!=0xfe)
    {
        cout<<"wrong radar data:"<<(unsigned int)buffer[0]<<(unsigned int)buffer[1]<<endl;
        exit(0);
    }
    //qDebug()<<(int)((unsigned char)buffer[3])<<" "<<(int)((unsigned char)buffer[5]);
    //cout<<"radar read success, set value:"<<endl;
    for(int i=0;i<2;i++)
    {
        distance[i]=(int)((unsigned char)buffer[2*i+3]);
        if((unsigned char)buffer[2*i+2]!=0xff)
        {
            distance[i]=256*(int)((unsigned char)buffer[2*i+2])+distance[i];
        }
        //cout<<distance[i]<<" ";
    }
    //cout<<endl;
    //qDebug()<<buffer;
}




