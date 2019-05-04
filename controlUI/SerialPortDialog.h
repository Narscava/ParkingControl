#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include "RingBuffer.h"
#include "SerialInfoDialog.h"
#include "GpsBufferWriteThread.h"
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
class SerialPortDialog : public QDialog{
    Q_OBJECT
public:
    explicit SerialPortDialog(QWidget *parent = 0,GpsRingBuffer* gpsRingBuffer=0);
    ~SerialPortDialog();
    CharRingBuffer* ringBuffer1;
    CharRingBuffer* ringBuffer2;
    CharRingBuffer* ringBuffer3;
signals:
    void userAgeChanged(const QString&);
    void serialPort1ContentChanged(const QString&);
    void serialPort2ContentChanged(const QString&);
    void serialPort3ContentChanged(const QString&);
private:
    QList<QSerialPortInfo> serialPortInfos;

    QSerialPort* serialPort1;
    QSerialPort* serialPort2;
    QSerialPort* serialPort3;

    QString* dialog1Content;
    QString* dialog2Content;
    QString* dialog3Content;

    QComboBox* comboBoxPortName1;//端口号
    QComboBox* comboBoxPortName2;
    QComboBox* comboBoxPortName3;

    QComboBox* comboBoxBaudRate1;//波特率
    QComboBox* comboBoxBaudRate2;
    QComboBox* comboBoxBaudRate3;

    QComboBox* comboBoxDataBits1;//数据位
    QComboBox* comboBoxDataBits2;
    QComboBox* comboBoxDataBits3;

    QComboBox* comboBoxParity1;//奇偶校验位
    QComboBox* comboBoxParity2;
    QComboBox* comboBoxParity3;

    QComboBox* comboBoxStopBit1;//设置停止位
    QComboBox* comboBoxStopBit2;
    QComboBox* comboBoxStopBit3;

    QComboBox* comboBoxFlowBit1;//流控
    QComboBox* comboBoxFlowBit2;
    QComboBox* comboBoxFlowBit3;

    QPushButton * openButton1;
    QPushButton * openButton2;
    QPushButton * openButton3;

    QPushButton * closeButton1;
    QPushButton * closeButton2;
    QPushButton * closeButton3;

    QPushButton * showButton1;
    QPushButton * showButton2;
    QPushButton * showButton3;

    GpsBufferWriteThread* GpsBufferWriteThread1;
    GpsBufferWriteThread* GpsBufferWriteThread2;
    GpsBufferWriteThread* GpsBufferWriteThread3;


    //ADD-ONs:应该先执行构造函数，然后fillSerialPortInfo,然后openSerialPort,最后readCom
    void send(QByteArray,const QSerialPort*);
    void closeSerialPort(QSerialPort*,CharRingBuffer*);
    void readCom(QSerialPort*,CharRingBuffer*);
    bool openSerialPort(QSerialPort*,CharRingBuffer*);//通过槽函数实现，未开启线程
    void fillSerialPortInfo(QSerialPort*,const QComboBox*,const QComboBox*,const QComboBox*,const QComboBox*,const QComboBox*,const QComboBox*);
};
#endif // SERIALPORTDIALOG_H
