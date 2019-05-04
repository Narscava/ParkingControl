//
// Created by Seayn on 2019/3/11.
//

#ifndef CONTROL_COMPASS_H
#define CONTROL_COMPASS_H

#include <iostream>
#include <thread>

//指南针传感器
class CompassEmulator
{
public:
    static volatile double direction;
    CompassEmulator();
    ~CompassEmulator();
    void dirThreadEmulate();
    double getDirection();
    static std::thread dirThread;//方向模拟线程 TODO:实现
    static volatile int dirTag;//线程启动标志
};

class Compass
{
public:
    int compassId;
    static volatile double direction;
    CompassEmulator compassEmulator;
    double updateDirection();//更新并返回当前方向
    Compass();

    Compass(int compassId_);
    ~Compass();

};
#endif //CONTROL_COMPASS_H
