#ifndef LARGECARCO_H
#define LARGECARCO_H

#define LARGECARCO_MAX_SPEED 0
#define LARGECARCO_MIN_SPEED 127
#define LARGECARCO_MAX_BRAKE 255
#define LARGECARCO_MIN_BRAKE 128
#define LARGECARCO_MAX_TURN_RANGE 32767
#define LARGECARCO_MIN_TURN_RANGE -32768
#define LARGECARCO_GEAR_ZERO 0
#define LARGECARCO_GEAR_FORWARD 1
#define LARGECARCO_GEAR_BACKWARD 2
#define LARGECARCO_LIGHT_ALL_OFF 0
#define LARGECARCO_LIGHT_RIGHT_ON 1
#define LARGECARCO_LIGHT_LEFT_ON 2
#define LARGECARCO_HORN_OFF 0
#define LARGECARCO_HORN_ON 1
#define LARGECARCO_LENGTH 8
#include<QDebug>
class LargeCarCO {
public:
    LargeCarCO();
    ~LargeCarCO();
    /*
    加速范围（127，0）仅代表程度，不表示具体加速度。127表示最小加速度，0最大加速
    */
    LargeCarCO& setSpeed(quint8);
    /*
    减速范围（128，255）仅代表程度，不表示具体加速度。128最小减速度，255最大减速度
    */
    LargeCarCO& setBrake(quint8);
    /*
    转向范围（-32768，32767）负代表左转，正代表右转。数值仅表示程度
    */
    LargeCarCO& setTurnRange(qint16);
    /*
    三种挡位0空挡，1表示前进挡，2表示后退挡
    */
    LargeCarCO& setGear(quint8);
    /*
    灯光 0不亮 1右转向灯亮 2左转向灯亮 3应急灯亮
    */
    LargeCarCO& setSignal(quint8);
    /*
    鸣笛 0静音 1鸣笛
    */
    LargeCarCO& setHorn(quint8);

    /*
    紧急制动，控制指令均归0
    */
    void emergencyBraking();
    /*
    所有的指令初始化到0
    */
    void init();
    quint8 getSpeed() { return speed; }
    qint16 getTurnRange() { return turnRange; }
    quint8 getGear() { return gear; }
    quint8 getSignal() { return signal; }
    quint8 getHorn() { return horn; }
    quint8* getCharOrder();//转化成实际的指令
    void printInfo();

private:
    quint8 speed = 127;//速度，占第0，1字节
    qint16 turnRange = 0;//转向，占第2字节
    quint8 gear = 0;//挡位，占第3字节
    quint8 signal = 0;//灯光,占第四字节
    quint8 horn = 0;//鸣笛，占第五字节
    quint8 charOrder[8] = { 0,0,0x80,0,0,0,0,0 };
};

#endif // LARGECARCO_H
