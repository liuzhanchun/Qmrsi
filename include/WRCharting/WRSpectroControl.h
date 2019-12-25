#pragma once
#ifndef WRSPECTROCONTROL
#define WRSPECTROCONTROL

#include <WRCharting/WRGlobal.h>
#include <WRCharting/WRMath.h>
#include <WRCharting/WRMutex.h>
#include <WRCharting/WRChartControl.h>
#include <WRCharting/WRSpectroDataRange.h>
#include <WRCharting/WRSpectroChannel.h>
#include <WRCharting/WRSpectroInitParams.h>
#include <WRCharting/WRSpectroDataSource.h>
#include <WRCharting/WRSpectroAxisElement.h>
#include <WRCharting/WRSpectroScrollElement.h>
#include <WRCharting/WRSpectroDataViewElement.h>
#include <WRCharting/WRSpectroGaugeElement.h>
#include <WRCharting/WRSpectroLineElement.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

#define WRSPECTROCONTROL_HOLDSTATUS	512UL

//表示频谱图控件。
class WRCHARTING_CLASS WRSpectroControl : public WRChartControl
{
    Q_OBJECT

	friend class WRSpectroChannel;
	friend class WRSpectroHAxisElement;
    friend class WRSpectroVAxisElement;
    friend class WRSpectroHScrollElement;
    friend class WRSpectroVScrollElement;
    friend class WRSpectroDataViewElement;
	friend class WRSpectroGaugleElement;
	friend class WRSpectroLineElement;
	friend class WRSpectroDataPointLineElement;
	friend class WRSpectroDataValueLineElement;

signals:
    //数据改变信号。
    void dataChanged(void);

    //显示数据范围更改信号。
    void showDataRangeUpdated(const WRSpectroDataRange& value);
    //显示数据点范围更改信号。
    void showDataPointRangeUpdated(const WRChartSampleRange& value);
    //显示数据值范围更改信号。
    void showDataValueRangeUpdated(const WRChartDValueRange& value);

    //显示数据范围改变信号。
    void showDataRangeChanged(const WRSpectroDataRange& value);
    //显示数据点范围更新信号。
    void showDataPointRangeChanged(const WRChartSampleRange& value);
    //显示数据值范围改变信号。
    void showDataValueRangeChanged(const WRChartDValueRange& value);

    //挂起状态改变信号。
    void holdStatusChanged(bool value);

    //背景颜色改变信号。
    void backColorChanged(WRColor value);

public slots:
    //显示数据范围改变信号。
    void setShowDataRange(const WRSpectroDataRange& value);
    //显示数据点范围更新信号。
    void setShowDataPointRange(const WRChartSampleRange& value);
    //显示数据值范围改变信号。
    void setShowDataValueRange(const WRChartDValueRange& value);

    //设置挂起状态。
    void setHoldStatus(bool value);
    //设置背景颜色。
    void setBackColor(WRColor value);

private:
	//同步对象
	WRMutex m_mutex;

	//纵坐标轴
	WRSpectroVAxisElement* m_vAxis;
	//横坐标轴
	WRSpectroHAxisElement* m_hAxis;
	//纵向滚动条
	WRSpectroVScrollElement* m_vScroll;
	//横向滚动条
	WRSpectroHScrollElement* m_hScroll;
	//数据视图
	WRSpectroDataViewElement* m_dataView;

	//通道集合。
	WRSpectroChannel m_channels[WRSPECTROCHANNELS];

	//后端数据源
	WRSpectroDataSource* m_backSource;
	//当前数据源
	WRSpectroDataSource* m_currSource;

	//显示数据范围
	WRSpectroDataRange m_showDataRange;

	//背景颜色
	WRColor m_backColor;

	//获取数据源对象。
	inline WRSpectroDataSource* dataSource(void) const
	{
		return m_currSource;
	}

	//当显示数据范围改变后调用此方法 。
    void onShowDataRangeChanged(void);
    //当显示数据点范围改变后调用此方法。
    void onShowDataPointRangeChanged(void);
    //当显示数据值范围改变后调用此方法。
    void onShowDataValueRangeChanged(void);

    //重置显示数据范围。
    inline void resetShowDataRange(const WRSpectroDataRange& value)
    {
        bool change = false;
        if (m_showDataRange.pointRange(value.pointRange()))
        {
            onShowDataPointRangeChanged();
            emit showDataPointRangeChanged(m_showDataRange.pointRange());
            change = true;
        }
        if (m_showDataRange.valueRange(value.valueRange()))
        {
            onShowDataValueRangeChanged();
            emit showDataValueRangeChanged(m_showDataRange.valueRange());
            change = true;
        }
        if (change)
        {
            onShowDataRangeChanged();
            emit showDataRangeChanged(m_showDataRange);
        }
    }

    //改变显示数据范围。
    inline bool changeShowDataRange(const WRSpectroDataRange& value)
    {
        bool change = false;
        if (m_showDataRange.pointRange(value.pointRange()))
        {
            onShowDataPointRangeChanged();
            emit showDataPointRangeUpdated(m_showDataRange.pointRange());
            emit showDataPointRangeChanged(m_showDataRange.pointRange());
            change = true;
        }
        if (m_showDataRange.valueRange(value.valueRange()))
        {
            onShowDataValueRangeChanged();
            emit showDataValueRangeUpdated(m_showDataRange.valueRange());
            emit showDataValueRangeChanged(m_showDataRange.valueRange());
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
    //改变数据值显示数据范围。
    inline bool changeShowDataValueRange(const WRChartDValueRange& value)
    {
        if (m_showDataRange.valueRange(value))
        {
            onShowDataValueRangeChanged();
            onShowDataRangeChanged();

            emit showDataValueRangeUpdated(m_showDataRange.valueRange());
            emit showDataValueRangeChanged(m_showDataRange.valueRange());
            emit showDataRangeUpdated(m_showDataRange);
            emit showDataRangeChanged(m_showDataRange);

            return true;
        }
        return false;
    }

	//禁用复制构造函数。
	WRSpectroControl(const WRSpectroControl& other);
	//禁用赋值操作符。
	WRSpectroControl& operator=(const WRSpectroControl& other);

	//执行控件的初始化。
	void initialize(void);
	//清理当前对象所占用的相关资源。
	~WRSpectroControl(void);
	
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
	
	//获取指定数据值偏移的位置。
	inline int getDataValueOffsetPos(int h, double v) const
	{
		int h1 = h - 1;
		return h1 - (int)(v * h1 / m_showDataRange.valueSpan() + 0.5);
	}
	//获取指定数据值的位置。
	inline int getDataValuePos(int h, double v) const
	{
		int h1 = h - 1;
		return h1 - (int)((v - m_showDataRange.valueBegin()) * h1 / m_showDataRange.valueSpan() + 0.5);
	}

	//获取指定长度的数据值跨度。
	inline double getDataValueSpan(int h, int y) const
	{
		return y * m_showDataRange.valueSpan() / (h - 1);
	}
	//获取指定位置的数据值。
	inline double getDataValueAt(int h, int y) const
	{
		return m_showDataRange.valueEnd() - y * m_showDataRange.valueSpan() / (h - 1);
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
            double value1 = getDataValueAt(height, yPos1);
            double value2 = getDataValueAt(height, yPos2);
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
            if (iOff)
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
			double showDataRange = m_showDataRange.valueSpan();
            double iOff = yOff * showDataRange / height;
            if (iOff != 0)
            {
				double showDataValueEnd = m_showDataRange.valueEnd() + iOff;
                if (showDataValueEnd > m_currSource->maxValue())
                {
                    showDataValueEnd = m_currSource->maxValue();
                }
                if (showDataValueEnd - showDataRange < m_currSource->minValue())
                {
                    showDataValueEnd = m_currSource->minValue() + showDataRange;
                }
                double showDataValueBegin = showDataValueEnd - showDataRange;
				range.update(showDataValueBegin, showDataValueEnd);
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
                    int xOff = (int)(xPos * (m_showDataRange.pointCount() - 1LL) / (width - 1.0) + 0.5);
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
                        int xOff = (int)(xPos * (m_showDataRange.pointCount() - 1LL) / (width - 1.0) + 0.5);
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
				double showDataRange = m_showDataRange.valueSpan();
				double showDataRange2 = showDataRange / 2;
				if (showDataRange2 > 0.001)
				{
					double i = yPos * showDataRange / height;
					double showDataValueEnd = m_showDataRange.valueEnd() - i / 2;
					if (showDataValueEnd - showDataRange2 < m_currSource->minValue())
					{
						showDataValueEnd = m_currSource->minValue() + showDataRange2;
					}
					double showDataValueBegin = showDataValueEnd - showDataRange2;
					range.update(showDataValueBegin, showDataValueEnd);
				}
            }
            else
            {
				if (m_showDataRange.valueBegin() > m_currSource->minValue() || m_showDataRange.valueEnd() < m_currSource->maxValue())
				{
					double showDataRange = m_showDataRange.valueSpan();
					double showDataRange2 = showDataRange * 2;
					if (showDataRange2 >= m_currSource->maxValue() - m_currSource->minValue())
					{
						range.update(m_currSource->minValue(), m_currSource->maxValue());
					}
					else
					{
						double i = yPos * showDataRange / height;
						double showDataValueEnd = m_showDataRange.valueEnd() + i;
						if (showDataValueEnd > m_currSource->maxValue())
						{
							showDataValueEnd = m_currSource->maxValue();
						}
						if (showDataValueEnd - showDataRange2 < m_currSource->minValue())
						{
							showDataValueEnd = m_currSource->minValue() + showDataRange2;
						}
						double showDataValueBegin = showDataValueEnd - showDataRange2;						
						range.update(showDataValueBegin, showDataValueEnd);
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
	//初始化默认频谱图控件。
	WRSpectroControl(void);

	//初始化频谱图控件，使用8位有符号整数数据源。
	WRSpectroControl(const WRSpectroInitParams<signed char>& initArgs);
	//初始化频谱图控件，使用8位无符号整数数据源。
	WRSpectroControl(const WRSpectroInitParams<unsigned char>& initArgs);

	//初始化频谱图控件，使用16位有符号整数数据源。
	WRSpectroControl(const WRSpectroInitParams<short>& initArgs);
	//初始化频谱图控件，使用16位无符号整数数据源。
	WRSpectroControl(const WRSpectroInitParams<unsigned short>& initArgs);

	//初始化频谱图控件，使用32位有符号整数数据源。
	WRSpectroControl(const WRSpectroInitParams<int>& initArgs);
	//初始化频谱图控件，使用32位无符号整数数据源。
	WRSpectroControl(const WRSpectroInitParams<unsigned int>& initArgs);

	//初始化频谱图控件，使用32位浮点数数据源。
	WRSpectroControl(const WRSpectroInitParams<float>& initArgs);
	//初始化频谱图控件，使用64位浮点数数据源。
	WRSpectroControl(const WRSpectroInitParams<double>& initArgs);

	//初始化频谱图控件，使用8位有符号整数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRSpectroInitParams<signed char>& initArgs);
	//初始化频谱图控件，使用8位无符号整数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRSpectroInitParams<unsigned char>& initArgs);

	//初始化频谱图控件，使用16位有符号整数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRSpectroInitParams<short>& initArgs);
	//初始化频谱图控件，使用16位无符号整数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRSpectroInitParams<unsigned short>& initArgs);

	//初始化频谱图控件，使用32位有符号整数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRSpectroInitParams<int>& initArgs);
	//初始化频谱图控件，使用32位无符号整数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRSpectroInitParams<unsigned int>& initArgs);

	//初始化频谱图控件，使用32位浮点数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRSpectroInitParams<float>& initArgs);
	//初始化频谱图控件，使用64位浮点数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRSpectroInitParams<double>& initArgs);

	//获取横坐标轴元素。
    inline WRSpectroHAxisElement* hAxis(void) const
    {
        return m_hAxis;
    }
    //获取纵坐标轴元素。
    inline WRSpectroVAxisElement* vAxis(void) const
    {
        return m_vAxis;
    }
    //获取横向滚动条元素。
    inline WRSpectroHScrollElement* hScroll(void) const
    {
        return m_hScroll;
    }
    //获取纵向滚动条元素。
    inline WRSpectroVScrollElement* vScroll(void) const
    {
        return m_vScroll;
    }
    //获取数据视图元素。
    inline WRSpectroDataViewElement* dataView(void) const
    {
        return m_dataView;
    }

	//获取通道对象。
	inline WRSpectroChannel* channel(int index)
	{
		return &m_channels[index];
	}

	//锁定当前对象以进行数据更新。
	inline void lock(void)
	{
		m_mutex.lock();
	}
	//完成数据更新，释放锁。
	inline void unlock(void)
	{
		m_mutex.unlock();
	}

	//更改指定通道的数据，如果数据为NULL，则表示清空数据。
	void alterData(int index, const void* data);
	//更改指定通道的数据，如果数据为NULL，则表示清空数据。
	void alterData(int index, const void* data, const int* markBuf, int markLen);
	//清队指定通道的数据。
	inline void clearData(int index)
	{
		alterData(index, 0);
	}

	//更改首个通道的数据，如果数据为NULL，则表示清空数据。
	inline void alterData(const void* data)
	{
		alterData(0, data);
	}
	//更改首个通道的数据，如果数据为NULL，则表示清空数据。
	inline void alterData(const void* data, const int* markBuf, int markLen)
	{
		alterData(0, data, markBuf, markLen);
	}
    //清除首个通道的数据。
	inline void clearData()
	{
		alterData(0, 0);
	}

	//更改指定通道集合的数据, 
	void alterData(const void** dataArray, const int* channelArray, int channelCount);

	//获取背景颜色。
    inline WRColor backColor(void) const
    {
        return m_backColor;
    }
    //设置背景颜色。
    bool backColor(WRColor value);

    //获取是否暂停数据。
    inline bool holdStatus(void) const
    {
        return readFlag(WRSPECTROCONTROL_HOLDSTATUS);
    }
    //设置是否暂停数据。
    bool holdStatus(bool value);

	//获取数据最小值。
    inline double dataMinValue(void) const
    {
		return m_currSource->minValue();
    }
    //获取数据最大值。
    inline double dataMaxValue(void) const
    {
		return m_currSource->maxValue();
    }
	//获取数据调整值。
    inline double dataOffValue(void) const
    {
		return m_currSource->offValue();
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

	//获取频率起始。
	inline long long freqBegin(void) const
	{
		return m_currSource->freqBegin();
	}
	//获取频率结束。
	inline long long freqEnd(void) const
	{
		return m_currSource->freqEnd();
	}

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

    //获取显示数据值起始。
    inline double showDataValueBegin(void) const
    {
        return m_showDataRange.valueBegin();
    }
    //获取显示数据值结束。
    inline double showDataValueEnd(void) const
    {
        return m_showDataRange.valueEnd();
    }
    //获取显示数据值间隔。
    inline double showDataValueSpan(void) const
    {
        return m_showDataRange.valueSpan();
    }

    //获取显示数据范围。
    inline const WRSpectroDataRange& showDataRange(void) const
    {
        return m_showDataRange;
    }
    //设置显示数据范围。
    bool showDataRange(const WRSpectroDataRange& value);

    //获取数据点显示数据范围。
    inline const WRChartSampleRange& showDataPointRange(void) const
    {
        return m_showDataRange.pointRange();
    }
    //设置数据点显示数据范围。
    bool showDataPointRange(const WRChartSampleRange& value);

    //获取数据值显示数据范围。
    inline const WRChartDValueRange& showDataValueRange(void) const
    {
        return m_showDataRange.valueRange();
    }
    //设置数据值显示数据范围。
    bool showDataValueRange(const WRChartDValueRange& value);

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

	//获取指定位置的数据值, 如果超出数据视图范围，则返回False。
	inline bool getDataValueAt(int y, double* v) const
	{
		y -= m_dataView->top();
		if (y >= 0 && y < m_dataView->height())
		{
			*v = getDataValueAt(m_dataView->height(), y);
			return true;
		}
		return false;
	}
	//获取指定位置的数据值, 如果超出数据视图范围，则返回False。
	inline bool getDataValueAt(const WRPoint& p, double* v) const
	{
		int y = p.y() - m_dataView->top();
		if (y >= 0 && y < m_dataView->height())
		{
			*v = getDataValueAt(m_dataView->height(), y);
			return true;
		}
		return false;
	}

	//获取指定通道指定数据点的值。
	inline bool getDataValueAt(int channel, int pointIndex, double* value) const
	{
		if (channel >= WRSPECTROCHANNELS)
		{
			return false;
		}
		return m_currSource->channel(channel)->getValue(pointIndex, value);
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

	//添加数据点线条。
    WRSpectroDataPointLineElement* addDataPointLine(int position);
    //添加数据值线条。
    WRSpectroDataValueLineElement* addDataValueLine(double position);

    //移除测量元素。
    void remove(WRSpectroGaugeElement** element);
};

//#pragma warning(pop)

#endif //WRSPECTROCONTROL
