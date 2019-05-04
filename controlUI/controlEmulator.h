//
// Created by Seayn on 2019/3/21.
//

#ifndef CONTROL_CONTROLEMULATOR_H
#define CONTROL_CONTROLEMULATOR_H

#include <thread>
#include <iostream>

class ControlEmulator
{
public:
    ControlEmulator();
    ~ControlEmulator();
    static volatile double velocity;//当前速度
    static volatile double turn;//当前轮胎转向角度

    //这两个统一在ThreadSpeedUp中进行处理
    static volatile int speedUpTag;//加速指令指示
    static volatile int brakeTag;//刹车指令指示

    static volatile int setHornTag;//鸣笛


    static volatile int gearTag;//设置挡位
    static volatile int signalTag;//转向灯
    static volatile int turnTag;//转向范围

    static std::thread velocityThread;//速度模拟线程
    static std::thread hornThread;//鸣笛模拟线程
    static std::thread signalThread;//转向灯模拟线程
    static std::thread turnThread;//转向模拟线程


    void ThreadSignal();//转向灯管理线程
    void ThreadSpeedUp();//加速管理线程
    void ThreadHorn();//鸣笛管理线程
    void ThreadTurn();//轮胎转向管理线程

    void allThreadStart();//模拟所需全部线程启动
    void emergencyStop();//紧急制动
    void init();
};
#endif //CONTROL_CONTROLEMULATOR_H
