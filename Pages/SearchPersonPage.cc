#include "SearchPersonPage.h"
#include "ui_SearchPersonPage.h"
#include <QMessageBox>
#include "Core/Data.h"
#include "Core/RoomRecordManager.h"

SearchPersonPage::SearchPersonPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchPersonPage)
{
    ui->setupUi(this);
}

SearchPersonPage::~SearchPersonPage()
{
    delete ui;
}

void SearchPersonPage::on_LE_SEARCH_clicked()
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
        if (!pManager->searchRecordByPerson(p, record)) {
            QMessageBox::warning(this, tr("通知"), tr("未查询到入住/预定记录。"));
        } else {
            ui->LE_ROOM->setText(QString::number(record.roomNum));
            ui->LE_ROOM_TYPE->setText(Data::GetRoomTypeStr(record.type));
            ui->CB_CHECKIN_DATE->setDateTime(record.checkIn);
            ui->CB_CHECKOUT_DATE->setDateTime(record.checkOut);
            // 计算费用
            updateFee(record);
            bool hasRoomMate = !record.p2.name.isEmpty();
            if (hasRoomMate) {
                auto& p2 = record.p2;
                ui->LE_NAME_2->setText(p2.name);
                ui->LE_PHONE_2->setText(p2.phoneNumber);
                ui->LE_ID_2->setText(p2.idNumber);
            }

        }
    }
}

void SearchPersonPage::updateFee(const Data::RoomRecord& record)
{
    QDate start = record.checkIn;
    QDate end = record.checkOut;
    int days = start.daysTo(end);
    int price = days * Data::PRICE[record.type];
    ui->LE_FEE->setText(QString::number(price));
}

