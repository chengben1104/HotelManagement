#include "date_time_edit.h"
#include "date_time_widget.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QDateTime>
DateTimeEdit::DateTimeEdit(QWidget *parent) : QComboBox(parent)
{
	initPage();
}

void DateTimeEdit::initPage()
{
	auto table = new QTableWidget;
    table->setMinimumHeight(360);
    table->setMaximumHeight(480);
    //table->setMinimumWidth(280);
	table->verticalHeader()->setVisible(false);
	table->horizontalHeader()->setVisible(false);
	table->setColumnCount(1);
	table->setRowCount(1);

	auto cell = new DateTimeWidget;
    cell->setMinimumHeight(360);
    cell->setMinimumWidth(285);
    table->setCellWidget(0, 0, cell);
    cell->setDate(QDate::currentDate());
	this->setModel(table->model());
	this->setView(table);

    this->setEditable(true);
	this->setProperty("type", "datetime");

    connect(cell, &DateTimeWidget::signal_dateTime, this, [this](const QDate& dt)
	{
        this->setEditText(dt.toString("yyyy-MM-dd"));
		this->hidePopup();
        Q_EMIT dateChanged(dt);
	});

	connect(cell, &DateTimeWidget::signal_cancel, this, [this]
	{
		hidePopup();
	});
}

void DateTimeEdit::setDateTime(const QDate& dt)
{
	auto pTable = static_cast<QTableWidget*>(const_cast<QAbstractItemView*>(view()));
	auto pWidget = static_cast<DateTimeWidget*>(pTable->cellWidget(0, 0));
    pWidget->setDate(dt);
    this->setEditText(dt.toString("yyyy-MM-dd"));
}

QDate DateTimeEdit::datetime() const
{
    return QDate::fromString(this->currentText(), "yyyy-MM-dd");
}
