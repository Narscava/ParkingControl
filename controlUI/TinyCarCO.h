#ifndef TINYCARCO_H
#define TINYCARCO_H

#define TINYCARCO_MAX_SPEED 0xFF
#define TINYCARCO_MIN_SPEED 0
#define TINYCARCO_ORIENTATION_FORWARD 0
#define TINYCARCO_ORIENTATION_BACKWARD 1
/**
 * @brief The TinyCarCO class
 * tiny car control order
 */
#include<QObject>
//小车控制的最底层指令
class TinyCarCO{
private:
    /**
     * @brief leftSpeed
     * left wheel speed,range from 0x00 to 0xFF
     */
    quint8 leftSpeed;
    /**
     * @brief rightSpeed
     * right wheel speed,range from 0x00 to 0xFF
     */
    quint8 rightSpeed;
    /**
     * @brief leftOrientation
     * left wheel orientation range 0 means forward ,1 means backward
     * 左轮转的方向 0表示向前，1表示向后
     */
    qint8 leftOrientation;
    /**
     * @brief rightOrientation
     * right wheel orientation range 0 means forward ,1 means backward
     * 左轮转的方向 0表示向前，1表示向后
     */
    qint8 rightOrientation;
    quint8 charOrder[10] = { 0xFF,0xFE,0,0,0,0,0,0,0,0 };
public:
    void init();
    quint8 getLeftSpeed(){return leftSpeed;}
    quint8 getRightSpeed(){return rightSpeed;}
    qint8 getLeftOrientation(){return leftOrientation;}
    qint8 getRightOrientation(){return rightOrientation;}
    void printInfo();
    TinyCarCO& setLeftSpeed(quint8);
    TinyCarCO& setRightSpeed(quint8);
    TinyCarCO& setLeftOrientation(qint8);
    TinyCarCO& setRightOrientation(qint8);
    quint8* getCharOrder();//转化成实际的指令

};
#endif // TINYCARCO_H
