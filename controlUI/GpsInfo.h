#ifndef GPSINFO_H
#define GPSINFO_H
//一海里=1.852公里
#define KNOTS2KPH 1.852
#include<QDebug>
struct GpsInfo
{
    double longitude;//经度
    double latitude;//纬度
    int quality;
    double time;//时分秒
    unsigned long date;//日月年
    double altitude;//高度
    double speed;//速度
    double course;//航向
    //GpsInfo(double lon=0,double lat=0,int quality=0):longitude(lon),latitude(lat),quality(quality){}
    GpsInfo(double lon=0,double lat=0,int quality=0,unsigned long time=0,unsigned date=0,double alt=0,double speed=0,double course=0)
        :longitude(lon),latitude(lat),quality(quality),time(time),date(date),altitude(alt),speed(speed*KNOTS2KPH),course(course) {}
    void printInfo(){
        qDebug()<<toString();
    }
    QString toString(){
        QString content=QObject::tr("%1 %2 %3 %4 %5 %6 %7 %8").arg(longitude,8,'f',10).arg(latitude,8,'f',10).arg(quality).arg(time).arg(date).arg(altitude).arg(speed).arg(course);
        return content;
    }
};
Q_DECLARE_METATYPE(GpsInfo)
#endif // GPSINFO_H
