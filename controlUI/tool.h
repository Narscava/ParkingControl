//
// Created by Seayn on 2019/3/15.
//

#ifndef CONTROL_TOOL_H
#define CONTROL_TOOL_H

#include <cmath>
class Tool
{
public:
    template<typename T>
    static int getArrLen(T & arr)
    {
        return sizeof(arr)/ sizeof(arr[0]);
    }
    //根据经纬度计算出水平距离上1经度对应米数
   static double getDistanceInX(double latitude)
    {
        double averR=6371393;//地球平均半径
        double xDis=averR*cos(latitude*3.141592653589793238/180)/360.0;
        return xDis;
    }
    static double getDistanceInY()
    {
        return 111133.33333333333333333333333333;
    }

    //计算经度差值
    static double getXInLong(double distance, double latitude)
    {
        double temp=getDistanceInX(latitude);
        return distance/temp;
    }
    //计算纬度差值
    static double getYInLa(double distance)
    {
        return distance/111133.33333333333333333333333333;
    }

    //根据偏置值与方向计算相对中心某一特定位置的经纬度
    /**坐标变换公式
     * s =  os = oa + as = x cos(theta) + y sin(theta)
t =  ot = ay – ab = y cos(theta) – x sin(theta)
     * @param biasX
     * @param biasY
     * @param longti
     * @param lati
     * @param dir
     * @return
     */
    static double getLongWith(double biasX,double biasY,double longti,double dir)
    {
        double rad=dir*3.1415926535/180.0;//计算得到弧度值
        double cosA=cos(dir);//余弦值计算
        double sinA=sin(dir);//正弦值计算
        rad=-rad;//变负以代入公式
        longti=longti+biasX*cosA+biasY*sinA;
        return longti;
    }

    static double getLatiWith(double biasX,double biasY,double lati,double dir)
    {
        double rad=dir*3.1415926535/180.0;//计算得到弧度值
        double cosA=cos(dir);//余弦值计算
        double sinA=sin(dir);//正弦值计算
        rad=-rad;//变负以代入公式
        lati=lati+biasY*cosA-biasX*sinA;
        return lati;
    }


    //直线运动模拟，下一gps经度位置计算
    static double updateOnLineLong(double longti,double lati,double dir,double velocity)
    {
        double retLongti=0;
        double rad=dir*3.1415926535/180.0;//计算得到弧度值
        //以0.1秒为单位进行计算
        //0.1秒内移动距离
        double distance=velocity*0.1;
        retLongti=longti+getXInLong(distance*sin(rad),lati);
        return retLongti;
    }
    //直线运动模拟，下一gps纬度位置计算
    static double updateOnLineLati(double longti,double lati,double dir,double velocity)
    {
        double retLati=0;
        double rad=dir*3.1415926535/180.0;//计算得到弧度值
        //以0.1秒为单位进行计算
        //0.1秒内移动距离
        double distance=velocity*0.1;
        retLati=lati+getYInLa(distance*cos(rad));
        return retLati;
    }

    //用于UI展示用的数据处理函数
    /**
     * 为方便进行处理，统一为以放大double值后所得到的int值，并以cm为单位
     * @param longti
     * @param lati
     * @return
     */
    static int getUIX(double longti,double lati)
    {
        //换算成cm，1经度对应cm数
        double tempVar1=getDistanceInX(lati)*100;
        double result=longti*tempVar1;
        return (int)result;
    }
    static int getUIY(double lati)
    {
        double tempVar1=getDistanceInY()*100;
        //由于UI的Y值向下递增，因此这里采取负值
        double result=-tempVar1*lati;

        return (int)result;
    }
    //两点间直线距离计算
    static double getLineDistance(double x,double y)
    {
        double var=pow(x,2)+pow(y,2);
        return sqrt(var);
    }
};


#endif //CONTROL_TOOL_H
