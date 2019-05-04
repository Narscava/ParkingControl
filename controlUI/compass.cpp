//
// Created by Seayn on 2019/3/12.
//
#include "compass.h"
#include "controlEmulator.h"
#include "carEmulate.h"

//CompassEmulator部分
volatile double CompassEmulator::direction=-90;
volatile int CompassEmulator::dirTag=1;
volatile double Compass::direction=-90;
std::thread CompassEmulator::dirThread;
CompassEmulator::CompassEmulator()
{

}
CompassEmulator::~CompassEmulator()
{

}
void CompassEmulator::dirThreadEmulate()
{
    using namespace std;


    auto lambdaDir=[]()->void
    {
        double dir=direction;

        while(dirTag)
        {


            double dis=ControlEmulator::velocity*0.1;//0.1秒内运动的距离
            double rad;
            if(Car::r==0)
            {
                rad=-1;
                continue;
            }
            else
            {
                 rad=dis/Car::r;//转向弧度值
            }

            using namespace std;
            //std::cout.precision(20);
            //std::cout<<"vel="<<ControlEmulator::velocity<<std::endl;
           // cout<<"dis="<<dis<<endl;
              //cout<<"r="<<Car::r<<endl;
            //根据挡位以及转向角度确定方向偏离位置
            //分为左打前，左打后，右打前，右打后
           // cout<<dis<<" "<<" "<<Car::r<<rad<<endl;
            //TODO:修BUG
            switch((ControlEmulator::turn<0)^(ControlEmulator::gearTag==1))
            {
                //车辆向右偏转
                case true:
                {
                    //cout<<"R with dir : "<<dir<<endl;

                    dir=dir+rad*180.0/3.1415926535;
                    //cout<<"R with dir 2 : "<<dir<<endl;
                    if(dir>=360.0||dir<=-360.0)
                    {
                        dir-=360.0;
                        break;
                    }
                    break;
                }
                //车辆向左偏转
                case false:
                {
                    //cout<<"L with dir : "<<dir<<endl;

                    dir=dir-rad*180.0/3.1415926535;
                    //cout<<"L with dir 2 : "<<dir<<endl;
                    if(dir<=-360.0||dir>=360.0)
                    {
                        dir+=360.0;
                        break;
                    }
                    break;

                }
                default:dir=0.0;
            }

            direction=dir;
            _sleep(100);
        }

    };
    dirThread =std::thread(lambdaDir);
    dirThread.detach();
}
//需添加更多实现
double CompassEmulator::getDirection()
{
    return 0.0;
}

//Compass部分
Compass::Compass()
{
    compassEmulator=CompassEmulator();
    compassId=-1;
}


Compass::Compass(int compassId_)
{
    compassId=compassId_;
    //获取到指南针的信号输入
    compassEmulator=CompassEmulator();
}

Compass::~Compass()
{

}

double Compass::updateDirection()
{
    direction=compassEmulator.getDirection();
    return direction;
}

