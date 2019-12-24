#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <iostream>
#include <stdio.h>
#include <WinSock2.h>
#include <stdlib.h>

class CUdpServer
{
public:
    CUdpServer(int nPort);
    ~CUdpServer();
    int UdpInit();
    int ReceiveData(char * pBuffer, UINT & nRecv, UINT RecvSize);
    int ReceiveData(char * pBuffer, UINT & nRecv);
    int ReceiveAudio(char * pBuffer, UINT & nRecv, UINT RecvSize );

public:
    SOCKET m_ReceivingSocket;
    SOCKADDR_IN m_SenderAddr;
    int m_SenderAddrSize;
    int m_nPort;
};
extern CUdpServer *g_pUdpData;

#endif // UDPSERVER_H
