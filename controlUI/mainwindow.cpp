#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    realTag=false;

//QTui相关初始化
    ui->setupUi(this);
    qtimer=new QTimer(this);
    connect(qtimer,SIGNAL(timeout()),this,SLOT(timeout()));
    qtimer->start(100);
//仿真相关初始化


    using namespace std;

    /**模拟的车库最终定位点与起始定位点横向距离为1.07m，纵向距离为1.3m
     * 初始小车入点面朝方向为以正北方为0度起，逆时针旋转90度（-90度）
     * 最终进入方向为小车面朝方向为以正北方为0度起，旋转0度
     * 车库宽1m，长0.8m，小车全长0.67m，宽0.655m
     * 36度外轮转角情况下其阿克曼转向半径约为0.87m
     */
    //转向采用阿克曼模型而非差速转向模型

    //Garage garage=Garage(103.0,31.0,-90.0,103.0+Tool::getXInLong(1.07,31.0),31.0-Tool::getYInLa(1.3),180.0,1);
    int tag=1;
    Garage garage;
    //左侧倒车进入的车库
    if(tag==0)
    {
        garage=Garage(0,0,-90.0,Tool::getXInLong(1.12,0),Tool::getYInLa(-1.22),0,1);
        garage.leftIn();
        inWay=0;
    }
    //右侧倒车进入的车库
    else if(tag==1)
    {
        garage=Garage(0,0,90.0,Tool::getXInLong(1.12,0),Tool::getYInLa(1.22),-180,1);
        garage.rightIn();
        inWay=1;
    }


    //该维度上1long=;
    //雷达集初始化
        RadarSet radarSet=RadarSet();

        //四个轮子的参数初始化
        Wheel wheel[4];
        wheel[0]=Wheel(Wheel::LFWheel,Tool::getXInLong(-0.2975,31.0),Tool::getYInLa(0.2));
        wheel[1]=Wheel(Wheel::RFWheel,Tool::getXInLong(0.2975,31.0),Tool::getYInLa(0.2));
        wheel[2]=Wheel(Wheel::LBWheel,Tool::getXInLong(-0.2975,31.0),Tool::getYInLa(-0.2));
        wheel[3]=Wheel(Wheel::RBWheel,Tool::getXInLong(0.2975,31.0),Tool::getYInLa(-0.2));


        //四个边缘的参数初始化
        Edge edge[4];

        //视频输入初始化
        VideoJudges videoJudges;

        //Gps初始化
        Gps gps=Gps(wheel);

        Car car=Car(garage,radarSet,wheel,edge,videoJudges,gps);
        car.setCarInfo(0.4,0.595,0.135,0.655,0.595);
        car.compass.compassEmulator.direction=-90;
        //car.updateR(10);
        //cout<<car.r<<endl;


        cout.precision(15);
        //double a=Tool::getDistanceInX(garage.la);
        //double b=Tool::getDistanceInY();
        //cout<<garage.la<<" "<<garage.lo<<" x:"<<a*garage.la<<" y:"<<b*garage.lo<<endl<<" Onelo:"<<a<<" Onela:"<<b<<endl;
        //ControlEmulator controlEmulator=ControlEmulator();

        /*
        controlEmulator.velocity=0;
        controlEmulator.speedUpTag=97;
        controlEmulator.setHornTag=0;
        controlEmulator.signalTag=0;
        //controlEmulator.turnTag=0;//直行
        controlEmulator.gearTag=2;//后退挡
        controlEmulator.turnTag=-32000;//直行
        */

        //TODO:统一线程实现方式
        //controlEmulator.init();
        //controlEmulator.allThreadStart();


        //进行控制的模拟
        car.startEmulation();

        //真实操纵

        //car.radarSet.communication->Rconnect();     //连接雷达
        //car.radarSet.RcheckAlert();
        /*
        realTag=true;
        car.controller.realInit();//命令发送初始化
        car.gps.Rinit();//gps设备初始化
        car.RautoControl();
        */
        //数据更新需要单独开启一个线程去处理


        /*
        int count=0;
        auto lambdaDelay=[&count,&car]()->void

        {

                while(count<10)
                {
                    count++;
                    //cout<<"checkOnce"<<endl;
                    cout<<car.radarSet.communication->distance[0]<<endl;
                    _sleep(200);
                }
        };
        std::thread t=std::thread(lambdaDelay);
        t.detach();
*/
/*
        while(true)
        {

            //cout<<"checkOnce"<<endl;
            cout<<gps.RcheckFirstPoint();
            _sleep(2000);
        }
        */
           //TODO: 修bug
        //car.RautoControl();
        //car.controller.RsetGear(0);
        //car.controller.RsetGear(1);
        //car.controller.RsetGear(2);
        //car.controller.RsetSpeed(0x0280);//实际速度设置为0x07/0xff的程度比较合适
        //car.controller.RsetSpeed(-18000);对小车而言值为负只代表最大减速
        //car.controller.RsetSpeed(12767);
        //car.controller.RsetTurnRange(22132);
        //car.controller.RsetTurnRange(0);

}

void MainWindow::timeout()
{
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    using namespace std;
    QPainter painter(this);
    painter.setPen(QPen(Qt::red,20,Qt::SolidLine,Qt::RoundCap));
    painter.drawPoint(GpsEmulator::x,GpsEmulator::y);


    painter.setPen(QPen(Qt::black,5,Qt::SolidLine,Qt::RoundCap));
    if(inWay==0)
    {
        //左侧倒入的车库的绘制
        painter.drawLine(QPointF(200,450),QPointF(440,450));
        painter.drawLine(QPointF(560,450),QPointF(800,450));

        painter.drawLine(QPointF(440,450),QPointF(440,575));
        painter.drawLine(QPointF(560,450),QPointF(560,575));
        painter.drawLine(QPointF(440,575),QPointF(560,575));

        painter.setPen(QPen(Qt::blue,20,Qt::SolidLine,Qt::RoundCap));
        painter.drawPoint(Tool::getUIX(0,0)+400,Tool::getUIY(0)+400);
        painter.setPen(QPen(Qt::yellow,20,Qt::SolidLine,Qt::RoundCap));
        painter.drawPoint(Tool::getUIX(Tool::getXInLong(1.12,0),0)+400,Tool::getUIY(Tool::getYInLa(-1.22))+400);

    }
    else if(inWay==1)
    {
        //右侧倒入的车库的绘制
        painter.drawLine(QPointF(200,350),QPointF(440,350));
        painter.drawLine(QPointF(560,350),QPointF(800,350));

        painter.drawLine(QPointF(440,350),QPointF(440,225));
        painter.drawLine(QPointF(560,350),QPointF(560,225));
        painter.drawLine(QPointF(440,225),QPointF(560,225));

        painter.setPen(QPen(Qt::blue,20,Qt::SolidLine,Qt::RoundCap));
        painter.drawPoint(Tool::getUIX(0,0)+400,Tool::getUIY(0)+400);
        painter.setPen(QPen(Qt::yellow,20,Qt::SolidLine,Qt::RoundCap));
        painter.drawPoint(Tool::getUIX(Tool::getXInLong(1.12,0),0)+400,Tool::getUIY(Tool::getYInLa(1.22))+400);
    }

    //cout<<Tool::getUIX(Tool::getXInLong(2.0,0),0)+400<<" "<<Tool::getUIY(Tool::getYInLa(-1.6))+400<<endl;
    /*
    for(int i=0;i<ThreadEmulator::count;i++)
    {
        painter.drawPoint(ThreadEmulator::xArr[i],ThreadEmulator::yArr[i]);
    }*/


    /*
    ThreadEmulator threadEmulator=ThreadEmulator();
    threadEmulator.threadOn();
    int i=0;
    while(i<100)
    {
        i++;
        _sleep(50);
        painter.drawPoint(ThreadEmulator::X,ThreadEmulator::Y);
    }
    */

}
