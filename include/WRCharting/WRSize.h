#pragma once
#ifndef WRSIZE
#define WRSIZE

#include <QSize>

//表示尺寸。
class WRSize
{
private:
    QSize m_d;

public:
	//初始化尺寸。
	inline WRSize(void)
        : m_d(0, 0)
    {
        //add code here
	}
	//初始化尺寸。
	inline WRSize(int width, int height)
        : m_d(width, height)
    {
        //add code here
	}
	//初始化尺寸。
    inline WRSize(const QSize& other)
        : m_d(other)
    {
        //add code here
	}

	//获取宽度值。
	inline int width(void) const
	{
        return m_d.width();
	}
	//设置宽度值。
	inline void width(int value)
    {
        m_d.setWidth(value);
	}

	//获取高度值。
	inline int height(void) const
    {
        return m_d.height();
	}
	//设置高度值。
	inline void height(int value)
    {
        m_d.setHeight(value);
	}

	//改变数据点，如果发生了改变，则返回True，否则返回False。
	inline bool change(int width, int height)
	{
		bool changed = false;
        if (m_d.width() != width)
        {
            m_d.setWidth(width);
			changed = true;
		}
        if (m_d.height() != height)
        {
            m_d.setHeight(height);
			changed = true;
		}
		return changed;
	}
	//更新数据点，直接改变数据。
	inline void update(int width, int height)
    {
        m_d.setWidth(width);
        m_d.setHeight(height);
	}

	//改变数据点，如果发生了改变，则返回True，否则返回False。
	inline bool change(const WRSize& other)
	{
        if (m_d != other.m_d)
        {
            m_d = other.m_d;
            return true;
        }
        return false;
	}
	//更新数据点，直接改变数据。
	inline void update(const WRSize& other)
    {
        m_d = other.m_d;
	}

	//改变数据点，如果发生了改变，则返回True，否则返回False。
    inline bool change(const QSize& other)
	{
        if (m_d != other)
        {
            m_d = other;
            return true;
        }
        return false;
	}
	//更新数据点，直接改变数据。
    inline void update(const QSize& other)
	{
        m_d = other;
	}

	//判断当前尺寸是否为空尺寸。
	inline bool empty(void) const
    {
        return m_d.isEmpty();
	}

	//判断是否和指定尺寸相等。
	inline bool equals(const WRSize& other) const
    {
        return m_d == other.m_d;
	}

	//重写等于操作符。
	inline bool operator == (const WRSize& other) const
    {
        return m_d == other.m_d;
	}
	//重载不等于操作符。
	inline bool operator != (const WRSize& other) const
    {
        return m_d != other.m_d;
	}

    //获取尺寸值。
    inline operator QSize&(void)
    {
        return m_d;
    }
	//获取尺寸值。
    inline operator const QSize&(void) const
    {
        return m_d;
	}

	//判断是否和指定尺寸相等。
    inline bool equals(const QSize& other) const
    {
        return m_d == other;
	}

	//重写等于操作符。
    inline bool operator == (const QSize& other) const
    {
        return m_d == other;
	}
	//重载不等于操作符。
    inline bool operator != (const QSize& other) const
    {
        return m_d != other;
	}
};

#endif //WRSIZE
