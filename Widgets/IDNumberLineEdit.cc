#include "IDNumberLineEdit.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QDebug>

IDNumberLineEdit::IDNumberLineEdit(QWidget* parent) : QLineEdit(parent)
{
    setMaxLength(18);
    QRegExp regx("^[1-9]\\d{5}(18|19|20)\\d{2}((0[1-9])|(1[0-2]))(([0-2][1-9])|10|20|30|31)\\d{3}[0-9Xx]$");
    QRegExpValidator* regValidator = new QRegExpValidator(regx, this);
    setValidator(regValidator);
}

bool IDNumberLineEdit::isValid() const
{
    QString content = text();
    int pos = 0;
    QValidator::State state = validator()->validate(content, pos);
    return state == QValidator::Acceptable;
}

void IDNumberLineEdit::validateText()
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

void IDNumberLineEdit::keyPressEvent(QKeyEvent *ev)
{
    QLineEdit::keyPressEvent(ev);
    validateText();
}
