#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include <QWidget>

namespace Ui {
class SearchPage;
}

class SearchPage : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPage(QWidget *parent = nullptr);
    ~SearchPage();

private slots:
    void on_RB_ROOM_clicked();

    void on_RD_PERSON_clicked();

private:
    Ui::SearchPage *ui;
};

#endif // SEARCHPAGE_H
