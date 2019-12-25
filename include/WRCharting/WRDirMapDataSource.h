#pragma once
#ifndef WRDIRMAPDATASOURCE
#define WRDIRMAPDATASOURCE

#include <QAtomicInt>
#include <WRCharting/WRDirMapDataRange.h>

//表示向频图数据源。
class WRDirMapDataSource
{
public:
	//枚举数据处理方式。
	enum ProcMethod
	{
		//最大值。
		MaxValue,
		//平均值。
		Average,
	};

private:
    //引用计数。
    QAtomicInt m_refCnt;

	//禁用复制构造函数。
	WRDirMapDataSource(const WRDirMapDataSource& other);
	//禁用赋值操作符。
	WRDirMapDataSource& operator=(const WRDirMapDataSource& other);

protected:
    long m_version;
	double m_specMinValue;
	double m_specMaxValue;
	double m_specOffValue;
	double m_specDifValue;
	double m_angleMeasure;
	double m_angleMinValue;
	double m_angleMaxValue;
	int m_points;
	bool m_isClosed;
    bool m_changed;
    bool m_isClear;
	long long m_freqBegin;
	long long m_freqEnd;
	int m_buffers;
    int m_capacity;

	//初始化向频图数据源。
	WRDirMapDataSource(void)
	{
		m_refCnt = 1;
		m_version = 0;
        m_changed = false;
        m_isClear = false;
	}
	//清理当前对象所占用的相关资源。
	virtual ~WRDirMapDataSource(void)
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

	//获取幅度最小值。
	inline double specMinValue(void) const
	{
		return m_specMinValue;
	}
	//获取幅度最大值。
	inline double specMaxValue(void) const
	{
		return m_specMaxValue;
	}
	//获取幅度调整值。
	inline double specOffValue(void) const
	{
		return m_specOffValue;
	}
	//获取幅度差异值。
	inline double specDifValue(void) const
	{
		return m_specDifValue;
	}
	
	//获取角度单位量。
	inline double angleMeasure(void) const
	{
		return m_angleMeasure;
	}

	//获取角度最小值。
	inline double angleMinValue(void) const
	{
		return m_angleMinValue;
	}
	//获取角度最大值。
	inline double angleMaxValue(void) const
	{
		return m_angleMaxValue;
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
	
	//获取数据角度缓存。
	inline int buffers(void) const
	{
		return m_buffers;
	}
	//获取数据角度容量。
	inline int capacity(void) const
	{
		return m_capacity;
	}

    //清除所有数据。
    virtual void clear(void) = 0;
	//添加指定的数据, 该数据将写入缓存中。
	virtual void append(const void* specBuffer, const void* angleBuffer, int dataFrames) = 0;

	//检查如果，如果数据改变，则将改变的数据生效。返回数据版本号。
	virtual long validate(void) = 0;

	//取出从指定起始位置开始的指定数量的数据。
	virtual void retrieve(double* pBuf, ProcMethod tWay, const WRChartSampleRange& pointRange, const WRChartDValueRange& angleRange, int height) = 0;
	//取出从指定起始位置开始的指定数量的数据。
	virtual void retrieve(double* pBuf, ProcMethod tWay, const WRChartSampleRange& pointRange, const WRChartDValueRange& angleRange, int* pointIndex, int pointCount,  int height) = 0;

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

#endif //WRDIRMAPDATASOURCE
