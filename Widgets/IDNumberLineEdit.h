#ifndef IDNUMBERLINEEDIT_H
#define IDNUMBERLINEEDIT_H

#include <QLineEdit>
#include <QWidget>

class IDNumberLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    IDNumberLineEdit(QWidget* parent=nullptr);
    bool isValid() const;
private Q_SLOTS:
    void validateText();
protected:
    virtual void keyPressEvent(QKeyEvent* ev) override;
};

#endif // IDNUMBERLINEEDIT_H
