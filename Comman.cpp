#include "Comman.h"

CComman::CComman()
{

}
volatile bool g_bIsRun = false;

double CComman::max(QVector<double> _dataVec,uint64_t & pox)
{
    if ( _dataVec.count() == 0)
    {
        return 0;
    }

    double max = _dataVec.at(0);
    pox = 0;
    for(int i = 1; i < _dataVec.count(); i++)
    {
        if(_dataVec.at(i) > max)
        {
            max = _dataVec.at(i);
            pox = i;
        }
    }

    return max;
}
