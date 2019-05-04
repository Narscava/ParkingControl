//
// Created by Seayn on 2019/3/26.
//
#include "controlEmulator.h"

ControlEmulator::ControlEmulator() {velocity=0;}
ControlEmulator::~ControlEmulator() {}
volatile double ControlEmulator::velocity;
volatile double ControlEmulator::turn;//当前轮胎转向程度 -32768~32767
volatile int ControlEmulator::speedUpTag;
volatile int ControlEmulator::brakeTag;
volatile int ControlEmulator::setHornTag;
volatile int ControlEmulator::gearTag;

volatile int ControlEmulator::signalTag;
volatile int ControlEmulator::turnTag;
std::thread ControlEmulator::velocityThread;
std::thread ControlEmulator::hornThread;
std::thread ControlEmulator::signalThread;
std::thread ControlEmulator::turnThread;
void ControlEmulator::ThreadSpeedUp()
{
    {

        //当a超出范围时自动终止加速线程
        //速度管理线程
        auto lambdaVelocity=[this]()->void
        {
            //128-speedUpTag=初始加速度
            double bias=-20;//加速度偏置值，用于模拟
           // std::cout<<"aaa"<<std::endl;
            //处于加速状态时
            //当tag=127时视为当前无加速，大于127为刹车，小于127为加速，最大加速为0
            //tag=-1时强行中断当前线程
            while(speedUpTag<256&&speedUpTag>=0)
            {
                velocity+=((double)(127.0-speedUpTag+bias)/100.0);
                if(velocity<0)//速度不可能低于0
                {
                    velocity=0.0;
                }
                _sleep(100);//速度每0.1秒更新一次
                double turnBias=turnTag<0?-(double)turnTag:(double)turnTag;
                //随着速度增加或者方向改变bias的值也会发生改变即摩擦力的改变模拟，最终会达到匀速
                bias=(-10.0-2*velocity)*(1+turnBias/32768.0);
                //std::cout<<"turnBias:"<<turnBias<<std::endl;
            }
        };
        velocityThread=std::thread(lambdaVelocity);
        velocityThread.detach();
      //  velocityThread.detach();
    }
}
void ControlEmulator::ThreadHorn()
{
    auto lambdaHorn=[this]()->void
    {
        //不为这两个值时强行中断线程
        while(setHornTag==0||setHornTag==1)
        {
            if(setHornTag==1)
            {
                for(int i=0;i<5;i++)
                {
               //     std::cout<<"didi"<<std::endl;

                }
                setHornTag=0;//鸣笛后自动停止
                _sleep(100);
            }
            _sleep(100);
        }
    };
    hornThread=std::thread(lambdaHorn);
    hornThread.detach();
}

void ControlEmulator::ThreadSignal()
{
    auto lambdaSignal=[this]()->void
    {
        while(signalTag>=0&&signalTag<=3)
        {
            switch (signalTag)
            {
                case 3:
                {
                    for(int i=0;i<5;i++)
                    {
                     //   std::cout<<"EmergencySignalOn"<<std::endl;
                        _sleep(100);
                    }
                    break;
                }
                case 0:
                {
                    break;
                }
                case 1:
                {
                    for(int i=0;i<5;i++)
                    {
                      //  std::cout<<"RightSignal On"<<std::endl;
                        _sleep(100);
                    }
                    break;
                }
                case 2:
                {
                    for(int i=0;i<5;i++)
                    {
                      //  std::cout<<"LeftSignal On"<<std::endl;
                        _sleep(100);
                    }
                    break;
                }

            }

        }

    };

    signalThread=std::thread(lambdaSignal);
    signalThread.detach();
}

void ControlEmulator::ThreadTurn()
{
    auto lambdaTurn=[this]()->void
    {
        int i=0;
        while(turnTag<=32767&&turnTag>=-32768)
        {
            //采用线性收敛的方式进行简单模拟
            turn=(double)turnTag*0.8+turn*0.20;
            i++;
            if(i==4)
            {
                i=0;
                turn=turnTag;//连续迭代4次后，直接锁定方向
            }
      //    std::cout<<"Turn To:"<<turnTag<<" with value of:"<<turn<<std::endl;
            _sleep(300);
        }
    };
    turnThread=std::thread(lambdaTurn);
    turnThread.detach();
}

void ControlEmulator::emergencyStop()
{
    speedUpTag=255;//最大刹车
    turnTag=0;
    signalTag=3;//应急灯打开
    setHornTag=1;//鸣笛
    gearTag=0;//退回空挡
}
void ControlEmulator::init()
{
    speedUpTag=255;
    setHornTag=0;
    turnTag=0;
    gearTag=0;
    signalTag=0;
}
void ControlEmulator::allThreadStart()
{
    ThreadSignal();
    ThreadHorn();
    ThreadTurn();
    ThreadSpeedUp();
}


