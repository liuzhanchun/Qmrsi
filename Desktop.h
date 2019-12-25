#ifndef DESKTOP_H
#define DESKTOP_H

#include <QWidget>
#include "SpectroThread.h"

namespace Ui {
class CDesktop;
}
class CSpectroThread;

class CDesktop : public QWidget
{
    Q_OBJECT

public:
    explicit CDesktop(QWidget *parent = nullptr);
    ~CDesktop();

private:
    Ui::CDesktop *ui;
    WRSpectroControl* chart;
    CSpectroThread* thread;
};

#endif // DESKTOP_H
