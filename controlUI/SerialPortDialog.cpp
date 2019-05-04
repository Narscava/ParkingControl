#include "SerialPortDialog.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");
SerialPortDialog::SerialPortDialog(QWidget* parent,GpsRingBuffer* gpsRingBuffer):
    QDialog(parent){


    //this->resize(260, 70);
    this->setWindowTitle(QStringLiteral("串口设置"));
    if(gpsRingBuffer==0){
        qDebug()<<"GpsRingBuffer is not init";
        gpsRingBuffer=new GpsRingBuffer;
    }
    ringBuffer1=new CharRingBuffer();
    ringBuffer2=new CharRingBuffer();
    ringBuffer3=new CharRingBuffer();

    GpsBufferWriteThread1=new GpsBufferWriteThread(ringBuffer1,gpsRingBuffer,this,QStringLiteral("GPS 第1路"));
    GpsBufferWriteThread1->start();

    GpsBufferWriteThread2=new GpsBufferWriteThread(ringBuffer2,gpsRingBuffer,this,QStringLiteral("GPS 第2路"));
    GpsBufferWriteThread2->start();

    GpsBufferWriteThread3=new GpsBufferWriteThread(ringBuffer3,gpsRingBuffer,this,QStringLiteral("GPS 第3路"));
    GpsBufferWriteThread3->start();
    QGridLayout* layout=new QGridLayout(this);
    layout->addWidget(new QLabel(QStringLiteral("端口号")),0,1);
    layout->addWidget(new QLabel(QStringLiteral("波特率")),0,2);
    layout->addWidget(new QLabel(QStringLiteral("数据位")),0,3);
    layout->addWidget(new QLabel(QStringLiteral("奇偶校验")),0,4);
    layout->addWidget(new QLabel(QStringLiteral("停止位")),0,5);
    layout->addWidget(new QLabel(QStringLiteral("流控")),0,6);
    layout->addWidget(new QLabel(QStringLiteral("操作")),0,7);
    layout->addWidget(new QLabel(QStringLiteral("操作")),0,8);
    comboBoxPortName1=new QComboBox(this);
    comboBoxBaudRate1=new QComboBox(this);
    comboBoxDataBits1=new QComboBox(this);
    comboBoxParity1=new QComboBox(this);
    comboBoxStopBit1=new QComboBox(this);
    comboBoxFlowBit1=new QComboBox(this);

    comboBoxPortName2=new QComboBox(this);
    comboBoxBaudRate2=new QComboBox(this);
    comboBoxDataBits2=new QComboBox(this);
    comboBoxParity2=new QComboBox(this);
    comboBoxStopBit2=new QComboBox(this);
    comboBoxFlowBit2=new QComboBox(this);

    comboBoxPortName3=new QComboBox(this);
    comboBoxBaudRate3=new QComboBox(this);
    comboBoxDataBits3=new QComboBox(this);
    comboBoxParity3=new QComboBox(this);
    comboBoxStopBit3=new QComboBox(this);
    comboBoxFlowBit3=new QComboBox(this);
    serialPort1=new QSerialPort();
    serialPort2=new QSerialPort();
    serialPort3=new QSerialPort();

    QString description;
    QString manufacturer;
    QString serialNumber;

    //获取可以用的串口
    serialPortInfos = QSerialPortInfo::availablePorts();

    //输出当前系统可以使用的串口个数
    qDebug() << "Total numbers of ports: " << serialPortInfos.count();

    //将所有可以使用的串口设备添加到ComboBox中
    for (const QSerialPortInfo &serialPortInfo : serialPortInfos){
        QStringList list;
        description = serialPortInfo.description();
        manufacturer = serialPortInfo.manufacturer();
        serialNumber = serialPortInfo.serialNumber();

        list << serialPortInfo.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << serialPortInfo.systemLocation()
             << (serialPortInfo.vendorIdentifier() ? QString::number(serialPortInfo.vendorIdentifier(), 16) : blankString)
             << (serialPortInfo.productIdentifier() ? QString::number(serialPortInfo.productIdentifier(), 16) : blankString);

        comboBoxPortName1->addItem(list.first(), list);
        comboBoxPortName2->addItem(list.first(), list);
        comboBoxPortName3->addItem(list.first(), list);
    }

    //设置波特率
    comboBoxBaudRate1->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    comboBoxBaudRate1->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    comboBoxBaudRate1->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    comboBoxBaudRate1->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    comboBoxBaudRate1->setCurrentIndex(3);

    comboBoxBaudRate2->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    comboBoxBaudRate2->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    comboBoxBaudRate2->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    comboBoxBaudRate2->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    comboBoxBaudRate2->setCurrentIndex(3);

    comboBoxBaudRate3->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    comboBoxBaudRate3->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    comboBoxBaudRate3->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    comboBoxBaudRate3->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    comboBoxBaudRate3->setCurrentIndex(3);

    //设置数据位
    comboBoxDataBits1->addItem(QStringLiteral("5"), QSerialPort::Data5);
    comboBoxDataBits1->addItem(QStringLiteral("6"), QSerialPort::Data6);
    comboBoxDataBits1->addItem(QStringLiteral("7"), QSerialPort::Data7);
    comboBoxDataBits1->addItem(QStringLiteral("8"), QSerialPort::Data8);
    comboBoxDataBits1->setCurrentIndex(3);

    comboBoxDataBits2->addItem(QStringLiteral("5"), QSerialPort::Data5);
    comboBoxDataBits2->addItem(QStringLiteral("6"), QSerialPort::Data6);
    comboBoxDataBits2->addItem(QStringLiteral("7"), QSerialPort::Data7);
    comboBoxDataBits2->addItem(QStringLiteral("8"), QSerialPort::Data8);
    comboBoxDataBits2->setCurrentIndex(3);

    comboBoxDataBits3->addItem(QStringLiteral("5"), QSerialPort::Data5);
    comboBoxDataBits3->addItem(QStringLiteral("6"), QSerialPort::Data6);
    comboBoxDataBits3->addItem(QStringLiteral("7"), QSerialPort::Data7);
    comboBoxDataBits3->addItem(QStringLiteral("8"), QSerialPort::Data8);
    comboBoxDataBits3->setCurrentIndex(3);
    //设置奇偶校验位
    comboBoxParity1->addItem(tr("None"), QSerialPort::NoParity);
    comboBoxParity1->addItem(tr("Even"), QSerialPort::EvenParity);
    comboBoxParity1->addItem(tr("Odd"), QSerialPort::OddParity);
    comboBoxParity1->addItem(tr("Mark"), QSerialPort::MarkParity);
    comboBoxParity1->addItem(tr("Space"), QSerialPort::SpaceParity);

    comboBoxParity2->addItem(tr("None"), QSerialPort::NoParity);
    comboBoxParity2->addItem(tr("Even"), QSerialPort::EvenParity);
    comboBoxParity2->addItem(tr("Odd"), QSerialPort::OddParity);
    comboBoxParity2->addItem(tr("Mark"), QSerialPort::MarkParity);
    comboBoxParity2->addItem(tr("Space"), QSerialPort::SpaceParity);

    comboBoxParity3->addItem(tr("None"), QSerialPort::NoParity);
    comboBoxParity3->addItem(tr("Even"), QSerialPort::EvenParity);
    comboBoxParity3->addItem(tr("Odd"), QSerialPort::OddParity);
    comboBoxParity3->addItem(tr("Mark"), QSerialPort::MarkParity);
    comboBoxParity3->addItem(tr("Space"), QSerialPort::SpaceParity);
    //设置停止位
    comboBoxStopBit1->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    comboBoxStopBit1->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    comboBoxStopBit2->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    comboBoxStopBit2->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    comboBoxStopBit3->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    comboBoxStopBit3->addItem(QStringLiteral("2"), QSerialPort::TwoStop);
    //添加流控
    comboBoxFlowBit1->addItem(tr("None"), QSerialPort::NoFlowControl);
    comboBoxFlowBit1->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    comboBoxFlowBit1->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);

    comboBoxFlowBit2->addItem(tr("None"), QSerialPort::NoFlowControl);
    comboBoxFlowBit2->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    comboBoxFlowBit2->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);

    comboBoxFlowBit3->addItem(tr("None"), QSerialPort::NoFlowControl);
    comboBoxFlowBit3->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    comboBoxFlowBit3->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);

    SerialInfoDialog* infoDialog1=new SerialInfoDialog(this);
    connect(this,&SerialPortDialog::serialPort1ContentChanged,infoDialog1,&SerialInfoDialog::updateBroswerText);

    SerialInfoDialog* infoDialog2=new SerialInfoDialog(this);
    connect(this,&SerialPortDialog::serialPort2ContentChanged,infoDialog2,&SerialInfoDialog::updateBroswerText);

    SerialInfoDialog* infoDialog3=new SerialInfoDialog(this);
    connect(this,&SerialPortDialog::serialPort3ContentChanged,infoDialog3,&SerialInfoDialog::updateBroswerText);

    openButton1=new QPushButton(QStringLiteral("打开串口"),this);
    //点击按照界面打开对应的串口，并且显示新打开窗口显示串口接收的数据，将数据存储到双端队列中
    connect(openButton1,&QPushButton::clicked,[this,infoDialog1](){
        this->fillSerialPortInfo(serialPort1,comboBoxPortName1,comboBoxBaudRate1,
                                 comboBoxDataBits1,comboBoxParity1,comboBoxStopBit1,comboBoxFlowBit1);
        if(this->openSerialPort(serialPort1,ringBuffer1)){
            infoDialog1->setWindowTitle(serialPort1->portName());
            infoDialog1->show();
            openButton1->setDisabled(true);
            closeButton1->setEnabled(true);
            showButton1->setEnabled(true);
        }else{
            QMessageBox* msgBox=new QMessageBox(this);
            msgBox->setAttribute(Qt::WA_DeleteOnClose);
            msgBox->setText(QStringLiteral("串口打开失败"));
            msgBox->show();
        }

    });
    closeButton1=new QPushButton(QStringLiteral("关闭串口"),this);
    closeButton1->setDisabled(true);
    connect(closeButton1,&QPushButton::clicked,[this](){
        openButton1->setEnabled(true);
        closeButton1->setDisabled(true);
        showButton1->setDisabled(true);
        closeSerialPort(serialPort1,ringBuffer1);
    });
    showButton1=new QPushButton(QStringLiteral("显示信息"),this);
    showButton1->setDisabled(true);
    connect(showButton1,&QPushButton::clicked,[this,infoDialog1](){
        infoDialog1->setWindowTitle(serialPort1->portName());
        infoDialog1->show();
    });

    openButton2=new QPushButton(QStringLiteral("打开串口"),this);
    connect(openButton2,&QPushButton::clicked,[this,infoDialog2](){
        this->fillSerialPortInfo(serialPort2,comboBoxPortName2,comboBoxBaudRate2,
                                 comboBoxDataBits2,comboBoxParity2,comboBoxStopBit2,comboBoxFlowBit2);
        if(this->openSerialPort(serialPort2,ringBuffer2)){
            infoDialog2->setWindowTitle(serialPort2->portName());
            infoDialog2->show();
            openButton2->setDisabled(true);
            closeButton2->setEnabled(true);
        }else{
            QMessageBox* msgBox=new QMessageBox(this);
            msgBox->setAttribute(Qt::WA_DeleteOnClose);
            msgBox->setText(QStringLiteral("串口打开失败"));
            msgBox->show();
        }
    });

    closeButton2=new QPushButton(QStringLiteral("关闭串口"),this);
    closeButton2->setDisabled(true);
    connect(closeButton2,&QPushButton::clicked,[this](){
        openButton2->setEnabled(true);
        closeButton2->setDisabled(true);
        closeSerialPort(serialPort2,ringBuffer2);
    });
    showButton2=new QPushButton(QStringLiteral("显示信息"),this);
    showButton2->setDisabled(true);
    connect(showButton2,&QPushButton::clicked,[this,infoDialog2](){
        infoDialog2->setWindowTitle(serialPort2->portName());
        infoDialog2->show();
    });

    openButton3=new QPushButton(QStringLiteral("打开串口"),this);
    connect(openButton3,&QPushButton::clicked,[this,infoDialog3](){
        this->fillSerialPortInfo(serialPort3,comboBoxPortName3,comboBoxBaudRate3,
                                 comboBoxDataBits3,comboBoxParity3,comboBoxStopBit3,comboBoxFlowBit3);
        if(this->openSerialPort(serialPort3,ringBuffer3)){
            infoDialog3->setWindowTitle(serialPort2->portName());
            infoDialog3->show();
            openButton3->setDisabled(true);
            closeButton3->setEnabled(true);
        }else{
            QMessageBox* msgBox=new QMessageBox(this);
            msgBox->setAttribute(Qt::WA_DeleteOnClose);
            msgBox->setText(QStringLiteral("串口打开失败"));
            msgBox->show();
        }
    });

    closeButton3=new QPushButton(QStringLiteral("关闭串口"),this);
    closeButton3->setDisabled(true);
    connect(closeButton3,&QPushButton::clicked,[this](){
        openButton3->setEnabled(true);
        closeButton3->setDisabled(true);
        closeSerialPort(serialPort3,ringBuffer3);
    });
    showButton3=new QPushButton(QStringLiteral("显示信息"),this);
    showButton3->setDisabled(true);
    connect(showButton3,&QPushButton::clicked,[this,infoDialog3](){
        infoDialog3->setWindowTitle(serialPort3->portName());
        infoDialog3->show();
    });

    layout->addWidget(comboBoxPortName1,1,1);
    layout->addWidget(comboBoxBaudRate1,1,2);
    layout->addWidget(comboBoxDataBits1,1,3);
    layout->addWidget(comboBoxParity1,1,4);
    layout->addWidget(comboBoxStopBit1,1,5);
    layout->addWidget(comboBoxFlowBit1,1,6);

    layout->addWidget(comboBoxPortName2,2,1);
    layout->addWidget(comboBoxBaudRate2,2,2);
    layout->addWidget(comboBoxDataBits2,2,3);
    layout->addWidget(comboBoxParity2,2,4);
    layout->addWidget(comboBoxStopBit2,2,5);
    layout->addWidget(comboBoxFlowBit2,2,6);

    layout->addWidget(comboBoxPortName3,3,1);
    layout->addWidget(comboBoxBaudRate3,3,2);
    layout->addWidget(comboBoxDataBits3,3,3);
    layout->addWidget(comboBoxParity3,3,4);
    layout->addWidget(comboBoxStopBit3,3,5);
    layout->addWidget(comboBoxFlowBit3,3,6);

    layout->addWidget(openButton1,1,7);
    layout->addWidget(closeButton1,1,8);
    layout->addWidget(showButton1,1,9);
    layout->addWidget(openButton2,2,7);
    layout->addWidget(closeButton2,2,8);
    layout->addWidget(showButton2,2,9);
    layout->addWidget(openButton3,3,7);
    layout->addWidget(closeButton3,3,8);
    layout->addWidget(showButton3,3,9);
}

SerialPortDialog::~SerialPortDialog(){

    qDebug() << "start destroy widget SerialPortDialog";
    GpsBufferWriteThread1->stopImmediately();
    GpsBufferWriteThread1->wait();

    GpsBufferWriteThread2->stopImmediately();
    GpsBufferWriteThread2->wait();

    GpsBufferWriteThread3->stopImmediately();
    GpsBufferWriteThread3->wait();
    closeSerialPort(serialPort1,ringBuffer1);
    closeSerialPort(serialPort2,ringBuffer2);
    closeSerialPort(serialPort3,ringBuffer3);

    delete ringBuffer1;
    delete ringBuffer2;
    delete ringBuffer3;

    qDebug() << "end destroy widget SerialPortDialog";
}

void SerialPortDialog::send(QByteArray content,const QSerialPort* serialPort){
    if(serialPort==serialPort1)
        emit serialPort1ContentChanged(content);
    else if(serialPort==serialPort2){
        emit serialPort2ContentChanged(content);
    }else if(serialPort==serialPort3){
        emit serialPort3ContentChanged(content);
    }
}
void SerialPortDialog::closeSerialPort(QSerialPort* serialPort,CharRingBuffer* ringBuffer){
    if(serialPort->isOpen()){
        serialPort->clear();
        serialPort->close();
        qDebug()<<serialPort->portName()<<"has been closed";
    }
    char temp=NULL;
    while(!ringBuffer->pop(temp)){
        if(temp==NULL)
            break;
    }
}
bool SerialPortDialog::openSerialPort(QSerialPort* serialPort,CharRingBuffer* ringBuffer){
    if(serialPort->open(QSerialPort::OpenModeFlag::ReadOnly)){
        qDebug()<<serialPort->portName()<<"open success!!";
    }else{
        qDebug()<<serialPort->portName()<<"open fail!!";
        return false;
    }
    disconnect(serialPort,&QSerialPort::readyRead,0,0);
    connect(serialPort,&QSerialPort::readyRead,[this,serialPort,ringBuffer](){
        readCom(serialPort,ringBuffer);
    });
    return true;
}
void SerialPortDialog::readCom(QSerialPort* serialPort,CharRingBuffer* ringBuffer){
    QByteArray temp = serialPort->readAll();
    send(temp,serialPort);
    foreach (char var, temp) {
        ringBuffer->push(var);
    }
}
void SerialPortDialog::fillSerialPortInfo(QSerialPort* serialPort,const QComboBox* comboBoxPortName,const QComboBox* comboBoxBaudRate,
                                         const QComboBox*comboBoxDataBits,const QComboBox* comboBoxParity,const QComboBox* comboBoxStopBit,
                                          const QComboBox* comboBoxFlowBit ){
    serialPort->setPortName(comboBoxPortName->currentData().value<QStringList>().first());
    serialPort->setBaudRate(comboBoxBaudRate->currentData().value<QSerialPort::BaudRate>());
    serialPort->setDataBits(comboBoxDataBits->currentData().value<QSerialPort::DataBits>());
    serialPort->setParity(comboBoxParity->currentData().value<QSerialPort::Parity>());
    serialPort->setStopBits(comboBoxStopBit->currentData().value<QSerialPort::StopBits>());
    serialPort->setFlowControl(comboBoxFlowBit->currentData().value<QSerialPort::FlowControl>());
    qDebug()<<QStringLiteral("端口号:")<<serialPort->portName()<<QStringLiteral(";波特率:")<<serialPort->baudRate()
           <<QStringLiteral(";数据位:")<<serialPort->dataBits()<<QStringLiteral(";奇偶校验位:")<<serialPort->parity()
          <<QStringLiteral(";停止位:")<<serialPort->stopBits()<<QStringLiteral(";流控:")<<serialPort->flowControl();
}
