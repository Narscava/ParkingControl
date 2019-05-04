//
// Created by Seayn on 2019/3/12.
//

#ifndef CONTROL_GARAGE_H
#define CONTROL_GARAGE_H
#include <iostream>
class Garage
{
public:
    double startLo;//车库外第一停止点经度
    double startLa;//车库外第一停止点纬度
    double startDirection;//开始点车辆应面对方向
    double la;//最终停放位置纬度
    double lo;//最终停放位置经度
    double inDirection;//车库入口方向
    int garageId;//车库id，默认为-1

    double LLa;//入口左侧纬度
    double LLo;//入口左侧经度
    double RLa;//入口右侧纬度
    double RLo;//入口右侧经度
    Garage(double startLo_,double startLa_,double startDirection_,double lo_ ,double la_, double direction_,int garageId_);
    Garage();
    ~Garage();
    void setEntrance(double LLa_,double LLo_,double RLa_,double RLo_);
    void setInfo(double startLo_, double startLa_, double startDirection_, double la_, double lo_, double direction_);//用于更新车库信息
    void setInfo(double startLo_, double startLa_, double startDirection_, double la_, double lo_, double direction_,
                 int garageId_);//用于更新车库信息,重载版本


    int inTrail;//0-从左侧倒车进入 1-从右侧倒车进入
    void leftIn();
    void rightIn();
private:
    void setInTrail(int a);
};

#endif //CONTROL_GARAGE_H
