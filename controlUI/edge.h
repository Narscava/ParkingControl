//
// Created by Seayn on 2019/3/11.
//

#ifndef CONTROL_EDGE_H
#define CONTROL_EDGE_H
//车辆边缘计算
class Edge
{
public:
    static const int LFEdge=0,RFEdge=1,LBEdge=2,RBEdge=3;//边缘类型,L=left,R=right,F=front,B=behind
    int type;//范围为0-3,标志边缘类型，作用等同于id,-1代表尚未初始化处理
    double longt;//当前边缘的经度值
    double lat;//当前边缘的维度值

    //轮子坐标修正相关，偏置参数以车辆面向正北方为准进行修正
    double biasLong;//轮子的经度偏置参数
    double biasLa;//轮子的纬度偏置参数
    Edge();
    Edge(int type_,double biasLong_,double biasLa_);
    ~Edge();
    void updateLongAndLaWithBiasValueAndDirection(double direction,double lo_,double la_);//根据当前方向以及偏置参数进行边缘的定位
};



#endif //CONTROL_EDGE_H
