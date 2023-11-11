#include "CheckInPage.h"
#include "ui_CheckInPage.h"
#include <QMessageBox>
#include "Core/Data.h"
#include "Core/RoomRecordManager.h"

CheckInPage::CheckInPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckInPage),
    m_valid(false)
{
    ui->setupUi(this);
}

CheckInPage::~CheckInPage()
{
    delete ui;
}

void CheckInPage::on_PB_SEARCH_clicked()
{
    QString name = ui->LE_NAME_1->text();
    QString phone = ui->LE_PHONE_1->text();
    QString id = ui->LE_ID_1->text();

    if (name.isEmpty() || phone.isEmpty() || id.isEmpty() || !ui->LE_PHONE_1->isValid() || !ui->LE_ID_1->isValid()) {
        QMessageBox::warning(this, tr("通知"), tr("请输入正确的个人信息"));
        return;
    } else {
        Data::Person p;
        Data::RoomRecord record;
        p.idNumber = id;
        p.phoneNumber = phone;
        p.name = name;
        RoomRecordManager* pManager = RoomRecordManager::GetInstance();
        if(!pManager->searchBookingRecordByPerson(p, record)) {
            auto result = QMessageBox::question(this, tr("通知"), tr("无预定信息，是否前往预定？"));
            if (result == QMessageBox::Yes) {
                // 发送信号跳转到预定页面
                Q_EMIT jumpToBooking(p);
            } else {

            }
        } else {
            m_valid = true;
            m_record = record;
            // 根据房型判断是否可以有同住人
            if (record.type == Data::Single) {
                ui->LE_ID_2->setEnabled(false);
                ui->LE_NAME_2->setEnabled(false);
                ui->LE_PHONE_2->setEnabled(false);
            } else {
                QMessageBox::information(this, tr("通知"), tr("已查询到预定信息，请输入同住人信息入住"));
                ui->LE_ID_2->setEnabled(true);
                ui->LE_NAME_2->setEnabled(true);
                ui->LE_PHONE_2->setEnabled(true);
            }

            ui->LE_ROOM->setText(QString::number(record.roomNum));
            ui->LE_ROOM_TYPE->setText(Data::GetRoomTypeStr(record.type));
            ui->CB_CHECKIN_DATE->setDateTime(record.checkIn);
            ui->CB_CHECKOUT_DATE->setDateTime(record.checkOut);
            QDate start = record.checkIn;
            QDate end = record.checkOut;
            int days = start.daysTo(end);
            int price = days * Data::PRICE[record.type];
            ui->LE_FEE->setText(QString::number(price));
        }
    }
}

void CheckInPage::on_PB_CHECKIN_clicked()
{
    if (!m_valid) {
        QMessageBox::warning(this, tr("通知"), tr("没有正确的预定信息，请重新查询。"));
        return;
    } else {
        QString name = ui->LE_NAME_2->text();
        QString phone = ui->LE_PHONE_2->text();
        QString id = ui->LE_ID_2->text();
        Data::Person p;
        if (m_record.type != Data::Single) {
            // 如果有输入入住人信息，则需要完整正确
            if (!name.isEmpty() || !phone.isEmpty() || !id.isEmpty()) {
                if (name.isEmpty() || phone.isEmpty() || id.isEmpty() || !ui->LE_PHONE_2->isValid() || !ui->LE_ID_2->isValid()) {
                    QMessageBox::warning(this, tr("通知"), tr("请输入正确的入住人信息"));
                    return;
                } else {
                    p.name = name;
                    p.phoneNumber = phone;
                    p.idNumber = id;
                    m_record.p2 = p;
                }
            }
        }
        RoomRecordManager* pManager = RoomRecordManager::GetInstance();
        if (pManager->checkIn(p, m_record)) {
            QMessageBox::information(this, tr("通知"), tr("入住成功，您的房间号是：%1").arg(QString::number(m_record.roomNum)));
        }   else {
            QMessageBox::warning(this, tr("通知"), tr("发生错误，请和工作人员联系。"));
        }
        m_valid = false;



    }
}

