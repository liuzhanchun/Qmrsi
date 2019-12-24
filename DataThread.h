#ifndef DATATHREAD_H
#define DATATHREAD_H
#include <QThread>

class CDataThread:public QThread
{
public:
    CDataThread();
    void run();
};

#endif // DATATHREAD_H
