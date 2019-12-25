#include "SpectroThread.h"

CSpectroThread::CSpectroThread(WRSpectroControl* chart)
    : m_file(QStringLiteral(":/spec.dat")), m_status(false)
{
    m_chart = chart;
    m_chart->addRef();

    m_params.freqBegin = 30000000LL;
    m_params.freqEnd = 3610000000LL;
    m_params.dataSize = 143200;
    m_params.minValue = 36;
    m_params.maxValue = 226;
    m_params.offValue = -196;
    m_params.isClosed = false;

    WRSpectroInitParams<unsigned char> initArgs(m_params.minValue,
                                                m_params.maxValue,
                                                m_params.offValue,
                                                m_params.dataSize,
                                                m_params.isClosed,
                                                m_params.freqBegin,
                                                m_params.freqEnd);

    m_chart->initialize(initArgs);

    m_status = true;
    start();

    m_resetApex = true;
}
CSpectroThread::~CSpectroThread()
{
    if (m_status)
    {
        m_status = false;
        wait();
    }
    m_chart->release();
}
void CSpectroThread::resetApex(void)
{
      m_resetApex = true;
}

void CSpectroThread::run(void)
{
    m_file.open(QIODevice::ReadOnly);

    int length = m_params.dataSize;
    unsigned char* buf = new unsigned char[length];
    unsigned char * apexBuffer = new unsigned char[length];
    int* markBuffer = new int[m_params.dataSize];
    for (int i = 0; i < m_params.dataSize; ++i)
    {
        markBuffer[i] = i;
    }
    while (m_status) {
       if (m_file.read((char*)buf, length) != length)
       {
           m_file.seek(0);
           continue;
       }
       bool apexChanged = false;
       if (m_resetApex)
       {
           for (int i = 0; i < length; ++i)
           {
               apexBuffer[i] = buf[i];
           }
           m_resetApex = false;
           apexChanged = true;
       }
       else
       {
           for (int i = 8; i < length; ++i)
           {
               if (buf[i] > apexBuffer[i])
               {
                   apexBuffer[i] = buf[i];
                   apexChanged = true;
               }
           }
       }
       m_chart->lock();
       {
           if (apexChanged)
           {
               m_chart->alterData(0, apexBuffer);
           }
           m_chart->alterData(1, buf , markBuffer, m_params.dataSize);
       }
       m_chart->unlock();

       QThread::msleep(20);
    }
    delete[] buf;
    delete[] apexBuffer;
    delete[] markBuffer;

    m_file.close();
}
