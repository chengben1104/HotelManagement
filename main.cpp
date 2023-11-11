#include "MainWindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include "Dialogs/LoginDialog.h"
#include "Dialogs/MyDialog.h"
#include "Core/Data.h"

void initStyle()
{
    //加载样式表
    QFile file(":/style.qss");
    if (file.open(QFile::ReadOnly)) {
        qDebug() << "加载样式表";

        //将打开 QSS 样式表文件后，将其内容读取为一个 QByteArray 对象并转换为一个 QString 格式的 qss 变量
        QString qss = QLatin1String(file.readAll());

        //一个白色（#FFFFFF）调色板颜色被设置并使用 Qt 应用程序对象的 setPalette() 函数设置为
        //应用程序的背景色使用 setStyleSheet() 函数将存储在 qss 字符串中的样式表应用于整个应用程序的UI界面
        QString paletteColor = "#FFFFFF";
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initStyle();
    Data::Initialize();
    LoginDialog dlg;
    Dialog dl;
    MainWindow w;
    MainWindows ws;
    w.hide();
    ws.hide();
    QObject::connect(&dlg, &LoginDialog::login, [&](){
        //dlg.close();
        //w.show();
        dl.show();

    });
    QObject::connect(&dl, &Dialog::log, [&](){
        dlg.close();
        w.show();
    });
    QObject::connect(&dlg, &LoginDialog::logins, [&](){
        dlg.close();
        ws.show();
    });
    dlg.show();

    return a.exec();
}
