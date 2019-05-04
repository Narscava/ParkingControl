#include "LargeCarCO.h"

LargeCarCO::LargeCarCO() {}
LargeCarCO::~LargeCarCO(){}
LargeCarCO& LargeCarCO::setTurnRange(qint16 turnRange) {//0~15位,第0、1个字节

//    if (turnRange > LARGECARCO_MAX_TURN_RANGE) {
//        turnRange = LARGECARCO_MAX_TURN_RANGE;
//    }
//    else if (turnRange < LARGECARCO_MIN_TURN_RANGE) {
//        turnRange = LARGECARCO_MIN_TURN_RANGE;
//    }
    this->turnRange = turnRange;
    return *this;
}

LargeCarCO& LargeCarCO::setSpeed(quint8 speed) {//16~23位,第2个字节.0表示最大加速度，127表示最小加速度
//    if (speed < LARGECARCO_MAX_SPEED) {
//        speed = LARGECARCO_MAX_SPEED;
//    }
//    else
    if (speed > LARGECARCO_MIN_SPEED) {
        speed = LARGECARCO_MIN_SPEED;
    }
    this->speed = speed;
    return *this;
}
LargeCarCO& LargeCarCO::setBrake(quint8 brake) {//16~23位，第2个字节，128最小减速度，255最大减速度
//    if (brake > LARGECARCO_MAX_BRAKE) {
//        brake = LARGECARCO_MAX_BRAKE;
//    }
//    else
    if (brake < LARGECARCO_MIN_BRAKE) {
        brake = LARGECARCO_MIN_BRAKE;
    }
    this->speed = brake;
    return *this;
}
/*
    三种挡位0空挡，1表示前进挡，2表示后退挡
*/
LargeCarCO& LargeCarCO::setGear(quint8 gear) {//24~31，第3个字节
    if (gear == LARGECARCO_GEAR_ZERO || gear == LARGECARCO_GEAR_FORWARD || gear == LARGECARCO_GEAR_BACKWARD) {
        this->gear = gear;
    }else{
        qDebug("geal=%d,setting error",gear);
    }
    return *this;
}
 /*
   灯光 0不亮 1右转向灯亮 2左转向灯亮 3应急灯亮
*/
 LargeCarCO& LargeCarCO::setSignal(quint8 signal) {//32-39,第4个字节
     if (signal==LARGECARCO_LIGHT_ALL_OFF||signal==LARGECARCO_LIGHT_LEFT_ON||signal==LARGECARCO_LIGHT_RIGHT_ON) {
         this->signal = signal;
     }else{
         qDebug("signal=%d,setting error",signal);
     }
     return *this;
 }
/*
（1）代表鸣笛；(0)代表静音
*/
LargeCarCO& LargeCarCO::setHorn(quint8 horn) {//40-47,第5个字节
    if (horn == LARGECARCO_HORN_OFF || horn == LARGECARCO_HORN_ON) {
        this->horn = horn;
    }else{
        qDebug("horn=%d,setting error",horn);
    }
    return *this;
}


void LargeCarCO::emergencyBraking() {
    init();
    setBrake(LARGECARCO_MAX_BRAKE);
    qDebug()<<QStringLiteral("紧急刹车");
}

void LargeCarCO::init() {
    for (int i = 0; i < 8; i++) {
        this->charOrder[i] = 0;
    }
    setTurnRange(0);
    setSpeed(LARGECARCO_MIN_SPEED);
    setSignal(0);
    setHorn(0);
    setGear(0);
}
quint8* LargeCarCO::getCharOrder() {
    //转向
    quint8 low = (turnRange & 0x00FF);
    quint8 high = (turnRange >>8) & 0x00FF;
    this->charOrder[0] = low;
    this->charOrder[1] = high;
    //速度
    this->charOrder[2] = speed;
    //挡位
    this->charOrder[3] =gear;
    //转向灯
    this->charOrder[4] = signal;
    //鸣笛
    this->charOrder[5] = horn;
    return charOrder;
}
void LargeCarCO::printInfo(){
    qDebug("Large Car Control Order: speed:%d,turnRange:%d,gear:%d%s,lightSignal:%d%s,hore:%d%s",
           speed,turnRange,
           gear,gear==0?QStringLiteral("空挡"):gear==1?QStringLiteral("前进挡"):QStringLiteral("后退档"),
           signal,signal==0?QStringLiteral("所有灯光关闭"):signal==1?QStringLiteral("右转向灯亮"):QStringLiteral("左转向灯亮"),
           horn,horn==0?QStringLiteral("静音"):QStringLiteral("鸣笛")
           );
}
