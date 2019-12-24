#include "UdpServer.h"

CUdpServer *g_pUdpData = nullptr; //定义全局指针;

CUdpServer::CUdpServer(int nPort)
{
    m_nPort = nPort;
    m_SenderAddrSize = sizeof(m_SenderAddr);
    UdpInit();
}


CUdpServer::~CUdpServer()
{
    closesocket(m_ReceivingSocket);
    WSACleanup();
}

int CUdpServer::UdpInit()
{
    WSADATA wsaData;

    SOCKADDR_IN ReceiverAddr;
    int nPort = m_nPort;
    int Ret;
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        //printf("Error\n");
        return -1;
    }
    if ((m_ReceivingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    {
        //printf("ERROR:socket failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }
    ReceiverAddr.sin_family = AF_INET;
    ReceiverAddr.sin_port = htons(nPort);
    ReceiverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    if (bind(m_ReceivingSocket, (SOCKADDR*)&ReceiverAddr, sizeof(ReceiverAddr)) == SOCKET_ERROR)
    {
        //printf("ERROR: bind failed with error %d\n", WSAGetLastError());
        closesocket(m_ReceivingSocket);
        WSACleanup();
        return -1;
    }
    return 0;
}

int CUdpServer::ReceiveData(char * pBuffer, UINT & nRecv, UINT RecvSize = 0)
{
    char buffer[60000] = "\0";
    char byPackage[10] = { 0 };
    UINT nPackage = 0;
    struct timeval tv;
    fd_set readfds;


    FD_ZERO(&readfds);
    FD_SET(m_ReceivingSocket, &readfds);
    tv.tv_sec =2;
    tv.tv_usec = 50;
    select(m_ReceivingSocket + 1, &readfds, nullptr, nullptr, &tv);
    if (FD_ISSET(m_ReceivingSocket, &readfds))
    {
        if ((recvfrom(m_ReceivingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&m_SenderAddr, &m_SenderAddrSize)) == SOCKET_ERROR)
        {
            nRecv = 0;
            return -1;
        }
        memcpy(pBuffer, buffer , 60000);
        nRecv = 60000;
    }
    return 0;
}
int CUdpServer::ReceiveAudio(char * pBuffer, UINT & nRecv, UINT RecvSize = 0)
{
    char buffer[60000] = "\0";
    char byPackage[10] = { 0 };
    UINT nPackage = 0;
    struct timeval tv;
    fd_set readfds;


    FD_ZERO(&readfds);
    FD_SET(m_ReceivingSocket, &readfds);
    tv.tv_sec =0;
    tv.tv_usec = 50;
    select(m_ReceivingSocket + 1, &readfds, nullptr, nullptr, &tv);
    if (FD_ISSET(m_ReceivingSocket, &readfds))
    {
        if ((recvfrom(m_ReceivingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&m_SenderAddr, &m_SenderAddrSize)) == SOCKET_ERROR)
        {
            nRecv = 0;
            return -1;
        }
        memcpy(pBuffer, buffer , 60000);
        nRecv = 60000;
    }
    return 0;
}
int CUdpServer::ReceiveData(char * pBuffer, UINT & nRecv)
{
    char buffer[60000] = "\0";
    memset(buffer, 0, 60000);
    UINT nPackage = 0;
    memset(&m_SenderAddr, 0, sizeof(sockaddr_in));
    if ((recvfrom(m_ReceivingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&m_SenderAddr, &m_SenderAddrSize)) == SOCKET_ERROR)
    {
        return -1;
    }
    memcpy(pBuffer, buffer, 60000);
    return 0;
}

