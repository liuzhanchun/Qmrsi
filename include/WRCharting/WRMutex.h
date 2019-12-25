#pragma once
#ifndef WRMUTEX
#define WRMUTEX

#include <QMutex>

//表示互斥体。
class WRMutex
{
private:
	//内部变量。
    QMutex m_cs;

	//禁止复制构造函数。
	WRMutex(const WRMutex& other);
	//禁止赋值操作符。
	WRMutex& operator=(const WRMutex& other);

public:
	//构造函数。
	inline WRMutex(void)
        : m_cs(QMutex::Recursive)
    {
        //add code here
    }
	//析构函数。
	inline ~WRMutex(void)
    {
        //add code here
	}

	//加锁。
	inline void lock(void)
    {
        m_cs.lock();
	}
	//尝试加锁。
	inline bool tryLock(void)
    {
        return m_cs.tryLock();
	}
	//解锁。
	inline void unlock(void)
    {
        m_cs.unlock();
	}
};
//表示同步锁。
class WRSynch
{
private:
	//同步对象。
	WRMutex& m_mutex;

public:
	//构造函数。
	inline explicit WRSynch(WRMutex& mutex) : m_mutex(mutex)
	{
		m_mutex.lock();
	}
	//复制函数。
	inline WRSynch(const WRSynch& cast) : m_mutex(cast.m_mutex)
	{
		m_mutex.lock();
	}

	//析构函数。
	inline ~WRSynch(void)
	{
		m_mutex.unlock();
	}
};

#endif //WRMUTEX
