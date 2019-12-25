#pragma once
#ifndef WRCHARTDVALUERANGE
#define WRCHARTDVALUERANGE

//表示图形双精度数值范围
class WRChartDValueRange
{
private:
    //起始
    double m_begin;
    //结束
    double m_end;

public:
    //初始化数据值范围
    inline WRChartDValueRange()
        :m_begin(0), m_end(0)
    {
        //add code here
    }

    //初始化数据值范围
    inline WRChartDValueRange(double begin, double end)
        : m_begin(begin), m_end(end)
    {
        //add code here
    }
    //初始化数据值范围
    inline WRChartDValueRange(const WRChartDValueRange& other)
            : m_begin(other.m_begin), m_end(other.m_end)
    {
        //add code here
    }

    //重载赋值操作符
    inline WRChartDValueRange& operator=(const WRChartDValueRange& other)
    {
        if (this != &other)
        {
            m_begin = other.m_begin;
            m_end = other.m_end;
        }
        return *this;
    }

    //获取起始
    inline double begin(void) const
    {
        return m_begin;
    }
    //设置起始
    inline bool begin(double value)
    {
        if (value != m_begin)
        {
            m_begin = value;
            return true;
        }
        return false;
    }

    //获取结束
    inline double end(void) const
    {
        return m_end;
    }
    //设置结束
    inline bool end(double value)
    {
        if (value != m_end)
        {
            m_end = value;
            return true;
        }
        return false;
    }

    //获取跨度
    inline double span(void) const
    {
        return m_end - m_begin;
    }

    //改变数据值范围
    inline bool change(const WRChartDValueRange& other)
    {
        if (other.m_begin != m_begin || other.m_end != m_end)
        {
            m_begin = other.m_begin;
            m_end = other.m_end;
            return true;
        }
        return false;
    }
    //改变数据值范围
    inline bool change(double begin, double end)
    {
        if (begin != m_begin || end != m_end)
        {
            m_begin = begin;
            m_end = end;
            return true;
        }
        return false;
    }

    //更新数据值范围
    inline void update(const WRChartDValueRange& other)
    {
        m_begin = other.m_begin;
        m_end = other.m_end;
    }
    //更新数据值范围
    inline void update(double begin, double end)
    {
        m_begin = begin;
        m_end = end;
    }
};

#endif // WRCHARTDVALUERANGE
