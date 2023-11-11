#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_container(new QTabWidget(this))
    , m_bookingPage(new BookingPage(this))
    , m_checkInPage(new CheckInPage(this))
    , m_checkOutPage(new CheckOutPage(this))
    , m_searchPage(new SearchPage(this))
    , m_systemPage(new SystemPage(this))
{
    ui->setupUi(this);
    m_container->addTab(m_bookingPage, tr("预定"));
    m_container->addTab(m_checkInPage, tr("入住"));
    m_container->addTab(m_checkOutPage, tr("退房"));
    m_container->addTab(m_searchPage, tr("查询"));
    m_container->addTab(m_systemPage, tr("系统"));
    setCentralWidget(m_container);

    connect(m_checkInPage, &CheckInPage::jumpToBooking, this, &MainWindow::onJumpToBooking, Qt::DirectConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onJumpToBooking(const Data::Person &p)
{
    m_bookingPage->setPerson(p);
    m_container->setCurrentWidget(m_bookingPage);
}


MainWindows::MainWindows(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_container(new QTabWidget(this))
    , m_bookingPage(new BookingPage(this))
    , m_searchPage(new SearchPage(this))
    , m_systemPage(new SystemPage(this))
{
    ui->setupUi(this);
    m_container->addTab(m_bookingPage, tr("预定"));
    m_container->addTab(m_searchPage, tr("查询"));
    m_container->addTab(m_systemPage, tr("系统"));
    setCentralWidget(m_container);

}

MainWindows::~MainWindows()
{
    delete ui;
}
