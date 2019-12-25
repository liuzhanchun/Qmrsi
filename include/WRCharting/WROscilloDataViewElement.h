#pragma once
#ifndef WROSCILLODATAVIEWELEMENT
#define WROSCILLODATAVIEWELEMENT

#include <WRCharting/WRGlobal.h>
#include <WRCharting/WRChartDataViewElement.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

#define WROSCILLODATAVIEW_GRIDVISIBLE	65536UL
#define WROSCILLODATAVIEW_ZEROVISIBLE	131072UL
#define WROSCILLODATAVIEW_BUFFERINVALID	262144UL

//表示波形图数据视图元素。
class WRCHARTING_CLASS WROscilloDataViewElement : public WRChartDataViewElement
{
    Q_OBJECT

    Q_PROPERTY(WRColor backColor READ backColor WRITE setBackColor NOTIFY backColorChanged)
    Q_PROPERTY(WRColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
    Q_PROPERTY(bool gridVisible READ gridVisible WRITE setGridVisible NOTIFY gridVisibleChanged)
    Q_PROPERTY(WRColor zeroColor READ zeroColor WRITE setZeroColor NOTIFY zeroColorChanged)
    Q_PROPERTY(bool zeroVisible READ zeroVisible WRITE setZeroVisible NOTIFY zeroVisibleChanged)
    Q_PROPERTY(WRColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)

    friend class WROscilloControl;

signals:
    //背景颜色改变信号。
    void backColorChanged(WRColor value);
    //网格颜色改变信号。
    void gridColorChanged(WRColor value);
    //网格可视性改变信号。
    void gridVisibleChanged(bool value);
    //零值颜色改变信号。
    void zeroColorChanged(WRColor value);
    //零值可视性改变信号。
    void zeroVisibleChanged(bool value);
    //线条颜色改变信号。
    void lineColorChanged(WRColor value);

public slots:
    //设置背景颜色。
    void setBackColor(WRColor value);
    //设置网格颜色。
    void setGridColor(WRColor value);
    //设置网格可视性。
    void setGridVisible(bool value);
    //设置零值颜色。
    void setZeroColor(WRColor value);
    //设置零值可视性。
    void setZeroVisible(bool value);
    //设置线条颜色。
    void setLineColor(WRColor value);

private:
    int* m_showIndex;       //显示索引
    double* m_showBuffer;   //显示缓存

    QPoint* m_pointBuffer;	//点缓存
    int m_pointLength;		//点长度

    WRColor m_backColor;    //背景颜色
    WRColor m_gridColor;    //网格颜色
    WRColor m_zeroColor;    //零值颜色
    WRColor m_lineColor;    //线条颜色

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
			m_pointLength = 0;
		}
	}

	//重建点缓存。
    void createBuffer(void);

	//获取缓存是否无效。
    inline bool bufferInvalid(void) const
    {
        return readFlag(WROSCILLODATAVIEW_BUFFERINVALID);
    }
    //设置缓存是否无效。
    inline void bufferInvalid(bool value)
    {
        writeFlag(WROSCILLODATAVIEW_BUFFERINVALID, value);
    }

    //当显示数据范围改变后调用此方法 。
    void onShowDataRangeChanged(void);
    //当显示数据点范围改变后调用此方法。
    void onShowDataPointRangeChanged(void);
    //当显示数据值范围改变后调用此方法。
    void onShowDataValueRangeChanged(void);

	//初始化数据点索引。
	void initIndex(void);

	//初始化波形图对象。
	WROscilloDataViewElement(void);
	//清理当前对象所占用的相关资源。
	~WROscilloDataViewElement(void);

protected:
	//当大小改变后调用此方法。
    void onSizeChanged(void);
    //当宽度改变后调用此方法。
    void onWidthChanged(void);
    //当高度改变后调用此方法。
    void onHeightChanged(void);

    //执行缩放处理。
    bool doZoom(const WRPoint& begPos, const WRPoint& endPos);
    //执行移动处理。
    bool doMove(const WRPoint& begPos, const WRPoint& endPos);

	//鼠标滚动处理。
	bool onMouseWheel(const QWheelEvent& e);

	//执行绘制处理。
    void onPaint(QPainter& painter);

public:
	//使缓存无效。
	inline void invalidateBuffer(void)
	{
		bufferInvalid(true);
	}

	//获取背景颜色。
    inline WRColor backColor(void) const
    {
        return m_backColor;
    }
    //设置背景颜色。
    bool backColor(WRColor value);

	//获取网格颜色。
    inline WRColor gridColor(void) const
    {
        return m_gridColor;
    }
    //设置网格颜色。
    bool gridColor(WRColor value);

	//获取网格是否显示。
	inline bool gridVisible(void) const
	{
		return readFlag(WROSCILLODATAVIEW_GRIDVISIBLE);
	}
	//设置网格是否显示。
	bool gridVisible(bool value);

	//获取零值颜色。
	inline WRColor zeroColor(void) const
	{
		return m_zeroColor;
	}
	//设置零值颜色。
	bool zeroColor(WRColor value);

	//获取零值是否显示。
	inline bool zeroVisible(void) const
	{
		return readFlag(WROSCILLODATAVIEW_ZEROVISIBLE);
	}
	//设置零值是否显示。
	bool zeroVisible(bool value);

	//获取线条颜色。
	inline WRColor lineColor(void) const
	{
		return m_lineColor;
	}
	//设置线条颜色。
	bool lineColor(WRColor value);
};

//#pragma warning(pop)

#endif //WROSCILLODATAVIEWELEMENT
