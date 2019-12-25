#pragma once
#ifndef WRCHARTDATAVIEWELEMENT
#define WRCHARTDATAVIEWELEMENT

#include <WRCharting/WRGlobal.h>
#include <WRCharting/WRColor.h>
#include <WRCharting/WRChartElement.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

#define WRCHARTDATAVIEW_VSCALABLE		256UL
#define WRCHARTDATAVIEW_HSCALABLE		512UL

//表示图形数据视图元素。
class WRCHARTING_CLASS WRChartDataViewElement : public WRChartElement
{
    Q_OBJECT

    Q_ENUMS(MouseDragMode)
    Q_ENUMS(MouseRectMode)

    Q_PROPERTY(bool vScalable READ vScalable WRITE setVScalable NOTIFY vScalableChanged)
    Q_PROPERTY(bool hScalable READ hScalable WRITE setHScalable NOTIFY hScalableChanged)

    Q_PROPERTY(MouseDragMode mouseDragMode READ mouseDragMode WRITE setMouseDragMode NOTIFY mouseDragModeChanged)
    Q_PROPERTY(MouseRectMode mouseRectMode READ mouseRectMode WRITE setMouseRectMode NOTIFY mouseRectModeChanged)

    Q_PROPERTY(WRColor mouseRectColor READ mouseRectColor WRITE setMouseRectColor NOTIFY mouseRectColorChanged)
    Q_PROPERTY(WRColor mouseLineColor READ mouseLineColor WRITE setMouseLineColor NOTIFY mouseLineColorChanged)

public:
    //枚举图形数据视图鼠标拖动模式。
    enum MouseDragMode
    {
        //默认模式，不执行任何处理
        MouseDragNone = 0,
        //移动模式，拖动图形的显示
        MouseDragMove = 1,
        //缩放模式，画出起始到结束之间的矩形，释放后只显示矩形之间的内容
        MouseDragZoom = 2,
        //矩形模式，画出起始到结束之间的矩形
        MouseDragRect = 3,
        //线条模式，画出起始到结束之间的线条
        MouseDragLine = 4
    };
    //枚举图形数据视图鼠标矩形模式。
    enum MouseRectMode
    {
        //任意处理
        MouseRectCustom = 0,
        //纵坐标轴作为矩形全部
        MouseRectVWhole = 1,
        //横坐标轴作为矩形全部
        MouseRectHWhole = 2
    };

signals:
    //是否水平缩放改变信号。
    void hScalableChanged(bool value);
    //是否纵向缩放改变信号。
    void vScalableChanged(bool value);

    //鼠标拖动改变信号。
    void mouseDragChanged(const WRPoint& begPos, const WRPoint& endPos);
    //鼠标手动释放信号。
    void mouseDragReleased(const WRPoint& begPos, const WRPoint& endPos);

    //鼠标手动模式改变信号。
    void mouseDragModeChanged(MouseDragMode value);
    //鼠标矩形模式改变信号。
    void mouseRectModeChanged(MouseRectMode value);

    //鼠标矩形颜色改变信号。
    void mouseRectColorChanged(WRColor value);
    //鼠标线条颜色改变信号。
    void mouseLineColorChanged(WRColor value);

public slots:
    //设置是否横向缩放。
    void setHScalable(bool value);
    //设置是否纵向缩放。
    void setVScalable(bool value);

    //设置鼠标拖动模式。
    void setMouseDragMode(MouseDragMode value);
    //设置鼠标矩形模式。
    void setMouseRectMode(MouseRectMode value);

    //设置鼠标矩形颜色。
    void setMouseRectColor(WRColor value);
    //设置鼠标线条颜色。
    void setMouseLineColor(WRColor value);

private:
    MouseDragMode m_mouseDragMode;	//鼠标拖动模式
    MouseRectMode m_mouseRectMode;	//鼠标矩形模式

    WRColor m_mouseRectColor;	//鼠标矩形颜色
    WRColor m_mouseLineColor;	//鼠标线条颜色

protected:
    //初始化图形对象。
    WRChartDataViewElement(void)
        : m_mouseRectColor(0xFF, 0xFF, 0xFF, 0x40), m_mouseLineColor(245, 245, 240)
    {
        writeFlag(WRCHARTDATAVIEW_VSCALABLE, true);
        writeFlag(WRCHARTDATAVIEW_HSCALABLE, true);

        m_mouseDragMode = MouseDragNone;
        m_mouseRectMode = MouseRectCustom;
    }
    //清理当前对象所占用的相关资源。
    ~WRChartDataViewElement(void)
    {
        //add code here
    }

    //执行缩放处理。
    virtual bool doZoom(const WRPoint& begPos, const WRPoint& endPos);
    //执行移动处理。
    virtual bool doMove(const WRPoint& begPos, const WRPoint& endPos);

    //鼠标按下处理，如果需要重绘，则返回True。
    bool onMouseDown(const QMouseEvent& e);
    //鼠标释放处理，如果需要重绘，则返回True。
    bool onMouseUp(const QMouseEvent& e);
    //鼠标移动处理，如果需要重绘，则返回True。
    bool onMouseMove(const QMouseEvent& e);

    //执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
    void onPaintMouseFeedback(QPainter& painter);

public:
    //获取是否横向缩放。
    inline bool hScalable(void) const
    {
        return readFlag(WRCHARTDATAVIEW_HSCALABLE);
    }
    //设置是否横向缩放。
    bool hScalable(bool value);

    //获取是否纵向缩放。
    inline bool vScalable(void) const
    {
        return readFlag(WRCHARTDATAVIEW_VSCALABLE);
    }
    //设置是否纵向缩放。
    bool vScalable(bool value);

    //获取鼠标拖动模式。
    inline MouseDragMode mouseDragMode(void) const
    {
        return m_mouseDragMode;
    }
    //设置鼠标拖动模式。
    bool mouseDragMode(MouseDragMode value);

    //获取鼠标矩形模式。
    inline MouseRectMode mouseRectMode(void) const
    {
        return m_mouseRectMode;
    }
    //设置鼠标矩形模式。
    bool mouseRectMode(MouseRectMode value);

    //获取鼠标矩形颜色。
    inline WRColor mouseRectColor(void) const
    {
        return m_mouseRectColor;
    }
    //设置鼠标矩形颜色。
    bool mouseRectColor(WRColor value);

    //获取鼠标线条颜色。
    inline WRColor mouseLineColor(void) const
    {
        return m_mouseLineColor;
    }
    //设置鼠标线条颜色。
    bool mouseLineColor(WRColor value);
};

//#pragma warning(pop)

#endif // WRCHARTDATAVIEWELEMENT
