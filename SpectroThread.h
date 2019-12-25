#ifndef SPECTROTHREAD_H
#define SPECTROTHREAD_H
#include <QThread>
#include <QFile>
#include <WRCharting/WRSpectroControl.h>
#include "SpecParams.h"

class CSpectroThread: public QThread
{
public:
    CSpectroThread(WRSpectroControl* chart);
    ~CSpectroThread();
    void resetApex(void);

protected:
    void run(void);
private:
    QFile m_file;
    bool m_status;
    WRSpectroControl* m_chart;
    SpecParams m_params;
    bool m_resetApex;
};

#endif // SPECTROTHREAD_H
