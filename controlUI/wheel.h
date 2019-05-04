//
// Created by Seayn on 2019/3/14.
//

#ifndef CONTROL_WHEEL_H
#define CONTROL_WHEEL_H
class Wheel//轮子，分为前轮和后轮共四种
{
public:
    //轮子基本数据记录
    static const int LFWheel=0,RFWheel=1,LBWheel=2,RBWheel=3;//轮子类型,L=left,R=right,F=front,B=behind
    int type;//范围为0-3,标志轮子类型，作用等同于id,-1代表尚未初始化处理
    double longt;//当前轮子的经度值
    double lat;//当前轮子的维度值

    //轮子坐标修正相关，偏置参数以车辆面向正北方为准进行修正
    double biasLong;//轮子的经度偏置参数
    double biasLa;//轮子的维度偏置参数
    Wheel();
    Wheel(int type_,double biasLong_,double biasLa_);
    ~Wheel();
    void updateLongAndLaWithBiasValueAndDirection(double direction,double lo_,double la_);//根据当前方向以及偏置参数进行轮子的定位
};
#endif //CONTROL_WHEEL_H
