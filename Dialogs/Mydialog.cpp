#include "Mydialog.h"
#include "ui_Mydialog.h"
#include "Mydialog.h"
#include "MainWindow.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(buttonBoxSure()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::buttonBoxSure()
{

    int s =123;
    if(ui->lineEdit->text().toInt()==s)
    {
         QMessageBox::information(this, tr("系统通知"), tr("验证成功！\n请耐心等待..."));
        emit log();
    }
    else
    {
        QMessageBox::warning(this, tr("系统通知"), tr("验证码错误！"));
    }
}
