#include "GpsBufferWriteThread.h"

#include <QDebug>
#include <string.h>
GpsBufferWriteThread::GpsBufferWriteThread(CharRingBuffer* ringBuffer,GpsRingBuffer* gpsRingBuffer, QObject *parent = 0, QString name=tr("")):QThread(parent){
    this->charRingBuffer=ringBuffer;
    this->gpsRingBuffer=gpsRingBuffer;
    this->name=name;
    NewParser = new NmeaPres();
    if (NewParser->NmeaInitParsers() == false){
        qDebug()<<"init nmea parser error";
        delete NewParser;
    }
}
void GpsBufferWriteThread::run(){//将char缓冲区中的数据拼接成gpsInfo类型数据，并存入环形缓冲区
    m_isCanRun = true;
    qDebug()<<name<<"GpsBufferWriteThread has started";
    QString stringBuffer;
    char receive_char;
    while(true){
        if (charRingBuffer->pop(receive_char)) {
            stringBuffer.append(receive_char);
            if (receive_char == 10) {
                std::string gpsData;
                if(haveStartAndIsGGA(stringBuffer)&&NewParser->isValidSentenceChecksum(stringBuffer.toStdString(), gpsData)){
                    NewParser->ParseNmea0183Sentence(gpsData);
                    GlobalGpsStruct globalGps;
                    NewParser->getGpsGlobalStruct(globalGps);
                    gpsRingBuffer->push(GpsInfo(globalGps.fLongitude,globalGps.fLatitude,globalGps.quality,globalGps.ulTime,globalGps.ulDate,globalGps.fAltitude,globalGps.fSpeed,globalGps.fCourse));
                }
                //qDebug()<<stringBuffer;
                stringBuffer.clear();
            }
        }else{
            this->msleep(GPSBUFFERWIRTETHREAD_BOLCKTIME);//阻塞否则cpu占用太高
        }
        QMutexLocker locker(&m_lock);
        if(!m_isCanRun)//在每次循环判断是否可以运行，如果不行就退出循环
        {
            return;
        }else{
            locker.unlock();
        }
    }
}
GpsBufferWriteThread::~GpsBufferWriteThread(){
    qDebug()<<name<<" has been destoried";
    delete NewParser;
}
void GpsBufferWriteThread::stopImmediately()
{
    QMutexLocker locker(&m_lock);
    m_isCanRun = false;
    locker.unlock();
}
bool GpsBufferWriteThread::haveStartAndIsGGA(QString s) {
    if (s.size() < 8) return false;
    QString hex=s.mid(1, 5);
    if (hex.compare("GPGGA")!=0)//todo 为了获取速度需要去掉这一块
        return false;
    for (int i = 0; i<s.size(); i++) {
        if (s[i] == '*') return true;
    }
    return false;
}
