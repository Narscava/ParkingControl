#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "tool.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    ThreadEmulator threadE=ThreadEmulator();
    threadE.threadOn();
    */
    MainWindow w;
    w.show();


    return a.exec();
}
