#pragma once
#ifndef WRPOINT
#define WRPOINT

#include <QPoint>

//表示点。
class WRPoint
{
private:
    QPoint m_d;

public:
	//初始化点。
	inline WRPoint(void)
    {
        //add code here
	}
	//初始化点。
	inline WRPoint(int x, int y)
        : m_d(x, y)
    {
        //add code here
	}
	//初始化点。
    inline WRPoint(const QPoint& p)
        : m_d(p)
    {
        //add code here
	}

	//获取X值。
	inline int x(void) const
	{
        return m_d.x();
	}
	//设置X值。
	inline void x(int value)
    {
        m_d.setX(value);
	}

	//获取Y值。
	inline int y(void) const
	{
        return m_d.y();
	}
	//设置Y值。
	inline void y(int value)
    {
        m_d.setY(value);
	}

	//改变数据点，如果发生了改变，则返回True，否则返回False。
	inline bool change(int x, int y)
	{
		bool changed = false;
        if (m_d.x() != x)
		{
            m_d.setX(x);
			changed = true;
		}
        if (m_d.y() != y)
		{
            m_d.setY(y);
			changed = true;
		}
		return changed;
	}
	//更新数据点，直接改变数据。
	inline void update(int x, int y)
    {
        m_d.setX(x);
        m_d.setY(y);
    }

	//改变数据点，如果发生了改变，则返回True，否则返回False。
	inline bool change(const WRPoint& other)
	{
        if (m_d != other.m_d)
        {
            m_d = other.m_d;
            return true;
        }
        return false;
	}
	//更新数据点，直接改变数据。
	inline void update(const WRPoint& other)
    {
        m_d = other.m_d;
	}

	//改变数据点，如果发生了改变，则返回True，否则返回False。
    inline bool change(const QPoint& other)
	{
        if (m_d != other)
        {
            m_d = other;
            return true;
        }
        return false;
	}
	//更新数据点，直接改变数据。
    inline void update(const QPoint& other)
    {
        m_d = other;
	}

	//判断是否和指定点相等。
	inline bool equals(const WRPoint& other) const
    {
        return m_d == other.m_d;
	}

	//重写等于操作符。
	inline bool operator == (const WRPoint& other) const
    {
        return m_d == other.m_d;
	}
	//重载不等于操作符。
	inline bool operator != (const WRPoint& other) const
    {
        return m_d != other.m_d;
	}

    //获取点值。
    inline operator QPoint&(void)
    {
        return m_d;
    }
	//获取点值。
    inline operator const QPoint&(void) const
    {
        return m_d;
	}

	//判断是否和指定点相等。
    inline bool equals(const QPoint& other) const
	{
        return m_d == other;
	}

	//重写等于操作符。
    inline bool operator == (const QPoint& other) const
    {
        return m_d == other;
	}
	//重载不等于操作符。
    inline bool operator != (const QPoint& other) const
    {
        return m_d != other;
	}
};

#endif //WRPOINT
