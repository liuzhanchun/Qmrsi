#include "NetWork.h"
#include "ui_NetWork.h"

CNetWork::CNetWork(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CNetWork)
{
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint); //关闭对话框的问号和X按钮
    ui->setupUi(this);

    //使用正则表达式限制端口号
    QRegExp rxp("^([0-9]|[1-9]\\d|[1-9]\\d{2}|[1-9]\\d{3}|[1-5]\\d{4}|6[0-4]\\d{3}|65[0-4]\\d{2}|655[0-2]\\d|6553[0-5])$");
    QRegExpValidator *pRep = new QRegExpValidator(rxp, this);
    ui->port->setValidator(pRep);
    ui->port->setEnabled(false);
    ui->receive_ip->setEnabled(false);
    ui->control_ip->setEnabled(false);

}

CNetWork::~CNetWork()
{
    delete ui;
}

QString CNetWork::GetIPInfo(int &nPort,QString &receiveip,QString &controlip)
{
    nPort = QsPort.toInt();
    receiveip = QsReceiveIP;
    controlip = QsControlIP;
    return "OK";
}

void CNetWork::on_connect_clicked()
{
    QsPort = ui->port->text();
    if(QsPort.isEmpty())
        QsPort = "5025";
    QsReceiveIP = ui->receive_ip->text();
    if(QsReceiveIP.isEmpty())
        QsReceiveIP = "192.168.0.226";
    QsControlIP = ui->control_ip->text();
    if(QsControlIP.isEmpty())
        QsControlIP = "192.168.0.138";
    CNetWork::accept();
}

void CNetWork::on_auto_ip_clicked()
{
    ui->port->setText("5025");
    ui->receive_ip->setText("192.168.0.226");
    ui->control_ip->setText("192.168.0.138");
    ui->port->setEnabled(false);
    ui->receive_ip->setEnabled(false);
    ui->control_ip->setEnabled(false);

}

void CNetWork::on_maual_ip_clicked()
{
    ui->port->setEnabled(true);
    ui->receive_ip->setEnabled(true);
    ui->control_ip->setEnabled(true);
}
