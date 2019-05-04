#include "radarSet.h"
#include<QDebug>
#include<iostream>
volatile int RadarSet::alertNum=-2;
std::thread RadarSet::checkAlertThread;
RadarSet::RadarSet()
{
    radarSetId=-1;
    communication=new Rcommunication();
}

RadarSet::RadarSet(Radar *radarArr1, int radarSetId)
{
    count=0;
    count=Tool::getArrLen(radarArr1);
    for(int i=0;i<count;i++)
    {
        radarArr[i]=radarArr1[i];
    }
    communication=new Rcommunication();
}

RadarSet::~RadarSet()
{
    //TODO:检查这里delete指针会导致崩溃的原因
    //大概率是由于继承自QOBject的Rcommunication在父对象QMainWindow析构时自动析构，如果这里提前delete
    //将导致QMainWindow析构NULL指针导致程序崩溃
    /*
    if(communication!=nullptr)
    {
        delete communication;
    }
        */
};

int RadarSet::checkAlert()
{
    for(int i=0;i<count;i++)
    {
        if(radarArr[i].Alert())
        {
            return i;
        }
    }
    return -1;
}
int RadarSet::RcheckAlert()
{
    using namespace std;

    /*qDebug()<<"exe to here";
    auto lambdaCheckAlert=[this]()->void
    {

            int count=0;
            while(true)
            {
                for(int i=0;i<Tool::getArrLen(communication->distance);i++)
                {
                    if(communication->distance[i]<40)//距离小于40cm时报警
                    {
                        //qDebug()<<"Radar:"<<i<<" Alerts:"<<communication->distance[i];
                        alertNum=i;
                    }
                    //cout<<"dis:"<<communication->distance[i]<<" ";
                }
                //cout<<endl;

                count++;
            }
    };
    checkAlertThread=std::thread(lambdaCheckAlert);
    checkAlertThread.detach();
    */
    alertNum=-1;
    for(int i=0;i<Tool::getArrLen(communication->distance);i++)
    {
        if(communication->distance[i]<40)//距离小于40cm时报警
        {
            //qDebug()<<"Radar:"<<i<<" Alerts:"<<communication->distance[i];
            alertNum=i;
        }
        //cout<<"dis:"<<communication->distance[i]<<" ";
    }
    return alertNum;
}

