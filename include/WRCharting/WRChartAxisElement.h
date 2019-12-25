#pragma once
#ifndef WRCHARTAXISELEMENT
#define WRCHARTAXISELEMENT

#include <WRCharting/WRGlobal.h>
#include <WRCharting/WRColor.h>
#include <WRCharting/WRChartElement.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

#define WRCHARTAXIS_DOCK		256UL
#define WRCHARTAXIS_SCALABLE	1024UL

#define WRCHARTAXIS_WIDTH		20

//表示图形坐标轴元素。
class WRCHARTING_CLASS WRChartAxisElement : public WRChartElement
{
    Q_OBJECT

    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool scalable READ scalable WRITE setScalable NOTIFY scalableChanged)

    Q_PROPERTY(WRColor backColor READ backColor WRITE setBackColor NOTIFY backColorChanged)
    Q_PROPERTY(WRColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(WRColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)

signals:
    //可视改变信号。
    void visibleChanged(bool value);
    //否缩放改变信号。
    void scalableChanged(bool value);

    //背景颜色改变信号。
    void backColorChanged(WRColor value);
    //线条颜色改变信号。
    void lineColorChanged(WRColor value);
    //文本颜色改变信号。
    void textColorChanged(WRColor value);

public slots:
    //设置可视性。
    void setVisible(bool value);
    //设置缩放性。
    void setScalable(bool value);

    //设置背景颜色。
    void setBackColor(WRColor value);
    //设置线条颜色。
    void setLineColor(WRColor value);
    //设置文字颜色。
    void setTextColor(WRColor value);

private:
    //背景颜色
    WRColor m_backColor;
    //线条颜色
    WRColor m_lineColor;
    //文字颜色。
    WRColor m_textColor;

protected:
    //初始化当前对象。
    WRChartAxisElement(void)
        : m_backColor(65, 71, 81), m_lineColor(174, 181, 190), m_textColor(174, 181, 190)
    {
        WRChartElement::buffered(true);
        writeFlag(WRCHARTAXIS_SCALABLE, true);
        writeFlag(WRCHARTAXIS_DOCK,  true);
    }
    //清理当前对象所占用的相关资源。
    ~WRChartAxisElement(void)
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
        return readFlag(WRCHARTAXIS_SCALABLE);
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

    //获取线条颜色。
    inline WRColor lineColor(void) const
    {
        return m_lineColor;
    }
    //设置线条颜色。
    bool lineColor(WRColor value);

    //获取文字颜色。
    inline WRColor textColor(void) const
    {
        return m_textColor;
    }
    //设置文字颜色。
    bool textColor(WRColor value);
};

//表示波形图横向坐标轴元素。
class WRCHARTING_CLASS WRChartHAxisElement : public WRChartAxisElement
{
    Q_OBJECT

    Q_PROPERTY(bool dockBottom READ dockBottom WRITE setDockBottom NOTIFY dockChanged)

signals:
    //停靠改变信号。
    void dockChanged(bool value);

public slots:
    //设置纵纵向坐标轴是否停靠在左侧。
    void setDockBottom(bool value);

protected:
    //初始化当前对象。
    WRChartHAxisElement(void)
    {
        //add code here
    }
    //清理当前对象所占用的相关资源。
    ~WRChartHAxisElement(void)
    {
        //add code here
    }

public:
    //获取横向坐标轴是否停靠在底部。
    inline bool dockBottom(void) const
    {
        return readFlag(WRCHARTAXIS_DOCK);
    }
    //设置横向坐标轴是否停靠在底部。
    bool dockBottom(bool value);
};

//表示波形图纵向坐标轴元素。
class WRCHARTING_CLASS WRChartVAxisElement : public WRChartAxisElement
{
    Q_OBJECT

    Q_PROPERTY(bool dockLeft READ dockLeft WRITE setDockLeft NOTIFY dockChanged)

signals:
    //停靠改变信号。
    void dockChanged(bool value);

public slots:
    //设置纵纵向坐标轴是否停靠在左侧。
    void setDockLeft(bool value);

protected:
    //初始化当前对象。
    WRChartVAxisElement(void)
    {
        //add code here
    }
    //清理当前对象所占用的相关资源。
    ~WRChartVAxisElement(void)
    {
        //add code here
    }

public:
    //获取纵纵向坐标轴是否停靠在左侧。
    inline bool dockLeft(void) const
    {
        return readFlag(WRCHARTAXIS_DOCK);
    }
    //设置纵纵向坐标轴是否停靠在左侧。
    bool dockLeft(bool value);
};

//#pragma warning(pop)

#endif // WRCHARTAXISELEMENT
