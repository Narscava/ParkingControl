#ifndef TINYCARSERIALPORTDIALOG_H
#define TINYCARSERIALPORTDIALOG_H

#include "PreDefinition.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDialog>
#include <QList>
namespace Ui {
class TinyCarSerialPortDialog;
}

class TinyCarSerialPortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TinyCarSerialPortDialog(QWidget *parent = 0);
    ~TinyCarSerialPortDialog();

private:
    Ui::TinyCarSerialPortDialog *ui;
    QList<QSerialPortInfo> serialPortInfos;
    void init();
};

#endif // TINYCARSERIALPORTDIALOG_H
