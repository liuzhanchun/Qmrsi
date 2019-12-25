#pragma once
#ifndef WRSPECTRODATARANGE
#define WRSPECTRODATARANGE

#include <WRCharting/WRChartDValueRange.h>
#include <WRCharting/WRChartSampleRange.h>

//表示频谱图数据范围
class WRSpectroDataRange
{
private:
    //数据点范围
    WRChartSampleRange m_pointRange;
    //数据值范围
    WRChartDValueRange m_valueRange;

public:
	//初始化频谱图数据范围。
	inline WRSpectroDataRange(void)
	{
		//add code here
	}
	//初始化频谱图数据范围。
    inline WRSpectroDataRange(const WRChartSampleRange& pointRange, const WRChartDValueRange& valueRange)
        : m_pointRange(pointRange), m_valueRange(valueRange)
    {
        //add code here
    }
    //初始化频谱图数据范围。
    inline WRSpectroDataRange(int pointBegin, int pointCount, double valueBegin, double valueEnd)
        : m_pointRange(pointBegin, pointCount), m_valueRange(valueBegin, valueEnd)
    {
        //add code here
    }
    //初始化频谱图数据范围
    inline WRSpectroDataRange(const WRSpectroDataRange& other)
            : m_pointRange(other.m_pointRange), m_valueRange(other.m_valueRange)
    {
        //add code here
    }

    //重载赋点操作符
    inline WRSpectroDataRange& operator=(const WRSpectroDataRange& other)
    {
        if (this != &other)
        {
            m_pointRange = other.m_pointRange;
            m_valueRange = other.m_valueRange;
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

    //获取数据值范围
    inline const WRChartDValueRange& valueRange(void) const
    {
        return m_valueRange;
    }
    //获取数据值范围
    inline WRChartDValueRange& valueRange()
    {
        return m_valueRange;
    }
    //设置数据值范围
    inline bool valueRange(const WRChartDValueRange& value)
    {
        return m_valueRange.change(value);
    }
    //设置数据值范围
    inline bool valueRange(double begin, double end)
    {
        return m_valueRange.change(begin, end);
    }

    //获取数据值起始
    inline double valueBegin(void) const
    {
        return m_valueRange.begin();
    }
    //设置数据值起始
    inline bool valueBegin(double value)
    {
        return m_valueRange.begin(value);
    }

    //获取数据值结束
    inline double valueEnd(void) const
    {
        return m_valueRange.end();
    }
    //设置数据值结束
    inline bool valueEnd(double value)
    {
        return m_valueRange.end(value);
    }

    //获取数据值跨度
    inline double valueSpan(void) const
    {
        return m_valueRange.span();
    }
};

#endif //WRSPECTRODATARANGE
