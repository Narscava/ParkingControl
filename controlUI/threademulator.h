#ifndef THREADEMULATOR_H
#define THREADEMULATOR_H

#include "threademulator.h"
#include<thread>

class ThreadEmulator
{
public:
    int static volatile X;
    int static volatile Y;
    int static volatile Tag;
    int static volatile count;
    int static volatile xArr[1000];
    int static volatile yArr[1000];
    ThreadEmulator();
    void threadOn();
};

#endif // THREADEMULATOR_H
