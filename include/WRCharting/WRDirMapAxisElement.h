#pragma once
#ifndef WRDIRMAPAXISELEMENT
#define WRDIRMAPAXISELEMENT

#include <WRCharting/WRGlobal.h>
#include <WRCharting/WRChartAxisElement.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

//表示向频图横向坐标轴元素。
class WRCHARTING_CLASS WRDirMapHAxisElement : public WRChartHAxisElement
{
    Q_OBJECT

    friend class WRDirMapControl;

private:
	//初始化当前对象。
	WRDirMapHAxisElement(void)
	{
		//add code here
	}
	//清理当前对象所占用的相关资源。
	~WRDirMapHAxisElement(void)
	{
		//add code here
	}

protected:
	//鼠标滚动处理，如果需要重绘，则返回True。
	bool onMouseWheel(const QWheelEvent& e);
	//鼠标按下处理，如果需要重绘，则返回True。
	bool onMouseDown(const QMouseEvent& e);
	//鼠标释放处理，如果需要重绘，则返回True。
	bool onMouseUp(const QMouseEvent& e);
	//鼠标移动处理，如果需要重绘，则返回True。
	bool onMouseMove(const QMouseEvent& e);
	
	//鼠标双击处理，如果需要重绘，则返回True。
	bool onMouseDoubleClick(const QMouseEvent& e);

	//执行绘制处理。
	void onPaint(QPainter& painter);
	//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
	void onPaintMouseFeedback(QPainter& painter);
};

//表示向频图纵向坐标轴元素。
class WRCHARTING_CLASS WRDirMapVAxisElement : public WRChartVAxisElement
{
    Q_OBJECT

    friend class WRDirMapControl;

private:
	//初始化当前对象。
	WRDirMapVAxisElement(void)
	{
		//add code here
	}
	//清理当前对象所占用的相关资源。
	~WRDirMapVAxisElement(void)
	{
		//add code here
	}

protected:
	//鼠标滚动处理，如果需要重绘，则返回True。
	bool onMouseWheel(const QWheelEvent& e);
	//鼠标按下处理，如果需要重绘，则返回True。
	bool onMouseDown(const QMouseEvent& e);
	//鼠标释放处理，如果需要重绘，则返回True。
	bool onMouseUp(const QMouseEvent& e);
	//鼠标移动处理，如果需要重绘，则返回True。
	bool onMouseMove(const QMouseEvent& e);
	
	//鼠标双击处理，如果需要重绘，则返回True。
	bool onMouseDoubleClick(const QMouseEvent& e);

	//执行绘制处理。
	void onPaint(QPainter& painter);
	//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
	void onPaintMouseFeedback(QPainter& painter);
};

//#pragma warning(pop)

#endif //WRDIRMAPAXISELEMENT
