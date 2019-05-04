#ifndef RADAR_H
#define RADAR_H

#include "radarEmulator.h"
class Radar//单个雷达
{
public:
    double distance;//雷达所测出的距离
    double distanceAlert;//报警距离
    int radarId;//当前雷达id

    Radar(int radarId,RadarEmulator radarEmulate1, double distance,double distanceAlert);//由于雷达测量数据以及报警跟在车辆上安装的实际位置相关，在替换为真实雷达输入后有概率需要对此部分进行少量修改
    Radar();
    ~Radar();
    bool Alert();//检测当前距离是否报警，报警返回true

    RadarEmulator radarEmulator;//模拟的雷达输入，之后应在RadarEmulate基础之上实现真实输入
};

#endif // RADAR_H
