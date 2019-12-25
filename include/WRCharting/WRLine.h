#pragma once
#ifndef WRLINE
#define WRLINE

#include <WRCharting/WRPoint.h>

//表示线条。
class WRLine
{
private:
	WRPoint m_beg;
	WRPoint m_end;

public:
	//初始化线条。
	inline WRLine(void)
	{
		//add code here
	}
	//初始化线条。
	inline WRLine(int begX, int begY, int endX, int endY)
		: m_beg(begX, begY), m_end(endX, endY)
	{
		//add code here
	}
	//初始化线条。
	inline WRLine(const WRPoint& beg, const WRPoint& end)
		: m_beg(beg), m_end(end)
	{
		//add code here
	}
    //初始化线条。
    inline WRLine(const QPoint& beg, const QPoint& end)
        : m_beg(beg), m_end(end)
    {
        //add code here
    }
    //初始化线条。
    inline WRLine(const WRPoint& beg, const QPoint& end)
        : m_beg(beg), m_end(end)
    {
        //add code here
    }
    //初始化线条。
    inline WRLine(const QPoint& beg, const WRPoint& end)
        : m_beg(beg), m_end(end)
    {
        //add code here
    }

	//获取起始。
	inline const WRPoint& beg(void) const
	{
		return m_beg;
	}
	//获取起始。
	inline WRPoint& beg(void)
	{
		return m_beg;
	}

	//获取结束。
	inline const WRPoint& end(void) const
	{
		return m_end;
	}
	//获取结束。
	inline WRPoint& end(void)
	{
		return m_end;
	}

	//获取起始X值。
	inline int begX(void) const
	{
		return m_beg.x();
	}
	//设置起始X值。
	inline void begX(int value)
	{
		m_beg.x(value);
	}

	//获取起始Y值。
	inline int begY(void) const
	{
		return m_beg.y();
	}
	//设置起始Y值。
	inline void begY(int value)
	{
		m_beg.y(value);
	}

	//获取结束X值。
	inline int endX(void) const
	{
		return m_end.x();
	}
	//设置结束X值。
	inline void endX(int value)
	{
		m_end.x(value);
	}

	//获取结束Y值。
	inline int endY(void) const
	{
		return m_end.y();
	}
	//设置结束Y值。
	inline void endY(int value)
	{
		m_end.y(value);
	}

	//判断是否和指定线条相等。
	inline bool equals(const WRLine& other) const
	{
		return m_beg == other.m_beg && m_end == other.m_end;
	}

	//重写等于操作符。
	inline bool operator == (const WRLine& other) const
	{
		return m_beg == other.m_beg && m_end == other.m_end;
	}
	//重载不等于操作符。
	inline bool operator != (const WRLine& other) const
	{
		return m_beg != other.m_beg || m_end != other.m_end;
	}
};

#endif //WRLINE
