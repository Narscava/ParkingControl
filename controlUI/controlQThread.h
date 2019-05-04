#ifndef CONTROLQTHREAD_H
#define CONTROLQTHREAD_H
#include <QThread>
#include "garage.h"
#include "gps.h"
#include "radarSet.h"
#include "command.h"
#include<iostream>
#include <QMutex>
class ControlQthread:public QThread
{
    Q_OBJECT
public:
    QMutex m_threadRunLock;
    Controller *controller;
    Gps *gps;
    RadarSet* radarSet;
    Garage *garage;
    ControlQthread(QObject* parent,Controller &controller_,Gps &gps_,RadarSet &radarSet_,
                   Garage &garage_);
    void run();
};

#endif // CONTROLQTHREAD_H
