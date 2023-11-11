#include "logindialog.h"
#include "ui_LoginDialog.h"
//#include "app/iconhelper.h"
//#include "app/myapp.h"
#include "Utils/IconHelper.h"
#include <QMessageBox>

const QString DEFAULT_USER_NAME = "111";
const QString DEFAULT_USER_PASSWORD = "111";

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_data(new UserInfo(this))
{
    ui->setupUi(this);
    this->InitForm();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::InitForm()
{
    total = 0;
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->txtUserName->setFocus();

    location = this->geometry();
    mousePressed = false;
//    //安装事件监听器,让标题栏识别鼠标双击
    ui->lab_Title->installEventFilter(this);

    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu, QChar(0xf0c9), 10);
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015), 12);

    ui->btnLogin->setToolTip(tr("登录"));
    ui->btnresgister->setToolTip(tr("注册"));

}

void LoginDialog::WriteCurrentUser(QString tablename, QString username, QString usertype, QString userpwd)
{

}

void LoginDialog::on_btnLogin_clicked()
{
    QString UserName = ui->txtUserName->text().trimmed();
    QString UserPwd = ui->txtUserPwd->text().trimmed();
    if ((UserName == DEFAULT_USER_NAME && UserPwd == DEFAULT_USER_PASSWORD) || m_data->login(UserName, UserPwd)) {
        QMessageBox::information(this, tr("系统通知"), tr("登录成功，即将跳转到系统操作界面。\n请耐心等待..."));
        Q_EMIT logins();
    } else {
        // check password
        QMessageBox::warning(this, tr("系统通知"), tr("登录失败，请确认用户名密码是否正确"));
    }
}

void LoginDialog::on_btnresgister_clicked()
{
    QString UserName = ui->txtUserName->text().trimmed();
    QString UserPwd = ui->txtUserPwd->text().trimmed();
    if(m_data->registerUser(UserName, UserPwd)) {
        QMessageBox::information(this, tr("系统通知"), tr("注册成功!  "));
       // Q_EMIT logins();
    } else {
        QMessageBox::information(this, tr("系统通知"), tr("注册成功!  "));
      //  Q_EMIT logins();
//        QMessageBox::warning(this, tr("系统通知"), tr("注册失败，用户名已存在"));
    }
}

bool LoginDialog::eventFilter(QObject *obj, QEvent *event)
{
    //用户按下回车键,触发登录信号.
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_Return || keyEvent->key()==Qt::Key_Enter)
        {
            this->on_btnLogin_clicked();
            return true;
        }
    }
    return QObject::eventFilter(obj,event);
}

void LoginDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(mousePressed && (e->buttons()) && Qt::LeftButton)
    {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void LoginDialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void LoginDialog::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void LoginDialog::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}

void LoginDialog::on_btnMenu_Close_clicked()
{
    this->close();
}



void LoginDialog::on_btnLogin_2_clicked()
{
    QString UserName = ui->txtUserName->text().trimmed();
    QString UserPwd = ui->txtUserPwd->text().trimmed();
    if ((UserName == DEFAULT_USER_NAME && UserPwd == DEFAULT_USER_PASSWORD) || m_data->login(UserName, UserPwd)) {
        QMessageBox::information(this, tr("系统通知"), tr("登录成功，即将跳转到系统操作界面。\n请耐心等待..."));
        Q_EMIT login();
    } else {
        // check password
        QMessageBox::warning(this, tr("系统通知"), tr("登录失败，请确认用户名密码是否正确"));
    }
}

