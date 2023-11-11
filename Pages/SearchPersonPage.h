#ifndef SEARCHPERSONPAGE_H
#define SEARCHPERSONPAGE_H

#include <QWidget>
#include "Core/Data.h"

namespace Ui {
class SearchPersonPage;
}

class SearchPersonPage : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPersonPage(QWidget *parent = nullptr);
    ~SearchPersonPage();


private slots:
    void on_LE_SEARCH_clicked();

private:
    Ui::SearchPersonPage *ui;

    void updateFee(const Data::RoomRecord& record);
};

#endif // SEARCHPERSONPAGE_H
