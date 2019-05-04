#ifndef CONTROLORDERINTERFACE_H
#define CONTROLORDERINTERFACE_H

#define CONTROLORDER_MAX_SPEED 32767
#define CONTROLORDER_ZERO_SPEED 0
#define CONTROLORDER_MIN_SPEED -32768
#define CONTROLORDER_MAX_TURN_RANGE 32767
#define CONTROLORDER_MIN_TURN_RANGE -32768
#define CONTROLORDER_GEAR_ZERO 0
#define CONTROLORDER_GEAR_FORWARD 1
#define CONTROLORDER_GEAR_BACKWARD 2
#define CONTROLORDER_LIGHT_ALL_OFF 0
#define CONTROLORDER_LIGHT_RIGHT_ON 1
#define CONTROLORDER_LIGHT_LEFT_ON 2
#define CONTROLORDER_HORN_OFF 0
#define CONTROLORDER_HORN_ON 1

#include "LargeCarCO.h"
#include "TinyCarCO.h"
#include "GpsInfo.h"
#include<QObject>
/**
 * @brief The ControlOrder class
 * control order to control auto car
 * can transfer to bigCarOrder Cor smallCalOrder's order
 */
class ControlOrder
{
private:
    /**
     * @brief speed
     * range from -32768 to 32767
     */
    qint16 speed=0;
    /**
     * @brief turnRange
     * range from -32768 to 32767
     */
    qint16 turnRange=0;
    qint16 lastTurnRange=0;
    /**
     * @brief gear
     * range :0空挡，1前进挡，2后退档
     */
    qint8 gear=0;
    /**
     * @brief lightSignal
     * range:0关闭所有灯光，1右转向灯亮，2左转向灯亮
     */
    qint8 lightSignal=0;
    /**
     * @brief horn 鸣笛
     * range: 0静音 1鸣笛
     */
    qint8 horn=0;

    GpsInfo gpsInfo;
public:
    ControlOrder(){}
    ~ControlOrder(){}
    /*
        加速范围（-32768,32767）仅代表程度，不表示具体加速度。-32768表示最大刹车的加速度，32767最大加速
    */
    ControlOrder& setSpeed(int);
    /*
        转向范围（-32768，32767）负代表左转，正代表右转。数值仅表示程度
    */
    ControlOrder& setTurnRange(int);
    ControlOrder& setLastTurnRange(int);
    /*
        三种挡位0空挡，1表示前进挡，2表示后退挡
    */
    ControlOrder& setGear(qint8);
    /*
        灯光 0不亮 1右转向灯亮 2左转向灯亮 3应急灯亮
        */
    ControlOrder& setLightSignal(qint8);
    /*
        鸣笛 0静音 1鸣笛
    */
    ControlOrder& setHorn(qint8);
    void setGpsInfo(GpsInfo gps);
    void init();
    qint16 getSpeed() { return speed; }
    qint16 getLastTurnRange() { return lastTurnRange; }
    qint16 getTurnRange() { return turnRange; }
    qint8 getGear() { return gear; }
    qint8 getLightSignal() { return lightSignal; }
    qint8 getHorn() { return horn; }
    GpsInfo getGpsInfo(){return gpsInfo;}
    static void NormalCO2TinyCarCO(ControlOrder&,TinyCarCO&);
    static void NormalCO2LargeCarCO(ControlOrder&,LargeCarCO&);
    static void TinyCarCO2NormalCO(TinyCarCO&,ControlOrder&);
    static void LargeCarCO2NormalCO(LargeCarCO&,ControlOrder&);
    void printInfo();
};
#endif // CONTROLORDERINTERFACE_H
