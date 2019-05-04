#ifndef SERIALINFODIALOG_H
#define SERIALINFODIALOG_H

#include <QDialog>

namespace Ui {
class SerialInfoDialog;
}

class SerialInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialInfoDialog(QWidget *parent = 0);
    void updateBroswerText(const QString&);
    void saveFile();
    ~SerialInfoDialog();

private:
    Ui::SerialInfoDialog *ui;
};

#endif // SERIALINFODIALOG_H
