#ifndef MOBILEPHONELINEEDIT_H
#define MOBILEPHONELINEEDIT_H

#include <QLineEdit>
#include <QWidget>

class MobilePhoneLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    MobilePhoneLineEdit(QWidget* parent=nullptr);
    bool isValid() const;
private Q_SLOTS:
    void validateText();

protected:
    virtual void keyPressEvent(QKeyEvent* ev) override;
};

#endif // MOBILEPHONELINEEDIT_H
