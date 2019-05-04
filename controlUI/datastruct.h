#ifndef DATASTRUCT_H
#define DATASTRUCT_H
//这里是一些用于存储数据的类的实现

class Command
{
public:
    int state;
    double velocity;//当前速度
    double turn;//当前轮胎转向角度
    //这两个统一在ThreadSpeedUp中进行处理
    int speedUpTag;//加速指令指示
    int brakeTag;//刹车指令指示

    int setHornTag;//鸣笛
    int gearTag;//设置挡位
    int signalTag;//转向灯
    int turnTag;//转向范围
    Command()
    {
        state=-1;
    }
    Command(double velocity_,double turn_,int speedUpTag_,int brakeTag_,int setHornTag_,int gearTag_,int signalTag_,int turnTag_)
    {
        state=0;
        velocity=velocity_;
        turn=turn_;
        speedUpTag=speedUpTag_;
        brakeTag=brakeTag_;
        setHornTag=setHornTag_;
        gearTag=gearTag_;
        signalTag=signalTag_;
        turnTag=turnTag_;
    }

    ~Command()
    {

    }
};
class XYPoint//坐标存储相关
{
public:
    double X;
    double Y;
    XYPoint(double X_,double Y_)
    {
        X=X_;
        Y=Y_;
    }
    ~XYPoint()
    {

    }
};

#endif // DATASTRUCT_H
