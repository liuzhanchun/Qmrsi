#pragma once
#ifndef WRCHARTSAMPLERANGE
#define WRCHARTSAMPLERANGE

//表示图形样本范围
class WRChartSampleRange
{
private:
    //起始
    int m_begin;
    //数量
    int m_count;

public:
    //初始化数据点范围
    inline WRChartSampleRange()
        :m_begin(0), m_count(0)
    {
        //add code here
    }

    //初始化数据点范围
    inline WRChartSampleRange(int begin, int count)
        : m_begin(begin), m_count(count)
    {
        //add code here
    }
    //初始化数据点范围
    inline WRChartSampleRange(const WRChartSampleRange& other)
            : m_begin(other.m_begin), m_count(other.m_count)
    {
        //add code here
    }

    //重载赋操作符
    inline WRChartSampleRange& operator=(const WRChartSampleRange& other)
    {
        if (this != &other)
        {
            m_begin = other.m_begin;
            m_count = other.m_count;
        }
        return *this;
    }

    //获取起始
    inline int begin(void) const
    {
        return m_begin;
    }
    //设置起始
    inline bool begin(int value)
    {
        if (value != m_begin)
        {
            m_begin = value;
            return true;
        }
        return false;
    }

    //获取数量
    inline int count(void) const
    {
        return m_count;
    }
    //设置数量
    inline bool count(int value)
    {
        if (value != m_count)
        {
            m_count = value;
            return true;
        }
        return false;
    }

    //获取结束
    inline int end(void) const
    {
        return m_begin + m_count - 1;
    }

    //改变数据点范围
    inline bool change(const WRChartSampleRange& other)
    {
        if (other.m_begin != m_begin || other.m_count != m_count)
        {
            m_begin = other.m_begin;
            m_count = other.m_count;
            return true;
        }
        return false;
    }
    //改变数据点范围
    inline bool change(int begin, int count)
    {
        if (begin != m_begin || count != m_count)
        {
            m_begin = begin;
            m_count = count;
            return true;
        }
        return false;
    }

    //直接使用新的值更新当前对象。
    inline void update(const WRChartSampleRange& other)
    {
        m_begin = other.m_begin;
        m_count = other.m_count;
    }
    //直接使用新的值更新当前对象。
    inline void update(int begin, int count)
    {
        m_begin = begin;
        m_count = count;
    }
};

#endif // WRCHARTSAMPLERANGE
