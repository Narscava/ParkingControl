#ifndef RADARSET_H
#define RADARSET_H

#include"radar.h"
#include"tool.h"
#include "communication.h"
#include <thread>
class RadarSet//多个雷达进行处理的集合类
{
public:
    int count;//当前雷达数量
    Radar radarArr[6];//已绑定的雷达
    int radarSetId;//当前雷达集合id
    RadarSet();
    ~RadarSet();
    RadarSet(Radar * radarArr1,int radarSetId);//构造函数，需要存有雷达的数组
    int checkAlert();//检测当前是否有雷达进行报警，如果报警则返回对应雷达,否则返回-1
    static volatile int alertNum;
    static std::thread checkAlertThread;
    Rcommunication *communication;
    int RcheckAlert();

};

#endif // RADARSET_H
