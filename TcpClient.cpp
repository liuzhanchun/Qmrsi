#include "TcpClient.h"

CTcpClient *g_pTcpClient = nullptr;
CTcpClient::CTcpClient(QObject *parent) :
    QObject(parent)
{
    m_ServerIP =new QHostAddress();
    m_BaRecv.resize(512);

}
OPT_RET CTcpClient::TcpInit(quint16 nPort,QString ip)
{
    m_IP =ip;
    m_nPort = nPort;
    if(!m_ServerIP->setAddress(m_IP))					//(b)
    {

      return OPT_UNKNOW_ERROR;
    }
    /* 创建了一个QTcpSocket类对象，并将信号/槽连接起来 */
    m_TcpSocket = new QTcpSocket();
    connect(m_TcpSocket,SIGNAL(connected()),this,SLOT (OnConnect()));
    connect(m_TcpSocket,SIGNAL(disconnected()),this,SLOT (OnDisConnect ()));
    connect(m_TcpSocket,SIGNAL(readyRead()),this,SLOT (OnReceived()));
    //connect(m_TcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
    connect(m_TcpSocket,SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ConnectError()));
    m_TcpSocket->connectToHost(*m_ServerIP,m_nPort);
   // qDebug("rrr=%d\n",)
    return OPT_SUCCESS;
}

OPT_RET CTcpClient::TcpSend(QString msg)
{
    m_TcpSocket->write(msg.toLatin1().data(),msg.length());
    m_TcpSocket->waitForBytesWritten(100);
    return OPT_SUCCESS;
}

OPT_RET CTcpClient::SendCmd(QString cmd)
{
    QString msg_cmd = cmd+LFCR;
    m_TcpSocket->write(msg_cmd.toLatin1().data(),msg_cmd.length());
    m_TcpSocket->waitForBytesWritten(100);
    //m_TcpSocket->flush();
    return OPT_SUCCESS;
}

OPT_RET CTcpClient::SendRecv(QString cmd,QByteArray DataRecv,int len,int nTimeout)
{
    QString QsRvce;
    QString msg_cmd = cmd+LFCR;
    m_TcpSocket->write(msg_cmd.toLatin1().data(),msg_cmd.length());
    m_TcpSocket->flush();
    m_TcpSocket->waitForReadyRead(200);
    if(m_nRecvLen>0)
    {
        QsRvce = m_BaRecv;
        if(QsRvce.contains(cmd,Qt::CaseSensitive))//成功返回true  第二个参数表示是否大小写敏感
        {
            DataRecv.resize(m_nRecvLen);
            DataRecv = m_BaRecv;
            len = m_nRecvLen;

            m_BaRecv.clear();  /*!<清空内容*/
            m_nRecvLen = 0;
            return OPT_SUCCESS;
        }


    }
    m_BaRecv.clear();  /*!<清空内容*/
    m_nRecvLen = 0;
    return OPT_RECV_FAIL;
}




OPT_RET CTcpClient::OnReceived()
{
    QByteArray data = m_TcpSocket->readAll();
    if (data.length() <= 0)
    {
       m_nRecvLen = 0;
       return OPT_RECV_FAIL;
    }
    m_BaRecv.resize(data.length());
    m_BaRecv = data;
    m_nRecvLen = data.length();
   // emit msg_para();
    return OPT_SUCCESS;
}
bool CTcpClient::ConnectError()
{
    g_bIsRun = false;
    return true;
}


bool CTcpClient::OnConnect()
{

    g_bIsRun = true;
    return true;
}
bool CTcpClient::OnDisConnect()
{

    g_bIsRun = false;
    return true;
}
