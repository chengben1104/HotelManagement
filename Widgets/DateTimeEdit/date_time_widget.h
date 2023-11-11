#ifndef DATE_TIME_WIDGET_H
#define DATE_TIME_WIDGET_H

#include <QWidget>
#include <QDate>

namespace Ui
{
	class DateTimeWidget;
}

class DateTimeWidget : public QWidget
{
Q_OBJECT

public:
	explicit DateTimeWidget(QWidget* parent = nullptr);
	~DateTimeWidget();

    void setDate(const QDate& date1);
    void setDate(const QDate& date1, const QDate& date2);
    int getFirstDay() const;
    int getSecondDay() const;
    QDate getDate1() const;
    QDate getDate2() const;

    void setRangeSelectMode(bool enable);
    bool isRangeSelecteEnabled() const;
protected:
	void showEvent(QShowEvent *event) override;

private:
	void initPage();
	void updateDays(int current);


signals:
	void signal_cancel();
    void signal_dateTime(const QDate&);
//	void signal_dateTime(const QDate&, const QTime&);

private:
	Ui::DateTimeWidget* ui;
    bool m_rangeSelect;
    QDate m_date1;
    QDate m_date2;
    QVariantList m_dayList;
    QVariantList m_yearList;
};

#endif // DATE_TIME_WIDGET_H
