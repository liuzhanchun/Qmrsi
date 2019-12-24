#ifndef MEASURE_H
#define MEASURE_H
#include "datadef.h"

class CMeasure
{
public:
    CMeasure();
    virtual ~CMeasure();
    bool DataPro ( bool meas=true );
    int GetMeasID ( void ) { return m_nMeasID; } //返回当前测量类型
    void SetMeasID (int measid){m_nMeasID=measid;}
    bool GetDataPro (double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu ,WaveStatus &Status);
    bool GetLevelPro(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata);

protected:
    virtual void ReadData ( void ) = 0;
    virtual int GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status) = 0;
    virtual int GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata) = 0;

    int m_nMeasID; //测量类型标记, 表示是哪种测量, 基类(含子基类)此ID都为NULL
};

extern CMeasure *g_pMea;

#endif // MEASURE_H
