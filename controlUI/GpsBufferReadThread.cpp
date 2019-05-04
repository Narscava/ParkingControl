#include "GpsBufferReadThread.h"
#include <QDebug>
GpsBufferReadThread::GpsBufferReadThread(GpsRingBuffer* gpsRingBuffer,QObject *parent=0):QThread(parent){
    this->gpsRingBuffer=gpsRingBuffer;
}

GpsBufferReadThread::~GpsBufferReadThread(){
    qDebug()<<"GpsBufferReadThread has been destoried";
}

void GpsBufferReadThread::stopImmediately(){
    QMutexLocker locker(&m_lock);
    m_isCanRun = false;
    locker.unlock();
}

void GpsBufferReadThread::run(){
    m_isCanRun=true;
    int i=0;
    GpsInfo gpsInfo;
    while(true){
        if(gpsRingBuffer->pop(gpsInfo)){
            qDebug()<<(++i);
            gpsInfo.printInfo();
        }else{
            this->msleep(GPSBUFFERREADTHREAD_BOLCKTIME);//阻塞否则cpu占用太高
        }
        QMutexLocker locker(&m_lock);
        if(!m_isCanRun)//在每次循环判断是否可以运行，如果不行就退出循环
        {
            return;
        }else{
            locker.unlock();
        }
    }
    qDebug()<<"GpsBufferReadThread has started";
}
