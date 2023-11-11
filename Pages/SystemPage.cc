#include "SystemPage.h"
#include "ui_SystemPage.h"
#include <QMessageBox>

SystemPage::SystemPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemPage),
    m_btnQuit(new QPushButton(this))
{
    ui->setupUi(this);
    m_btnQuit->setObjectName("btn-quit");
    m_btnQuit->move(this->width() - m_btnQuit->width(), 0);
    connect(m_btnQuit, &QPushButton::clicked, this, &SystemPage::onQuitClicked, Qt::DirectConnection);

    // 修改此处字符串实现不同的文本内容
    ui->LB_CONTENT->setText("应用名称：大众酒店管理系统\n系统版本：1.0.0\n开发者：程奔\n联系方式：152****3474\n");
}

SystemPage::~SystemPage()
{
    delete ui;
}

void SystemPage::onQuitClicked()
{
    // 再次确认是否需要退出
    auto btn = QMessageBox::question(this, tr("退出确认"), tr("请确认是否退出系统"));
    if (btn == QMessageBox::Yes) {  // 确认退出
        qApp->quit();
    } else {
        // do nothing
    }
}

/**
 * @brief SystemPage::resizeEvent
 * @param ev
 * 利用窗口大小变换事件保持退出按钮一直在右上角
 */
void SystemPage::resizeEvent(QResizeEvent *ev)
{
    QWidget::resizeEvent(ev);
    m_btnQuit->move(this->width() - m_btnQuit->width(), 0);
}
