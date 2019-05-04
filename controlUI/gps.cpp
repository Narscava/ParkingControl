//
// Created by Seayn on 2019/3/17.
//

#include "gps.h"


volatile double GpsEmulator::longtitude;
volatile double GpsEmulator::latitude;
volatile double GpsEmulator::height;
volatile int GpsEmulator::gpsThreadTag=1;
volatile int GpsEmulator::x=0;
volatile int GpsEmulator::y=0;


std::thread GpsEmulator::gpsLocationEmulator;
std::thread Gps::timeStateThread;
volatile int Gps::stopTag=0;
volatile int Gps::RtimeState;
//GpsEmulate实现
GpsEmulator::GpsEmulator()
{

}
GpsEmulator::GpsEmulator(Wheel *wheelIn)
{
    wheel[0]=wheelIn[0];
    wheel[1]=wheelIn[1];
    wheel[2]=wheelIn[2];
    wheel[3]=wheelIn[3];
}

GpsEmulator::~GpsEmulator()
{

}
//根据指南针方向以及速度与转向方向模拟gps位置的更新
//难点：阿克曼转向几何的模拟
//分为onCurve与onLine两种情况来进行处理，即直行和转向
//需要后轮中心的gps坐标
//应用微积分的思想将离散的速度作为连续值进行计算
//TODO： 需要重构gps定位以及轮子的相对坐标，使得可计算onCurve情况下的坐标变化
/**onCurve与onLine可以通过查看车辆轮子转向角度来决定选择哪种方法
 * onCurve实现
 * 需要中间变量：阿克曼转向半径，车辆中心gps，车辆后轮中心gps偏置值，车辆朝向
 * 这四者用于进行阿克曼转向几何曲线轨迹的建模
 * 需要模拟变量：当前模拟速度（离散），用于计算轨迹上的运动距离并计算出相应角度
 * 最后根据角度和曲线轨迹对gps坐标进行修正，从而完成一次模拟
 */
 /**
  * onLine实现
  * 需要中间变量：车辆中心gps，车辆朝向
  * 需要模拟变量：当前模拟速度（离散）
  */
void GpsEmulator::ThreadGpsEmulate()
{
    using namespace std;
    cout.precision(18);
    //记录初始坐标值对应UIpixel位置

    int startX=Tool::getUIX(longtitude,latitude);
    int startY=Tool::getUIY(latitude);
    auto lambdaGps=[this,startX,startY]()->void
    {
        while(gpsThreadTag)
        {
            int previousTag;//前一状态存储
            //UI坐标
            //TODO:核心数据处理
            //onLine实现
            //均+400是为了让其从屏幕中央开始绘制
            if(ControlEmulator::turn<=20&&ControlEmulator::turn>=-20)
            {

                _sleep(100);
                //cout<<"A-longti:"<<longtitude<<" lati:"<<latitude<<" velocity:"<<ControlEmulator::velocity<<" turn:"<<ControlEmulator::turn<<" dir:"<<CompassEmulator::direction<<endl;

                x=Tool::getUIX(longtitude,latitude)-startX+400;
                y=Tool::getUIY(latitude)-startY+400;
               // cout<<"A-x="<<x<<" y="<<y<<" vel="<<ControlEmulator::velocity<<" turn:"<<ControlEmulator::turn<<" dir:"<<CompassEmulator::direction<<endl;
                double velocity;
                if(ControlEmulator::gearTag==2)
                {
                    velocity=-ControlEmulator::velocity;
                    previousTag=-1;
                }
                else if(ControlEmulator::gearTag==1)
                {
                    velocity=ControlEmulator::velocity;
                    previousTag=1;
                }
                else
                {
                    velocity=previousTag*ControlEmulator::velocity;
                }

                longtitude=Tool::updateOnLineLong(longtitude,latitude,CompassEmulator::direction,velocity);
                latitude=Tool::updateOnLineLati(longtitude,latitude,CompassEmulator::direction,velocity);
            }//onCurve实现
            else if(ControlEmulator::turn>20||ControlEmulator::turn<-20)
            {
                //目前按照离散的直线形式来进行模拟
                _sleep(100);
                //cout<<"B-longti:"<<longtitude<<" lati:"<<latitude<<" velocity:"<<ControlEmulator::velocity<<" turn:"<<ControlEmulator::turn<<" direction:"<<CompassEmulator::direction<<endl;
                x=Tool::getUIX(longtitude,latitude)-startX+400;
                y=Tool::getUIY(latitude)-startY+400;
                //cout<<"B-x="<<x<<" y="<<y<<" vel="<<ControlEmulator::velocity<<" turn:"<<ControlEmulator::turn<<" dir:"<<CompassEmulator::direction<<endl;

                double velocity;
                if(ControlEmulator::gearTag==2)
                {
                    velocity=-ControlEmulator::velocity;
                }
                else if(ControlEmulator::gearTag==1)
                {
                    velocity=ControlEmulator::velocity;
                }
                else
                {
                    velocity=ControlEmulator::velocity;
                }

                longtitude=Tool::updateOnLineLong(longtitude,latitude,CompassEmulator::direction,velocity);
                latitude=Tool::updateOnLineLati(longtitude,latitude,CompassEmulator::direction,velocity);
            }
        }
    };


    gpsLocationEmulator =std::thread(lambdaGps);
    gpsLocationEmulator.detach();


    //gpsLocationEmulator.join();
}






//Gps实现
//构造函数，默认
Gps::Gps()
{
    gpsId=-1;
}
//构造函数，含id
Gps::Gps(int gpsId_)
{
    gpsId=gpsId_;
    gpsEmulator = GpsEmulator();
    serialPortDialog= new SerialPortDialog();
}
Gps::Gps(Wheel *wheelIn)
{
    wheel[0]=wheelIn[0];
    wheel[1]=wheelIn[1];
    wheel[2]=wheelIn[2];
    wheel[3]=wheelIn[3];
    gpsEmulator=GpsEmulator(wheel);
    //serialPortDialog= new SerialPortDialog();
}
//更新gps数据
void Gps::updateGps()
{

    longtitude=gpsEmulator.longtitude;
    latitude=gpsEmulator.latitude;
    height=gpsEmulator.height;
    return;;
}

Gps::~Gps()
{

}

void Gps::RsetGarageInfo(double loIn_, double laIn_, double loFin_, double laFin_,double inDir_)
{
    loIn=loIn_;
    laIn=laIn_;
    loFin=loFin_;
    laFin=laFin_;
    inDir=inDir_;
}


bool Gps::Rinit()
{
    RtimeState=0;
    using namespace std;
    auto RlambdaTimeStateThread=[this]()->void
    {
            /*
            //进入转向并后退的状态
            _sleep(5000);
            RtimeState=2;
            cout<<"mode 2"<<endl;
            _sleep(24000);
            //进入修正方向并后退的状态
            RtimeState=3;
            cout<<"mode 3"<<endl;
            _sleep(10000);
            //进入停止状态
            RtimeState=4;
            cout<<"mode 4"<<endl;
            _sleep(10000);
            cout<<"exit"<<endl;
            RtimeState=-1;*/
            int count=0;
            while(RtimeState!=-1&&RtimeState!=6)
            {
                //cout<<"Time:"<<100*count<<endl;
                if(stopTag==1)
                {
                    _sleep(100);
                    continue;
                }
                _sleep(100);
                count++;
                if(count>=490)
                {
                    RtimeState=-1;
                    cout<<"exit:"<<count*100<<endl;
                    continue;
                }
                if(count>=390)
                {
                    RtimeState=4;
                    cout<<"mode 4:"<<count*100<<endl;
                    continue;
                }
                if(count>=290)
                {
                    RtimeState=3;
                    cout<<"mode 3:"<<count*100<<endl;
                    continue;
                }
                if(count>=50)
                {
                    RtimeState=2;
                    cout<<"mode 2:"<<count*100<<endl;
                    continue;
                }


            }
    };
    timeStateThread=std::thread(RlambdaTimeStateThread);
    timeStateThread.detach();

}
bool Gps::RcheckFirstPoint()
{
    return RtimeState==2?true:false;
}

bool Gps::RcheckDirection()
{
    return RtimeState==3?true:false;
}

bool Gps::RcheckFinalPoint()
{
    return RtimeState==4?true:false;
}

