//
// Created by Seayn on 2019/3/21.
//

#ifndef CONTROL_COMMAND_H
#define CONTROL_COMMAND_H
#include "controlEmulator.h"

//实际控制部分接入
#include "ControlOrder.h"
#include "TinyCarCO.h"
#include "TinyCarCommunication.h"
#include "TinyCarSerialPortDialog.h"
class Controller
{
public:
    ControlEmulator controlEmulator;
    Controller();
    ~Controller();

    bool emergenceBraking();//紧急制动
    bool init();//指令完全清除
    bool setSpeed(int a);//加速范围127~0，0代表最大加速
    bool setBrake(int a);//减速范围128~255 255达标最大减速
    bool setTurnRange(int a);//设置转向范围 -32768~32767，正代表右转，最大36度
    bool setGear(int a);//设置挡位，0-空挡，1-前进档，2后退挡
    bool setSignal(int a);//设置转向灯，0-不亮，1-右转向灯亮，2-左转向灯亮，3-应急灯亮
    bool setHorn(int a);//鸣笛0-静音 ，1-鸣笛

    //外观模式部分
    bool setSlowSpeedOnLine();//慢速运行-直线
    bool setSlowSpeedOnCurve();//慢速运行-曲线
    bool setMaxSpeed();
    bool setLeftMaxTurn();//最大左转
    bool setOnLine();//直行
    bool setRightMaxTurn();//最大右转
    bool brake();//刹车
    bool didi();//鸣笛
    bool didiOn();//开始鸣笛
    bool didiOff();//取消鸣笛

    bool leftSignal();//左转向灯亮
    bool rightSignal();//右转向灯亮
    bool emergenceSignal();//应急灯亮
    bool signalOff();//关闭信号灯

    bool goUpWard();//前进挡
    bool emptyGear();//空挡
    bool goBackWard();//倒退档

    //真实设备接入部分,以开头的R进行标志

    ControlOrder *controlOrder;
    TinyCarCO *tinyCarCO;
    TinyCarCommunication *tinyCarCommunication;

    void realInit();//接入真实设备相关的初始化操作

    bool RsetSpeed(int a);//注意，这个范围是-32768~32767
    bool RsetTurnRange(int a);
    bool RsetGear(int a);
private:
    bool realTag;//是否启用真实设备



};

#endif //CONTROL_COMMAND_H
