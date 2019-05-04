#include "SerialInfoDialog.h"
#include "ui_SerialInfoDialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
SerialInfoDialog::SerialInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialInfoDialog)
{
    ui->setupUi(this);
    connect(ui->saveAsButton,&QPushButton::clicked,this,&SerialInfoDialog::saveFile);
}

SerialInfoDialog::~SerialInfoDialog()
{
    delete ui;
}
void SerialInfoDialog::updateBroswerText(const QString& content){
    ui->textBrowser->insertPlainText(content);
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void SerialInfoDialog::saveFile()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                tr("Open File"),
                                                "./../QtControl/GnnNema",
                                                tr("Text Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"),
                                       tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << ui->textBrowser->toPlainText();
        file.close();
    }
}
