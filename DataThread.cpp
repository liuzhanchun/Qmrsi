#include "DataThread.h"
#include "Comman.h"
#include "MeasSwitch.h"
#include "Measure.h"

CDataThread::CDataThread()
{

}
void CDataThread::run()
{
    while(g_bIsRun)
    {

        g_MeasSwitch.EnterLock();
        g_pMea->DataPro();
        g_MeasSwitch.LeaveLock();
        QThread::msleep(16);
    }
}
