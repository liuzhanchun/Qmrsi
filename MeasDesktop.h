#ifndef MEASDESKTOP_H
#define MEASDESKTOP_H

#include <QWidget>

namespace Ui {
class CMeasDesktop;
}

class CMeasDesktop : public QWidget
{
    Q_OBJECT

public:
    explicit CMeasDesktop(QWidget *parent = nullptr);
    ~CMeasDesktop();

private slots:
    void btn_ModeClick();

private:
    Ui::CMeasDesktop *ui;
};

#endif // MEASDESKTOP_H
