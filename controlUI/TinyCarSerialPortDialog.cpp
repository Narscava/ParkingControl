#include "TinyCarSerialPortDialog.h"
#include "ui_TinyCarSerialPortDialog.h"

#include<QFile>
#include<QStringList>
#include<QMessageBox>
static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");
TinyCarSerialPortDialog::TinyCarSerialPortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TinyCarSerialPortDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("software settings"));
    init();
    connect(this->ui->confirm,&QPushButton::clicked,[this](){
        //写到文件里面，到时候读写线程直接从文件里面读
        QFile file("./../controlUI/softwareConfig/config.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Text);

        file.write(QByteArray::number(this->ui->system->currentData().value<int>()));
        file.write(QByteArray(" "));
        file.write(QByteArray::number(this->ui->carType->currentData().value<int>()));
        file.write(QByteArray(" "));
        file.write((this->ui->comboBox_1->currentData().value<QStringList>().first()).toUtf8());
        file.write(QByteArray(" "));
        file.write(QByteArray::number(this->ui->comboBox_2->currentData().value<QSerialPort::BaudRate>()));
        file.write(QByteArray(" "));
        file.write(QByteArray::number(this->ui->comboBox_3->currentData().value<QSerialPort::DataBits>()));
        file.write(QByteArray(" "));
        file.write(QByteArray::number(this->ui->comboBox_4->currentData().value<QSerialPort::Parity>()));
        file.write(QByteArray(" "));
        file.write(QByteArray::number(this->ui->comboBox_5->currentData().value<QSerialPort::StopBits>()));
        file.write(QByteArray(" "));
        file.write(QByteArray::number(this->ui->comboBox_6->currentData().value<QSerialPort::FlowControl>()));
        file.write(QByteArray(" "));
        file.close();
        QMessageBox* msgBox=new QMessageBox(this);
        msgBox->setAttribute(Qt::WA_DeleteOnClose);
        msgBox->setText(QStringLiteral("setting success"));
        msgBox->show();
    });
}

TinyCarSerialPortDialog::~TinyCarSerialPortDialog()
{
    delete ui;
}
void TinyCarSerialPortDialog::init(){
    this->ui->carType->addItem("LargeCar",LARGECARTYPE);
    this->ui->carType->addItem("TinyCar",TINYCARTYPE);

    this->ui->system->addItem("Windows",PREDEFINITIONWINDOWS);
    this->ui->system->addItem("Linux",PREDEFINITIONLINUX);

    serialPortInfos = QSerialPortInfo::availablePorts();
    QString description;
    QString manufacturer;
    QString serialNumber;
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

        this->ui->comboBox_1->addItem(list.first(), list);
        //设置波特率
        this->ui->comboBox_2->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
        this->ui->comboBox_2->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
        this->ui->comboBox_2->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
        this->ui->comboBox_2->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
        this->ui->comboBox_2->setCurrentIndex(3);

        //设置数据位
        this->ui->comboBox_3->addItem(QStringLiteral("5"), QSerialPort::Data5);
        this->ui->comboBox_3->addItem(QStringLiteral("6"), QSerialPort::Data6);
        this->ui->comboBox_3->addItem(QStringLiteral("7"), QSerialPort::Data7);
        this->ui->comboBox_3->addItem(QStringLiteral("8"), QSerialPort::Data8);
        this->ui->comboBox_3->setCurrentIndex(3);

        //设置奇偶校验位
        this->ui->comboBox_4->addItem(tr("None"), QSerialPort::NoParity);
        this->ui->comboBox_4->addItem(tr("Even"), QSerialPort::EvenParity);
        this->ui->comboBox_4->addItem(tr("Odd"), QSerialPort::OddParity);
        this->ui->comboBox_4->addItem(tr("Mark"), QSerialPort::MarkParity);
        this->ui->comboBox_4->addItem(tr("Space"), QSerialPort::SpaceParity);

        //设置停止位
        this->ui->comboBox_5->addItem(QStringLiteral("1"), QSerialPort::OneStop);
        this->ui->comboBox_5->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

        //添加流控
        this->ui->comboBox_6->addItem(tr("None"), QSerialPort::NoFlowControl);
        this->ui->comboBox_6->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
        this->ui->comboBox_6->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);


    }
}
