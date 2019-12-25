#pragma once
#ifndef WRCOLOR
#define WRCOLOR

#include <QColor>

//表示颜色值。
class WRColor
{
private:
	//蓝色分量
	unsigned char m_b;
	//绿色分量
	unsigned char m_g;
	//红色分量
	unsigned char m_r;
	//Alpha分量
	unsigned char m_a;

public:
	//初始化颜色值。
	inline WRColor(void)
	{
		//add code here
	}
	//初始化颜色值。
    inline WRColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF)
	{
		m_r = r;
		m_g = g;
		m_b = b;
		m_a = a;
	}
    //初始化颜色值。
    inline WRColor(const QColor& other)
    {
        m_r = (unsigned char)other.red();
        m_g = (unsigned char)other.green();
        m_b = (unsigned char)other.blue();
        m_a = (unsigned char)other.alpha();
    }

	//获取蓝色分量。
	inline unsigned char blue(void) const
	{
		return m_b;
	}
	//设置蓝色分量。
	inline void blue(unsigned char value)
	{
		m_b = value;
	}

	//获取绿色分量。
	inline unsigned char green(void) const
	{
		return m_g;
	}
	//设置绿色分量。
	inline void green(unsigned char value)
	{
		m_g = value;
	}

	//获取红色分量。
	inline unsigned char red(void) const
	{
		return m_r;
	}
	//设置红色分量。
	inline void red(unsigned char value)
	{
		m_r = value;
	}

	//获取Alpha分量。
	inline unsigned char alpha(void) const
	{
		return m_a;
	}
	//设置Alpha分量。
	inline void alpha(unsigned char value)
	{
		m_a = value;
	}

	//更新颜色值。
	inline bool change(const WRColor& other)
	{
		if (*(unsigned int*)this == *(const unsigned int*)(&other))
		{
			*(unsigned int*)this = *(const unsigned int*)(&other);
			return true;
		}
		return false;
	}
	//更新颜色值。
    inline bool change(const unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF)
	{
		if (m_r != r || m_g != g || m_b != b || m_a != a)
		{
			m_r = r;
			m_g = g;
			m_b = b;
			m_a = a;
			return true;
		}
		return false;
    }
    //更新颜色值。
    inline bool change(const QColor& other)
    {
        if (m_r != other.red() || m_g != other.green() || m_b != other.blue() || m_a != other.alpha())
        {
            m_r = (unsigned char)other.red();
            m_g = (unsigned char)other.green();
            m_b = (unsigned char)other.blue();
            m_a = (unsigned char)other.alpha();
            return true;
        }
        return false;
    }

	//更新颜色值。
	inline void update(const WRColor& other)
	{
		*(unsigned int*)this = *(const unsigned int*)(&other);
	}
	//更新颜色值。
    inline void update(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF)
	{
		m_r = r;
		m_g = g;
		m_b = b;
		m_a = a;
	}
    //更新颜色值。
    inline void update(const QColor& other)
    {
        m_r = (unsigned char)other.red();
        m_g = (unsigned char)other.green();
        m_b = (unsigned char)other.blue();
        m_a = (unsigned char)other.alpha();
    }

	//执行反色。
	inline void inverse(void)
	{
		m_r = 255 - m_r;
		m_g = 255 - m_g;
		m_b = 255 - m_b;
	}

	//返回颜色的RBG值。
	inline unsigned int toRgb(void) const
	{
		return m_r | (((short)m_g) << 8) | (((unsigned int)m_b) << 16);
	}

	//将当前颜色和指定颜色按其Alpha分量进行混合。
	inline void blend(const WRColor& other)
	{
		unsigned int r1 = other.m_a;
		unsigned int r2 = 255 - other.m_a;
		m_r = (unsigned char)(m_r * r2 / 255 + other.m_r * r1 / 255);
		m_g = (unsigned char)(m_g * r2 / 255 + other.m_g * r1 / 255);
		m_b = (unsigned char)(m_b * r2 / 255 + other.m_b * r1 / 255);
	}
	//将当前颜色和指定颜色按指定的Alpha分量进行混合。
	inline void blend(const WRColor& other, unsigned char alpha)
	{
		unsigned int r1 = alpha;
		unsigned int r2 = 255 - alpha;
		m_r = (unsigned char)(m_r * r2 / 255 + other.m_r * r1 / 255);
		m_g = (unsigned char)(m_g * r2 / 255 + other.m_g * r1 / 255);
		m_b = (unsigned char)(m_b * r2 / 255 + other.m_b * r1 / 255);
	}

	//判断是否和指定颜色相等。
	inline bool equals(const WRColor& other) const
	{
		return *(const unsigned int*)this == *(const unsigned int*)(&other);
	}

	//重写等于操作符。
	inline bool operator == (const WRColor& other) const
	{
		return *(const unsigned int*)this == *(const unsigned int*)(&other);
	}
	//重载不等于操作符。
	inline bool operator != (const WRColor& other) const
	{
		return *(const unsigned int*)this != *(const unsigned int*)(&other);
	}
\
    //判断是否和指定颜色相等。
    inline bool equals(const QColor& other) const
    {
        return m_r == other.red() && m_g == other.green() && m_b == other.blue() && m_a == other.alpha();
    }

    //重写等于操作符。
    inline bool operator == (const QColor& other) const
    {
        return m_r == other.red() && m_g == other.green() && m_b == other.blue() && m_a == other.alpha();
    }
    //重载不等于操作符。
    inline bool operator != (const QColor& other) const
    {
        return m_r != other.red() || m_g != other.green() || m_b != other.blue() || m_a != other.alpha();
    }

    //获取颜色值。
    inline operator QColor(void) const
    {
        QColor v(m_r, m_g, m_b, m_a);
        return v;
    }
};

#endif //WRCOLOR
