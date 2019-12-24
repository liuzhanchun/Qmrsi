#ifndef MEASSWITCH_H
#define MEASSWITCH_H
#include <QMutex>
#include "datadef.h"
class CMeasSwitch
{
public:
    CMeasSwitch();
    ~CMeasSwitch ();
    CMeasSwitch ( const CMeasSwitch & ); //disallowed
    CMeasSwitch & operator= ( CMeasSwitch & ); //disallowed
    static CMeasSwitch m_Instance;  //唯一的实例
public:
    static CMeasSwitch &GetInstance ( void ) { return m_Instance; }
    void Initial ( void );
    void SwitchMeas ( int id, bool switch_now = true );

    void EnterLock ( void );
    void LeaveLock ( void );
private:
    void SetPointerNull ( void );
    int m_nPostID;
    QMutex *m_pMutex;

};

extern CMeasSwitch &g_MeasSwitch;

#endif // MEASSWITCH_H
