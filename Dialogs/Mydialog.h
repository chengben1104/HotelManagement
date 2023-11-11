#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include "LoginDialog.h"

namespace Ui {
class Dialog;
}

class LoginDialog;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

signals:
    void log();
public slots:
    void buttonBoxSure();
private:
    Ui::Dialog *ui;
};

#endif // MYDIALOG_H
