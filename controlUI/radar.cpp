#include "radar.h"

//雷达构造函数实现
Radar::Radar(int radarId, RadarEmulator radarEmulate1, double distance, double distanceAlert)
{
    this->radarId=radarId;
    this->radarEmulator=radarEmulate1;
    this->distance=distance;
    this->distanceAlert=distanceAlert;
};
//id为-1代表当前没有雷达
Radar::Radar() {radarId=-1;}

bool Radar::Alert()
{
    return distance <= distanceAlert;
};

Radar::~Radar()
{
   // std::cout<<"radar "<<radarId<<" executed destructors"<<std::endl;
};
