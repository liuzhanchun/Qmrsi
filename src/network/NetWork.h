#ifndef NETWORK_H
#define NETWORK_H

#include <QDialog>
#include <QString>


namespace Ui {
class CNetWork;
}

class CNetWork : public QDialog
{
    Q_OBJECT

public:
    explicit CNetWork(QWidget *parent = 0);
    ~CNetWork();
    QString GetIPInfo(int &nPort,QString &receiveip,QString &controlip);



private slots:
    void on_connect_clicked();

    void on_auto_ip_clicked();

    void on_maual_ip_clicked();

private:
    Ui::CNetWork *ui;
    QString QsPort;
    QString QsReceiveIP;
    QString QsControlIP;
};

#endif // NETWORK_H
