#include "MeasDesktop.h"
#include "ui_MeasDesktop.h"

CMeasDesktop::CMeasDesktop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMeasDesktop)
{
    ui->setupUi(this);
}

CMeasDesktop::~CMeasDesktop()
{
    delete ui;
}
