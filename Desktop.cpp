#include "Desktop.h"
#include "ui_Desktop.h"

CDesktop::CDesktop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDesktop)
{
    ui->setupUi(this);

}

CDesktop::~CDesktop()
{
    delete ui;
}
