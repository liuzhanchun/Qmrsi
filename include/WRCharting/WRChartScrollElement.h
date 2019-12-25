#pragma once
#ifndef WRCHARTSCROLLELEMENT
#define WRCHARTSCROLLELEMENT

#include <WRCharting/WRGlobal.h>
#include <WRCharting/WRColor.h>
#include <WRCharting/WRChartElement.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

#define WRCHARTSCROLL_DOCK		256UL
#define WRCHARTSCROLL_SCALABLE	1024UL

#define WRCHARTSCROLL_WIDTH 	20

//表示图形滚动条元素。
class WRCHARTING_CLASS WRChartScrollElement : public WRChartElement
{
    Q_OBJECT

    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool scalable READ scalable WRITE setScalable NOTIFY scalableChanged)

    Q_PROPERTY(WRColor backColor READ backColor WRITE setBackColor NOTIFY backColorChanged)
    Q_PROPERTY(WRColor foreColor READ foreColor WRITE setForeColor NOTIFY foreColorChanged)

signals:
    //可视改变信号。
    void visibleChanged(bool value);
    //否缩放改变信号。
    void scalableChanged(bool value);

    //背景颜色改变信号。
    void backColorChanged(WRColor value);
    //文本颜色改变信号。
    void foreColorChanged(WRColor value);

public slots:
    //设置可视性。
    void setVisible(bool value);
    //设置缩放性。
    void setScalable(bool value);

    //设置背景颜色。
    void setBackColor(WRColor value);
    //设置前景颜色。
    void setForeColor(WRColor value);

private:
    //背景颜色
    WRColor m_backColor;
    //前景颜色。
    WRColor m_foreColor;

protected:
    //初始化当前对象。
    WRChartScrollElement(void)
        : m_backColor(4, 0, 0), m_foreColor(75, 243, 167)
    {
        WRChartElement::visible(false);
        writeFlag(WRCHARTSCROLL_SCALABLE, true);
        writeFlag(WRCHARTSCROLL_DOCK,  false);
    }
    //清理当前对象所占用的相关资源。
    ~WRChartScrollElement(void)
    {
        //add code here
    }

public:
    //获取是否可见。
    inline bool visible(void) const
    {
        return WRChartElement::visible();
    }
    //设置是否可见，如果可见性改变，则返回True。
    bool visible(bool value);

    //获取是否支持缩放。
    inline bool scalable(void) const
    {
        return readFlag(WRCHARTSCROLL_SCALABLE);
    }
    //设置是否支持缩放。
    bool scalable(bool value);

    //获取背景颜色。
    inline WRColor backColor(void) const
    {
        return m_backColor;
    }
    //设置背景颜色。
    bool backColor(WRColor value);

    //获取前景颜色。
    inline WRColor foreColor(void) const
    {
        return m_foreColor;
    }
    //设置前景颜色。
    bool foreColor(WRColor value);
};

//表示波形图横向滚动条元素。
class WRCHARTING_CLASS WRChartHScrollElement : public WRChartScrollElement
{
    Q_OBJECT

    Q_PROPERTY(bool dockBottom READ dockBottom WRITE setDockBottom NOTIFY dockChanged)

signals:
    //停靠改变信号。
    void dockChanged(bool value);

public slots:
    //设置纵纵向滚动条是否停靠在左侧。
    void setDockBottom(bool value);

protected:
    //初始化当前对象。
    WRChartHScrollElement(void)
    {
        //add code here
    }
    //清理当前对象所占用的相关资源。
    ~WRChartHScrollElement(void)
    {
        //add code here
    }

public:
    //获取横向滚动条是否停靠在底部。
    inline bool dockBottom(void) const
    {
        return readFlag(WRCHARTSCROLL_DOCK);
    }
    //设置横向滚动条是否停靠在底部。
    bool dockBottom(bool value);
};

//表示波形图纵向滚动条元素。
class WRCHARTING_CLASS WRChartVScrollElement : public WRChartScrollElement
{
    Q_OBJECT

    Q_PROPERTY(bool dockLeft READ dockLeft WRITE setDockLeft NOTIFY dockChanged)

signals:
    //停靠改变信号。
    void dockChanged(bool value);

public slots:
    //设置纵纵向滚动条是否停靠在左侧。
    void setDockLeft(bool value);

protected:
    //初始化当前对象。
    WRChartVScrollElement(void)
    {
        //add code here
    }
    //清理当前对象所占用的相关资源。
    ~WRChartVScrollElement(void)
    {
        //add code here
    }

public:
    //获取纵纵向滚动条是否停靠在左侧。
    inline bool dockLeft(void) const
    {
        return readFlag(WRCHARTSCROLL_DOCK);
    }
    //设置纵纵向滚动条是否停靠在左侧。
    bool dockLeft(bool value);
};

//#pragma warning(pop)

#endif // WRCHARTSCROLLELEMENT
