#include "Measure.h"

CMeasure *g_pMea = nullptr; //定义全局指针
CMeasure::CMeasure()
{

}
CMeasure::~CMeasure()
{

}

bool CMeasure::DataPro ( bool meas )
{
    ReadData();
    return 0;
}
bool CMeasure::GetDataPro ( double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status )
{
    GetData(data,nLen,freq,level,itu,Status);
    return 0;
}
bool CMeasure::GetLevelPro(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata)
{
    GetLevel(data,nLen,freq,leveldata);
    return 0;
}
