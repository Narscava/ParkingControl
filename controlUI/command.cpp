//
// Created by Seayn on 2019/3/21.
//

#include "command.h"

bool Controller::setSpeed(int a)
{
    ControlEmulator::speedUpTag=a;
    return true;
}
bool Controller::setBrake(int a)
{
    ControlEmulator::brakeTag=a;
    return true;
}
bool Controller::setGear(int a)
{
    ControlEmulator::gearTag=a;
    return true;
}
bool Controller::setHorn(int a)
{
    ControlEmulator::setHornTag=a;
    return true;
}
bool Controller::setSignal(int a)
{
    ControlEmulator::signalTag=a;
    return true;
}
bool Controller::emergenceBraking()
{
    controlEmulator.emergencyStop();
    return true;
}
bool Controller::init()
{
    controlEmulator.init();
    return true;
}
bool Controller::setTurnRange(int a)
{
    ControlEmulator::turnTag=a;
    return true;
}
bool Controller::setSlowSpeedOnLine()
{
    ControlEmulator::speedUpTag=116;
    return true;
}
bool Controller::setSlowSpeedOnCurve()
{
    ControlEmulator::speedUpTag=106;
    return true;
}
bool Controller::setMaxSpeed()
{
    ControlEmulator::speedUpTag=0;
    return true;
}
bool Controller::setLeftMaxTurn()
{
    ControlEmulator::turnTag=-32767;
    return true;
}
bool Controller::setRightMaxTurn()
{
    ControlEmulator::turnTag=32767;
    return true;
}
bool Controller::brake()
{
    ControlEmulator::speedUpTag=255;
    return true;
}
bool Controller::didi()
{
    ControlEmulator::setHornTag=~ControlEmulator::setHornTag;
    return true;
}

bool Controller::goUpWard()
{
    ControlEmulator::gearTag=1;
    return true;
}
bool Controller::emptyGear()
{
    ControlEmulator::gearTag=0;
    return true;
}
bool Controller::goBackWard()
{
    ControlEmulator::gearTag=2;
    return true;
}
bool Controller::setOnLine()
{
    ControlEmulator::turnTag=0;
    return true;
}
bool Controller::leftSignal()
{
    setSignal(2);
    return true;
}
bool Controller::rightSignal()
{
    setSignal(1);
    return true;
}
bool Controller::emergenceSignal()
{
    setSignal(3);
    return true;
}
bool Controller::signalOff()
{
    setSignal(0);
    return true;
}
bool Controller::didiOn()
{
    setHorn(1);
    return true;
}
bool Controller::didiOff()
{
    setHorn(0);
    return true;
}





//真实控制相关部分
bool Controller::RsetSpeed(int a)
{
    controlOrder->setSpeed(a);
    controlOrder->NormalCO2TinyCarCO(*controlOrder,*tinyCarCO);
    tinyCarCommunication->sendMessage(tinyCarCO->getCharOrder());
    return true;
}
bool Controller::RsetGear(int a)
{
    controlOrder->setGear(a);
    controlOrder->NormalCO2TinyCarCO(*controlOrder,*tinyCarCO);    
    tinyCarCommunication->sendMessage(tinyCarCO->getCharOrder());
    return true;
}
bool Controller::RsetTurnRange(int a)
{
    controlOrder->setTurnRange(a);
    controlOrder->NormalCO2TinyCarCO(*controlOrder,*tinyCarCO);
    tinyCarCommunication->sendMessage(tinyCarCO->getCharOrder());
    return true;
}


//初始化相关部分
Controller::Controller()
{
    controlEmulator=ControlEmulator();
    realTag=false;
}
Controller::~Controller()
{


    if(realTag==true)
    {
        delete controlOrder;
        delete tinyCarCO;
        delete tinyCarCommunication;//warning:同样不能进行delete
    }
}

void Controller::realInit()
{
    realTag=true;
    controlOrder =new ControlOrder();
    controlOrder->init();
    tinyCarCO=new TinyCarCO();
    tinyCarCO->init();
    tinyCarCommunication=new TinyCarCommunication();
    tinyCarCommunication->connect();
}
