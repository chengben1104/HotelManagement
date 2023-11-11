#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

#include "Pages/BookingPage.h"
#include "Pages/CheckInPage.h"
#include "Pages/CheckOutPage.h"
#include "Pages/SearchPage.h"
#include "Pages/SystemPage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTabWidget* m_container;    // 选项卡切换容器
    BookingPage* m_bookingPage;
    CheckInPage* m_checkInPage;
    CheckOutPage* m_checkOutPage;
    SearchPage* m_searchPage;
    SystemPage* m_systemPage;

private Q_SLOTS:
    void onJumpToBooking(const Data::Person& p);
};

class MainWindows : public QMainWindow
{
    Q_OBJECT

public:
    MainWindows(QWidget *parent = nullptr);
    ~MainWindows();

private:
    Ui::MainWindow *ui;
    QTabWidget* m_container;    // 选项卡切换容器
    BookingPage* m_bookingPage;
    SearchPage* m_searchPage;
    SystemPage* m_systemPage;

};
#endif // MAINWINDOW_H
