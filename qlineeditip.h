#ifndef QLINEEDITIP_H
#define QLINEEDITIP_H

#include <QLineEdit>
#include <QKeyEvent>

class QLineEditIP : public QLineEdit
{
    Q_OBJECT

public:
    explicit QLineEditIP(QWidget *parent = 0);
    QString shiftText(QString str);
    QString insertShift(QString tr);
    int insertTextPosition(QString str ,QString data ,QString str2);
    QString shift(QString tr);
    void setFont(QFont &font);
    int rightMove(QString tr,int C);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QString IP;
    QString space;
};

#endif // QLINEEDITIP_H
