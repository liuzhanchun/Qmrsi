#pragma once
#ifndef WRCHARTELEMENT
#define WRCHARTELEMENT

#include <WRCharting/WRRect.h>
#include <WRCharting/WRGlobal.h>
#include <WRCharting/WRChartPrivate.h>
#include <QImage>
#include <QObject>
#include <QPainter>

//#pragma warning(push)
//#pragma warning(disable:4251)

#define WRCHARTELEMENT_VISIBLE		1UL
#define WRCHARTELEMENT_FOCUSED		2UL
#define WRCHARTELEMENT_FOCUSABLE	4UL
#define WRCHARTELEMENT_BUFFERED		8UL
#define WRCHARTELEMENT_INVALID		16UL

//表示图形无素。
class WRCHARTING_CLASS WRChartElement : public QObject
{
    Q_OBJECT

    Q_PROPERTY(WRRect rect READ rect)
    Q_PROPERTY(WRPoint pos READ pos)
    Q_PROPERTY(WRSize size READ size)
    Q_PROPERTY(int left READ left)
    Q_PROPERTY(int top READ top)
    Q_PROPERTY(int right READ right)
    Q_PROPERTY(int bottom READ bottom)
    Q_PROPERTY(int width READ width)
    Q_PROPERTY(int height READ height)

    friend class WRChartPrivate;
	friend class WRChartControl;

signals:
    //键盘按下信号。
    void keyDown(QKeyEvent* e);
    //键盘释放信号。
    void keyUp(QKeyEvent* e);

    //鼠标移动信号。
    void mouseMove(QMouseEvent* e);
    //鼠标滚动信号。
    void mouseWheel(QWheelEvent* e);

    //鼠标按下信号。
    void mouseDown(QMouseEvent* e);
    //鼠标释放信号。
    void mouseUp(QMouseEvent* e);

    //鼠标双击信号。
    void mouseDoubleClick(QMouseEvent* e);

    //鼠标进入信号。
    void mouseEnter(void);
    //鼠标离开信号。
    void mouseLeave(void);

private:
    unsigned long m_flags;          //标记值
    WRRect m_rect;                  //矩形区域
    WRChartPrivate* m_info;         //信息内容

    WRChartElement* m_prev;         //与当前元素平级的上一个元素
    WRChartElement* m_next;         //与当前元素平级的下一个元素
    WRChartElement* m_childFirst;   //当前元素的第一个子元素
    WRChartElement* m_childLast;    //当前元素的最末个子元素
    WRChartElement* m_parent;       //当前元素的父级元素

    QImage* m_bitmap;               //缓存位图

	//禁用复制构造函数。
	WRChartElement(const WRChartElement& other);
	//禁用赋值操作符。
	WRChartElement& operator=(const WRChartElement& other);

    //设置元素以及子级元素信息。
    void info(WRChartPrivate* value);
	//执行绘制处理。
    void doPaint(QPainter& painter);

protected:
	//初始化图形元素。
	WRChartElement(void);
	//释放图形元素所占用的相关资源。
	virtual ~WRChartElement(void);

    //获取基本信息。
    template <class T> T* info(void) const
    {
        return static_cast<T*>(m_info);
    }

	//读取标记
	inline bool readFlag(unsigned long field) const
	{
        return ((m_flags & field) != 0);
	}
	//写入标记
	inline void writeFlag(unsigned long field, bool value)
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

	//设置是否可见，如果可见性改变，则返回True。
	inline void visible(bool value)
	{
		writeFlag(WRCHARTELEMENT_VISIBLE, value);
	}
    //获取是否可见。
    inline bool visible(void) const
    {
        return readFlag(WRCHARTELEMENT_VISIBLE);
    }

	//设置是否可以获取焦点。
	inline void focusable(bool value)
	{
		writeFlag(WRCHARTELEMENT_FOCUSABLE, value);
	}
	//设置是否获取焦点。
	inline void focused(bool value)
	{
		if (readFlag(WRCHARTELEMENT_FOCUSED) != value)
		{
			writeFlag(WRCHARTELEMENT_INVALID, true);
			writeFlag(WRCHARTELEMENT_FOCUSED, value);
		}
	}

	//获取缓存是否无效。
	inline bool invalid(void) const
	{
		return readFlag(WRCHARTELEMENT_INVALID);
	}
	//设置缓存是否无效。
	inline void invalid(bool value)
	{
		writeFlag(WRCHARTELEMENT_INVALID, value);
	}

	//获取是否具有缓存。
	inline bool buffered(void) const
	{
		return readFlag(WRCHARTELEMENT_BUFFERED);
	}
	//设置是否具有缓存。
	inline void buffered(bool value)
	{
		writeFlag(WRCHARTELEMENT_BUFFERED, value);
	}

    //获取鼠标当前位置。
    inline const WRPoint& mouseCurrPos(void) const
    {
        return m_info->m_mouseCurrPos;
    }

    //获取鼠标保存位置。
    inline const WRPoint& mouseSavePos(void) const
    {
        return m_info->m_mouseSavePos;
    }
    //设置鼠标保存位置。
    inline void mouseSavePos(const WRPoint& value)
    {
        m_info->m_mouseSavePos = value;
    }
    //设置鼠标保存位置。
    inline void mouseSavePos(const QPoint& value)
    {
        m_info->m_mouseSavePos = value;
    }

	//将指定的子元素插入到首位（底层）。
	void addFirst(WRChartElement* child);
	//将指定的子元素添加到末尾（顶层）。
	void addLast(WRChartElement* child);
	//将指定的子元素插入到指定元素之前（下层）。
	void addAfter(WRChartElement* current, WRChartElement* child);
	//将指定的子元素插入到指定元素之后（上层）。
	void addBefore(WRChartElement* current, WRChartElement* child);
	//移除指定的子元素。
	void remove(WRChartElement* child);

	//当矩形改变后调用此方法。
	virtual void onRectChanged(void);

	//当位置改变后调用此方法。
	virtual void onPosChanged(void);
	//当X坐标改变后调用此方法。
	virtual void onLeftChanged(void);
	//当Y坐标改变后调用此方法。
	virtual void onTopChanged(void);

	//当大小改变后调用此方法。
	virtual void onSizeChanged(void);
	//当宽度改变后调用此方法。
	virtual void onWidthChanged(void);
	//当高度改变后调用此方法。
	virtual void onHeightChanged(void);

	//当布局时调用此方法。
	virtual void onLayout(const WRRect& rect);
	//改变元素布局。
	void doLayout(const WRRect& rect);

	//设置为鼠标捕获。
    inline void setCapture(void)
    {
        if (!m_info->m_capture)
        {
            m_info->m_widget->grabMouse();
        }
        m_info->m_capture = this;
    }
	//释放鼠标捕获。
    inline void releaseCapture(void)
    {
        if (m_info->m_capture == this)
        {
            m_info->m_widget->releaseMouse();
            m_info->m_capture = 0;
        }
    }

	//键盘按下处理，如果需要重绘，则返回True。
    virtual bool onKeyDown(const QKeyEvent& e);
	//键盘释放处理，如果需要重绘，则返回True。
    virtual bool onKeyUp(const QKeyEvent& e);

    //鼠标移动处理，如果需要重绘，则返回True。
    virtual bool onMouseMove(const QMouseEvent& e);
	//鼠标滚动处理，如果需要重绘，则返回True。
    virtual bool onMouseWheel(const QWheelEvent& e);

	//鼠标按下处理，如果需要重绘，则返回True。
    virtual bool onMouseDown(const QMouseEvent& e);
	//鼠标释放处理，如果需要重绘，则返回True。
    virtual bool onMouseUp(const QMouseEvent& e);

	//鼠标双击处理，如果需要重绘，则返回True。
    virtual bool onMouseDoubleClick(const QMouseEvent& e);

	//鼠标进入处理，如果需要重绘，则返回True。
    virtual bool onMouseEnter(void);
	//鼠标离开处理，如果需要重绘，则返回True。
	virtual bool onMouseLeave(void);

	//执行绘制处理。
    virtual void onPaint(QPainter& painter);
	//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
    virtual void onPaintMouseFeedback(QPainter& painter);

    //获取指定宽度的位图的行宽。
    inline static int getBitmapWidth(int w)
    {
        int r = w % 4;
        if (r > 0) w += 4 - r;
        return w;
    }

public:
	//获取矩形。
	inline const WRRect& rect(void) const { return m_rect; }
	//获取位置。
	inline const WRPoint& pos(void) const { return m_rect.pos(); }
	//获取尺寸。
	inline const WRSize& size(void) const { return m_rect.size(); }
	//获取左上角X坐标轴。
	inline int left(void) const { return m_rect.left(); }
	//获取左上角Y坐标轴。
	inline int top(void) const { return m_rect.top(); }
	//获取右下角X坐标轴(不包含在区域内)。
	inline int right(void) const { return m_rect.right(); }
	//获取右下角Y坐标轴(不包含在区域内)。
	inline int bottom(void) const { return m_rect.bottom(); }
	//获取宽度。
	inline int width(void) const { return m_rect.width(); }
	//获取高度。
	inline int height(void) const { return m_rect.height(); }

	//获取与当前元素平级的上一个元素。
	inline WRChartElement* prev(void) const { return m_prev; }
	//获取与当前元素平级的下一个元素。
	inline WRChartElement* next(void) const { return m_next; }

	//获取当前元素的父元素。
	inline WRChartElement* parent(void) const { return m_parent; }

	//获取当前元素的第一个子元素。
	inline WRChartElement* childFirst(void) const { return m_childFirst; }
	//获取当前元素的最末个子元素。
	inline WRChartElement* childLast(void) const { return m_childLast; }

	//获取当前元素所属的控件。
    inline WRChartControl* owner(void) const
    {
        return m_info->m_control;
    }

    //获取所属窗口对象。
    inline QWidget* widget(void) const
    {
        return m_info->m_widget;
    }
    //判断是否正在处理。
    inline bool effect(void) const
    {
        if (m_info->m_widget)\
            return true;
        return false;
    }

    //选中当前元素。
    bool select(void);

    //判断是否选中。
    inline bool selected(void) const
    {
        return m_info->m_focused == this;
    }

    //判断是否鼠标在其上。
    inline bool mouseHovered(void) const
    {
        return m_info->m_current == this;
    }
    //判断是否捕获了鼠标。
    inline bool mouseCaptured(void) const
    {
        return m_info->m_capture == this;
    }

	//获取是否可以获取焦点。
	inline bool focusable(void) const
	{
		return readFlag(WRCHARTELEMENT_FOCUSABLE);
	}
	//获取是否获取焦点。
	inline bool focused(void) const
	{
		return readFlag(WRCHARTELEMENT_FOCUSED);
	}

	//使元素无效，下次需要重绘。
	inline void invalidate(void)
	{
		invalid(true);
	}

	//X值是否包含在内部。
	virtual bool containsX(int x) const;
	//Y值是否包含在内部。
	virtual bool containsY(int y) const;
	//判断指定的点是否在内部。
	virtual bool contains(const WRPoint& p) const;
	//判断指定的点是否在内部。
	inline bool contains(int x, int y) const
	{
		return contains(WRPoint(x, y));
	}
	//判断指定的点是否在内部。
    inline bool contains(const WRPoint* p) const
	{
		return contains(*p);
	}
    //判断指定的点是否在内部。
    inline bool contains(const QPoint& p) const
    {
        return contains(*(WRPoint*)((void*)&p));
    }
    //判断指定的点是否在内部。
    inline bool contains(const QPoint* p) const
    {
        return contains(*(WRPoint*)((void*)p));
    }

	//要求元素重新布局。
    void doLayout(void);
	//请求元素所在的图形进行重新绘制。
    void doUpdate(void);

	//命中测试。
	WRChartElement* hitTest(const WRPoint& pos);
};

//#pragma warning(pop)

#endif //WRCHARTELEMENT
