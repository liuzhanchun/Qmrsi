#pragma once
#ifndef WRSPECTRODATASOURCE
#define WRSPECTRODATASOURCE

#include <QAtomicInt>

//表示频谱图数据通道。
class WRSpectroDataChannel
{
public:
	//获取抽取方式。
	enum ZoomMethod
	{
		//取范围值。
		Range = 0,
		//取最大值。
		MaxValue = 1,
		//取最小值。
		MinValue = 2,
	};

private:
	//禁用复制构造函数。
	WRSpectroDataChannel(const WRSpectroDataChannel& other);
	//禁用赋值操作符。
	WRSpectroDataChannel& operator=(const WRSpectroDataChannel& other);

protected:	
	//数据版本。
	long m_version;

	//初始化频谱图数据通道。
	WRSpectroDataChannel(void)
	{
		m_version = 0;
	}
	//清理当前对象所占用的相关资源。
	virtual ~WRSpectroDataChannel(void)
	{
		//add code here
	}

public:
	//获取数据版本。
	inline long version(void) const
	{
		return m_version;
	}

	//更新指定的数据。
	virtual void change(const void* data) = 0;
	//更新指定的数据。
	virtual void change(const void* data, const int* markBuf, int markLen) = 0;

	//使数据改变生效，并返回当前版本。
	virtual long validate() = 0;

	//取出从指定起始位置开始的指定数量的数据。
	virtual bool retrieve(double* pBuf, int nBeg, int nCnt) = 0;
	//取出从指定起始位置开始的按指定范围和方法的数据。
	virtual bool retrieve(double* pBuf, int nBeg, int* pIdx, int nCnt, ZoomMethod tWay) = 0;

	//取出从指定起始位置开始的指定数量范围内的标记数据。
	virtual int retrieve(int** pBuf, int nBeg, int nCnt) = 0;

	//获取指定索引的数据值。
	virtual bool getValue(int index, double* value) const = 0;
};

//表示频谱图数据源。
class WRSpectroDataSource
{
private:
    //引用计数。
    QAtomicInt m_refCnt;

	//禁用复制构造函数。
	WRSpectroDataSource(const WRSpectroDataSource& other);
	//禁用赋值操作符。
	WRSpectroDataSource& operator=(const WRSpectroDataSource& other);

protected:
	double m_minValue;
	double m_maxValue;
	double m_offValue;
	int m_points;
	bool m_isClosed;
	long long m_freqBegin;
	long long m_freqEnd;

protected:
	//初始化频谱图数据源。
	WRSpectroDataSource(void)
	{
		m_refCnt = 1;
	}
	//清理当前对象所占用的相关资源。
	virtual ~WRSpectroDataSource(void)
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
	
	//获取指定索引的通道。
	virtual WRSpectroDataChannel* channel(int index) = 0;

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

#endif //WRSPECTRODATASOURCE
