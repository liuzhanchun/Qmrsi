#pragma once
#ifndef WRSPECTROCHANNEL
#define WRSPECTROCHANNEL

#include <WRCharting/WRGlobal.h>
#include <WRCharting/WRColor.h>
#include <QObject>
#include <QPainter>

#define WRSPECTROCHANNELS 32

#define WRSPECTROCHANNEL_VISIBLE	256U
#define WRSPECTROCHANNEL_INVALID	512U

//#pragma warning(push)
//#pragma warning(disable:4251)

//声明频谱图控件。
class WRSpectroControl;

//表示频谱图通道。
class WRCHARTING_CLASS WRSpectroChannel : public QObject
{
    Q_OBJECT

    Q_ENUMS(DataZoomMethod)

	friend class WRSpectroControl;
	friend class WRSpectroDataViewElement;

public:
    //枚举数据抽取方式。
    enum DataZoomMethod
    {
        //显示数据范围值。
        ShowDataRange = 0,
        //显示最大值。
        ShowMaxValue = 1,
        //显示最小值。
        ShowMinValue = 2,
    };

signals:
    //可视性改变信号。
    void visibleChanged(bool value);
    //线条颜色改变信号。
    void lineColorChanged(WRColor value);
    //标记颜色改变信号。
    void markColorChanged(WRColor value);
    //缩放方式改变信号。
    void dataZoomMethodChanged(DataZoomMethod value);

public slots:
    //设置可视性。
    void setVisible(bool value);

    //设置线条颜色。
    void setLineColor(WRColor value);
    //设置标记颜色。
    void setMarkColor(WRColor value);

    //设置绽放方式。
    void setDataZoomMethod(DataZoomMethod value);

private:
	//所有者。
	WRSpectroControl* m_owner;
	//标记值。
	unsigned int m_flags;
	//索引号。
	int m_index;
	//点缓存。
	QPoint* m_pointBuffer;
	//标记点缓存。
	QPoint* m_markPointBuffer;
	//点长度。
	int m_pointLength;
	//标记点长度。
	int m_markPointLength;
	//标记点数量。
	int m_markPointCount;
	//数据抽取方式。
	DataZoomMethod m_dataZoomMethod;
	//线条颜色。
	WRColor m_lineColor;
	//标记颜色。
	WRColor m_markColor;

	//读取标记
    inline bool readFlag(unsigned int field) const
    {
        return ((m_flags & field) != 0);
    }
    //写入标记
	inline void writeFlag(unsigned int field, bool value)
    {
        if (value)
        {
            m_flags |= field;
        }
        else
        {
            m_flags &= ~field;
        }
    }

	//获取界面是否无效。
    inline bool invalid(void) const
    {
        return readFlag(WRSPECTROCHANNEL_INVALID);
    }
    //设置界面是否无效。
    inline void invalid(bool value)
    {
        writeFlag(WRSPECTROCHANNEL_INVALID, value);
    }

	//获取点缓存。
	inline QPoint* getPointBuffer(int n)
	{
		if (m_pointBuffer == 0)
		{
			m_pointBuffer = new QPoint[n];
			m_pointLength = n;
		}
		else if (m_pointLength != n)
		{
			delete[] m_pointBuffer;
			m_pointBuffer = new QPoint[n];
			m_pointLength = n;
		}
		return m_pointBuffer;
	}
	//删除点删除。
	inline void delPointBuffer(void)
	{
		if (m_pointBuffer)
		{
			delete[] m_pointBuffer;
			m_pointBuffer = 0;
			m_pointLength = 0;
		}
	}

	//获取标记点缓存。
	inline QPoint* getMarkPointBuffer(int n)
	{
		if (m_markPointBuffer == 0)
		{
			m_markPointBuffer = new QPoint[n];
			m_markPointLength = n;
		}
		else if (m_markPointLength != n)
		{
			delete[] m_markPointBuffer;
			m_markPointBuffer = new QPoint[n];
			m_markPointLength = n;
		}
		return m_markPointBuffer;
	}
	//删除标记点删除。
	inline void delMarkPointBuffer(void)
	{
		if (m_markPointBuffer)
		{
			delete[] m_markPointBuffer;
			m_markPointBuffer = 0;
			m_markPointLength = 0;
			m_markPointCount = 0;
		}
	}

	//重建缓存。
	void createBuffer(void);

	//执行绘制处理。
	void onPaint(QPainter& painter);

	//禁用复制构造函数。
	WRSpectroChannel(const WRSpectroChannel& other);
	//禁用赋值操作符。
	WRSpectroChannel& operator=(const WRSpectroChannel& other);

	//初始化当前对象。
	inline WRSpectroChannel(void)
	{
        writeFlag(WRSPECTROCHANNEL_VISIBLE, true);
        writeFlag(WRSPECTROCHANNEL_INVALID, true);
		m_pointBuffer = 0;
		m_pointLength = 0;
		m_markPointBuffer = 0;
		m_markPointLength = 0;
		m_markPointCount = 0;
		m_dataZoomMethod = ShowMaxValue;
	}
	//清理当前对象所占用的相关资源。
	inline ~WRSpectroChannel(void)
	{
		delPointBuffer();
		delMarkPointBuffer();
	}

public:
	//获取通道索引号。
	inline int index(void) const
	{
		return m_index;
	}

	//获取是否可见。
    inline bool visible(void) const
    {
        return readFlag(WRSPECTROCHANNEL_VISIBLE);
    }
    //设置是否可见。
    bool visible(bool value);

	//获取线条颜色。
	inline WRColor lineColor(void) const
	{
		return m_lineColor;
	}
	//设置线条颜色。
	bool lineColor(WRColor value);
	
	//获取标记颜色。
	inline WRColor markColor(void) const
	{
		return m_markColor;
	}
	//设置标记颜色。
	bool markColor(WRColor value);

	//使当前缓存内容无效。
    inline void invalidate(void)
    {
		invalid(true);
    }

	//更改数据，如果数据为NULL，则表示清空数据。
	void alterData(const void* data);
	//更改数据，如果数据为NULL，则表示清空数据, 如果。
	void alterData(const void* data, const int* markBuf, int markLen);
	//清除数据。
	inline void clearData(void)
	{
		alterData(0);
	}

	//数据抽取方式。
	inline DataZoomMethod dataZoomMethod(void) const
	{
		return m_dataZoomMethod;
	}
	//设置数据抽取方式。
	bool dataZoomMethod(DataZoomMethod value);
};

//#pragma warning(pop)

#endif //WRSPECTROCHANNEL
