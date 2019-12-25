#pragma once
#ifndef WRWATERFALLDATASOURCE
#define WRWATERFALLDATASOURCE

#include <QAtomicInt>

//表示瀑布图数据源。
class WRWaterfallDataSource
{
private:
    //引用计数。
    QAtomicInt m_refCnt;

	//禁用复制构造函数。
	WRWaterfallDataSource(const WRWaterfallDataSource& other);
	//禁用赋值操作符。
	WRWaterfallDataSource& operator=(const WRWaterfallDataSource& other);

protected:
    long m_version;
	double m_minValue;
	double m_maxValue;
	double m_offValue;
	double m_difValue;
	int m_points;
	bool m_isClosed;
    bool m_changed;
    bool m_isClear;
	long long m_freqBegin;
	long long m_freqEnd;
	int m_buffers;
	int m_capacity;	
	long long m_frames;

	//初始化瀑布图数据源。
	WRWaterfallDataSource(void)
	{
		m_refCnt = 1;
        m_version = 0;
        m_changed = false;
        m_isClear = false;
		m_frames = 0;
	}
	//清理当前对象所占用的相关资源。
	virtual ~WRWaterfallDataSource(void)
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

    //获取数据版本号。
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
	//获取数据调整值。
	inline double offValue(void) const
	{
		return m_offValue;
	}
	//获取数据差异值。
	inline double difValue(void) const
	{
		return m_difValue;
	}

	//获取数据点数量。
	inline int points(void) const
	{
		return m_points;
	}
	//获取是否闭区间。
	inline bool isClosed(void) const
	{
		return m_isClosed;
	}
	//获取频率起始值。
	inline long long freqBegin(void) const
	{
		return m_freqBegin;
	}
	//获取频率结束值。
	inline long long freqEnd(void) const
	{
		return m_freqEnd;
	}

	//获取数据帧缓存。
	inline int buffers(void) const
	{
		return m_buffers;
	}
	//获取数据帧容量。
	inline int capacity(void) const
	{
		return m_capacity;
	}

	//获取数据总帧数。
	inline long long frames(void) const
	{
		return m_frames;
	}

    //清除所有数据。
    virtual void clear(void) = 0;
	//添加指定的数据, 该数据将写入缓存中。
	virtual void append(const void* specBuffer, const long long* timeBuffer, int dataFrames) = 0;

    //检查如果，如果数据改变，则将改变的数据生效，返回数据版本。
    virtual long validate(void) = 0;

	//取出从指定起始位置开始的指定数量的数据。
	virtual void retrieve(double* pBuf, int pBeg, int pCnt, int fBeg, int fCnt) const = 0;
	//取出从指定起始位置开始的指定数量的数据。
	virtual void retrieve(double* pBuf, int pBeg, int* pIdx, int pCnt, int fBeg, int fCnt) const = 0;
	//取出从指定起始位置开始的指定数量的数据。
	virtual void retrieve(double* pBuf, int pBeg, int pCnt, int fBeg, int* fIdx, int fCnt) const = 0;
	//取出从指定起始位置开始的指定数量的数据。
	virtual void retrieve(double* pBuf, int pBeg, int* pIdx, int pCnt, int fBeg, int* fIdx, int fCnt) const = 0;

	//获取指定位置的数据值。
	virtual double getValue(int frameIndex, int pointIndex) const = 0;

	//获取指定索引的时间值。
	virtual long long getTimeValue(int index) const = 0;

    //获取指定索引处的频率。
    inline long long getFreqValue(int index) const
    {
        if (m_isClosed)
        {
            return m_freqBegin + index * (m_freqEnd - m_freqBegin) / (m_points - 1);
        }
        else
        {
			return m_freqBegin + index * (m_freqEnd - m_freqBegin) / m_points;
		}
    }
};

#endif //WRWATERFALLDATASOURCE
