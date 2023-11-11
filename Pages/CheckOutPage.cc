#include "CheckOutPage.h"
#include "ui_CheckOutPage.h"
#include "QMessageBox"
#include "Core/RoomRecordManager.h"

CheckOutPage::CheckOutPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckOutPage),
    m_valid(false)
{
    ui->setupUi(this);
    connect(ui->CB_CHECKOUT_DATE, &DateTimeEdit::dateChanged, this, &CheckOutPage::onLeaveDateChanged, Qt::DirectConnection);
}

CheckOutPage::~CheckOutPage()
{
    delete ui;
}

void CheckOutPage::on_PB_FIND_clicked()
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
        if(!pManager->searchRecordByPerson(p, record)) {
            QMessageBox::warning(this, tr("通知"), tr("无入住信息，请联系工作人员确认。"));
        } else {
            m_valid = true;
            m_record = record;
            ui->CB_CHECKIN_DATE->setDateTime(record.checkIn);
            ui->CB_CHECKIN_DATE->setEnabled(false);
            ui->CB_CHECKOUT_DATE->setDateTime(record.checkOut);
            ui->LE_ROOM->setText(QString::number(record.roomNum));
            updateFee();
        }
    }
}


void CheckOutPage::on_PB_CHECKOUT_clicked()
{
    if (!m_valid) {
        QMessageBox::warning(this, tr("通知"), tr("没有正确的入住信息，请重新查询。"));
        return;
    } else {
        updateFee();
        RoomRecordManager* pManager = RoomRecordManager::GetInstance();
        if (!pManager->checkOut(m_record)) {
            QMessageBox::warning(this, tr("通知"), tr("发生错误，请联系工作人员"));
        } else {
            QMessageBox::information(this, tr("通知"), tr("退房成功，感谢入住。"));
        }
        m_valid = false;
    }
}

void CheckOutPage::onLeaveDateChanged(const QDate &date)
{
    updateFee();
}

void CheckOutPage::updateFee()
{
    if (m_valid) {
        QDate start = m_record.checkIn;
        QDate end = ui->CB_CHECKOUT_DATE->datetime();
        if (start > end) {
            end = m_record.checkOut;
        }
        int days = start.daysTo(end);
        int price = days * Data::PRICE[m_record.type];
        ui->LE_FEE->setText(QString::number(price));
    } else {
        ui->LE_FEE->setText("");
    }
}

