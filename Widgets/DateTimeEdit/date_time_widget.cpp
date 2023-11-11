#include "date_time_widget.h"
#include "ui_date_time_widget.h"
#include "Widgets/DateTimeEdit/button_day.h"
#include <QDateTime>
#include <QDate>
#include <QMenu>

DateTimeWidget::DateTimeWidget(QWidget* parent) : QWidget(parent), ui(new Ui::DateTimeWidget),
    m_rangeSelect(false)
{
    ui->setupUi(this);
    initPage();
}

DateTimeWidget::~DateTimeWidget()
{
    delete ui;
}

void DateTimeWidget::setDate(const QDate &date1)
{
    m_date1 = date1;
}

void DateTimeWidget::initPage()
{
#if SUPPORT_C11
#else
    DateTime::MapInsert::initMonth();
#endif
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);

    auto pMenu = new QMenu(this);
    pMenu->setProperty("type", "month");
    ui->btnMonth->setMenu(pMenu);

    for (auto itor = DateTime::month().begin(); itor != DateTime::month().end(); ++itor)
    {
        auto pMonth = pMenu->addAction(itor.value(), this, [this]
        {
            auto const pAction = qobject_cast<QAction*>(sender());
            if (Q_NULLPTR == pAction)
            {
                return;
            }
            ui->btnMonth->setText(pAction->text());
            ui->btnMonth->setData(DateTime::month().key(pAction->text()));

//			updateDays(ui->dateEdit->date().day());
        });

        pMonth->setData(itor.key());
    }

    // day widget
    for (int index = 0; index < 42; ++index)
    {
        auto btn = new ButtonDay(index + 1);
        btn->setFixedSize(QSize(30, 30));
        ui->gridLayout->addWidget(btn, index / 7, index % 7);

        btn->setType(((index % 7 == 0) || (index % 7 == 6)) ? DateTime::WEEKEND : DateTime::WORKDAY);
        btn->setRole(DateTime::CURRENT_MONTH);

        m_dayList.append(QVariant::fromValue(static_cast<void*>(btn)));

        connect(btn, &QPushButton::clicked, this, [this]
        {
            for (const auto& pbt : m_dayList)
            {
                auto pb = static_cast<ButtonDay*>(pbt.value<void*>());
                if (Q_NULLPTR == pb)
                {
                    continue;
                }

//                if (pb->role().testFlag(DateTime::SELECT_DAY))
//                {
//                    pb->setRole(DateTime::CURRENT_MONTH);
//                    break;
//                }
            }

            auto const btn = qobject_cast<ButtonDay*>(sender());
            btn->setRole(DateTime::SELECT_DAY);

            if (btn->month().testFlag(DateTime::PREV_MONTH_DAY))
            {
                if (ui->btnMonth->data().toInt() == 1)
                {
                    ui->btnMonth->setData(12);
                    ui->btnYear->setData(ui->btnYear->data().toInt() - 1);
                    ui->btnYear->setText(QString("%1年").arg(ui->btnYear->data().toInt()));
                }
                else
                {
                    ui->btnMonth->setData(ui->btnMonth->data().toInt() - 1);
                }
                ui->btnMonth->setText(DateTime::month().value(ui->btnMonth->data().toInt()));
            }

            if (btn->month().testFlag(DateTime::NEXT_MONTH_DAY))
            {
                if (ui->btnMonth->data().toInt() == 12)
                {
                    ui->btnMonth->setData(1);
                    ui->btnYear->setData(ui->btnYear->data().toInt() + 1);
                    ui->btnYear->setText(QString("%1年").arg(ui->btnYear->data().toInt()));
                }
                else
                {
                    ui->btnMonth->setData(ui->btnMonth->data().toInt() + 1);
                }
                ui->btnMonth->setText(DateTime::month().value(ui->btnMonth->data().toInt()));
            }

            updateDays(btn->data().toInt());
        });
    }

    // year widget
    for (int index = 0; index < 20; ++index)
    {
        auto btn = new ButtonDay(index + 1);
        btn->setFixedSize(QSize(60, 30));
        ui->gridLayoutYears->addWidget(btn, index / 4, index % 4);
//		btn->setData(ui->dateEdit->date().year() - 10 + index);
        btn->setText(QString("%1年").arg(btn->data().toInt()));
        btn->setRole(DateTime::OTHER);

        m_yearList.append(QVariant::fromValue(static_cast<void*>(btn)));
        connect(btn, &QPushButton::clicked, this, [this]
        {
            for (const auto& pbt : m_yearList)
            {
                auto pb = static_cast<ButtonDay*>(pbt.value<void*>());
                if (Q_NULLPTR == pb)
                {
                    continue;
                }

                if (pb->role().testFlag(DateTime::CURRENT_YEAR))
                {
                    pb->setRole(DateTime::OTHER);
                    break;
                }
            }

            auto const btn = qobject_cast<ButtonDay*>(sender());
            btn->setRole(DateTime::CURRENT_YEAR);
            ui->stackedWidget->setCurrentWidget(ui->wdgCalendar);
            ui->btnYear->setData(btn->data());
            ui->btnYear->setText(QString("%1年").arg(btn->data().toInt()));
//			updateDays(ui->dateEdit->date().day());

            ui->btnMonth->setVisible(true);
            ui->btnPrev->setVisible(true);
            ui->btnNext->setVisible(true);
            ui->wdgConfirm->setVisible(true);
        });
    }

    connect(ui->btnYear, &QPushButton::clicked, this, [this]
    {
        int index = 0;
        for (const auto& pbt : m_yearList)
        {
            auto btn = static_cast<ButtonDay*>(pbt.value<void*>());
            if (Q_NULLPTR == btn)
            {
                continue;
            }

            btn->setData(ui->btnYear->data().toInt() - 10 + index++);
            btn->setText(QString("%1年").arg(btn->data().toInt()));
            btn->setRole(ui->btnYear->data().toInt() == btn->data().toInt() ? DateTime::CURRENT_YEAR : DateTime::OTHER);
        }
        ui->stackedWidget->setCurrentWidget(ui->wdgYears);

        ui->btnMonth->setVisible(false);
        ui->btnPrev->setVisible(false);
        ui->btnNext->setVisible(false);
        ui->wdgConfirm->setVisible(false);
    });

    connect(ui->btnToday, &QPushButton::clicked, this, [this]
    {
        QDate dt = QDate::currentDate();
        ui->btnMonth->setData(dt.month());
        ui->btnYear->setData(dt.year());
        ui->btnMonth->setText(DateTime::month().value(dt.month()));
        ui->btnYear->setText(QString("%1年").arg(dt.year()));

        updateDays(dt.day());
    });



    connect(ui->btnConfirm, &QPushButton::clicked, this, [this]
    {
        Q_EMIT signal_dateTime(m_date1);
        Q_EMIT signal_cancel();
    });

    connect(ui->btnCancel, &QPushButton::clicked, this, [this]
    {
        emit signal_cancel();
    });

    connect(ui->btnPrev, &QPushButton::clicked, this, [this]
    {
        int _days = getFirstDay();
        if (ui->btnMonth->data().toInt() == 1)
        {
            ui->btnMonth->setData(12);
            ui->btnYear->setData(ui->btnYear->data().toInt() - 1);
            ui->btnYear->setText(QString("%1年").arg(ui->btnYear->data().toInt()));
        }
        else
        {
            ui->btnMonth->setData(ui->btnMonth->data().toInt() - 1);
        }
        ui->btnMonth->setText(DateTime::month().value(ui->btnMonth->data().toInt()));

        updateDays(_days);
    });

    connect(ui->btnNext, &QPushButton::clicked, this, [this]
    {
        int _days = getFirstDay();
        if (ui->btnMonth->data().toInt() == 12)
        {
            ui->btnMonth->setData(1);
            ui->btnYear->setData(ui->btnYear->data().toInt() + 1);
            ui->btnYear->setText(QString("%1年").arg(ui->btnYear->data().toInt()));
        }
        else
        {
            ui->btnMonth->setData(ui->btnMonth->data().toInt() + 1);
        }
        ui->btnMonth->setText(DateTime::month().value(ui->btnMonth->data().toInt()));

        updateDays(_days);
    });

}

void DateTimeWidget::showEvent(QShowEvent *event)
{
    ui->stackedWidget->setCurrentWidget(ui->wdgCalendar);
    if(!ui->wdgConfirm->isVisible())
    {
        ui->btnMonth->setVisible(false);
        ui->btnPrev->setVisible(false);
        ui->btnNext->setVisible(false);
        ui->wdgConfirm->setVisible(false);
    }
    QDate dt = QDate::currentDate();
    if(!m_date1.isValid()) {
        dt = QDate::currentDate();
    } else {
        dt = m_date1;
    }
    ui->btnMonth->setData(dt.month());
    ui->btnYear->setData(dt.year());
    ui->btnMonth->setText(DateTime::month().value(dt.month()));
    ui->btnYear->setText(QString("%1年").arg(dt.year()));

    updateDays(dt.day());
}

void DateTimeWidget::updateDays(int current)
{
    QDate dt = QDate(ui->btnYear->data().toInt(), ui->btnMonth->data().toInt(), 01);
    int days = dt.dayOfWeek();

    QDate prevDt = dt.addDays(-1);

    int offset = prevDt.day() - days + 1;
    for (int index = 0; index < days; ++index)
    {
        auto btn = static_cast<ButtonDay*>(m_dayList[index].value<void*>());
        btn->setText(QString::number(offset + index));
        btn->setData(offset + index);
        btn->setMonth(DateTime::PREV_MONTH_DAY);
        btn->setRole(DateTime::NON_CURRENY_MONTH);
    }

    QDate nextDt = dt.addMonths(1).addDays(-1);
    int count = nextDt.day() - dt.day() + 1;

    offset = 0;
    bool hasFirstSelectDay = false;
    int firstOffset = 0;
    for (int index = days; index < count + days; ++index)
    {
        auto btn = static_cast<ButtonDay*>(m_dayList[index].value<void*>());
        btn->setText(QString::number(++offset));
        btn->setData(offset);

        if (!m_rangeSelect) {
            btn->setRole(DateTime::CURRENT_MONTH);
            if (offset == current) {
                btn->setRole(DateTime::SELECT_DAY);
                m_date1 = QDate(ui->btnYear->data().toInt(), ui->btnMonth->data().toInt(), getFirstDay());
            }
        } else {
            if (btn->role().testFlag(DateTime::SELECT_DAY)) {
                hasFirstSelectDay = true;
                firstOffset = offset;
                if (firstOffset >= offset) {    //选择的日期先于当前日期，重新选择
                    btn->setMonth(DateTime::CURRENT_MONTH_DAY);
                    hasFirstSelectDay = false;
                }
            } else {
                btn->setMonth(DateTime::CURRENT_MONTH_DAY);
            }

            // 选定日期
            if (offset == current)
            {
                if (hasFirstSelectDay) {
                    for (int _index = days; _index < count + days; ++_index) {
                        auto btn = static_cast<ButtonDay*>(m_dayList[index].value<void*>());
                        if (btn->role().testFlag(DateTime::SELECT_DAY2)) {
                            btn->setRole(DateTime::CURRENT_MONTH);
                        }
                    }
                    btn->setRole(DateTime::SELECT_DAY2);
                    m_date2 = QDate(ui->btnYear->data().toInt(), ui->btnMonth->data().toInt(), btn->data().toInt());
                } else {
                    btn->setRole(DateTime::SELECT_DAY);
                    m_date1 = QDate(ui->btnYear->data().toInt(), ui->btnMonth->data().toInt(), btn->data().toInt());
                }
            }
        }

    }

    offset = 0;
    for (int index = count + days; index < m_dayList.size(); ++index)
    {
        auto btn = static_cast<ButtonDay*>(m_dayList[index].value<void*>());
        btn->setText(QString::number(++offset));
        btn->setData(offset);
        btn->setMonth(DateTime::NEXT_MONTH_DAY);
        btn->setRole(DateTime::NON_CURRENY_MONTH);
    }
//	ui->dateEdit->setDate(QDate(ui->btnYear->data().toInt(), ui->btnMonth->data().toInt(), current));

    QDate cdt = QDate::currentDate();
//	if (ui->dateEdit->date().month() != cdt.month() || ui->dateEdit->date().year() != cdt.year())
//	{
//		return;
//	}

    for (const auto& btn : m_dayList)
    {
        auto pb = static_cast<ButtonDay*>(btn.value<void*>());
        if (Q_NULLPTR == pb)
        {
            continue;
        }

        if (pb->month().testFlag(DateTime::CURRENT_MONTH_DAY) && !pb->role().testFlag(DateTime::SELECT_DAY) && pb->data().toInt() == cdt.day())
        {
            pb->setRole(DateTime::CURRENT_DAY);
            break;
        }
    }
}

int DateTimeWidget::getFirstDay() const
{
    int day = 0;
    for (int idx = 0; idx < m_dayList.count(); ++idx) {
        auto btn = static_cast<ButtonDay*>(m_dayList[idx].value<void*>());
        if (btn->role() == DateTime::SELECT_DAY) {
            day = btn->data().toInt();
            break;
        }
    }
    return day;
}

int DateTimeWidget::getSecondDay() const
{
    int day = 0;
    for (int idx = 0; idx < m_dayList.count(); ++idx) {
        auto btn = static_cast<ButtonDay*>(m_dayList[idx].value<void*>());
        if (btn->role() == DateTime::SELECT_DAY2) {
            day = btn->data().toInt();
        }
    }
    return day;
}

QDate DateTimeWidget::getDate1() const
{
    return m_date1;
}

QDate DateTimeWidget::getDate2() const
{
    return m_date2;
}

void DateTimeWidget::setRangeSelectMode(bool enable)
{
    m_rangeSelect = enable;
}

bool DateTimeWidget::isRangeSelecteEnabled() const
{
    return m_rangeSelect;
}

void DateTimeWidget::setDate(const QDate &date1, const QDate &date2)
{
    m_date1 = date1;
    m_date2 = date2;
}
