#pragma once
#ifndef WRWATERFALLGAUGEELEMENT
#define WRWATERFALLGAUGEELEMENT

#include <WRCharting/WRGlobal.h>
#include <WRCharting/WRChartElement.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

//表示瀑布图测量元素。
class WRCHARTING_CLASS WRWaterfallGaugeElement : public WRChartElement
{
    Q_OBJECT

	friend class WRWaterfallControl;
	friend class WRWaterfallLineElement;
    friend class WRWaterfallDataFrameLineElement;
    friend class WRWaterfallDataPointLineElement;

signals:
    //可视改变信号。
    void visibleChanged(bool value);

public:
	//枚举类型。
	enum Type
	{
		//数据帧线条
		DataFrameLine,
		//数据点线条
		DataPointLine,
	};

private:
    //初始化瀑布图数据测量元素。
    WRWaterfallGaugeElement(void)
    {
        focusable(true);
    }
    //清理当前对象所占用的相关资源。
    ~WRWaterfallGaugeElement(void)
    {
        //add code here
    }

public:
	//获取元素类型。
	virtual Type type(void) const = 0;
	//执行元素排列。
    virtual void arrange(void) = 0;

	//获取是否可见。
	inline bool visible(void) const
	{
		return WRChartElement::visible();
	}
	//设置是否可见，如果可见性改变，则返回True。
    inline bool visible(bool value)
    {
		if (value != WRChartElement::visible())
		{
			WRChartElement::visible(value);
			doUpdate();
            emit visibleChanged(value);
			return true;
		}
		return false;
	}
};

//#pragma warning(pop)

#endif //WRWATERFALLGAUGEELEMENT
