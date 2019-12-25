#pragma once
#ifndef WROSCILLOINITPARAMS
#define WROSCILLOINITPARAMS

//表示波形图初始化参数。
template <class T> class WROscilloInitParams
{
private:
	T m_minValue;
	T m_maxValue;
	int m_sampleRate;
	int m_buffers;
	int m_capacity;

public:
	//初始化参数。
	WROscilloInitParams(T minValue, T maxValue, int sampleRate, int buffers, int capacity)
	{
		m_minValue = minValue;
		m_maxValue = maxValue;
		m_sampleRate = sampleRate;
		m_buffers = buffers;
		m_capacity = capacity;
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

	//获取数据采样率。
	inline int sampleRate(void) const
	{
		return m_sampleRate;
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
};

#endif //WROSCILLOINITPARAMS
