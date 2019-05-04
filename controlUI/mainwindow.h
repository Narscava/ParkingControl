#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QTimer>
#include <QMainWindow>
#include <QPainter>
#include <thread>
#include "threademulator.h"


#include "command.h"
#include "controlEmulator.h"
#include "edge.h"
#include "radar.h"
#include "tool.h"
#include "videoCorrection.h"
#include "wheel.h"
#include "carEmulate.h"
#include "compass.h"
#include "garage.h"
#include "gps.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int realTag;
    int inWay;//进入方式, 0代表左侧，1代表右侧
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);//覆盖已有的UI绘制函数，注意绘制只能在UI线程中完成
private slots: //槽函数
    void timeout();
private:
    QTimer *qtimer;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
