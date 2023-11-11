#include "SearchPage.h"
#include "ui_SearchPage.h"
#include "SearchPersonPage.h"
#include "SearchRoomPage.h"

SearchPage::SearchPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchPage)
{
    ui->setupUi(this);
    ui->STACK_WID->addWidget(new SearchRoomPage(this));
    ui->STACK_WID->addWidget(new SearchPersonPage(this));
}

SearchPage::~SearchPage()
{
    delete ui;
}

void SearchPage::on_RB_ROOM_clicked()
{
    ui->STACK_WID->setCurrentIndex(0);
}

void SearchPage::on_RD_PERSON_clicked()
{
    ui->STACK_WID->setCurrentIndex(1);
}

