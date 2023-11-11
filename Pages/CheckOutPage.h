#ifndef CHECKOUTPAGE_H
#define CHECKOUTPAGE_H

#include <QWidget>
#include "Core/Data.h"

namespace Ui {
class CheckOutPage;
}

class CheckOutPage : public QWidget
{
    Q_OBJECT

public:
    explicit CheckOutPage(QWidget *parent = nullptr);
    ~CheckOutPage();

private slots:
    void on_PB_FIND_clicked();
    void on_PB_CHECKOUT_clicked();
    void onLeaveDateChanged(const QDate& date);
private:
    Ui::CheckOutPage *ui;
    Data::RoomRecord m_record;
    bool m_valid;

    void updateFee();
};

#endif // CHECKOUTPAGE_H
