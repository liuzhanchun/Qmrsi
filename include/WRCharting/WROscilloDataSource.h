#pragma once
#ifndef WROSCILLODATASOURCE
#define WROSCILLODATASOURCE

#include <QAtomicInt>

//表示波形图数据源。
class WROscilloDataSource
{
private:
    QAtomicInt m_refCnt;    //引用计数。

	//禁用复制构造函数。
	WROscilloDataSource(const WROscilloDataSource& other);
	//禁用赋值操作符。
	WROscilloDataSource& operator=(const WROscilloDataSource& other);

protected:
    long m_version;			//数据版本
    double m_minValue;		//数据最小值
    double m_maxValue;		//数据最大值
    int m_sampleRate;		//采样速率
    int m_buffers;			//数据缓存
    int m_capacity;			//数据容量
    bool m_changed;			//数据改变标识
    bool m_isClear;			//是否清除
    long long m_points;		//数据总量

protected:
	//初始化波形图数据源。
	WROscilloDataSource(void)
	{
        m_refCnt = 1;
        m_version = 0;
        m_changed = false;
        m_isClear = false;
		m_points = 0;
	}
	//清理当前对象所占用的相关资源。
	virtual ~WROscilloDataSource(void)
	{
		//add code here
	}

public:
    //添加对象引用。
    inline void addRef(void)
    {
        m_refCnt.ref();
    }
    //释放对象引用, 如果引用计数为0，则删除对象，返回True，否则返回False。
    inline bool release(void)
    {
        if (!m_refCnt.deref())
        {
            delete this;
            return true;
        }
        return false;
    }

    //获取数据版本。
    inline long version(void) const
    {
        return m_version;
    }

	//获取数据最小值。
	inline double minValue(void) const
	{
		return m_minValue;
	}
	//获取数据最大值。
	inline double maxValue(void) const
	{
		return m_maxValue;
	}

	//获取数据采样率。
	inline int sampleRate(void) const
	{
		return m_sampleRate;
	}
	
    //获取数据点缓存。
	inline int buffers(void) const
	{
		return m_buffers;
	}
    //获取数据点容量。
	inline int capacity(void) const
	{
		return m_capacity;
	}

	//获取数据总点数。
	inline long long points(void) const
	{
		return m_points;
	}

    //清除所有数据。
    virtual void clear(void) = 0;
	//写入指定的数据。
	virtual void append(const void* data, int size, long long time) = 0;

	//使数据改变生效，并返回当前版本。
    virtual long validate() = 0;

	//取出从指定起始位置开始的指定数量的数据。
	virtual void retrieve(double* pBuf, int nBeg, int nCnt) = 0;
	//取出从指定起始位置开始的按指定范围和方法的数据。
	virtual void retrieve(double* pBuf, int nBeg, int* pIdx, int nCnt) = 0;

	//获取指定索引的数据值。
	virtual double getValue(int index) const = 0;
	
	//获取指定索引的时间值。
	virtual long long getTimeValue(int index) const = 0;
};

#endif //WROSCILLODATASOURCE
