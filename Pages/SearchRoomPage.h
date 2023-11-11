#ifndef SEARCHROOMPAGE_H
#define SEARCHROOMPAGE_H

#include <QWidget>
#include "Core/Data.h"

namespace Ui {
class SearchRoomPage;
}

class SearchRoomPage : public QWidget
{
    Q_OBJECT

public:
    explicit SearchRoomPage(QWidget *parent = nullptr);
    ~SearchRoomPage();

private slots:
    void on_PB_SEARCH_NUMBER_clicked();

private:
    Ui::SearchRoomPage *ui;
    QDate m_dateStart;
    QDate m_dateEnd;

    void updateRoomSummary();
private Q_SLOT:
    void onRoomTypeChanged(Data::RoomType type);
    void onStartDateChanged(const QDate& start);
    void onEndDateChanged(const QDate& end);

};

#endif // SEARCHROOMPAGE_H
