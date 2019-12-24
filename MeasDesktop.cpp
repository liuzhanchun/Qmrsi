#include "MeasDesktop.h"
#include "ui_MeasDesktop.h"
#include "MeasSwitch.h"

CMeasDesktop::CMeasDesktop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMeasDesktop)
{
    ui->setupUi(this);
    QList<QToolButton *> btns = this->findChildren<QToolButton *>();
    foreach (QToolButton * btn, btns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btn_ModeClick()));
    }
}

CMeasDesktop::~CMeasDesktop()
{
    delete ui;
}
void CMeasDesktop::btn_ModeClick()
{
    QToolButton *btn = (QToolButton *)sender();
    QString objName = btn->objectName();
    if (objName == "FFM")
    {
        g_MeasSwitch.EnterLock();
        g_MeasSwitch.SwitchMeas(RXFFM);
        g_MeasSwitch.LeaveLock();

    }
    else if (objName == "PSCAN")
    {
        g_MeasSwitch.EnterLock();
        g_MeasSwitch.SwitchMeas(RXPSCAN);
        g_MeasSwitch.LeaveLock();
    }
    else if (objName == "DFIND")
    {

    }

}
