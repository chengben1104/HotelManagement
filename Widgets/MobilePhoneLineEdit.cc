#include "MobilePhoneLineEdit.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QDebug>

MobilePhoneLineEdit::MobilePhoneLineEdit(QWidget* parent) : QLineEdit(parent)
{

    QRegExp regx("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
    QRegExpValidator* regValidator = new QRegExpValidator(regx, this);
    setValidator(regValidator);
//    connect(this, &QLineEdit::editingFinished, this, &MobilePhoneLineEdit::onValidatorChanged, Qt::DirectConnection);
//    connect(this, &QLineEdit::returnPressed, this, &MobilePhoneLineEdit::onValidatorChanged, Qt::DirectConnection);

}

bool MobilePhoneLineEdit::isValid() const
{
    QString content = text();
    int pos = 0;
    QValidator::State state = validator()->validate(content, pos);
    return state == QValidator::Acceptable;
}

void MobilePhoneLineEdit::validateText()
{
    QString content = text();
    int pos = 0;
    QValidator::State state = validator()->validate(content, pos);
    if (state != QValidator::Acceptable) {
        setStyleSheet("\
                      QLineEdit { \
                          border: 1px solid red; \
                      } \
                      ");
    } else {
        setStyleSheet("\
                      QLineEdit { \
                          border: 1px solid black; \
                      } \
                      ");
    }
}

void MobilePhoneLineEdit::keyPressEvent(QKeyEvent *ev)
{
    QLineEdit::keyPressEvent(ev);
    validateText();
}
