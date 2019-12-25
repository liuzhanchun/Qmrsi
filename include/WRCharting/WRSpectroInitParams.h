#pragma once
#ifndef WRSPECTROINITPARAMS
#define WRSPECTROINITPARAMS

//表示频谱图初始化参数。
template <class T> class WRSpectroInitParams
{
private:
	T m_minValue;
	T m_maxValue;
	bool m_isClosed;
	int m_points;
	double m_offValue;
	long long m_freqBegin;
	long long m_freqEnd;

public:
	//初始化参数。
	WRSpectroInitParams(T minValue, T maxValue, double offValue, int points, bool isClosed, long long freqBegin, long long freqEnd)
	{
		m_minValue = minValue;
		m_maxValue = maxValue;
		m_offValue = offValue;
		m_points = points;
		m_isClosed = isClosed;
		m_freqBegin = freqBegin;
		m_freqEnd = freqEnd;
	}

	//获取数据最小值。
	inline T minValue(void) const
	{
		return m_minValue;
	}
	//获取数据最大值。
	inline T maxValue(void) const
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
};

#endif //WRSPECTROINITPARAMS
