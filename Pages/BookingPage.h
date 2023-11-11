#ifndef BOOKINGPAGE_H
#define BOOKINGPAGE_H

#include <QWidget>
#include <QDate>
#include <QShowEvent>
#include "Core/RoomRecordManager.h"

namespace Ui {
class BookingPage;
}

class BookingPage : public QWidget
{
    Q_OBJECT

public:
    explicit BookingPage(QWidget *parent = nullptr);
    ~BookingPage();

    void setPerson(const Data::Person& p);
Q_SIGNALS:
    void checkInRecord(const Data::RoomRecord& record);
private slots:
    void on_PB_CONFIRM_clicked();
    void onStartDateChanged(const QDate& date);
    void onEndDateChanged(const QDate& date);
    void onRoomTypeChanged(Data::RoomType type);
private:
    Ui::BookingPage *ui;
    QDate m_dateStart;
    QDate m_dateEnd;

    /**
     * @brief updateRoomSummary
     * 更新房间情况表格的方法
     */
    void updateRoomSummary();
    void updateFee();

protected:
    virtual void showEvent(QShowEvent* ev) override;
};

#endif // BOOKINGPAGE_H
