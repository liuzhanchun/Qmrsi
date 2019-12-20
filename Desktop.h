#ifndef DESKTOP_H
#define DESKTOP_H

#include <QWidget>

namespace Ui {
class CDesktop;
}

class CDesktop : public QWidget
{
    Q_OBJECT

public:
    explicit CDesktop(QWidget *parent = nullptr);
    ~CDesktop();

private:
    Ui::CDesktop *ui;
};

#endif // DESKTOP_H
