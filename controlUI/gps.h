//
// Created by Seayn on 2019/3/13.
//

#ifndef CONTROL_GPS_H
#define CONTROL_GPS_H


#include <thread>
#include <cmath>
#include <iostream>
#include "tool.h"
#include "controlEmulator.h"
#include "compass.h"
#include "wheel.h"

#include "SerialPortDialog.h"

class GpsEmulator
{
public:
    ControlEmulator controlEmulator;//汽车控制模拟设备
    Compass compass;//指南针控制模拟设备
    Wheel wheel[4];//四个轮子
    static volatile double longtitude;//经度
    static volatile double latitude;//纬度
    static volatile double height;//高度
    static volatile int gpsThreadTag;//模拟线程开启标志
    static std::thread gpsLocationEmulator;//gps定位模拟线程
    static volatile int x;//UI绘制对应x坐标
    static volatile int y;//UI绘制对应y坐标

    GpsEmulator();
    GpsEmulator(Wheel * wheelIn);
    ~GpsEmulator();
    void ThreadGpsEmulate();//gps模拟线程


};

class Gps//处理并向车辆发送处理后的gps信息的类
{
public:
    double longtitude;//经度
    double latitude;//纬度
    double height;
    int gpsId;//当前gpsId
    SerialPortDialog *serialPortDialog;
    Wheel wheel[4];
    /**
     * @param gpsEmulate 应当获取与gps硬件直接或间接进行数据交互的接口并实现gpsEmulate的功能
     * **/
    GpsEmulator gpsEmulator;//gps数据输入


    double loIn;//车库外第一gps点经度
    double laIn;//车库外第一gps点纬度
    double loFin;//车库最终停止点经度
    double laFin;//车库最终停止点纬度
    double inDir;//进入方向

    Gps();
    Gps(Wheel * wheelIn);
    Gps(int gpsId_);
    ~Gps();
    void updateGps();


    static volatile int RtimeState;//时间控制线程所用标志位,初始为0,-1退出线程，具体含义参见仿真模拟里的stateThread的实现
    static std::thread timeStateThread;
    static volatile int stopTag;

    void RsetGarageInfo(double loIn_,double laIn_,double loFin_,double laFin_,double inDir_);
    bool RcheckFirstPoint();//返回当前gps与第一停止点的距离判定，误差达到厘米至分米级别则视为已到达指定位置
    bool RcheckFinalPoint();//同上，对最终停止点的判定
    bool RcheckDirection();//该函数本应集成至compass类中，但因处理方便暂时放于此处
    bool Rinit();

};


#endif //CONTROL_GPS_H
