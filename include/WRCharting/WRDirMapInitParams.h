#pragma once
#ifndef WRDIRMAPINITPARAMS
#define WRDIRMAPINITPARAMS

//表示向频图初始化参数。
template <class Ts, class Ta> class WRDirMapInitParams
{
private:
	Ts m_specMinValue;
	Ts m_specMaxValue;
	Ta m_angleMinValue;
	Ta m_angleMaxValue;
	bool m_isClosed;
	int m_points;
	double m_specOffValue;
	double m_angleMeasure;
	long long m_freqBegin;
	long long m_freqEnd;
	int m_buffers;
	int m_capacity;

public:
	//初始化参数。
	WRDirMapInitParams(Ts specMinValue, Ts specMaxValue, double specOffValue, double angleMeasure, Ta angleMinValue, Ta angleMaxValue, int points, bool isClosed, long long freqBegin, long long freqEnd, int buffers, int capacity)
	{
		m_specMinValue = specMinValue;
		m_specMaxValue = specMaxValue;
		m_specOffValue = specOffValue;
		m_angleMeasure = angleMeasure;
		m_angleMinValue = angleMinValue;
		m_angleMaxValue = angleMaxValue;
		m_points = points;
		m_isClosed = isClosed;
		m_freqBegin = freqBegin;
		m_freqEnd = freqEnd;
		m_buffers = buffers;
		m_capacity = capacity;
	}

	//获取幅度最小值。
	inline Ts specMinValue(void) const
	{
		return m_specMinValue;
	}
	//获取幅度最大值。
	inline Ts specMaxValue(void) const
	{
		return m_specMaxValue;
	}
	//获取幅度调整值。
	inline double specOffValue(void) const
	{
		return m_specOffValue;
	}
	
	//获取角度单位量。
	inline double angleMeasure(void) const
	{
		return m_angleMeasure;
	}

	//获取角度最小值。
	inline Ta angleMinValue(void) const
	{
		return m_angleMinValue;
	}
	//获取角度最大值。
	inline Ta angleMaxValue(void) const
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
};

#endif //WRDIRMAPINITPARAMS
