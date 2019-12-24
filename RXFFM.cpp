#include "RXFFM.h"
#include "TcpClient.h"
#include "UdpServer.h"

CRXFFM *g_pRXFFM = nullptr;

CRXFFM::CRXFFM()
{
    m_nMeasID = RXFFM;

    char Cmd[150];

    sprintf(Cmd, "FREQ 106.8 MHz");
    g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "FREQ:SPAN 40000 kHz");
   g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "BAND 250 kHz");
   g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "ATT:RF:MODE LowDistort");
   g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "ATT:AUT OFF");
   g_pTcpClient->SendCmd(Cmd);

//	 sprintf(Cmd, "ATT 30 dB");
//	 g_pRemote->FastSendCmd(Cmd);

    sprintf(Cmd, "DEM FM");
   g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "MEAS:THR 90");
    g_pTcpClient->SendCmd(Cmd);

    //sprintf(Cmd, "MEAS:TIME:MODE OFF");
    //g_pRemote->FastSendCmd(Cmd);

    sprintf(Cmd, "BANDwidth 200000");
   g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "MEAS:TIME 0.5 ms");
    g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "MEAS:DET AVG");
   g_pTcpClient->SendCmd(Cmd);


    sprintf(Cmd, "MEAS:BAND:XDB 26");
   g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "MEAS:BAND:BETA 0.01");
    g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "MEAS:SQUelch OFF");
   g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "FREQ:MODE FIX");
   g_pTcpClient->SendCmd(Cmd);

    sprintf(Cmd, "TRAC:MED SPECTRUM,Level");
    g_pTcpClient->SendCmd(Cmd);

   g_pTcpClient->SendCmd("ATTenuation:RF:MODE NORM");

    sprintf(Cmd, "TRAC ON");
   g_pTcpClient->SendCmd(Cmd);

}
CRXFFM::~CRXFFM(void)
{
    char Cmd[50];
    sprintf(Cmd, "TRAC OFF");
    g_pTcpClient->SendCmd(Cmd);
}
void CRXFFM::ReadData ( void )
{
   // g_pUdpData->UdpReceiveData();

    UINT nPoint = 0;
    char cBuffer[65536];
    short nData[32768];
    int num = 0;
    memset(cBuffer, 0, 65536);


    g_pUdpData->ReceiveData(cBuffer, nPoint, 0);



    if (nPoint > 0)
    {
        memset(nData, 0, 32768 * sizeof(short));
    }

}
int CRXFFM:: GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status)
{

    return 0;
}
int CRXFFM:: GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata)
{

    return 0;
}
