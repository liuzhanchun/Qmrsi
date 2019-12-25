#pragma once
#ifndef WRWATERFALLDATARANGE
#define WRWATERFALLDATARANGE

#include <WRCharting/WRChartSampleRange.h>

//表示瀑布图数据范围
class WRWaterfallDataRange
{
private:
    //数据点范围
    WRChartSampleRange m_pointRange;
    //数据帧范围
    WRChartSampleRange m_frameRange;

public:
	//初始化瀑布图数据范围。
	inline WRWaterfallDataRange(void)
	{
		//add code here
	}
    //初始化瀑布图数据范围。
    inline WRWaterfallDataRange(int pointBegin, int pointCount, int frameBegin, int frameCount)
        : m_pointRange(pointBegin, pointCount), m_frameRange(frameBegin, frameCount)
    {
        //add code here
    }
    //初始化瀑布图数据范围
    inline WRWaterfallDataRange(const WRChartSampleRange& pointRange, const WRChartSampleRange& frameRange)
            : m_pointRange(pointRange), m_frameRange(frameRange)
    {
        //add code here
    }
    //初始化瀑布图数据范围
    inline WRWaterfallDataRange(const WRWaterfallDataRange& other)
            : m_pointRange(other.m_pointRange), m_frameRange(other.m_frameRange)
    {
        //add code here
    }

    //重载赋点操作符
    inline WRWaterfallDataRange& operator=(const WRWaterfallDataRange& other)
    {
        if (this != &other)
        {
            m_pointRange = other.m_pointRange;
            m_frameRange = other.m_frameRange;
        }
        return *this;
    }

    //获取数据点范围
    inline const WRChartSampleRange& pointRange(void) const
    {
        return m_pointRange;
    }
    //获取数据点范围
    inline WRChartSampleRange& pointRange()
    {
        return m_pointRange;
    }
    //设置数据点范围
    inline bool pointRange(const WRChartSampleRange& value)
    {
        return m_pointRange.change(value);
    }
    //设置数据点范围
    inline bool pointRange(int begin, int count)
    {
        return m_pointRange.change(begin, count);
    }

    //获取数据起始
    inline int pointBegin(void) const
    {
        return m_pointRange.begin();
    }
    //设置数据起始
    inline bool pointBegin(int value)
    {
        return m_pointRange.begin(value);
    }

    //获取数据数量
    inline int pointCount(void) const
    {
        return m_pointRange.count();
    }
    //设置数据数量
    inline bool pointCount(int value)
    {
        return m_pointRange.count(value);
    }

    //获取数据数量
    inline int pointEnd(void) const
    {
        return m_pointRange.end();
    }

    //获取数据帧范围
    inline const WRChartSampleRange& frameRange(void) const
    {
        return m_frameRange;
    }
    //获取数据帧范围
    inline WRChartSampleRange& frameRange()
    {
        return m_frameRange;
    }
    //设置数据帧范围
    inline bool frameRange(const WRChartSampleRange& value)
    {
        return m_frameRange.change(value);
    }
    //设置数据帧范围
    inline bool frameRange(int begin, int end)
    {
        return m_frameRange.change(begin, end);
    }

    //获取数据值起始
    inline int frameBegin(void) const
    {
        return m_frameRange.begin();
    }
    //设置数据值起始
    inline bool frameBegin(int value)
    {
        return m_frameRange.begin(value);
    }

    //获取数据值数量
    inline int frameCount(void) const
    {
        return m_frameRange.count();
    }
    //设置数据值数量
    inline bool frameCount(int value)
    {
        return m_frameRange.count(value);
    }

    //获取数据值结束
    inline int frameEnd(void) const
    {
        return m_frameRange.end();
    }
};

#endif //WRWATERFALLDATARANGE
