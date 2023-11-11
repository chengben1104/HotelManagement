#ifndef ROOMSUMMARYTABLE_H
#define ROOMSUMMARYTABLE_H

#include <QTableWidget>
#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLabel>
#include <QHBoxLayout>

#include "Core/Data.h"

class RoomSummaryTable : public QTableWidget
{
    Q_OBJECT
public:
    struct RowWidgetItem {
        QRadioButton* radio;
        QLabel* picture;
        QLabel* type;
        QLabel* price;
        QLabel* remain;
        QLabel* amount;
    };
    RoomSummaryTable(QWidget* parent=nullptr);

    void setRoomSummary(const Data::RoomSummary& summary);
    Data::RoomType getSelectedRoomType() const;
Q_SIGNALS:
    void roomTypeChanged(Data::RoomType type);
private:
    Data::RoomSummary m_summary;
    RowWidgetItem m_items[4];
    QButtonGroup* m_radioGroup;

    void createItems();

private Q_SLOTS:
    void onButtonIdChanged(int id);
//protected:
//    virtual void showEvent(QShowEvent* ev) override;
};

#endif // ROOMSUMMARYTABLE_H
