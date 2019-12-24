#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QString>
#include "Comman.h"
#include <QHostAddress>
#include <QTcpSocket>
#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QHostAddress>
#include <QTcpSocket>

class CTcpClient : public QObject
{
    Q_OBJECT
public:
    explicit CTcpClient(QObject *parent = nullptr);
    OPT_RET TcpInit(quint16 nPort,QString ip);

    OPT_RET TcpSend(QString msg);
    OPT_RET TcpReceived(QString &msg,int length);
    OPT_RET SendCmd(QString cmd);
    OPT_RET SendRecv(QString cmd,QByteArray DataRecv,int len,int nTimeout = 50);

private:
    QHostAddress *m_ServerIP;
    QTcpSocket *m_TcpSocket;
    QString m_IP;
    quint16 m_nPort;
    QByteArray m_BaRecv;
    int m_nRecvLen;

signals:
    void msg_para();

private slots:
    bool OnConnect();
    bool OnDisConnect();
    bool ConnectError();
    OPT_RET OnReceived();
};

extern CTcpClient *g_pTcpClient;

#endif // TCPCLIENT_H
