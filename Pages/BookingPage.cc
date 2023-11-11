#include "BookingPage.h"
#include "ui_BookingPage.h"

#include <QMessageBox>

BookingPage::BookingPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookingPage)
{
    ui->setupUi(this);
    connect(ui->CB_CHECKIN_DATE, &DateTimeEdit::dateChanged, this, &BookingPage::onStartDateChanged, Qt::DirectConnection);
    connect(ui->CB_CHECKOUT_DATE, &DateTimeEdit::dateChanged, this, &BookingPage::onEndDateChanged, Qt::DirectConnection);
    connect(ui->TB_ROOM_INFO, &RoomSummaryTable::roomTypeChanged, this, &BookingPage::onRoomTypeChanged, Qt::DirectConnection);
}

BookingPage::~BookingPage()
{
    delete ui;
}

void BookingPage::setPerson(const Data::Person &p)
{
    ui->LE_NAME->setText(p.name);
    ui->LE_PHONE_NUMBER->setText(p.phoneNumber);
    ui->LE_ID->setText(p.idNumber);
}

/**
 * @brief BookingPage::on_PB_CONFIRM_clicked
 * 预定按钮处理函数
 */
void BookingPage::on_PB_CONFIRM_clicked()
{
    Data::RoomType type = ui->TB_ROOM_INFO->getSelectedRoomType();

    // 判断是否选择了正确的房间信息
    if (type == Data::RoomType::Invalid) {
        QMessageBox::warning(this, tr("通知"), tr("请选择要预定的房型"));
        return;
    }

    if (ui->LE_NAME->text().isEmpty() || !ui->LE_PHONE_NUMBER->isValid() || !ui->LE_ID->isValid()) {
        QMessageBox::warning(this, tr("通知"), tr("请输入正确的个人信息"));
        return;
    }

    Data::Person p;
    p.idNumber = ui->LE_ID->text();
    p.phoneNumber = ui->LE_ID->text();
    p.name = ui->LE_NAME->text();
    if (ui->RB_MALE->isChecked()) {
        p.gender = Data::Gender::Male;
    } else {
        p.gender = Data::Gender::Female;
    }
    Data::RoomRecord record;
    record.checkIn = m_dateStart;
    record.checkOut = m_dateEnd;
    record.p = p;
    record.type = type;

    RoomRecordManager* pManager = RoomRecordManager::GetInstance();
    if(!pManager->booking(record)) {
        QMessageBox::critical(this, tr("通知"), tr("预定失败，请联系工作人员"));
    } else {
        QMessageBox::information(this, tr("通知"), tr("预定成功"));
        Q_EMIT checkInRecord(record);
    }
    updateRoomSummary();
}

void BookingPage::onStartDateChanged(const QDate &date)
{
    m_dateStart = date;
    updateRoomSummary();
    updateFee();
}

void BookingPage::onEndDateChanged(const QDate &date)
{
    m_dateEnd = date;
    updateRoomSummary();
    updateFee();
}

void BookingPage::onRoomTypeChanged(Data::RoomType type)
{
    Q_UNUSED(type);
    updateFee();
}

void BookingPage::updateRoomSummary()
{
    if (m_dateStart < m_dateEnd) {
        Data::RoomSummary summary = RoomRecordManager::GetInstance()->getRoomSummary(m_dateStart, m_dateEnd);
        ui->TB_ROOM_INFO->setRoomSummary(summary);
        int days = m_dateStart.daysTo(m_dateEnd);
       ui->LE_DAY->setText(QString::number(days));
    } else {
        ui->LE_DAY->setText("");
    }
}

void BookingPage::updateFee()
{
    if (m_dateStart < m_dateEnd) {
        int days = m_dateStart.daysTo(m_dateEnd);
        Data::RoomType type = ui->TB_ROOM_INFO->getSelectedRoomType();
        // 更新价格
        if (type != Data::RoomType::Invalid) {
            double fee = days * Data::PRICE[type];
            ui->LE_FEE->setText(QString::number(fee));
        } else {
            ui->LE_FEE->setText("");
        }
    } else {
        ui->LE_FEE->setText("");
    }

}

void BookingPage::showEvent(QShowEvent *ev)
{
    QWidget::showEvent(ev);
    updateRoomSummary();
}

