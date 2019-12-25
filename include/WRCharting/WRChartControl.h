#pragma once
#ifndef WRCHARTCONTROL
#define WRCHARTCONTROL

#include <WRCharting/WRChartElement.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

class WRChartHAxisElement;
class WRChartVAxisElement;
class WRChartHScrollElement;
class WRChartVScrollElement;
class WRChartDataViewElement;

//表示图形控件。
class WRCHARTING_CLASS WRChartControl : public WRChartElement
{
    Q_OBJECT

    friend class WRChartPrivate;
    friend class WRChartElement;

private:
	//禁用复制构造函数。
	WRChartControl(const WRChartControl& other);
	//禁用赋值操作符。
	WRChartControl& operator=(const WRChartControl& other);

protected:
	//初始化图形控件。
	WRChartControl(void);
    //初始化图形控件。
    explicit WRChartControl(WRChartPrivate* info);

	//释放当前对象所占用的相关资源。
	virtual ~WRChartControl(void);

	//验证图形，如果需要重新绘制，则返回True。
	virtual bool validate(void);

    //过滤消息。
    bool eventFilter(QObject *obj, QEvent *event);

    //执行元素布局。
    static void arrange(const WRRect& rect, WRChartHAxisElement* hAxis, WRChartVAxisElement* vAxis, WRChartHScrollElement* hScroll, WRChartVScrollElement* vScroll, WRChartDataViewElement* dataView);

public:
	//添加对象引用。
	void addRef(void);
	//释放对象引用, 如果引用计数为0，则删除对象，返回True，否则返回False。
	bool release(void);

	//将当前图形控件与指定的窗口绑定，如果已经绑定窗口，则先解除绑定，然后再绑定窗口。
    inline void attach(QWidget* widget)
	{
        m_info->attach(widget);
	}
    //将当前图形控件与窗口解除绑定，并返回窗口对象。
    inline QWidget* detach(void)
    {
        return m_info->detach();
	}
};

//#pragma warning(pop)

#endif //WRCHARTCONTROL
