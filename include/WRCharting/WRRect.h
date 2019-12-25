#pragma once
#ifndef WRRECT
#define WRRECT

#include <QRect>
#include <WRCharting/WRSize.h>
#include <WRCharting/WRPoint.h>

//表示矩形。
class WRRect
{
private:
	WRPoint m_pos;
	WRSize m_size;

public:
	//初始化矩形。
	inline WRRect(void)
	{
		//add code here
	}
	//初始化矩形。
	inline WRRect(int left, int top, int width, int height)
		: m_pos(left, top), m_size(width, height)
	{
		//add code here
	}
	//初始化矩形。
    inline WRRect(const QRect& other)
        : m_pos(other.left(), other.top()), m_size(other.width(), other.height())
	{
		//add code here
	}
	//初始化矩形。
	inline WRRect(const WRPoint& p1, const WRPoint& p2)
	{
		int left, right;
        if (p1.x() > p2.x())
        {
            left = p2.x();
            right = p1.x();
        }
        else
        {
            left = p1.x();
            right = p2.x();
        }

		int top, bottom;
        if (p1.y() > p2.y())
        {
            top = p2.y();
            bottom = p1.y();
        }
        else
        {
            top = p1.y();
            bottom = p2.y();
        }

		m_pos.update(left, top);
		m_size.update(right - left + 1, bottom - top + 1);
	}
	//初始化矩形。
	inline WRRect(const WRPoint& p1, const WRPoint& p2, bool& leftToRight, bool& topToBottom)
	{
		int left, right;
        if (p1.x() > p2.x())
        {
            left = p2.x();
            right = p1.x();
			leftToRight = false;
        }
        else
        {
            left = p1.x();
            right = p2.x();
			leftToRight = true;
        }

		int top, bottom;
        if (p1.y() > p2.y())
        {
            top = p2.y();
            bottom = p1.y();
			topToBottom = false;
        }
        else
        {
            top = p1.y();
            bottom = p2.y();
			topToBottom = true;
        }

		m_pos.update(left, top);
		m_size.update(right - left + 1, bottom - top + 1);
	}

	//获取位置。
	inline const WRPoint& pos(void) const
	{
		return m_pos;
	}
	//获取位置。
	inline WRPoint& pos(void)
	{
		return m_pos;
	}

	//获取尺寸。
	inline const WRSize& size(void) const
	{
		return m_size;
	}
	//获取尺寸。
	inline WRSize& size(void)
	{
		return m_size;
	}

	//获取左上角X值。
	inline int left(void) const
	{
		return m_pos.x();
	}
	//设置左上角X值。
	inline void left(int value)
	{
		m_pos.x(value);
	}

	//获取左上角Y值。
	inline int top(void) const
	{
		return m_pos.y();
	}
	//设置左上角Y值。
	inline void top(int value)
	{
		m_pos.y(value);
	}

	//获取宽度值。
	inline int width(void) const
	{
		return m_size.width();
	}
	//设置宽度值。
	inline void width(int value)
	{
		m_size.width(value);
	}

	//获取高度值。
	inline int height(void) const
	{
		return m_size.height();
	}
	//设置高度值。
	inline void height(int value)
	{
		m_size.height(value);
	}

	//获取右下角X值。
	inline int right(void) const
	{
		return m_pos.x() + m_size.width();
	}
	//获取右下角Y值。
	inline int bottom(void) const
	{
		return m_pos.y() + m_size.height();
	}

	//判断当前矩形是否为空。
	inline bool empty(void) const
	{
		return m_size.empty();
	}

	//判断是否和指定矩形相等。
	inline bool equals(const WRRect& other) const
	{
		return m_pos == other.m_pos && m_size == other.m_size;
	}

	//重写等于操作符。
	inline bool operator == (const WRRect& other) const
	{
		return m_pos == other.m_pos && m_size == other.m_size;
	}
	//重载不等于操作符。
	inline bool operator != (const WRRect& other) const
	{
		return m_pos != other.m_pos || m_size != other.m_size;
	}

	//获取矩形值。
    inline operator QRect(void) const
	{
        QRect v(m_pos.x(), m_pos.y(), m_size.width(), m_size.height());
		return v;
	}

	//判断是否和指定矩形相等。
    inline bool equals(const QRect& other) const
	{
        return m_pos.x() == other.left() && m_pos.y() == other.top() && m_size.width() == other.width() && m_size.height() == other.height();
	}

	//重写等于操作符。
    inline bool operator == (const QRect& other) const
	{
        return m_pos.x() == other.left() && m_pos.y() == other.top() && m_size.width() == other.width() && m_size.height() == other.height();
	}
	//重载不等于操作符。
    inline bool operator != (const QRect& other) const
	{
        return m_pos.x() != other.left() || m_pos.y() != other.top() || m_size.width() != other.width() || m_size.height() != other.height();
	}

	//X值是否包含在内部。
	inline bool containsX(int x) const
	{
		return left() <= x && right() > x;
	}
	//Y值是否包含在内部。
	inline bool containsY(int y) const
	{
		return top() <= y && bottom() > y;
	}
	//判断指定的点是否在内部。
	inline bool contains(const WRPoint& p) const
	{
		return containsX(p.x()) && containsY(p.y());
	}

	//调节指定的点使其包含在当前范围内。
    inline void adjust(WRPoint& p) const
    {
        if (p.x()< left())
		{
			p.x(left());
		}
        else
		{
			int v = right() - 1;
			if (p.x() > v)
			{
				p.x(v);
			}
		}
        if (p.y() < top())
		{
			p.y(top());
		}
        else
		{
			int v = bottom() - 1;
			if (p.y() > v)
			{
				p.y(v);
			}
		}
    }
};

#endif //WRRECT
