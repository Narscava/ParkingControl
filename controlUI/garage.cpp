//
// Created by Seayn on 2019/3/18.
//

#include "garage.h"
Garage::~Garage()
{
    //std::cout<<"garage "<<garageId<<" executed destructors"<<std::endl;
}
Garage::Garage()
{    
    garageId=-1;
}
//车库构造函数
Garage::Garage(double startLo_, double startLa_, double startDirection_, double lo_, double la_, double direction_,
               int garageId_)
{
    startLa=startLa_;
    startLo=startLo_;
    startDirection=startDirection_;
    la=la_;
    lo=lo_;
    inDirection=direction_;
    garageId=garageId_;
}
//用于更新车库信息
void Garage::setInfo(double startLo_, double startLa_, double startDirection_, double la_, double lo_, double direction_)
{
    startLa=startLa_;
    startLo=startLo_;
    startDirection=startDirection_;
    la=la_;
    lo=lo_;
    inDirection=direction_;
}
//用于更新车库信息,重载版本
void Garage::setInfo(double startLo_, double startLa_, double startDirection_, double la_, double lo_, double direction_,
                     int garageId_)
{
    startLa=startLa_;
    startLo=startLo_;
    startDirection=startDirection_;
    la=la_;
    lo=lo_;
    inDirection=direction_;
    garageId=garageId_;
}

void Garage::setEntrance(double LLa_, double LLo_, double RLa_, double RLo_)
{
    LLa=LLa_;
    LLo=LLo_;
    RLa=RLa_;
    RLo=RLo_;
}
void Garage::leftIn()
{
    inTrail=0;
}
void Garage::rightIn()
{
    inTrail=1;
}

void Garage::setInTrail(int a)
{
    inTrail=a;
}
