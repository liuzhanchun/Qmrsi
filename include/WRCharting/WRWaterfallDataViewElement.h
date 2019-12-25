#pragma once
#ifndef WRWATERFALLDATAVIEWELEMENT
#define WRWATERFALLDATAVIEWELEMENT

#include <WRCharting/WRWaterfallDataPalette.h>
#include <WRCharting/WRChartDataViewElement.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

//表示瀑布图数据视图元素。
class WRCHARTING_CLASS WRWaterfallDataViewElement : public WRChartDataViewElement
{
    Q_OBJECT

    Q_PROPERTY(WRWaterfallDataPalette* dataPalette READ dataPalette WRITE setDataPalette NOTIFY dataPaletteChanged)

    friend class WRWaterfallControl;

signals:
    //数据调色板改变信号。
    void dataPaletteChanged(WRWaterfallDataPalette* value);

public slots:
    //设置数据调色板。
    void setDataPalette(WRWaterfallDataPalette* value);

private:
    QImage* m_bitmap;                   //图形对象
    WRWaterfallDataPalette* m_palette;  //调色板

    double* m_showBuffer;               //数据缓存
    int* m_showIndexP;                  //点显示索引
    int* m_showIndexF;                  //帧显示索引

    //当是否纵向改变后调用此方法。
    void onVerticalChanged(void);

    //当显示数据范围改变后调用此方法 。
    void onShowDataRangeChanged(void);
    //当显示数据点范围改变后调用此方法。
    void onShowDataPointRangeChanged(void);
    //当显示数据帧范围改变后调用此方法。
    void onShowDataFrameRangeChanged(void);

    //初始化横向数据点索引。
    void initHIndexP(void);
    //初始化横向向数据帧索引。
    void initHIndexF(void);
    //填充横向位图。
    void fillHBitmap(void);

    //初始化纵向数据点索引。
    void initVIndexP(void);
    //初始化纵向数据帧索引。
    void initVIndexF(void);
    //填充纵向位图。
    void fillVBitmap(void);

    //初始化瀑布图对象。
    WRWaterfallDataViewElement(void);
    //清理当前对象所占用的相关资源。
    ~WRWaterfallDataViewElement(void);

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
	//获取数据调色板。
	inline WRWaterfallDataPalette* dataPalette(void) const
	{
		return m_palette;
	}
	//设置数据调色板。
	bool dataPalette(WRWaterfallDataPalette* value);
	//设置数据调色板。
	bool dataPalette(const WRColor* list, int size);
};

//#pragma warning(pop)

#endif //WRWATERFALLDATAVIEWELEMENT
