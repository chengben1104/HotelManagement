#ifndef CHECKINPAGE_H
#define CHECKINPAGE_H

#include <QWidget>
#include "Core/Data.h"

namespace Ui {
class CheckInPage;
}

class CheckInPage : public QWidget
{
    Q_OBJECT

public:
    explicit CheckInPage(QWidget *parent = nullptr);
    ~CheckInPage();
Q_SIGNALS:
    void jumpToBooking(const Data::Person& p);
private slots:
    void on_PB_SEARCH_clicked();
    void on_PB_CHECKIN_clicked();

private:
    Ui::CheckInPage *ui;
    Data::RoomRecord m_record;
    bool m_valid;
};

#endif // CHECKINPAGE_H
