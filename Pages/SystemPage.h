#ifndef SYSTEMPAGE_H
#define SYSTEMPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QResizeEvent>

namespace Ui {
class SystemPage;
}

class SystemPage : public QWidget
{
    Q_OBJECT

public:
    explicit SystemPage(QWidget *parent = nullptr);
    ~SystemPage();

private:
    Ui::SystemPage *ui;
    QPushButton* m_btnQuit;

private Q_SLOTS:
    void onQuitClicked();
protected:
    virtual void resizeEvent(QResizeEvent* ev) override;
};

#endif // SYSTEMPAGE_H
