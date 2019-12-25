#pragma once
#ifndef WRCHARTPRIVATE
#define WRCHARTPRIVATE

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QAtomicInt>
#include <WRCharting/WRSize.h>
#include <WRCharting/WRPoint.h>
#include <WRCharting/WRGlobal.h>

//声明图形元素类。
class WRChartElement;
//声明图形控件类。
class WRChartControl;

//表示图形信息。
class WRCHARTING_CLASS WRChartPrivate
{
    friend class WRChartControl;
    friend class WRChartElement;

private:
    //定时器标识。
    int m_timerId;
    //引用计数。
    QAtomicInt m_refCnt;
    //窗口对象。
    QWidget* m_widget;
    //控件对象。
    WRChartControl* m_control;
    //获取焦点的元素。
    WRChartElement* m_focused;
    //捕获鼠标的元素。
    WRChartElement* m_capture;
    //命中鼠标的元素。
    WRChartElement* m_current;
    //鼠标当前位置。
    WRPoint m_mouseCurrPos;
    //鼠标记录位置。
    WRPoint m_mouseSavePos;

    //禁用复制构造函数。
    WRChartPrivate(const WRChartPrivate& other);
    //禁用赋值操作符。
    WRChartPrivate& operator=(const WRChartPrivate& other);

    //添加对象引用。
    inline void addRef(void)
    {
        m_refCnt.ref();
    }
    //释放对象引用, 如果引用计数为0，则返回True，否则返回False。
    inline bool release(void)
    {
        if (!m_refCnt.deref())
        {
            delete this;
            return true;
        }
        return false;
    }

    //查找可以获取焦点的元素。
    WRChartElement* getFocusableElement(WRChartElement* current);
    //查找下一个可以获取焦点的元素。
    WRChartElement* nextFocusableElement(void);

    //执行窗口绑定。
    void doAttach(QWidget* widget);
    //执行窗口解绑。
    void doDetach(void);

    //尺寸改变处理，如果不需要继续处理，则返回True。
    bool doSize(const WRSize& size);

    //获取焦点处理，如果不需要继续处理，则返回True。
    bool doGotFocus(void);
    //失去焦点处理，如果不需要继续处理，则返回True。
    bool doLostFocus(void);

    //绘制处理，如果不需要继续处理，则返回True。
    bool doPaint(void);

    //定时处理，如果不需要继续处理，则返回True。
    bool doTimer(int timerId);

    //键盘按下处理，如果不需要继续处理，则返回True。
    bool doKeyDown(QKeyEvent* e);
    //键盘释放处理，如果不需要继续处理，则返回True。
    bool doKeyUp(QKeyEvent* e);

    //鼠标滚动处理，如果不需要继续处理，则返回True。
    bool doMouseWheel(QWheelEvent* e);
    //鼠标按下处理，如果不需要继续处理，则返回True。
    bool doMouseDown(QMouseEvent* e);
    //鼠标释放处理，如果不需要继续处理，则返回True。
    bool doMouseUp(QMouseEvent* e);
    //鼠标移动处理，如果不需要继续处理，则返回True。
    bool doMouseMove(QMouseEvent* e);

    //鼠标双击处理，如果不需要继续处理，则返回True。
    bool doMouseDoubleClick(QMouseEvent* e);

    //鼠标进入处理，如果不需要继续处理，则返回True。
    bool doMouseEnter(void);
    //鼠标离开处理，如果不需要继续处理，则返回True。
    bool doMouseLeave(void);

    //将当前图形控件与指定的窗口绑定，如果已经绑定窗口，则先解除绑定，然后再绑定窗口。
    inline void attach(QWidget* widget)
    {
        if (m_widget)
        {
            doDetach();
        }
        doAttach(widget);
    }
    //将当前图形控件与窗口解除绑定，并返回窗口对象。
    inline QWidget* detach(void)
    {
        QWidget* widget = m_widget;
        if (m_widget)
        {
            doDetach();
        }
        return widget;
    }

protected:
    //初始化图形信息。
    WRChartPrivate(void);
    //清理当前对象所占用的相关资源。
    virtual ~WRChartPrivate(void);

public:
    //获取窗口对象。
    inline QWidget* widget(void)
    {
        return m_widget;
    }

    //获取控件对象。
    inline WRChartControl* control(void) const
    {
        return m_control;
    }

    //获取焦点的元素。
    inline WRChartElement* focused(void) const
    {
        return m_focused;
    }
    //捕获鼠标的元素。
    inline WRChartElement* capture(void) const
    {
        return m_capture;
    }
    //命中鼠标的元素。
    inline WRChartElement* current(void) const
    {
        return m_current;
    }

    //获取鼠标当前位置。
    inline const WRPoint& mouseCurrPos(void) const
    {
        return m_mouseCurrPos;
    }

    //获取鼠标保存位置。
    inline const WRPoint& mouseSavePos(void) const
    {
        return m_mouseSavePos;
    }
    //设置鼠标保存位置。
    inline void mouseSavePos(const WRPoint& value)
    {
        m_mouseSavePos = value;
    }
};

#endif // WRCHARTPRIVATE
