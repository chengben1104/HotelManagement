#ifndef DATE_TIME_EDIT_H
#define DATE_TIME_EDIT_H

#include <QComboBox>

class DateTimeEdit : public QComboBox
{
	Q_OBJECT
public:
	explicit DateTimeEdit(QWidget *parent = 0);

    QDate datetime() const;
    void setDateTime(const QDate& dt);
Q_SIGNALS:
    void dateChanged(const QDate& dt);
private:
	void initPage();
};
#endif // DATE_TIME_EDIT_H
