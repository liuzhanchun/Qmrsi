#pragma once
#ifndef WRSPECTROLINEELEMENT
#define WRSPECTROLINEELEMENT

#include <WRCharting/WRSpectroGaugeElement.h>
#include <WRCharting/WRColor.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

#define WRSPECTROLINEELEMENT_MOVEABLE	65536UL
#define WRSPECTROLINEELEMENT_MOUSECURSOR 131072UL

//表示频谱图线条元素。
class WRCHARTING_CLASS WRSpectroLineElement : public WRSpectroGaugeElement
{
    Q_OBJECT

	friend class WRSpectroDataValueLineElement;
	friend class WRSpectroDataPointLineElement;

signals:
    //颜色改变信号。
    void colorChanged(WRColor value);
    //是否移动改变信号。
    void moveableChanged(bool value);

public slots:
    //设置颜色。
    void setColor(WRColor value);
    //设置是否移动。
    void setMoveable(bool value);

private:	
	//线条颜色。
	WRColor m_color;

	//初始化频谱图线条元素。
	WRSpectroLineElement(void)
	{
		writeFlag(WRSPECTROLINEELEMENT_MOVEABLE, true);
        writeFlag(WRSPECTROLINEELEMENT_MOUSECURSOR, false);
	}
	//释放当前对象所占用的相关资源。
	~WRSpectroLineElement(void)
	{
		//add code here
	}

    //获取是否设置光标。
    inline bool mouseCursor() const
    {
        return readFlag(WRSPECTROLINEELEMENT_MOUSECURSOR);
    }
    //设置是否设置光标。
    inline void mouseCursor(bool value)
    {
        writeFlag(WRSPECTROLINEELEMENT_MOUSECURSOR, value);
    }

public:
	//获取线条颜色。
	inline WRColor color() const
	{
		return m_color;
	}
	//设置线条颜色。
	bool color(WRColor value);

	//获取可否移动。
	inline bool moveable() const
	{
		return readFlag(WRSPECTROLINEELEMENT_MOVEABLE);
	}
	//设置可否移动。
    bool moveable(bool value);
};

//表示频谱图数据点线条元素。
class WRCHARTING_CLASS WRSpectroDataPointLineElement : public WRSpectroLineElement
{
    Q_OBJECT

	friend class WRSpectroControl;

signals:
    //位置更改信号。
    void positionUpdated(int value);
    //位置改变信号。
    void positionChanged(int value);

public slots:
    //设置位置。
    void setPosition(int value);

private:
	//数据索引。
	int m_position;

	//初始化频谱图垂直线元素。
	WRSpectroDataPointLineElement(int position)
	{
        m_position = position;
	}
	//清理当前对象所占用的相关资源。
	~WRSpectroDataPointLineElement(void)
	{
		//add code here
	}

protected:
	//键盘按下处理，如果需要重绘，则返回True。
	bool onKeyDown(const QKeyEvent& e);
	//键盘释放处理，如果需要重绘，则返回True。
	bool onKeyUp(const QKeyEvent& e);

	//鼠标按下处理，如果需要重绘，则返回True。
	bool onMouseDown(const QMouseEvent& e);
	//鼠标释放处理，如果需要重绘，则返回True。
	bool onMouseUp(const QMouseEvent& e);
	//鼠标移动处理，如果需要重绘，则返回True。
	bool onMouseMove(const QMouseEvent& e);

    //鼠标离开处理，如果需要重绘，则返回True。
    bool onMouseLeave(void);

	//执行绘制处理。
	void onPaint(QPainter& painter);
	//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
	void onPaintMouseFeedback(QPainter& painter);

public:
	//获取元素标识。
	Type type() const;
	//更新元素的布局。
	void arrange(void);

	//获取数据索引。
	inline int position() const
	{
		return m_position;
	}
	//设置数据索引。
	bool position(int value);
};

//表示频谱图数据值线条元素。
class WRCHARTING_CLASS WRSpectroDataValueLineElement : public WRSpectroLineElement
{
    Q_OBJECT

	friend class WRSpectroControl;

signals:
    //位置更改信号。
    void positionUpdated(double value);
    //位置改变信号。
    void positionChanged(double value);

public slots:
    //设置位置。
    void setPosition(double value);

private:
	//数据值。
	double m_position;

	//初始化频谱图数据值线条元素。
	WRSpectroDataValueLineElement(double position)
	{
        m_position = position;
	}
	//清理当前对象所占用的相关资源。
	~WRSpectroDataValueLineElement(void)
	{
		//add code here
	}

protected:
	//键盘按下处理，如果需要重绘，则返回True。
	bool onKeyDown(const QKeyEvent& e);
	//键盘释放处理，如果需要重绘，则返回True。
	bool onKeyUp(const QKeyEvent& e);

	//鼠标按下处理，如果需要重绘，则返回True。
	bool onMouseDown(const QMouseEvent& e);
	//鼠标释放处理，如果需要重绘，则返回True。
	bool onMouseUp(const QMouseEvent& e);
	//鼠标移动处理，如果需要重绘，则返回True。
	bool onMouseMove(const QMouseEvent& e);

    //鼠标离开处理，如果需要重绘，则返回True。
    bool onMouseLeave(void);

	//执行绘制处理。
	void onPaint(QPainter& painter);
	//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
	void onPaintMouseFeedback(QPainter& painter);

public:
	//获取元素标识。
	Type type() const;
	//更新元素的布局。
	void arrange(void);

	//获取数据值。
	double position() const
	{
		return m_position;
	}
	//设置数据值。
	bool position(double value);
};

//#pragma warning(pop)

#endif //WRSPECTROLINEELEMENT
