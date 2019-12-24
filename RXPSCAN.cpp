#include "RXPSCAN.h"
#include "TcpClient.h"
#include "UdpServer.h"

CRXPSCAN *g_pRXPSCAN= nullptr;
CRXPSCAN::CRXPSCAN()
{
    m_nMeasID = RXPSCAN;

    char Cmd[50];
    //sprintf(Cmd, "TRAC OFF");
    //g_pRemote->FastSendCmd(Cmd);

    sprintf(Cmd, "FREQ:MODE PSC");
    g_pTcpClient->SendCmd(Cmd);


   sprintf(Cmd, "FREQ:PSC:MODE Normal");
   // sprintf(Cmd, "FREQ:MODE:PSC ON");
   g_pTcpClient->SendCmd(Cmd);




    sprintf(Cmd, "FREQ:START 20 MHz");
   g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "FREQ:STOP 1000 MHz");
    g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "FREQ:STEP 25 kHz");
   g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "BAND 120 kHz");
   g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "ATT:RF:MODE Normal");
    g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "ATT:AUT ON");
    g_pTcpClient->SendCmd(Cmd);



    //sprintf(Cmd, "MEAS:TIME:MODE ON");
    //pRemoteData->FastSendCmd(Cmd);

    sprintf(Cmd, "MEAS:DET POS");
   g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "MEAS:DWEL 0");
   g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "MEAS:HOLD 0");
    g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "TRAC:MED SCAN");
    g_pTcpClient->SendCmd(Cmd);



    sprintf(Cmd, "TRAC ON");
    g_pTcpClient->SendCmd(Cmd);
}

CRXPSCAN::~CRXPSCAN(void)
{
    char Cmd[50];
    sprintf(Cmd, "TRAC OFF");
    g_pTcpClient->SendCmd(Cmd);

}

void CRXPSCAN::ReadData ( void )
{

}
int CRXPSCAN:: GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status)
{
    return 0;
}
int CRXPSCAN:: GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata)
{
    return 0;
}

















