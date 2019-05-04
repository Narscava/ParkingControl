//
// Created by Seayn on 2019/3/10.
//
#include "carEmulate.h"

volatile double Car::r=0;
volatile int Car::rUpdateTag=1;
std::thread Car::updateRThread;
std::thread Car::autoControlThread;
std::thread Car::stateCheckThread;
volatile int Car::stateTag=0;
volatile int Car::stateCheckTag=1;
volatile int Car::controlTag=1;

Car::Car()
{
    carId=-1;

}

Car::Car(Garage garage1, RadarSet radarSet1, Wheel *wheelSet, Edge *edgeSet, VideoJudges videoJudges_, Gps gps_)
{

    controller=Controller();
    garage=garage1;
    radarSet=radarSet1;
    for(int i=0;i<Tool::getArrLen(wheelSet)&&i<4;i++)
    {
        wheel[i]=wheelSet[i];
    }
    for(int i=0;i<Tool::getArrLen(edgeSet)&&i<4;i++)
    {
        edge[i]=edgeSet[i];
    }
    videoJudges=videoJudges_;
    gps=gps_;
    gps.RsetGarageInfo(garage.startLo,garage.startLa,garage.lo,garage.la,garage.inDirection);

}

Car::~Car() {}
/**
* 控制线程所在函数，泊车核心
 * 知识共分为四大板块，1.阿克曼转向半径的计算（已实现），2.通过遗传算法实现对路径的规划
 * 3.通过控制算法尝试对路径进行复现 4.差错复位重新进行泊车/强制停车处理
**/
void Car::autoControl()
{
    using namespace std;
    //check if reaches the start point

    //run
    int posTag=0;//确定初始情况下的倒车方向
    if(gps.longtitude<garage.lo)//左侧开始
    {
        posTag-=1;
    } else//右侧开始
    {
        posTag+=1;
    }
    if(gps.latitude>garage.la)//北侧开始
    {
        posTag-=3;
    } else
    {
        posTag+=3;
    }
    //此时posTag=0,程序错误，=-4左北侧起始，=-2右北侧起始，=2左南侧起始，=4右南侧起始
    //左北侧起始情况
    if(-4==posTag)
    {
        //controller.setTurnRange(-32768);
        //controller.setTurnRange(-32768);//最大左转角度
        //TODO:速度控制，方位确定（两个线程）

        //TODO:速度控制，到达位置后紧急刹车（一个线程实现）


    }
    //check if reaches the stop point

    //run
    //控制所用线程（两个，一个用于检测状态，另一个则用于更新指令）

    auto lambdaControl=[this]()->void
    {
            int inTrail=garage.inTrail;

     /*
            controlEmulator.velocity=0;
            controlEmulator.speedUpTag=127;
            controlEmulator.setHornTag=0;
            controlEmulator.signalTag=0;
            //controlEmulator.turnTag=0;//直行
            controlEmulator.gearTag=2;//后退挡
            controlEmulator.turnTag=0;//直行
     */
           //默认从第一停止点开始，即经过倒挡转向→倒挡→刹车的过程完成
            //第一阶段：
            while(controlTag)
            {
                int count1=0;
                boolean tempTag=0;
                switch(stateTag)
                {
                    case 1:
                    {
                        cout<<"mode 1:keep going back"<<endl;
                        controller.goBackWard();
                        controller.setOnLine();
                        controller.setSlowSpeedOnLine();
                        break;
                    }
                    case 2:
                    {

                        cout<<"mode 2:turn and going back with dir:"<<compass.compassEmulator.direction<<" "<<inTrail<<endl;
                        /*
                        controller.setGear(2);//倒挡
                        //TODO:转向逻辑实现
                        controller.setTurnRange(-32000);//左转打死
                        controller.setSpeed(107);//以较慢速度进行倒挡
                        controller.setSignal(0);
                        controller.setHorn(0);
                         */

                        if(count1==0)
                        {
                            count1++;
                            controller.brake();
                        }
                        controller.goBackWard();
                        if(inTrail==0)
                        {
                            controller.setLeftMaxTurn();
                            controller.leftSignal();
                        }else
                        {
                            controller.setRightMaxTurn();
                            controller.rightSignal();
                        }
                        controller.setSlowSpeedOnCurve();
                        controller.didiOff();
                        break;
                    }
                    case 3:
                    {
                        cout<<"mode 3:going back with velocity:"<<controller.controlEmulator.velocity<<" and dir:"<<CompassEmulator::direction<<endl;
                        //controller.setSpeed(255);//第一次进入此处时先强制停下，以防方向偏差
                        /*
                        controller.setTurnRange(0);//方向修正
                        controller.setSpeed(116);//以较慢速度进行倒挡
                        controller.setSignal(0);
                        controller.setHorn(0);
                        */
                        controller.setOnLine();
                        controller.setSlowSpeedOnLine();
                        controller.signalOff();
                        controller.didiOff();
                        break;
                    }
                    case 4:
                    {
                        cout<<"mode 4:stop here"<<endl;
                        /*
                        controller.setSpeed(255);//强制停下



                        //TODO:将刹车后的操作替换为controller.init()
                        controller.setTurnRange(0);//方向修正
                        controller.setSignal(0);//关闭信号灯
                        controller.setHorn(0);//取消鸣笛
                        controller.setGear(0);
                        //存疑：目前没有手刹接口，即刹车要一直维持255状态
                        */
                        controller.emptyGear();
                        controller.brake();
                        controller.setOnLine();
                        controller.signalOff();
                        controller.didiOff();


                        break;
                    }
                    case 5://TODO:越界后调用缓冲的指令cache进行前数个位置的复现
                    {
                        controller.emergenceBraking();
                        break;
                    }
                    case 6:
                    {
                        controller.emergenceBraking();
                        break;
                    }
                    default://不应执行到这里，若执行至此则强制停车
                    {
                        controller.emergenceBraking();
                        break;
                    }

                }
                _sleep(50);
            }


    };



    auto lambdaStateCheck=[this]()->void
    {
        //TODO:使用状态模式的设计方式对此处状态表示的实现进行重构与替换

            stateTag=1;//初始化
            int previousTag;//前一tag的存储，用于保持状态
            int count=0;//状态4刹车计数,若计数完毕仍为4状态，则可确定已停止至定点
            //TODO:修内存BUG
            double templa=garage.la;
            double templo=garage.lo;
            double tempD=garage.inDirection;
            while(stateCheckTag)
            {
                _sleep(50);
                previousTag=stateTag;
                //当位置误差到达分米程度时，则视为已经到达合适位置

                //第一停止点状态检测相关变量
                double valX=Tool::getDistanceInX(gps.gpsEmulator.latitude)*(gps.gpsEmulator.longtitude-garage.startLo);
                double valY=Tool::getDistanceInY()*(gps.gpsEmulator.latitude-garage.startLa);
                double tempX=valX>0?valX:-valX;
                double tempY=valY>0?valY:-valY;

                //方向修正状态检测相关变量
                double valD=compass.compassEmulator.direction-tempD;
                double tempD=valD>0?valD:-valD;
                int tempD2=(int)tempD%360;

                //最终停止点状态检测相关变量
                double valX2=Tool::getDistanceInX(gps.gpsEmulator.latitude)*(gps.gpsEmulator.longtitude-templo);

                double valY2=valY=Tool::getDistanceInY()*(gps.gpsEmulator.latitude-templa);
                double tempX2=valX2>0?valX2:-valX2;
                double tempY2=valY2>0?valY2:-valY2;

                //WARNING:QT随机炸变量debug

                //cout<<Tool::getDistanceInX(0)*templo<<endl;
                //cout<<tempD2<<endl;
                //cout<<"tempX:"<<tempX<<" tempY:"<<tempY<<" tempD2:"<<tempD2<<" tempX2:"<<tempX2<<" tempY2:"<<tempY2<<endl;
                //cout<<Tool::getLineDistance(tempX,tempY)<<" "<<Tool::getLineDistance(tempX2,tempY2)<<endl;
                //cout<<"tempX2:"<<tempX2<<" tempY2:"<<tempY2<<" dis:"<<Tool::getLineDistance(tempX2,tempY2)<<endl;
                //cout<<" valX2:"<<valX2<<" valY2"<<valY2<<endl;              
                //cout<<" la:"<<gps.gpsEmulator.latitude<<" lo:"<<gps.gpsEmulator.longtitude<<" garaLa:"<<templa<<" garalo:"<<templo<<endl;
                //double b=Tool::getDistanceInX(0);
                //double c=b*templo;
                //cout<<templo<<" "<<b<<" "<<c<<endl;

                //Warning: if的逻辑顺序不可随意替换
                //目前实现逻辑：一旦进入4状态后则不可再进行更改
                if(count!=0)
                {
                    //count--;
                    continue;
                }

                if(Tool::getLineDistance(tempX,tempY)<0.1)
                {
                    stateTag=2;//状态进入2，即开始转向并倒车

                    continue;
                }



                if(Tool::getLineDistance(tempX2,tempY2)<0.1)
                {
                    stateTag=4;//状态进入4，即立即准备刹车
                    count=5;
                    continue;
                }

                if(tempD2<3)//方向偏差小于3度
                {

                    //TODO: 添加相应的指令缓冲cache，以防止方向修正过度的情况出现
                    stateTag=3;//状态进入3，开始修正方向与倒车

                    continue;
                }
                //TODO: state=5;即位置越界检查状态的检测以及对应的指令缓冲cache实现
                //状态置为previousTag，即说明车辆运行中且未触发以下任一条件
                stateTag=previousTag;

            }
            //线程结束与退出，相应状态初始化
            stateTag=0;
    };

    stateCheckThread=std::thread(lambdaStateCheck);
    stateCheckThread.detach();
    _sleep(100);
    autoControlThread=std::thread(lambdaControl);
    autoControlThread.detach();
}



//设置车辆本身参数

void Car::setCarInfo(double L_, double b_, double C_, double K_, double M_)
{
    L=L_;
    b=b_;
    C=C_;
    K=K_;
    M=M_;
    //计算中间量并存储
    //中间量(L+C)^2
    double temp1=L+C;
    temp1*=temp1;
    tempVar1=temp1;
    //中间量(K-M)/2
    tempVar2=(K-M)/2.0;
    return;
}
/**
 * 以车身最外点计算的最小转弯半径
 * r=sqrt{(L+C)^2+[l/tanθ +(K-M)/2]^2}
 * 实际转弯半径应再加上车身宽度的一半
 * L—轴距；θmax—转向轮外轮最大转角/转角；b—前轮距；
 * C—前悬长度；K—整车宽度；M—主销中心距
 * @param angel 汽车外轮转向角度
 */
void Car::updateR(double angel) //根据车辆转向角度更新阿克曼转向半径
{//这里应提前计算出转向公式的中间量以进行转化

    double rad=angel*3.1415926535/180.0;//计算得到弧度
    double tanA=tan(rad);
    double temp3=L/tanA;
    double temp4=pow(temp3+tempVar2,2);
    double temp5=tempVar1+temp4;
    r=temp3-K/2;
    //r=sqrt(temp5)+K/2;//note:这里加上了车辆宽度的一半，即这里是以车辆中轴开始计算的半径
    //setCarInfo(0.4,0.595,0.135,0.655,0.595);
    using namespace std;

    //cout<<"L="<<L<<" b="<<b<<" c="<<C<<" k="<<K<<" M="<<M<<" tanA="<<tanA<<endl;

    return;
}
void Car::updateR()
{
    double tempVarTurn=ControlEmulator::turn>0?ControlEmulator::turn:-ControlEmulator::turn;
    double angle=tempVarTurn*36.0/32768.0;
    using namespace std;
    updateR(angle);
}

void Car::updateRThreadFunc()
{

    auto lambdaUpdateR=[this]()->void
    {
        using namespace std;
        boolean tag=1;
        //TODO:排查BUG出现的原因
        //Warning:大概率是qt平台的问题，此处线程进入循环后发生内存泄漏，会强制修改一部分值，暂时使用分支语句进行应急
        while(rUpdateTag)
        {
            _sleep(100);           
            setCarInfo(1.08,0.595,0.135,0.655,0.595);
            updateR();
        }
    };
    updateRThread=std::thread(lambdaUpdateR);
    updateRThread.detach();
}
void Car::checkGPS()
{
    gps.updateGps();//gps更新数据
    //指南针传感器
    //将更新的值传递给四个轮子并进行位置的计算，主要用于转向半径计算以及经纬度更新
    for(int i=0;i<4;i++)
    {
        wheel[i].updateLongAndLaWithBiasValueAndDirection(angle,gps.longtitude,gps.latitude);
    }
    //将更新的值传递给四个边缘以进行碰撞检测计算的数据准备
    for(int i=0;i<4;i++)
    {
        edge[i].updateLongAndLaWithBiasValueAndDirection(angle,gps.longtitude,gps.latitude);
    }
    return;
}


void Car::startEmulation()
{
    controller.controlEmulator.init();
    controller.controlEmulator.allThreadStart();
    updateRThreadFunc();//阿克曼转向半径实时更新线程
    _sleep(100);//等待半径线程开启完毕后再开启方向模拟，否则会产生除0错误
    compass.compassEmulator.dirThreadEmulate();//方向模拟线程
    gps.gpsEmulator.ThreadGpsEmulate();//gps坐标模拟线程
    autoControl();//自动泊车控制线程
}

void Car::RautoControl()
{
    int count=10;
    using namespace std;
    int tag=0;
    int previousTag=0;//该处的previousTag与仿真实现处的tag作用不同，仅用于避障恢复现场使用
    int alertCount=0;
    radarSet.communication=new Rcommunication();
    radarSet.communication->Rconnect();
    while(gps.RtimeState!=-1)
    {

        //当位置误差到达分米程度时，则视为已经到达合适位置
        //状态1，设置初始速度
        radarSet.communication->RAlert();//更新distance值
        if(radarSet.RcheckAlert()!=-1)
        {
            if(tag!=5)
            {
                previousTag=tag;
                tag=5;
                gps.stopTag=1;
            }

            _sleep(200);

            controller.RsetSpeed(-0x7fff);
            controller.RsetGear(0);
            controller.RsetTurnRange(0);

            if(alertCount>45)//18s
            {
                tag=6;
                gps.RtimeState=6;
                gps.stopTag=1;
                cout<<"Sth Goes Wrong, Needs To Check."<<endl;
                continue;
            }
            alertCount++;
            continue;
        }
        else if(tag==5)
        {
            //tag=previousTag;
            gps.stopTag=0;
        }

        if(tag==0)
        {
            tag=1;
            controller.RsetGear(2);
            //setGear尽可能在设置速度之前
            controller.RsetSpeed(0x0680);
        }
        //状态2，开始倒车并附带转向
        if(gps.RcheckFirstPoint()&tag!=2)
        {
            cout<<"mode 2"<<endl;
            if(garage.inTrail==0)//左转倒车
            {
                tag=2;
                controller.RsetGear(2);
                controller.RsetTurnRange(-17000);
                controller.RsetSpeed(0x680);

            }
            else if(garage.inTrail==1)//右转倒车
            {
                tag=2;
                controller.RsetGear(2);
                controller.RsetTurnRange(17000);
                controller.RsetSpeed(0x680);


            }
        }
        //状态3，开始修正方向并进行终点检测
        if(gps.RcheckDirection()&tag!=3)
        {
            cout<<"mode 3"<<endl;
            tag=3;
            controller.RsetGear(2);
            controller.RsetSpeed(0x680);
            controller.RsetTurnRange(0);
        }
        if(count==0)
        {
            break;
        }
        //状态4，到达终点并进行刹车
        if(gps.RcheckFinalPoint()&tag!=4)
        {
            cout<<"mode 4"<<endl;
            tag=4;
            controller.RsetSpeed(-0x7fff);
            controller.RsetGear(0);//这里setgear有不明原因导致的内存泄漏
            controller.RsetTurnRange(0);
            //count--;
        }


        //目前gps处返回的数据单纯的基于时间及速度进行控制，后续应对gps相关进行修改
        _sleep(200);//获取GPS数据速度约为1秒5帧
    }
    controller.RsetGear(0);

    //RcontrolThread=new ControlQthread(nullptr,controller,gps,radarSet,garage);
    //RcontrolThread->start();
}
