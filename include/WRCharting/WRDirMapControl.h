#pragma once
#ifndef WRDIRMAPCONTROL
#define WRDIRMAPCONTROL

#include <WRCharting/WRGlobal.h>
#include <WRCharting/WRMath.h>
#include <WRCharting/WRColor.h>
#include <WRCharting/WRMutex.h>
#include <WRCharting/WRChartControl.h>
#include <WRCharting/WRDirMapDataRange.h>
#include <WRCharting/WRDirMapInitParams.h>
#include <WRCharting/WRDirMapDataSource.h>
#include <WRCharting/WRDirMapAxisElement.h>
#include <WRCharting/WRDirMapScrollElement.h>
#include <WRCharting/WRDirMapDataViewElement.h>
#include <WRCharting/WRDirMapGaugeElement.h>
#include <WRCharting/WRDirMapGaugeElement.h>
#include <WRCharting/WRDirMapLineElement.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

#define WRDIRMAPCONTROL_HOLDSTATUS	512UL

//表示向频图控件。
class WRCHARTING_CLASS WRDirMapControl : public WRChartControl
{
    Q_OBJECT

    Q_ENUMS(DataProcMethod)

	friend class WRDirMapHAxisElement;
    friend class WRDirMapVAxisElement;
    friend class WRDirMapHScrollElement;
    friend class WRDirMapVScrollElement;
    friend class WRDirMapDataViewElement;
	friend class WRDirMapGaugleElement;
	friend class WRDirMapLineElement;
	friend class WRDirMapDataAngleLineElement;
	friend class WRDirMapDataPointLineElement;

public:
    //枚举数据处理方式。
    enum DataProcMethod
    {
        //显示最大值。
        ShowMaxValue,
        //显示平均值。
        ShowAverage,
    };

signals:
    //数据改变信号。
    void dataChanged(void);

    //显示数据范围更改信号。
    void showDataRangeUpdated(const WRDirMapDataRange& value);
    //显示数据点范围更改信号。
    void showDataPointRangeUpdated(const WRChartSampleRange& value);
    //显示数据角度范围更改信号。
    void showDataAngleRangeUpdated(const WRChartDValueRange& value);

    //显示数据范围改变信号。
    void showDataRangeChanged(const WRDirMapDataRange& value);
    //显示数据点范围更新信号。
    void showDataPointRangeChanged(const WRChartSampleRange& value);
    //显示数据角度范围改变信号。
    void showDataAngleRangeChanged(const WRChartDValueRange& value);

    //数据处理方法改变信号。
    void dataProcMethodChanged(DataProcMethod value);

    //挂起状态改变信号。
    void holdStatusChanged(bool value);

    //背景颜色改变信号。
    void backColorChanged(WRColor value);

public slots:
    //显示数据范围改变信号。
    void setShowDataRange(const WRDirMapDataRange& value);
    //显示数据点范围更新信号。
    void setShowDataPointRange(const WRChartSampleRange& value);
    //显示数据角度范围改变信号。
    void setShowDataAngleRange(const WRChartDValueRange& value);

    //数据处理方法改变信号。
    void setDataProcMethod(DataProcMethod value);
    //设置挂起状态。
    void setHoldStatus(bool value);
    //设置背景颜色。
    void setBackColor(WRColor value);

private:
	//同步对象
	WRMutex m_mutex;

	//纵坐标轴
	WRDirMapVAxisElement* m_vAxis;
	//横坐标轴
	WRDirMapHAxisElement* m_hAxis;
	//纵向滚动条
	WRDirMapVScrollElement* m_vScroll;
	//横向滚动条
	WRDirMapHScrollElement* m_hScroll;
	//数据视图
	WRDirMapDataViewElement* m_dataView;

	//后端数据源
	WRDirMapDataSource* m_backSource;
	//当前数据源
	WRDirMapDataSource* m_currSource;

	//显示数据范围
	WRDirMapDataRange m_showDataRange;

	//数据处理方式。
	DataProcMethod m_dataProcMethod;

	//背景颜色
	WRColor m_backColor;

	//获取数据源对象。
	inline WRDirMapDataSource* dataSource(void) const
	{
		return m_currSource;
	}

	//当显示数据范围改变后调用此方法 。
    void onShowDataRangeChanged(void);
    //当显示数据点范围改变后调用此方法。
    void onShowDataPointRangeChanged(void);
    //当显示数据角度范围改变后调用此方法。
    void onShowDataAngleRangeChanged(void);

    //重置显示数据范围。
    inline void resetShowDataRange(const WRDirMapDataRange& value)
    {
        bool change = false;
        if (m_showDataRange.pointRange(value.pointRange()))
        {
            onShowDataPointRangeChanged();
            emit showDataPointRangeChanged(m_showDataRange.pointRange());
            change = true;
        }
        if (m_showDataRange.angleRange(value.angleRange()))
        {
            onShowDataAngleRangeChanged();
            emit showDataAngleRangeChanged(m_showDataRange.angleRange());
            change = true;
        }
        if (change)
        {
            onShowDataRangeChanged();
            emit showDataRangeChanged(m_showDataRange);
        }
    }

    //改变显示数据范围。
    inline bool changeShowDataRange(const WRDirMapDataRange& value)
    {
        bool change = false;
        if (m_showDataRange.pointRange(value.pointRange()))
        {
            onShowDataPointRangeChanged();
            emit showDataPointRangeUpdated(m_showDataRange.pointRange());
            emit showDataPointRangeChanged(m_showDataRange.pointRange());
            change = true;
        }
        if (m_showDataRange.angleRange(value.angleRange()))
        {
            onShowDataAngleRangeChanged();
            emit showDataAngleRangeUpdated(m_showDataRange.angleRange());
            emit showDataAngleRangeChanged(m_showDataRange.angleRange());
            change = true;
        }
        if (change)
        {
            onShowDataRangeChanged();
            emit showDataRangeUpdated(m_showDataRange);
            emit showDataRangeChanged(m_showDataRange);
            return true;
        }
        return false;
    }
    //改变数据点显示数据范围。
    inline bool changeShowDataPointRange(const WRChartSampleRange& value)
    {
        if (m_showDataRange.pointRange(value))
        {
            onShowDataPointRangeChanged();
            onShowDataRangeChanged();

            emit showDataPointRangeUpdated(m_showDataRange.pointRange());
            emit showDataPointRangeChanged(m_showDataRange.pointRange());
            emit showDataRangeUpdated(m_showDataRange);
            emit showDataRangeChanged(m_showDataRange);
            return true;
        }
        return false;
    }
    //改变数据角度显示数据范围。
    inline bool changeShowDataAngleRange(const WRChartDValueRange& value)
    {
        if (m_showDataRange.angleRange(value))
        {
            onShowDataAngleRangeChanged();
            onShowDataRangeChanged();

            emit showDataAngleRangeUpdated(m_showDataRange.angleRange());
            emit showDataAngleRangeChanged(m_showDataRange.angleRange());
            emit showDataRangeUpdated(m_showDataRange);
            emit showDataRangeChanged(m_showDataRange);

            return true;
        }
        return false;
    }

    //禁用复制构造函数。
	WRDirMapControl(const WRDirMapControl& other);
	//禁用赋值操作符。
	WRDirMapControl& operator=(const WRDirMapControl& other);

	//执行控件的初始化。
	void initialize(void);
	//清理当前对象所占用的相关资源。
	~WRDirMapControl(void);

    //获取指定实际值的显示值。
    inline unsigned char getShowValue(double value) const
    {
        if (value < m_currSource->specMinValue())
        {
            return 0x00;
        }
        if (value > m_currSource->specMaxValue())
        {
            return 0xFF;
        }
        return (char)((value - m_currSource->specMinValue()) * 255 / m_currSource->specDifValue() + 0.5);
    }
    //获取指定显示值的实际值。
    inline double getDataAngle(char value) const
    {
        return value * m_currSource->specDifValue() / 255 + m_currSource->specMinValue();
    }
	
	//获取指定数量的数据点宽度。
	inline int getDataPointWidth(int w, int v) const
	{
		return (int)(v * (w - 1LL) / (m_showDataRange.pointCount() - 1.0) + 0.5);
	}
	//获取指定数据点偏移的位置。
	inline int getDataPointOffsetPos(int w, int v) const
	{
		return (int)(v * (w - 1LL) / (m_showDataRange.pointCount() - 1.0) + 0.5);
	}
	//获取指定数据点的位置。
	inline int getDataPointPos(int w, int v) const
	{
		return (int)((v - m_showDataRange.pointBegin()) * (w - 1LL) / (m_showDataRange.pointCount() - 1.0) + 0.5);
	}
	
	//获取指定长度的数据点数量。
	inline int getDataPointCount(int w, int x) const
	{
		return (int)(x * (m_showDataRange.pointCount() - 1LL) / (w - 1.0) + 0.5);
	}
	//获取指定位置的数据点偏移。
	inline int getDataPointOffsetAt(int w, int x) const
	{
		return (int)(x * (m_showDataRange.pointCount() - 1LL) / (w - 1.0) + 0.5);
	}
    //获取指定位置的数据点。
    inline int getDataPointAt(int w, int x) const
    {
        return m_showDataRange.pointBegin() + (int)(x * (m_showDataRange.pointCount()- 1LL) / (w - 1.0) + 0.5);
	}

	//获取指定数据角度偏移的位置。
	inline int getDataAngleOffsetPos(int h, double v) const
	{
		int h1 = h - 1;
		return h1 - (int)(v * h1 / m_showDataRange.angleSpan() + 0.5);
	}
	//获取指定数据角度的位置。
	inline int getDataAnglePos(int h, double v) const
	{
		int h1 = h - 1;
		return h1 - (int)((v - m_showDataRange.angleBegin()) * h1 / m_showDataRange.angleSpan() + 0.5);
	}

	//获取指定长度的数据角度跨度。
	inline double getDataAngleSpan(int h, int y) const
	{
		return y * m_showDataRange.angleSpan() / (h - 1);
	}
	//获取指定位置的数据角度。
	inline double getDataAngleAt(int h, int y) const
	{
		return m_showDataRange.angleEnd() - y * m_showDataRange.angleSpan() / (h - 1);
	}

	//执行纵向鼠标水平缩放。
    inline void doMouseZoomH(WRChartSampleRange& range, int xPos1, int xPos2,  int width) const
    {
        if (xPos1 != xPos2)
        {
            int index1 = getDataPointAt(width, xPos1);
            int index2 = getDataPointAt(width, xPos2);
            if (index1 > index2)
            {
                range.update(index2, index1 - index2 + 1);
            }
            else if (index2 > index1)
            {
                range.update(index1, index2 - index1 + 1);
            }
        }
    }
    //执行纵向鼠标纵向缩放。
    inline void doMouseZoomV(WRChartDValueRange& range, int yPos1, int yPos2,  int height) const
    {
        if (yPos1 != yPos2)
        {
            double value1 = getDataAngleAt(height, yPos1);
            double value2 = getDataAngleAt(height, yPos2);
            if (value1 > value2)
            {
                range.update(value2, value1);
            }
            else if (value2 > value1)
            {
                range.update(value1, value2);
            }
        }
    }

	//执行纵向鼠标水平移动。
    inline void doMouseMoveH(WRChartSampleRange& range, int xPos1, int xPos2,  int width) const
    {
        if (xPos1 != xPos2)
        {
            int xOff = xPos2 - xPos1;
            int iOff = (int)WRMath::round(xOff * (m_showDataRange.pointCount() - 1LL) / (width - 1.0));
            if (iOff != 0)
            {
                int showDataPointBegin = 0;
				if (iOff < m_showDataRange.pointBegin())
				{
					showDataPointBegin = m_showDataRange.pointBegin() - iOff;
                }
                if (showDataPointBegin + m_showDataRange.pointCount() > m_currSource->points())
                {
                    showDataPointBegin =  m_currSource->points() - m_showDataRange.pointCount();
                }
                range.begin(showDataPointBegin);
            }
        }
    }
    //执行纵向鼠标纵向移动。
    inline void doMouseMoveV(WRChartDValueRange& range, int yPos1, int yPos2,  int height) const
    {
        if (yPos1 != yPos2)
        {
            int yOff = yPos2 - yPos1;
			double showDataRange = m_showDataRange.angleSpan();
            double iOff = yOff * showDataRange / height;
            if (iOff != 0)
            {
				double showDataAngleEnd = m_showDataRange.angleEnd() + iOff;
                if (showDataAngleEnd > m_currSource->angleMaxValue())
                {
                    showDataAngleEnd = m_currSource->angleMaxValue();
                }
                if (showDataAngleEnd - showDataRange < m_currSource->angleMinValue())
                {
                    showDataAngleEnd = m_currSource->angleMinValue() + showDataRange;
                }
                double showDataAngleBegin = showDataAngleEnd - showDataRange;
				range.update(showDataAngleBegin, showDataAngleEnd);
			}
		}
    }

	//执行纵向鼠标水平缩放。
    inline void doMouseWheelH(WRChartSampleRange& range, int xPos,  int delta, int width) const
    {
        if (xPos >= 0 && xPos < width)
        {
            if (delta > 0)
            {
                if (m_showDataRange.pointCount() > 2)
                {
                    int showDataPointCount = m_showDataRange.pointCount() / 2;
                    if (showDataPointCount < 2)
                    {
                        showDataPointCount = 2;
                    }
                    int xOff = (int)WRMath::round(xPos * (m_showDataRange.pointCount() - 1LL) / (width - 1.0));
                    int showDataPointBegin = m_showDataRange.pointBegin() + xOff / 2;
                    if (showDataPointBegin + showDataPointCount > m_currSource->points())
                    {
                        showDataPointBegin = m_currSource->points() - showDataPointCount;
                    }
                    range.update(showDataPointBegin, showDataPointCount);
                }
            }
            else
            {
                if (m_currSource->points() != m_showDataRange.pointCount())
                {
                    int showDataPointCount = m_showDataRange.pointCount() * 2;
                    if (showDataPointCount >= m_currSource->points())
                    {
                        range.update(0, m_currSource->points());
                    }
                    else
                    {
						int showDataPointBegin = 0;
                        int xOff = (int)WRMath::round(xPos * (m_showDataRange.pointCount() - 1LL) / (width - 1.0));
						if (xOff < m_showDataRange.pointBegin())
						{
							showDataPointBegin = m_showDataRange.pointBegin() - xOff;
                        }
                        if (showDataPointBegin + showDataPointCount > m_currSource->points())
                        {
                            showDataPointBegin = m_currSource->points() - showDataPointCount;
                        }
                        range.update(showDataPointBegin, showDataPointCount);
                    }
                }
            }
        }
    }
    //执行纵向鼠标纵向缩放。
    inline void doMouseWheelV(WRChartDValueRange& range, int yPos,  int delta, int height) const
    {
        if (yPos >= 0 && yPos < height)
        {
            if (delta > 0)
            {
				double showDataRange = m_showDataRange.angleSpan();
				double showDataRange2 = showDataRange / 2;
				if (showDataRange2 > 0.001)
				{
					double i = yPos * showDataRange / height;
					double showDataAngleEnd = m_showDataRange.angleEnd() - i / 2;
					if (showDataAngleEnd - showDataRange2 < m_currSource->angleMinValue())
					{
						showDataAngleEnd = m_currSource->angleMinValue() + showDataRange2;
					}
					double showDataAngleBegin = showDataAngleEnd - showDataRange2;
					range.update(showDataAngleBegin, showDataAngleEnd);
				}
            }
            else
            {
				if (m_showDataRange.angleBegin() > m_currSource->angleMinValue() || m_showDataRange.angleEnd() < m_currSource->angleMaxValue())
				{
					double showDataRange = m_showDataRange.angleSpan();
					double showDataRange2 = showDataRange * 2;
					if (showDataRange2 >= m_currSource->angleMaxValue() - m_currSource->angleMinValue())
					{
						range.update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
					}
					else
					{
						double i = yPos * showDataRange / height;
						double showDataAngleEnd = m_showDataRange.angleEnd() + i;
						if (showDataAngleEnd > m_currSource->angleMaxValue())
						{
							showDataAngleEnd = m_currSource->angleMaxValue();
						}
						if (showDataAngleEnd - showDataRange2 < m_currSource->angleMinValue())
						{
							showDataAngleEnd = m_currSource->angleMinValue() + showDataRange2;
						}
						double showDataAngleBegin = showDataAngleEnd - showDataRange2;						
						range.update(showDataAngleBegin, showDataAngleEnd);
					}
				}
            }
        }
    }

protected:	
	//当布局时调用此方法。
	void onLayout(const WRRect& rect);
	
	//键盘按下处理，如果需要重绘，则返回True。
	bool onKeyDown(const QKeyEvent& e);
	//键盘释放处理，如果需要重绘，则返回True。
	bool onKeyUp(const QKeyEvent& e);

	//执行绘制处理操作。
	void onPaint(QPainter& painter);
	//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
	void onPaintMouseFeedback(QPainter& painter);

	//验证图形，如果需要重新绘制，则返回True。
	bool validate(void);

public:
	//初始化默认向频图控件。
	WRDirMapControl(void);

	//初始化向频图控件，使用8位有符号整数幅度数据和16位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<signed char, short>& initArgs);
	//初始化向频图控件，使用8位无符号整数幅度数据和16位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned char, short>& initArgs);

	//初始化向频图控件，使用16位有符号整数幅度数据和16位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<short, short>& initArgs);
	//初始化向频图控件，使用16位无符号整数幅度数据和16位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned short, short>& initArgs);

	//初始化向频图控件，使用32位有符号整数幅度数据和16位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<int, short>& initArgs);
	//初始化向频图控件，使用32位无符号整数幅度数据和16位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned int, short>& initArgs);

	//初始化向频图控件，使用32位浮点数幅度数据和16位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<float, short>& initArgs);
	//初始化向频图控件，使用64位浮点数幅度数据和16位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<double, short>& initArgs);

	//初始化向频图控件，使用8位有符号整数幅度数据和16位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<signed char, unsigned short>& initArgs);
	//初始化向频图控件，使用8位无符号整数幅度数据和16位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned char, unsigned short>& initArgs);

	//初始化向频图控件，使用16位有符号整数幅度数据和16位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<short, unsigned short>& initArgs);
	//初始化向频图控件，使用16位无符号整数幅度数据和16位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned short, unsigned short>& initArgs);

	//初始化向频图控件，使用32位有符号整数幅度数据和16位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<int, unsigned short>& initArgs);
	//初始化向频图控件，使用32位无符号整数幅度数据和16位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned int, unsigned short>& initArgs);

	//初始化向频图控件，使用32位浮点数幅度数据和16位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<float, unsigned short>& initArgs);
	//初始化向频图控件，使用64位浮点数幅度数据和16位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<double, unsigned short>& initArgs);

	//初始化向频图控件，使用8位有符号整数幅度数据和32位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<signed char, int>& initArgs);
	//初始化向频图控件，使用8位无符号整数幅度数据和32位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned char, int>& initArgs);

	//初始化向频图控件，使用16位有符号整数幅度数据和32位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<short, int>& initArgs);
	//初始化向频图控件，使用16位无符号整数幅度数据和32位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned short, int>& initArgs);

	//初始化向频图控件，使用32位有符号整数幅度数据和32位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<int, int>& initArgs);
	//初始化向频图控件，使用32位无符号整数幅度数据和32位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned int, int>& initArgs);

	//初始化向频图控件，使用32位浮点数幅度数据和32位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<float, int>& initArgs);
	//初始化向频图控件，使用64位浮点数幅度数据和32位有符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<double, int>& initArgs);

	//初始化向频图控件，使用8位有符号整数幅度数据和32位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<signed char, unsigned int>& initArgs);
	//初始化向频图控件，使用8位无符号整数幅度数据和32位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned char, unsigned int>& initArgs);

	//初始化向频图控件，使用16位有符号整数幅度数据和32位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<short, unsigned int>& initArgs);
	//初始化向频图控件，使用16位无符号整数幅度数据和32位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned short, unsigned int>& initArgs);

	//初始化向频图控件，使用32位有符号整数幅度数据和32位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<int, unsigned int>& initArgs);
	//初始化向频图控件，使用32位无符号整数幅度数据和32位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned int, unsigned int>& initArgs);

	//初始化向频图控件，使用32位浮点数幅度数据和32位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<float, unsigned int>& initArgs);
	//初始化向频图控件，使用64位浮点数幅度数据和32位无符号整数方向数据。
	WRDirMapControl(const WRDirMapInitParams<double, unsigned int>& initArgs);

	//初始化向频图控件，使用8位有符号整数幅度数据和32位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<signed char, float>& initArgs);
	//初始化向频图控件，使用8位无符号整数幅度数据和32位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned char, float>& initArgs);

	//初始化向频图控件，使用16位有符号整数幅度数据和32位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<short, float>& initArgs);
	//初始化向频图控件，使用16位无符号整数幅度数据和32位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned short, float>& initArgs);

	//初始化向频图控件，使用32位有符号整数幅度数据和32位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<int, float>& initArgs);
	//初始化向频图控件，使用32位无符号整数幅度数据和32位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned int, float>& initArgs);

	//初始化向频图控件，使用32位浮点数幅度数据和32位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<float, float>& initArgs);
	//初始化向频图控件，使用64位浮点数幅度数据和32位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<double, float>& initArgs);

	//初始化向频图控件，使用8位有符号整数幅度数据和64位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<signed char, double>& initArgs);
	//初始化向频图控件，使用8位无符号整数幅度数据和64位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned char, double>& initArgs);

	//初始化向频图控件，使用16位有符号整数幅度数据和64位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<short, double>& initArgs);
	//初始化向频图控件，使用16位无符号整数幅度数据和64位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned short, double>& initArgs);

	//初始化向频图控件，使用32位有符号整数幅度数据和64位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<int, double>& initArgs);
	//初始化向频图控件，使用32位无符号整数幅度数据和64位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<unsigned int, double>& initArgs);

	//初始化向频图控件，使用32位浮点数幅度数据和64位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<float, double>& initArgs);
	//初始化向频图控件，使用64位浮点数幅度数据和64位浮点数方向数据。
	WRDirMapControl(const WRDirMapInitParams<double, double>& initArgs);

	//初始化向频图控件，使用8位有符号整数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<signed char, short>& initArgs);
	//初始化向频图控件，使用8位无符号整数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned char, short>& initArgs);

	//初始化向频图控件，使用16位有符号整数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<short, short>& initArgs);
	//初始化向频图控件，使用16位无符号整数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned short, short>& initArgs);

	//初始化向频图控件，使用32位有符号整数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<int, short>& initArgs);
	//初始化向频图控件，使用32位无符号整数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned int, short>& initArgs);

	//初始化向频图控件，使用32位浮点数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<float, short>& initArgs);
	//初始化向频图控件，使用64位浮点数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<double, short>& initArgs);

	//初始化向频图控件，使用8位有符号整数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<signed char, unsigned short>& initArgs);
	//初始化向频图控件，使用8位无符号整数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned char, unsigned short>& initArgs);

	//初始化向频图控件，使用16位有符号整数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<short, unsigned short>& initArgs);
	//初始化向频图控件，使用16位无符号整数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned short, unsigned short>& initArgs);

	//初始化向频图控件，使用32位有符号整数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<int, unsigned short>& initArgs);
	//初始化向频图控件，使用32位无符号整数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned int, unsigned short>& initArgs);

	//初始化向频图控件，使用32位浮点数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<float, unsigned short>& initArgs);
	//初始化向频图控件，使用64位浮点数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<double, unsigned short>& initArgs);

	//初始化向频图控件，使用8位有符号整数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<signed char, int>& initArgs);
	//初始化向频图控件，使用8位无符号整数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned char, int>& initArgs);

	//初始化向频图控件，使用16位有符号整数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<short, int>& initArgs);
	//初始化向频图控件，使用16位无符号整数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned short, int>& initArgs);

	//初始化向频图控件，使用32位有符号整数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<int, int>& initArgs);
	//初始化向频图控件，使用32位无符号整数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned int, int>& initArgs);

	//初始化向频图控件，使用32位浮点数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<float, int>& initArgs);
	//初始化向频图控件，使用64位浮点数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<double, int>& initArgs);

	//初始化向频图控件，使用8位有符号整数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<signed char, unsigned int>& initArgs);
	//初始化向频图控件，使用8位无符号整数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned char, unsigned int>& initArgs);

	//初始化向频图控件，使用16位有符号整数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<short, unsigned int>& initArgs);
	//初始化向频图控件，使用16位无符号整数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned short, unsigned int>& initArgs);

	//初始化向频图控件，使用32位有符号整数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<int, unsigned int>& initArgs);
	//初始化向频图控件，使用32位无符号整数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned int, unsigned int>& initArgs);

	//初始化向频图控件，使用32位浮点数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<float, unsigned int>& initArgs);
	//初始化向频图控件，使用64位浮点数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<double, unsigned int>& initArgs);

	//初始化向频图控件，使用8位有符号整数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<signed char, float>& initArgs);
	//初始化向频图控件，使用8位无符号整数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned char, float>& initArgs);

	//初始化向频图控件，使用16位有符号整数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<short, float>& initArgs);
	//初始化向频图控件，使用16位无符号整数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned short, float>& initArgs);

	//初始化向频图控件，使用32位有符号整数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<int, float>& initArgs);
	//初始化向频图控件，使用32位无符号整数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned int, float>& initArgs);

	//初始化向频图控件，使用32位浮点数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<float, float>& initArgs);
	//初始化向频图控件，使用64位浮点数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<double, float>& initArgs);

	//初始化向频图控件，使用8位有符号整数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<signed char, double>& initArgs);
	//初始化向频图控件，使用8位无符号整数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned char, double>& initArgs);

	//初始化向频图控件，使用16位有符号整数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<short, double>& initArgs);
	//初始化向频图控件，使用16位无符号整数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned short, double>& initArgs);

	//初始化向频图控件，使用32位有符号整数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<int, double>& initArgs);
	//初始化向频图控件，使用32位无符号整数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<unsigned int, double>& initArgs);

	//初始化向频图控件，使用32位浮点数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<float, double>& initArgs);
	//初始化向频图控件，使用64位浮点数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
	void initialize(const WRDirMapInitParams<double, double>& initArgs);

    //清除数据。
    void clearData(void);
	//写入数据。该方法可以在多线程环境中使用。
	void writeData(const void* specBuffer, const void* angleBuffer, int dataFrames);

	//获取背景颜色。
    inline WRColor backColor(void) const
    {
        return m_backColor;
    }
    //设置背景颜色。
    bool backColor(WRColor value);

	//获取横坐标轴元素。
    inline WRDirMapHAxisElement* hAxis(void) const
    {
        return m_hAxis;
    }
    //获取纵坐标轴元素。
    inline WRDirMapVAxisElement* vAxis(void) const
    {
        return m_vAxis;
    }
    //获取横向滚动条元素。
    inline WRDirMapHScrollElement* hScroll(void) const
    {
        return m_hScroll;
    }
    //获取纵向滚动条元素。
    inline WRDirMapVScrollElement* vScroll(void) const
    {
        return m_vScroll;
    }
    //获取数据视图元素。
    inline WRDirMapDataViewElement* dataView(void) const
    {
        return m_dataView;
    }

    //获取是否暂停数据。
    inline bool holdStatus(void) const
    {
        return readFlag(WRDIRMAPCONTROL_HOLDSTATUS);
    }
    //设置是否暂停数据。
    bool holdStatus(bool value);

	//获取幅度最小值。
    inline double specMinValue(void) const
    {
		return m_currSource->specMinValue();
    }
    //获取幅度最大值。
    inline double specMaxValue(void) const
    {
		return m_currSource->specMaxValue();
    }
	//获取幅度调整值。
    inline double specOffValue(void) const
    {
		return m_currSource->specOffValue();
    }
    //获取幅度差异值。
    inline double specDifValue(void) const
    {
		return m_currSource->specDifValue();
    }

	//获取角度最小值。
    inline double angleMinValue(void) const
    {
		return m_currSource->angleMinValue();
    }
    //获取角度最大值。
    inline double angleMaxValue(void) const
    {
		return m_currSource->angleMaxValue();
    }

	//获取数据点数量。
    inline int dataPointCount(void) const
    {
		return m_currSource->points();
    }
	//获取数据是否闭区间。
	inline bool dataIsClosed(void) const
	{
		return m_currSource->isClosed();
	}

	//获取数据频率起始。
	inline long long freqBegin(void) const
	{
		return m_currSource->freqBegin();
	}
	//获取数据频率结束。
	inline long long freqEnd(void) const
	{
		return m_currSource->freqEnd();
	}
	
	//获取数据处理方式。
	inline DataProcMethod dataProcMethod(void) const
	{
		return m_dataProcMethod;
	}
	//设置数据处理方式。
	bool dataProcMethod(DataProcMethod value);

    //获取显示数据点起始。
    inline int showDataPointBegin(void) const
    {
        return m_showDataRange.pointBegin();
    }
    //获取显示数据点数量。
    inline int showDataPointCount(void) const
    {
        return m_showDataRange.pointCount();
    }
    //获取显示数据点结束。
    inline int showDataPointEnd(void) const
    {
        return m_showDataRange.pointEnd();
    }

    //获取显示数据角度起始。
    inline double showDataAngleBegin(void) const
    {
        return m_showDataRange.angleBegin();
    }
    //获取显示数据角度跨度。
    inline double showDataAngleSpan(void) const
    {
        return m_showDataRange.angleSpan();
    }
    //获取显示数据角度结束。
    inline double showDataAngleEnd(void) const
    {
        return m_showDataRange.angleEnd();
    }

    //获取显示数据范围。
    inline const WRDirMapDataRange& showDataRange(void) const
    {
        return m_showDataRange;
    }
    //设置显示数据范围。
    bool showDataRange(const WRDirMapDataRange& value);

    //获取数据点显示数据范围。
    inline const WRChartSampleRange& showDataPointRange(void) const
    {
        return m_showDataRange.pointRange();
    }
    //设置数据点显示数据范围。
    bool showDataPointRange(const WRChartSampleRange& value);

    //获取数据角度显示数据范围。
    inline const WRChartDValueRange& showDataAngleRange(void) const
    {
        return m_showDataRange.angleRange();
    }
    //设置数据角度显示数据范围。
    bool showDataAngleRange(const WRChartDValueRange& value);

	//获取指定位置的数据点，如果超出数据视图范围，则返回False。
	inline bool getDataPointAt(int x, int* v) const
	{
		x -= m_dataView->left();
		if (x >= 0 && x < m_dataView->width())
		{
			*v = getDataPointAt(m_dataView->width(), x);
			return true;
		}
		return false;
	}
	//获取指定位置的数据点，如果超出数据视图范围，则返回False。
	inline bool getDataPointAt(const WRPoint& p, int* v) const
	{
		int x = p.x() - m_dataView->left();
		if (x >= 0 && x < m_dataView->width())
		{
			*v = getDataPointAt(m_dataView->width(), x);
			return true;
		}
		return false;
	}

	//获取指定位置的数据角度, 如果超出数据视图范围，则返回False。
	inline bool getDataAngleAt(int y, double* v) const
	{
		y -= m_dataView->top();
		if (y >= 0 && y < m_dataView->height())
		{
			*v = getDataAngleAt(m_dataView->height(), y);
			return true;
		}
		return false;
	}
	//获取指定位置的数据角度, 如果超出数据视图范围，则返回False。
	inline bool getDataAngleAt(const WRPoint& p, double* v) const
	{
		int y = p.y() - m_dataView->top();
		if (y >= 0 && y < m_dataView->height())
		{
			*v = getDataAngleAt(m_dataView->height(), y);
			return true;
		}
		return false;
	}

	//获取指定数据点的频率值。
	inline long long getFreqValueAt(int pointIndex) const
	{
		return m_currSource->getFreqValue(pointIndex);
	}
	//获取指定位置的频率值，如果超出数据视图范围，则返回False。
	inline bool getFreqValueAt(int x, long long* v) const
	{
		x -= m_dataView->left();
		if (x >= 0 && x < m_dataView->width())
		{
			int p = getDataPointAt(m_dataView->width(), x);
			*v = m_currSource->getFreqValue(p);
			return true;
		}
		return false;
	}
	//获取指定位置的频率值，如果超出数据视图范围，则返回False。
	inline bool getFreqValueAt(const WRPoint& p, long long* v) const
	{
		int x = p.x() - m_dataView->left();
		if (x >= 0 && x < m_dataView->width())
		{
			int i = getDataPointAt(m_dataView->width(), x);
			*v = m_currSource->getFreqValue(i);
			return true;
		}
		return false;
	}

    //添加数据角度线条。
    WRDirMapDataAngleLineElement* addDataAngleLine(double position);
	//添加数据点线条。
    WRDirMapDataPointLineElement* addDataPointLine(int position);

    //移除测量元素。
    void remove(WRDirMapGaugeElement** element);
};

//#pragma warning(pop)

#endif //WRDIRMAPCONTROL
