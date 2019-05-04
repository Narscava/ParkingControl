//
// Created by Seayn on 2019/3/10.
//
#include <thread>
#include <cmath>

#include "tool.h"
#include "control.h"
#include "garage.h"
#include "gps.h"
#include "radarSet.h"
#include "wheel.h"
#include "videoCorrection.h"
#include "compass.h"
#include "edge.h"
#include "command.h"
#include "datastruct.h"
#include "controlQThread.h"
#ifndef CONTROL_CAREMULATE_H
#define CONTROL_CAREMULATE_H

//主要采用装饰者设计模式进行实现
class Car
{
    public:
    //定位部分

            static volatile double r;//阿克曼转向半径
            static volatile int rUpdateTag;//阿克曼转向半径更新标志

            double compassDirection;//指南针指向方向
            Garage garage;//预计要停放的车库
            Gps gps;//车辆本身带有的gps
    //车辆状态部分
            //double velocity;//当前速度
            double angle;//车辆当前轮子方向
            int carId;//车辆id
    //车辆设备部分
            Compass compass;
            RadarSet radarSet;//车辆所载雷达集合
            Wheel wheel[4];//车辆的四个轮子，默认wheel[2]为左后轮，wheel[3]为右后轮
            VideoJudges videoJudges;//视频传输部分
     //边缘碰撞计算部分
            Edge edge[4];
     //车辆本身参数部分
            double L;//轴距 TODO:查找莫名写入该位置的原因
            double b;//前轮距
            double C;//前悬长度
            double K;//整车宽度
            double M;//主销中心距 即主销偏距的一种定义 kingpin offset
            double tempVar1;
            double tempVar2;//用于转向半径计算的临时中间量，在重新设置参数后自动更新

            //命令控制器部分，附带速度管理
            Controller controller;

            //算法核心：指令发送线程
            static std::thread autoControlThread;
            //算法核心：状态检测线程
            static std::thread stateCheckThread;

            //算法核心：状态标志位
            static volatile int stateTag;
            //两个线程的控制标志位
            static volatile int controlTag;
            static volatile int stateCheckTag;
            //算法核心：基于安全考量的指令缓冲存储
            Command commandCache[200];

            //实时更新转向半径的线程
            static std::thread updateRThread;

            ControlQthread* RcontrolThread;
    void autoControl();//实现接受指令并实时与状态进行交互的线程函数
    void updateR(double angel);
    //angel为前轮转向角度，可为负值,根据当前前轮转向角度更新车辆转向的阿克曼转向半径
    void updateR();
    void checkGPS();//用于检测GPS并用于更新四个轮子与边缘的gps
    Car();
    Car(Garage garage1,RadarSet radarSet1,Wheel * wheelSet,
            Edge *edgeSet,VideoJudges videoJudges_,Gps gps_);
    ~Car();
    //发送指令，该函数可能仍需要大量更改
    //设置车辆本身参数
    void updateRThreadFunc();
    // car.setCarInfo(0.4,0.595,0.135,0.655,0.595);
    void setCarInfo(double L_,double b_,double C_,double K_,double M_);

    //进行仿真模拟的所有启动以及初始化工作
    void startEmulation();

    void RautoControl();//真实小车控制函数
private:
    void speedControl();//线程调用函数，用于速度控制
    void checkDirection();//线程调用函数，用于速度控制
    void stopAtPrecisePostion();//线程调用函数，用于精确倒车并停止
};


#endif //CONTROL_CAREMULATE_H
