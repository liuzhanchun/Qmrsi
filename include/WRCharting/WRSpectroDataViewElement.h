#pragma once
#ifndef WRSPECTRODATAVIEWELEMENT
#define WRSPECTRODATAVIEWELEMENT

#include <WRCharting/WRGlobal.h>
#include <WRCharting/WRChartDataViewElement.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

#define WRSPECTRODATAVIEW_GRIDVISIBLE	65536UL

//表示频谱图数据视图元素。
class WRCHARTING_CLASS WRSpectroDataViewElement : public WRChartDataViewElement
{
    Q_OBJECT

    Q_PROPERTY(WRColor backColor READ backColor WRITE setBackColor NOTIFY backColorChanged)
    Q_PROPERTY(WRColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
    Q_PROPERTY(bool gridVisible READ gridVisible WRITE setGridVisible NOTIFY gridVisibleChanged)

    friend class WRSpectroControl;
	friend class WRSpectroChannel;

signals:
    //背景颜色改变信号。
    void backColorChanged(WRColor value);
    //网格颜色改变信号。
    void gridColorChanged(WRColor value);
    //网格可视性改变信号。
    void gridVisibleChanged(bool value);

public slots:
    //设置背景颜色。
    void setBackColor(WRColor value);
    //设置网格颜色。
    void setGridColor(WRColor value);
    //设置网格可视性。
    void setGridVisible(bool value);

private:
    int* m_showIndex;       //显示索引
    double* m_showBuffer;   //显示缓存

    WRColor m_backColor;    //背景颜色
    WRColor m_gridColor;    //网格颜色

    //当显示数据范围改变后调用此方法 。
    void onShowDataRangeChanged(void);
    //当显示数据点范围改变后调用此方法。
    void onShowDataPointRangeChanged(void);
    //当显示数据值范围改变后调用此方法。
    void onShowDataValueRangeChanged(void);

	//初始化数据点索引。
	void initIndex(void);

	//初始化频谱图对象。
	WRSpectroDataViewElement(void);
	//清理当前对象所占用的相关资源。
	~WRSpectroDataViewElement(void);

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
		return readFlag(WRSPECTRODATAVIEW_GRIDVISIBLE);
	}
	//设置网格是否显示。
	bool gridVisible(bool value);
};

//#pragma warning(pop)

#endif //WRSPECTRODATAVIEWELEMENT
