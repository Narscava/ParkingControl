#-------------------------------------------------
#
# Project created by QtCreator 2019-04-06T14:43:18
#
#-------------------------------------------------

QT       += core gui
QT       +=serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = controlUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    GpsBufferReadThread.cpp \
    GpsBufferWriteThread.cpp \
    SerialInfoDialog.cpp \
    SerialPortDialog.cpp \
    communication.cpp \
    controlQThread.cpp \
    gpsSerialPort.cpp \
        mainwindow.cpp \
    nmeaPres.cpp \
    nmeaparser.cpp \
    nmeautils.cpp \
    radar.cpp \
    radarEmulator.cpp \
    radarSet.cpp \
    threademulator.cpp \
    wheel.cpp \
    edge.cpp \
    command.cpp \
    controlEmulator.cpp \
    compass.cpp \
    gps.cpp \
    garage.cpp \
    carEmulate.cpp \
    TinyCarCO.cpp \
    TinyCarCommunication.cpp \
    TinyCarSerialPortDialog.cpp \
    ControlOrder.cpp \
    LargeCarCO.cpp

HEADERS  += mainwindow.h \
    ControlMessageStruct.h \
    GpsBufferReadThread.h \
    GpsBufferWriteThread.h \
    SerialInfoDialog.h \
    SerialPortDialog.h \
    communication.h \
    communication.h \
    controlQThread.h \
    gpsSerialPort.h \
    nmeaPres.h \
    nmeaparser.h \
    nmeautils.h \
    radar.h \
    radarEmulator.h \
    radarSet.h \
    threademulator.h \
    tool.h \
    wheel.h \
    edge.h \
    videoCorrection.h \
    command.h \
    controlEmulator.h \
    compass.h \
    gps.h \
    garage.h \
    carEmulate.h \
    datastruct.h \
    controlSerialPortCommunication.h \
    PreDefinition.h \
    AbstractCommunication.h \
    TinyCarCO.h \
    RingBuffer.h \
    TinyCarCommunication.h \
    TinyCarSerialPortDialog.h \
    ControlOrder.h \
    GpsInfo.h \
    LargeCarCO.h

FORMS    += mainwindow.ui \
    SerialInfoDialog.ui \
    TinyCarSerialPortDialog.ui
INCLUDEPATH += H:\boost_1_66_0\boost_1_66_0
