#include "controlQThread.h"

ControlQthread::ControlQthread(QObject* parent,Controller &controller_,Gps & gps_,RadarSet &radarSet_,
                               Garage &garage_)
{
    this->controller=&controller_;
    this->gps=&gps_;
    this->radarSet=&radarSet_;
    this->garage=&garage_;


}
void ControlQthread::run()
{
    controller->tinyCarCommunication=new TinyCarCommunication();
    controller->tinyCarCommunication->connect();
    using namespace std;
    int count=10;
    int tag=0;
    int previousTag=0;//该处的previousTag与仿真实现处的tag作用不同，仅用于避障恢复现场使用
    int alertCount=0;
    controller->RsetSpeed(1);



    while(true)
    {
        QMutexLocker locker(&m_threadRunLock);
        controller->controlOrder->setGear(0);
        controller->controlOrder->NormalCO2TinyCarCO(*controller->controlOrder,*controller->tinyCarCO);
        controller->tinyCarCommunication->sendMessage(controller->tinyCarCO->getCharOrder());

    }

    /*
    controller->RsetSpeed(0x7eee);
    QThread::sleep(1);
    controller->RsetSpeed(0x7eee);
    controller->RsetSpeed(0x7eee);
    QThread::sleep(1);
    controller->RsetSpeed(0x7eee);
    QThread::sleep(1);
    controller->RsetSpeed(0x7eee);
    QThread::sleep(1);
    controller->RsetSpeed(0x7eee);
    QThread::sleep(1);
    controller->RsetSpeed(0x7eee);
    controller->RsetSpeed(0x7eee);
    controller->RsetSpeed(0x7eee);
    controller->RsetSpeed(0x7eee);
    controller->RsetSpeed(0x7eee);
    controller->RsetSpeed(0x7eee);
    controller->RsetSpeed(0x7eee);
    _sleep(200);
*/


    controller->tinyCarCommunication->close();
    delete controller->tinyCarCommunication;

}
