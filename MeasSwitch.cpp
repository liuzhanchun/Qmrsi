#include "MeasSwitch.h"
#include "Measure.h"
#include "RXFFM.h"
#include "RXPSCAN.h"

CMeasSwitch CMeasSwitch::m_Instance;
CMeasSwitch &g_MeasSwitch = CMeasSwitch::GetInstance();


CMeasSwitch::CMeasSwitch()
{
    m_nPostID = RXNONE;
    m_pMutex = new QMutex();
}
CMeasSwitch::~CMeasSwitch(void)
{
    delete m_pMutex;
}



void CMeasSwitch::SwitchMeas ( int id, bool switch_now )
{

    m_nPostID = id;

    if ( g_pMea == nullptr || id != g_pMea->GetMeasID() ) //NULL:刚开机时
    {
        if ( g_pMea != nullptr )//不是开机的时候
        {
            delete g_pMea;
        }
        //id = RXFFM;
        SetPointerNull(); //////////////////////////////注意: 新添加对象, 要在这里加=NULL

        switch ( id )
        {
        case RXPSCAN: //rx
            g_pRXPSCAN = new CRXPSCAN;
            g_pMea = g_pRXPSCAN;
            break;


        default:
            g_pRXFFM = new CRXFFM;
            g_pMea = g_pRXFFM;
            break;

        }

    }
}



void CMeasSwitch::SetPointerNull ( void )
{
    g_pMea = nullptr;
    g_pRXFFM = nullptr;
    g_pRXPSCAN = nullptr;
}
void CMeasSwitch::EnterLock ( void )
{
    m_pMutex->lock();
}
void CMeasSwitch::LeaveLock ( void )
{
    m_pMutex->unlock();
}
