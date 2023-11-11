#include "RoomSummaryTable.h"
#include <QHeaderView>
#include <QDebug>

RoomSummaryTable::RoomSummaryTable(QWidget* parent) : QTableWidget(parent)
{
    const QStringList headers = QStringList() << "" << tr("照片") << tr("房型") << tr("单价/天") << tr("空房数") << tr("总量") << tr("");
    setRowCount(Data::ROOM_TYPE_COUNT);
    setColumnCount(headers.count());
    setHorizontalHeaderLabels(headers);
    const int WIDTH[7] = {40, 256, 100, 96, 96, 96, };
    for (int col = 0; col < headers.count(); ++col) {
        horizontalHeader()->setSectionResizeMode(col, QHeaderView::Fixed);
        setColumnWidth(col, WIDTH[col]);
    }

    horizontalHeader()->setSectionResizeMode(headers.count() - 1, QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setSelectionMode(QAbstractItemView::NoSelection);
    createItems();
}

void RoomSummaryTable::setRoomSummary(const Data::RoomSummary &summary)
{
    m_summary = summary;
    for (int i = 0; i < 4; ++i) {
        auto& pInfo = m_summary.info[i];
        auto& pWid = m_items[i];
        pWid.type->setText(Data::GetRoomTypeStr(pInfo));
        pWid.type->setAlignment(Qt::AlignCenter);
        pWid.remain->setText(QString::number(pInfo.remain));
        pWid.remain->setAlignment(Qt::AlignCenter);
        pWid.amount->setText(QString::number(pInfo.amount));
        pWid.amount->setAlignment(Qt::AlignCenter);
        pWid.price->setText(QString::number(pInfo.price));
        pWid.price->setAlignment(Qt::AlignCenter);
        pWid.picture->setScaledContents(true);
        QPixmap pixmap;
        pixmap.load(Data::GetRoomTypePicturePath(pInfo));
        pWid.picture->setPixmap(pixmap);
    }
}

Data::RoomType RoomSummaryTable::getSelectedRoomType() const
{
    Data::RoomType type = Data::Invalid;
    int value = m_radioGroup->checkedId();
    if (value == -1) {
        return type;
    } else {
        type = static_cast<Data::RoomType>(value);
    }
    return type;
}

void RoomSummaryTable::createItems()
{
    for (int row = 0; row < 4; ++row) {
        QWidget** pWid = reinterpret_cast<QWidget**>(&m_items[row]);
        auto& pItem = m_items[row];
        pItem.radio = new QRadioButton(this);
        pItem.picture = new QLabel(this);
        pItem.type = new QLabel(this);
        pItem.price = new QLabel(this);
        pItem.remain = new QLabel(this);
        pItem.amount = new QLabel(this);

        for (int col = 0; col < 6; ++col) {
            QWidget* pContainer = new QWidget(this);
            QHBoxLayout* pLayout = new QHBoxLayout;
            pLayout->addWidget(pWid[col]);
            pContainer->setLayout(pLayout);
            setCellWidget(row, col, pContainer);
        }
    }

    m_radioGroup = new QButtonGroup(this);
    for (int row = 0; row < 4; ++row) {
        m_radioGroup->addButton(m_items[row].radio, row);
    }
    connect(m_radioGroup, &QButtonGroup::idClicked,
            this, &RoomSummaryTable::onButtonIdChanged, Qt::DirectConnection);
}

void RoomSummaryTable::onButtonIdChanged(int id)
{
    Data::RoomType type = static_cast<Data::RoomType>(id);
    Q_EMIT roomTypeChanged(type);
}

//void RoomSummaryTable::showEvent(QShowEvent *ev)
//{
//    setRoomSummary(Data::gRoomSummary);
//    QTableWidget::showEvent(ev);
//}
