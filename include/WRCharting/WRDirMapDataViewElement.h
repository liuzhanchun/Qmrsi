#pragma once
#ifndef WRDIRMAPDATAVIEWELEMENT
#define WRDIRMAPDATAVIEWELEMENT

#include <WRCharting/WRDirMapDataPalette.h>
#include <WRCharting/WRChartDataViewElement.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

//表示向频图数据视图元素。
class WRCHARTING_CLASS WRDirMapDataViewElement : public WRChartDataViewElement
{
    Q_OBJECT

    Q_PROPERTY(WRDirMapDataPalette* dataPalette READ dataPalette WRITE setDataPalette NOTIFY dataPaletteChanged)

    friend class WRDirMapControl;

signals:
    //数据调色板改变信号。
    void dataPaletteChanged(WRDirMapDataPalette* value);

public slots:
    //设置数据调色板。
    void setDataPalette(WRDirMapDataPalette* value);

private:
    QImage* m_bitmap;               //图形句柄
    WRDirMapDataPalette* m_palette; //调色板

    double* m_showBuffer;           //数据缓存
    int* m_showIndex;               //显示索引

    //当显示数据范围改变后调用此方法 。
    void onShowDataRangeChanged(void);
    //当显示数据点范围改变后调用此方法。
    void onShowDataPointRangeChanged(void);
    //当显示数据角度范围改变后调用此方法。
    void onShowDataAngleRangeChanged(void);

    //初始化数据点索引。
    void initIndex(void);
    //填充位图。
    void fillBitmap(void);

    //初始化向频图对象。
    WRDirMapDataViewElement(void);
    //清理当前对象所占用的相关资源。
    ~WRDirMapDataViewElement(void);

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
	inline WRDirMapDataPalette* dataPalette(void) const
	{
		return m_palette;
	}
	//设置数据调色板。
	bool dataPalette(WRDirMapDataPalette* value);
	//设置数据调色板。
	bool dataPalette(const WRColor* list, int size);
};

//#pragma warning(pop)

#endif //WRDIRMAPDATAVIEWELEMENT
