#include "SearchRoomPage.h"
#include "ui_SearchRoomPage.h"
#include <QDebug>
#include "Core/RoomRecordManager.h"
#include <QMessageBox>

SearchRoomPage::SearchRoomPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchRoomPage)
{
    ui->setupUi(this);
    ui->TB_SUMMARY->hideColumn(1);  //隐藏图片
   // ui->TB_SUMMARY->hideColumn(3);  //隐藏单价
    connect(ui->TB_SUMMARY, &RoomSummaryTable::roomTypeChanged,
            this, &SearchRoomPage::onRoomTypeChanged, Qt::DirectConnection);
    connect(ui->CB_DATE_START, &DateTimeEdit::dateChanged,
            this, &SearchRoomPage::onStartDateChanged, Qt::DirectConnection);
    connect(ui->CB_DATE_END, &DateTimeEdit::dateChanged,
            this, &SearchRoomPage::onEndDateChanged, Qt::DirectConnection);
}

SearchRoomPage::~SearchRoomPage()
{
    delete ui;
}

void SearchRoomPage::updateRoomSummary()
{
    if (m_dateStart < m_dateEnd) {
        Data::RoomSummary summary = RoomRecordManager::GetInstance()->getRoomSummary(m_dateStart, m_dateEnd);
        ui->TB_SUMMARY->setRoomSummary(summary);
    }
}

void SearchRoomPage::onRoomTypeChanged(Data::RoomType type)
{
    //查询对应房间空余的房间号，并在列表中显示
    RoomRecordManager* pManager = RoomRecordManager::GetInstance();
    QList<int> rooms = pManager->getFreeRoomList(type, ui->CB_DATE_START->datetime(), ui->CB_DATE_END->datetime());
    ui->LST_ROOM_REMAIN->clear();
    QStringList labels;
    for (auto& room : rooms) {
        labels << QString::number(room);
    }
    ui->LST_ROOM_REMAIN->addItems(labels);
}

void SearchRoomPage::onStartDateChanged(const QDate &start)
{
    m_dateStart = start;
    updateRoomSummary();
}

void SearchRoomPage::onEndDateChanged(const QDate &end)
{
    m_dateEnd = end;
    updateRoomSummary();
}

void SearchRoomPage::on_PB_SEARCH_NUMBER_clicked()
{
    const QString room = ui->LE_ROOM_NUMBER->text();
    bool ok = true;
    int roomId = room.toInt(&ok);
    if (!ok || (roomId < Data::ROOM_ID_OFFSET || roomId > Data::ROOM_ID_OFFSET + Data::ROOM_AMOUNT)) {
        QMessageBox::critical(this, tr("通知"), tr("请输入正确的房间号"));
    } else {
        Data::RoomRecord record;
        record.roomNum = roomId;
        RoomRecordManager* pManager = RoomRecordManager::GetInstance();
        if(!pManager->searchRecordByRoom(m_dateStart, m_dateEnd, record)) {
            QMessageBox::information(this, tr("通知"), tr("该房间当前时段内空闲"));
        } else {
            QString state = record.isCheckIn ? tr("入住") : tr("预定");
            QString info = QString("该房间已被%1\n%1人：%2\n入住时间：%3\n离店时间：%4")
                    .arg(state)
                    .arg(record.p.name)
                    .arg(record.checkIn.toString("yyyy-MM-dd"))
                    .arg(record.checkOut.toString("yyyy-MM-dd"));
            QMessageBox::information(this, tr("通知"), info);
        }
    }
}

