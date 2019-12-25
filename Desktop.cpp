#include "Desktop.h"
#include "ui_Desktop.h"
#include "SpecParams.h"
#include <qstring.h>
CDesktop::CDesktop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDesktop)
{
    ui->setupUi(this);
   // WRSpectroControl ttt;
    chart = new WRSpectroControl();
    chart->channel(0)->lineColor(WRColor(0xF5, 0xF5, 0xF5));
    chart->channel(1)->lineColor(QColor(Qt::green));
    chart->channel(1)->markColor(QColor(Qt::red));
    chart->channel(1)->dataZoomMethod(WRSpectroChannel::ShowDataRange);
    thread = new CSpectroThread(chart);
    chart->attach(ui->spec);
    WRSpectroDataPointLineElement* vLine = chart->addDataPointLine(10);
    vLine->color(QColor(Qt::red));
    WRSpectroDataValueLineElement* hLine = chart->addDataValueLine(100);
    hLine->color(QColor(Qt::red));
    chart->dataView()->mouseDragMode(WRSpectroDataViewElement::MouseDragZoom);
  //  ttchart->attach(ui->spec);

   // m_spectroVLine = m_spectro->addDataPointLine(0);
  //  m_spectroVLine->color(WRColor(0xF5, 0xF5, 0xF5));

}

CDesktop::~CDesktop()
{
    if (thread)
    {
        delete thread;
        thread = 0;
    }
    chart->release();
    delete ui;
}
