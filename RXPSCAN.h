#ifndef RXPSCAN_H
#define RXPSCAN_H
#include "Measure.h"
#include "DataDef.h"

class CRXPSCAN: public CMeasure
{
public:
    CRXPSCAN(void);
    ~CRXPSCAN(void);
protected:
    void virtual ReadData ( void );
    int virtual  GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status);
    int virtual  GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata);

};
extern CRXPSCAN *g_pRXPSCAN;

#endif // RXPSCAN_H
