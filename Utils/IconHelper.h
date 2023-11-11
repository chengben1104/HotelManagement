#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QObject>
#include <QFont>
#include <QFontDatabase>
#include <QMutex>
#include <QLabel>
#include <QPushButton>
#include <QApplication>

//在 Qt 应用程序中使用 “Font Awesome” 图标字体，以便增强 UI 的视觉效果
class IconHelper : public QObject
{
private:
    explicit IconHelper(QObject *parent = 0);
    QFont iconFont;
    static IconHelper* _instance;

public:
    static IconHelper* Instance()
    {
        static QMutex mutex;
        if (!_instance) {
            QMutexLocker locker(&mutex);
            if (!_instance) {
                _instance = new IconHelper;
            }
        }
        return _instance;
    }

    void SetIcon(QLabel* lab, QChar c, int size = 10);
    void SetIcon(QPushButton* btn, QChar c, int size = 10);

};

#endif // ICONHELPER_H
