#include "iconhelper.h"

IconHelper* IconHelper::_instance = 0;

//使用 QFontDatabase 类将 “Font Awesome” 图标字体添加到应用程序字体库，并获得添加字体的名称，用此名称实例化 iconFont 变量
IconHelper::IconHelper(QObject*):
    QObject(qApp)
{
    int fontId = QFontDatabase::addApplicationFont(":/fonts/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    iconFont = QFont(fontName);
}

void IconHelper::SetIcon(QLabel* lab, QChar c, int size)
{
    iconFont.setPointSize(size);
    lab->setFont(iconFont);
    lab->setText(c);
}

void IconHelper::SetIcon(QPushButton* btn, QChar c, int size)
{
    iconFont.setPointSize(size);
    btn->setFont(iconFont);
    btn->setText(c);
}
