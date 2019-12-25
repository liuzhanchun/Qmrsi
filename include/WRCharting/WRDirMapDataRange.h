#pragma once
#ifndef WRDIRMAPDATARANGE
#define WRDIRMAPDATARANGE

#include <WRCharting/WRChartDValueRange.h>
#include <WRCharting/WRChartSampleRange.h>

//表示向频图数据范围
class WRDirMapDataRange
{
private:
    //数据点范围
    WRChartSampleRange m_pointRange;
    //数据角度范围
    WRChartDValueRange m_angleRange;

public:
	//初始化向频图数据范围。
	inline WRDirMapDataRange(void)
	{
		//add code here
	}
	//初始化向频图数据范围。
    inline WRDirMapDataRange(const WRChartSampleRange& pointRange, const WRChartDValueRange& angleRange)
        : m_pointRange(pointRange), m_angleRange(angleRange)
    {
        //add code here
    }
    //初始化向频图数据范围。
    inline WRDirMapDataRange(int pointBegin, int pointCount, double angleBegin, double angleEnd)
        : m_pointRange(pointBegin, pointCount), m_angleRange(angleBegin, angleEnd)
    {
        //add code here
    }
    //初始化向频图数据范围
    inline WRDirMapDataRange(const WRDirMapDataRange& other)
            : m_pointRange(other.m_pointRange), m_angleRange(other.m_angleRange)
    {
        //add code here
    }

    //重载赋点操作符
    inline WRDirMapDataRange& operator=(const WRDirMapDataRange& other)
    {
        if (this != &other)
        {
            m_pointRange = other.m_pointRange;
            m_angleRange = other.m_angleRange;
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

    //获取数据结束
    inline int pointEnd(void) const
    {
        return m_pointRange.end();
    }

    //获取数据角度范围
    inline const WRChartDValueRange& angleRange(void) const
    {
        return m_angleRange;
    }
    //获取数据角度范围
    inline WRChartDValueRange& angleRange()
    {
        return m_angleRange;
    }
    //设置数据角度范围
    inline bool angleRange(const WRChartDValueRange& value)
    {
        return m_angleRange.change(value);
    }
    //设置数据角度范围
    inline bool angleRange(double begin, double end)
    {
        return m_angleRange.change(begin, end);
    }

    //获取数据角度起始
    inline double angleBegin(void) const
    {
        return m_angleRange.begin();
    }
    //设置数据角度起始
    inline bool angleBegin(double value)
    {
        return m_angleRange.begin(value);
    }

    //获取数据角度结束
    inline double angleEnd(void) const
    {
        return m_angleRange.end();
    }
    //设置数据角度结束
    inline bool angleEnd(double value)
    {
        return m_angleRange.end(value);
    }

    //获取数据角度跨度
    inline double angleSpan(void) const
    {
        return m_angleRange.span();
    }
};

#endif //WRDIRMAPDATARANGE
