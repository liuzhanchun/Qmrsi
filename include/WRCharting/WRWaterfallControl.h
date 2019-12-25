#pragma once
#ifndef WRWATERFALLCONTROL
#define WRWATERFALLCONTROL

#include <WRCharting/WRGlobal.h>
#include <WRCharting/WRMath.h>
#include <WRCharting/WRMutex.h>
#include <WRCharting/WRChartControl.h>
#include <WRCharting/WRWaterfallDataRange.h>
#include <WRCharting/WRWaterfallInitParams.h>
#include <WRCharting/WRWaterfallDataSource.h>
#include <WRCharting/WRWaterfallAxisElement.h>
#include <WRCharting/WRWaterfallScrollElement.h>
#include <WRCharting/WRWaterfallDataViewElement.h>
#include <WRCharting/WRWaterfallGaugeElement.h>
#include <WRCharting/WRWaterfallLineElement.h>

//#pragma warning(push)
//#pragma warning(disable:4251)

#define WRWATERFALLCONTROL_VERTICAL		256UL
#define WRWATERFALLCONTROL_HOLDSTATUS	512UL

//表示瀑布图控件。
class WRCHARTING_CLASS WRWaterfallControl : public WRChartControl
{
    Q_OBJECT

	friend class WRWaterfallHAxisElement;
    friend class WRWaterfallVAxisElement;
    friend class WRWaterfallHScrollElement;
    friend class WRWaterfallVScrollElement;
    friend class WRWaterfallDataViewElement;
	friend class WRWaterfallGaugleElement;
	friend class WRWaterfallLineElement;
	friend class WRWaterfallDataFrameLineElement;
	friend class WRWaterfallDataPointLineElement;

signals:
    //数据改变信号。
    void dataChanged(void);

    //显示数据范围更改信号。
    void showDataRangeUpdated(const WRWaterfallDataRange& value);
    //显示数据点范围更改信号。
    void showDataPointRangeUpdated(const WRChartSampleRange& value);
    //显示数据角度范围更改信号。
    void showDataFrameRangeUpdated(const WRChartSampleRange& value);

    //显示数据范围改变信号。
    void showDataRangeChanged(const WRWaterfallDataRange& value);
    //显示数据点范围更新信号。
    void showDataPointRangeChanged(const WRChartSampleRange& value);
    //显示数据角度范围改变信号。
    void showDataFrameRangeChanged(const WRChartSampleRange& value);

    //是否纵向改变信号。
    void verticalChanged(bool value);

    //挂起状态改变信号。
    void holdStatusChanged(bool value);

    //背景颜色改变信号。
    void backColorChanged(WRColor value);

public slots:
    //显示数据范围改变信号。
    void setShowDataRange(const WRWaterfallDataRange& value);
    //显示数据点范围更新信号。
    void setShowDataPointRange(const WRChartSampleRange& value);
    //显示数据帧范围改变信号。
    void setShowDataFrameRange(const WRChartSampleRange& value);

    //设置是否纵向。
    void setVertical(bool value);
    //设置挂起状态。
    void setHoldStatus(bool value);
    //设置背景颜色。
    void setBackColor(WRColor value);

private:
	//同步对象
	WRMutex m_mutex;

	//纵坐标轴
	WRWaterfallVAxisElement* m_vAxis;
	//横坐标轴
	WRWaterfallHAxisElement* m_hAxis;
	//纵向滚动条
	WRWaterfallVScrollElement* m_vScroll;
	//横向滚动条
	WRWaterfallHScrollElement* m_hScroll;
	//数据视图
	WRWaterfallDataViewElement* m_dataView;

	//后端数据源
	WRWaterfallDataSource* m_backSource;
	//当前数据源
	WRWaterfallDataSource* m_currSource;

	//显示数据范围
	WRWaterfallDataRange m_showDataRange;
	
	//背景颜色
	WRColor m_backColor;

	//获取数据源对象。
	inline WRWaterfallDataSource* dataSource(void) const
	{
		return m_currSource;
	}

	//当显示数据范围改变后调用此方法 。
    void onShowDataRangeChanged(void);
    //当显示数据点范围改变后调用此方法。
    void onShowDataPointRangeChanged(void);
    //当显示数据帧范围改变后调用此方法。
    void onShowDataFrameRangeChanged(void);

    //重置显示数据范围。
    inline void resetShowDataRange(const WRWaterfallDataRange& value)
    {
        bool change = false;
        if (m_showDataRange.pointRange(value.pointRange()))
        {
            onShowDataPointRangeChanged();
            emit showDataPointRangeChanged(m_showDataRange.pointRange());
            change = true;
        }
        if (m_showDataRange.frameRange(value.frameRange()))
        {
            onShowDataFrameRangeChanged();
            emit showDataFrameRangeChanged(m_showDataRange.frameRange());
            change = true;
        }
        if (change)
        {
            onShowDataRangeChanged();
            emit showDataRangeChanged(m_showDataRange);
        }
    }

    //改变显示数据范围。
    inline bool changeShowDataRange(const WRWaterfallDataRange& value)
    {
        bool change = false;
        if (m_showDataRange.pointRange(value.pointRange()))
        {
            onShowDataPointRangeChanged();
            emit showDataPointRangeUpdated(m_showDataRange.pointRange());
            emit showDataPointRangeChanged(m_showDataRange.pointRange());
            change = true;
        }
        if (m_showDataRange.frameRange(value.frameRange()))
        {
            onShowDataFrameRangeChanged();
            emit showDataFrameRangeUpdated(m_showDataRange.frameRange());
            emit showDataFrameRangeChanged(m_showDataRange.frameRange());
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
    inline bool changeShowDataFrameRange(const WRChartSampleRange& value)
    {
        if (m_showDataRange.frameRange(value))
        {
            onShowDataFrameRangeChanged();
            onShowDataRangeChanged();

            emit showDataFrameRangeUpdated(m_showDataRange.frameRange());
            emit showDataFrameRangeChanged(m_showDataRange.frameRange());
            emit showDataRangeUpdated(m_showDataRange);
            emit showDataRangeChanged(m_showDataRange);

            return true;
        }
        return false;
    }

	//禁用复制构造函数。
	WRWaterfallControl(const WRWaterfallControl& other);
	//禁用赋值操作符。
	WRWaterfallControl& operator=(const WRWaterfallControl& other);

	//执行控件的初始化。
	void initialize(void);
	//清理当前对象所占用的相关资源。
	~WRWaterfallControl(void);

	//获取纵向指定数据点偏移的位置。
	inline int getVDataPointOffsetPos(int w, int v) const
	{
		return (int)(v * (w - 1LL) / (m_showDataRange.pointCount() - 1.0) + 0.5);
	}
	//获取纵向指定数据点的位置。
	inline int getVDataPointPos(int w, int v) const
	{
		return (int)((v - m_showDataRange.pointBegin()) * (w - 1LL) / (m_showDataRange.pointCount() - 1.0) + 0.5);
	}

	//获取横向指定数据点偏移的位置。
	inline int getHDataPointOffsetPos(int h, int v) const
	{
		int b = h - 1;
		return b - (int)(v * (long long)b / (m_showDataRange.pointCount() - 1.0) + 0.5);
	}
	//获取横向指定数据点的位置。
	inline int getHDataPointPos(int h, int v) const
	{
		int b = h - 1;
		return b - (int)((v - m_showDataRange.pointBegin()) * (long long)b / (m_showDataRange.pointCount() - 1.0) + 0.5);
	}

	//获取纵向指定位置的数据点偏移。
    inline int getVDataPointOffsetAt(int w, int x) const
    {
        return (int)(x * (m_showDataRange.pointCount() - 1LL) / (w - 1.0) + 0.5);
    }
	//获取纵向指定位置的数据点。
	inline int getVDataPointAt(int w, int x) const
	{
		return m_showDataRange.pointBegin() + (int)(x * (m_showDataRange.pointCount() - 1LL) / (w - 1.0) + 0.5);
	}

    //获取横向指定位置的数据点偏移。
    inline int getHDataPointOffsetAt(int h, int y) const
    {
        return m_showDataRange.pointCount() - 1 - (int)(y * (m_showDataRange.pointCount() - 1LL) / (h - 1.0) + 0.5);
    }
	//获取横向指定位置的数据点。
	inline int getHDataPointAt(int h, int y) const
	{
		return m_showDataRange.pointBegin() + m_showDataRange.pointCount() - 1 - (int)(y * (m_showDataRange.pointCount() - 1LL) / (h - 1.0) + 0.5);
	}

	//获取纵向指定数据帧偏移的位置。
	inline int getVDataFrameOffsetPos(int h, int v) const
	{
		return (int)(v * (h - 1LL) / (m_showDataRange.frameCount() - 1.0) + 0.5);
	}
	//获取纵向指定数据帧的位置。
	inline int getVDataFramePos(int h, int v) const
	{
		return (int)((v - m_showDataRange.frameBegin()) * (h - 1LL) / (m_showDataRange.frameCount() - 1.0) + 0.5);
	}

	//获取横向指定数据帧偏移的位置。
	inline int getHDataFrameOffsetPos(int w, int v) const
	{
		return (int)(v * (w - 1LL) / (m_showDataRange.frameCount() - 1.0) + 0.5);
	}
	//获取横向指定数据帧的位置。
	inline int getHDataFramePos(int w, int v) const
	{
		return (int)((v - m_showDataRange.frameBegin()) * (w - 1LL) / (m_showDataRange.frameCount() - 1.0) + 0.5);
	}

	//获取纵向指定位置的数据帧偏移。
	inline int getVDataFrameOffsetAt(int h, int y) const
	{
		return (int)(y * (m_showDataRange.frameCount() - 1LL) / (h - 1.0) + 0.5);
	}
    //获取纵向指定位置的数据帧。
    inline int getVDataFrameAt(int h, int y) const
    {
        return m_showDataRange.frameBegin() + (int)(y * (m_showDataRange.frameCount() - 1LL) / (h - 1.0) + 0.5);
    }

	//获取横向指定位置的数据帧偏移。
	inline int getHDataFrameOffsetAt(int w, int x) const
	{
		return (int)(x * (m_showDataRange.frameCount() - 1LL) / (w - 1.0) + 0.5);
	}
    //获取横向指定位置的数据帧。
    inline int getHDataFrameAt(int w, int x) const
    {
        return m_showDataRange.frameBegin() + (int)(x * (m_showDataRange.frameCount() - 1LL) / (w - 1.0) + 0.5);
    }

    //获取指定实际值的显示值。
    inline unsigned char getShowValue(double value) const
    {
        if (value < m_currSource->minValue())
        {
            return 0x00;
        }
        if (value > m_currSource->maxValue())
        {
            return 0xFF;
        }
        return (char)((value - m_currSource->minValue()) * 255 / m_currSource->difValue() + 0.5);
    }
    //获取指定显示值的实际值。
    inline double getDataValue(char value) const
    {
        return value * m_currSource->difValue() / 255 + m_currSource->minValue();
    }

    //执行横向向鼠标水平缩放。
    inline void doHMouseZoomH(WRChartSampleRange& range, int xPos1, int xPos2,  int width) const
    {
        if (xPos1 != xPos2)
        {
            int index1 = getHDataFrameAt(width, xPos1);
            int index2 = getHDataFrameAt(width, xPos2);
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
    //执行横向鼠标纵向缩放。
    inline void doHMouseZoomV(WRChartSampleRange& range, int yPos1, int yPos2,  int height) const
    {
        if (yPos1 != yPos2)
        {
            int index1 = getHDataPointAt(height, yPos1);
            int index2 = getHDataPointAt(height, yPos2);
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

    //执行纵向鼠标水平缩放。
    inline void doVMouseZoomH(WRChartSampleRange& range, int xPos1, int xPos2,  int width) const
    {
        if (xPos1 != xPos2)
        {
            int index1 = getVDataPointAt(width, xPos1);
            int index2 = getVDataPointAt(width, xPos2);
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
    inline void doVMouseZoomV(WRChartSampleRange& range, int yPos1, int yPos2,  int height) const
    {
        if (yPos1 != yPos2)
        {
            int index1 = getVDataFrameAt(height, yPos1);
            int index2 = getVDataFrameAt(height, yPos2);
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

    //执行横向鼠标水平移动。
    inline void doHMouseMoveH(WRChartSampleRange& range, int xPos1, int xPos2,  int width) const
    {
        if (xPos1 != xPos2)
        {
            int xOff = xPos2 - xPos1;
            int iOff = (int)WRMath::round(xOff * (m_showDataRange.frameCount() - 1LL) / (width - 1.0));
            if (iOff)
            {
                int showDataFrameBegin = 0;
				if (iOff < m_showDataRange.frameBegin())
				{
					showDataFrameBegin = m_showDataRange.frameBegin() - iOff;
				}
                if (showDataFrameBegin + m_showDataRange.frameCount() > m_currSource->capacity())
                {
                    showDataFrameBegin =  m_currSource->capacity() - m_showDataRange.frameCount();
                }
                range.begin(showDataFrameBegin);
            }
        }
    }
    //执行横向鼠标纵向移动。
    inline void doHMouseMoveV(WRChartSampleRange& range, int yPos1, int yPos2,  int height) const
    {
        if (yPos1 != yPos2)
        {
            int yOff = yPos2 - yPos1;
            int iOff = (int)WRMath::round(yOff * (m_showDataRange.pointCount() - 1LL) / (height - 1.0));
            if (iOff)
            {
                int showDataPointBegin = 0;
                if(m_showDataRange.pointBegin() + iOff > 0)
                {
                    showDataPointBegin = m_showDataRange.pointBegin() + iOff;
                }
                if (showDataPointBegin + m_showDataRange.pointCount() > m_currSource->points())
                {
                    showDataPointBegin =  m_currSource->points() - m_showDataRange.pointCount();
                }
                range.begin(showDataPointBegin);
            }
        }
    }

    //执行纵向鼠标水平移动。
    inline void doVMouseMoveH(WRChartSampleRange& range, int xPos1, int xPos2,  int width) const
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
    inline void doVMouseMoveV(WRChartSampleRange& range, int yPos1, int yPos2,  int height) const
    {
        if (yPos1 != yPos2)
        {
            int yOff = yPos2 - yPos1;
            int iOff = (int)WRMath::round(yOff * (m_showDataRange.frameCount() - 1LL) / (height - 1.0));
            if (iOff)
            {
                int showDataFrameBegin = 0;
				if (iOff < m_showDataRange.frameBegin())
				{
					showDataFrameBegin = m_showDataRange.frameBegin() - iOff;
				}
                if (showDataFrameBegin + m_showDataRange.frameCount() > m_currSource->capacity())
                {
                    showDataFrameBegin =  m_currSource->capacity() - m_showDataRange.frameCount();
                }
                range.begin(showDataFrameBegin);
            }
        }
    }

    //执行横向鼠标水平缩放。
    inline void doHMouseWheelH(WRChartSampleRange& range, int xPos,  int delta, int width) const
    {
        if (xPos >= 0 && xPos < width)
        {
            if (delta > 0)
            {
                if (m_showDataRange.frameCount() > 2)
                {
                    int showDataFrameCount = m_showDataRange.frameCount() / 2;
                    if (showDataFrameCount < 2)
                    {
                        showDataFrameCount = 2;
                    }
                    int xOff = (int)(xPos * (m_showDataRange.frameCount() - 1LL) / (width - 1.0) + 0.5);
                    int showDataFrameBegin = m_showDataRange.frameBegin() + xOff / 2;
                    if (showDataFrameBegin + showDataFrameCount > m_currSource->capacity())
                    {
                        showDataFrameBegin = m_currSource->capacity() - showDataFrameCount;
                    }
                    range.update(showDataFrameBegin, showDataFrameCount);
                }
            }
            else
            {
                if (m_currSource->capacity() != m_showDataRange.frameCount())
                {
                    int showDataFrameCount = m_showDataRange.frameCount() * 2;
                    if (showDataFrameCount >= m_currSource->capacity())
                    {
                        showDataFrameCount = m_currSource->capacity();
                    }
					int showDataFrameBegin = 0;
                    int xOff = (int)(xPos * (m_showDataRange.frameCount() - 1LL) / (width - 1.0) + 0.5);
					if (xOff < m_showDataRange.frameBegin())
					{
						showDataFrameBegin = m_showDataRange.frameBegin() - xOff;
					}
                    if (showDataFrameBegin + showDataFrameCount > m_currSource->capacity())
                    {
                        showDataFrameBegin = m_currSource->capacity() - showDataFrameCount;
                    }
                    range.update(showDataFrameBegin, showDataFrameCount);
                }
            }
        }
    }
    //执行横向鼠标纵向缩放。
    inline void doHMouseWheelV(WRChartSampleRange& range, int yPos,  int delta, int height) const
    {
        if (yPos >= 0 && yPos < height)
        {
            if (delta > 0)
            {
                if (m_showDataRange.pointCount() > 2)
                {
                   int  showDataPointCount = m_showDataRange.pointCount() / 2;
                    if (showDataPointCount < 2)
                    {
                        showDataPointCount = 2;
                    }
                    int yOff = m_showDataRange.pointCount() - (int)(yPos * (m_showDataRange.pointCount() - 1LL) / (height - 1.0) + 0.5);
                    int showDataPointBegin = m_showDataRange.pointBegin() + yOff / 2;
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
                        int yOff = m_showDataRange.pointCount() - (int)(yPos * (m_showDataRange.pointCount() - 1LL) / (height - 1.0) + 0.5);
						if (yOff < m_showDataRange.pointBegin())
						{
							showDataPointBegin = m_showDataRange.pointBegin() - yOff;
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

    //执行纵向鼠标水平缩放。
    inline void doVMouseWheelH(WRChartSampleRange& range, int xPos,  int delta, int width) const
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
    inline void doVMouseWheelV(WRChartSampleRange& range, int yPos,  int delta, int height) const
    {
        if (yPos >= 0 && yPos < height)
        {
            if (delta > 0)
            {
                if (m_showDataRange.frameCount() > 2)
                {
                    int showDataFrameCount = m_showDataRange.frameCount() / 2;
                    if (showDataFrameCount < 2)
                    {
                        showDataFrameCount = 2;
                    }
                    int yOff = (int)(yPos * (m_showDataRange.frameCount() - 1LL) / (height - 1.0) + 0.5);
                    int showDataFrameBegin = m_showDataRange.frameBegin() +yOff / 2;
                    if (showDataFrameBegin + showDataFrameCount > m_currSource->capacity())
                    {
                        showDataFrameBegin = m_currSource->capacity() - showDataFrameCount;
                    }
                    range.update(showDataFrameBegin, showDataFrameCount);
                }
            }
            else
            {
                if (m_currSource->capacity() != m_showDataRange.frameCount())
                {
                    int showDataFrameCount = m_showDataRange.frameCount() * 2;
                    if (showDataFrameCount >= m_currSource->capacity())
                    {
                        showDataFrameCount = m_currSource->capacity();
                    }
					int showDataFrameBegin = 0;
                    int yOff = (int)(yPos * (m_showDataRange.frameCount() - 1LL) / (height - 1.0) + 0.5);
					if (yOff < m_showDataRange.frameBegin())
					{
						showDataFrameBegin = m_showDataRange.frameBegin() - yOff;
					}
                    if (showDataFrameBegin + showDataFrameCount > m_currSource->capacity())
                    {
                        showDataFrameBegin = m_currSource->capacity() - showDataFrameCount;
                    }
                    range.update(showDataFrameBegin, showDataFrameCount);
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
	//初始化默认瀑布图控件。
	explicit WRWaterfallControl(bool vertical = true);

	//初始化瀑布图控件，使用8位有符号整数数据源。
	WRWaterfallControl(const WRWaterfallInitParams<signed char>& initArgs, bool vertical = true);
	//初始化瀑布图控件，使用8位无符号整数数据源。
	WRWaterfallControl(const WRWaterfallInitParams<unsigned char>& initArgs, bool vertical = true);

	//初始化瀑布图控件，使用16位有符号整数数据源。
	WRWaterfallControl(const WRWaterfallInitParams<short>& initArgs, bool vertical = true);
	//初始化瀑布图控件，使用16位无符号整数数据源。
	WRWaterfallControl(const WRWaterfallInitParams<unsigned short>& initArgs, bool vertical = true);

	//初始化瀑布图控件，使用32位有符号整数数据源。
	WRWaterfallControl(const WRWaterfallInitParams<int>& initArgs, bool vertical = true);
	//初始化瀑布图控件，使用32位无符号整数数据源。
	WRWaterfallControl(const WRWaterfallInitParams<unsigned int>& initArgs, bool vertical = true);

	//初始化瀑布图控件，使用32位浮点数数据源。
	WRWaterfallControl(const WRWaterfallInitParams<float>& initArgs, bool vertical = true);
	//初始化瀑布图控件，使用64位浮点数数据源。
	WRWaterfallControl(const WRWaterfallInitParams<double>& initArgs, bool vertical = true);

	//初始化瀑布图控件，使用8位有符号整数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRWaterfallInitParams<signed char>& initArgs);
	//初始化瀑布图控件，使用8位无符号整数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRWaterfallInitParams<unsigned char>& initArgs);

	//初始化瀑布图控件，使用16位有符号整数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRWaterfallInitParams<short>& initArgs);
	//初始化瀑布图控件，使用16位无符号整数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRWaterfallInitParams<unsigned short>& initArgs);

	//初始化瀑布图控件，使用32位有符号整数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRWaterfallInitParams<int>& initArgs);
	//初始化瀑布图控件，使用32位无符号整数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRWaterfallInitParams<unsigned int>& initArgs);

	//初始化瀑布图控件，使用32位浮点数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRWaterfallInitParams<float>& initArgs);
	//初始化瀑布图控件，使用64位浮点数数据源。该方法可以在多线程环境中使用。
	void initialize(const WRWaterfallInitParams<double>& initArgs);

    //清除数据。
    void clearData(void);
	//写入数据。该方法可以在多线程环境中使用。
	void writeData(const void* specBuffer, const long long* timeBuffer, int dataFrames);

	//获取横坐标轴元素。
    inline WRWaterfallHAxisElement* hAxis(void) const
    {
        return m_hAxis;
    }
    //获取纵坐标轴元素。
    inline WRWaterfallVAxisElement* vAxis(void) const
    {
        return m_vAxis;
    }
    //获取横向滚动条元素。
    inline WRWaterfallHScrollElement* hScroll(void) const
    {
        return m_hScroll;
    }
    //获取纵向滚动条元素。
    inline WRWaterfallVScrollElement* vScroll(void) const
    {
        return m_vScroll;
    }
    //获取数据视图元素。
    inline WRWaterfallDataViewElement* dataView(void) const
    {
        return m_dataView;
    }

	//获取是否纵向显示。
    inline bool vertical(void) const
    {
        return readFlag(WRWATERFALLCONTROL_VERTICAL);
    }
    //设置是否纵向显示。
    bool vertical(bool value);

    //获取是否暂停数据。
    inline bool holdStatus(void) const
    {
        return readFlag(WRWATERFALLCONTROL_HOLDSTATUS);
    }
    //设置是否暂停数据。
    bool holdStatus(bool value);

	//获取背景颜色。
    inline WRColor backColor(void) const
    {
        return m_backColor;
    }
    //设置背景颜色。
    bool backColor(WRColor value);

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
    //获取数据差异值。
    inline double dataDifValue(void) const
    {
		return m_currSource->difValue();
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
	
	//获取数据帧上限。
    inline int dataFrameLimit(void) const
    {
		return m_currSource->capacity();
    }
	//获取数据帧总量。
	inline long long dataFrameTotal(void) const
	{
		return m_currSource->frames();
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

    //获取显示数据帧起始。
    inline int showDataFrameBegin(void) const
    {
        return m_showDataRange.frameBegin();
    }
    //获取显示数据帧数量。
    inline int showDataFrameCount(void) const
    {
        return m_showDataRange.frameCount();
    }
    //获取显示数据帧结束。
    inline int showDataFrameEnd(void) const
    {
        return m_showDataRange.frameEnd();
    }

    //获取显示数据范围。
    inline const WRWaterfallDataRange& showDataRange(void) const
    {
        return m_showDataRange;
    }
    //设置显示数据范围。
    bool showDataRange(const WRWaterfallDataRange& value);

    //获取数据点显示数据范围。
    inline const WRChartSampleRange& showDataPointRange(void) const
    {
        return m_showDataRange.pointRange();
    }
    //设置数据点显示数据范围。
    bool showDataPointRange(const WRChartSampleRange& value);

    //获取数据帧显示数据范围。
    inline const WRChartSampleRange& showDataFrameRange(void) const
    {
        return m_showDataRange.frameRange();
    }
    //设置数据帧显示数据范围。
    bool showDataFrameRange(const WRChartSampleRange& value);

	//获取指定位置的数据点，如果超出数据视图范围，则返回False。
	inline bool getDataPointAt(int p, int* v) const
	{
		if (vertical())
		{
			int x = p - m_dataView->left();
			if (x >= 0 && x < m_dataView->width())
			{
				*v = getVDataPointAt(m_dataView->width(), x);
				return true;
			}
			return false;
		}
		else
		{
			int y = p - m_dataView->top();
			if (y >= 0 && y < m_dataView->height())
			{
				*v = getHDataPointAt(m_dataView->height(), y);
				return true;
			}
			return false;
		}
	}
	//获取指定位置的数据点，如果超出数据视图范围，则返回False。
	inline bool getDataPointAt(const WRPoint& p, int* v) const
	{
		if (vertical())
		{
			int x = p.x() - m_dataView->left();
			if (x >= 0 && x < m_dataView->width())
			{
				*v = getVDataPointAt(m_dataView->width(), x);
				return true;
			}
			return false;
		}
		else
		{
			int y = p.y() - m_dataView->top();
			if (y >= 0 && y < m_dataView->height())
			{
				*v = getHDataPointAt(m_dataView->height(), y);
				return true;
			}
			return false;
		}
	}

	//获取指定位置的数据帧, 如果超出数据视图范围，则返回False。
	inline bool getDataFrameAt(int p, int* v) const
	{
		if (vertical())
		{
			int y = p - m_dataView->top();
			if (y >= 0 && y < m_dataView->height())
			{
				*v = getVDataFrameAt(m_dataView->height(), y);
				return true;
			}
			return false;
		}
		else
		{
			int x = p - m_dataView->left();
			if (x >= 0 && x < m_dataView->width())
			{
				*v = getHDataFrameAt(m_dataView->width(), x);
				return true;
			}
			return false;
		}
	}
	//获取指定位置的数据帧, 如果超出数据视图范围，则返回False。
	inline bool getDataFrameAt(const WRPoint& p, int* v) const
	{
		if (vertical())
		{
			int y = p.y() - m_dataView->top();
			if (y >= 0 && y < m_dataView->height())
			{
				*v = getVDataFrameAt(m_dataView->height(), y);
				return true;
			}
			return false;
		}
		else
		{
			int x = p.x() - m_dataView->left();
			if (x >= 0 && x < m_dataView->width())
			{
				*v = getHDataFrameAt(m_dataView->width(), x);
				return true;
			}
			return false;
		}
	}

	//获取指定位置的数据值。
	inline double getDataValueAt(int frameIndex, int pointIndex) const
	{
		return m_currSource->getValue(frameIndex, pointIndex);
	}

	//获取指定数据点的频率值。
	inline long long getFreqValueAt(int pointIndex) const
	{
		return m_currSource->getFreqValue(pointIndex);
	}
	//获取指定位置的频率值，如果超出数据视图范围，则返回False。
	inline bool getFreqValueAt(int p, long long* v) const
	{
		if (vertical())
		{
			int x = p - m_dataView->left();
			if (x >= 0 && x < m_dataView->width())
			{
				int i = getVDataPointAt(m_dataView->width(), x);
				*v = m_currSource->getFreqValue(i);
				return true;
			}
			return false;
		}
		else
		{
			int y = p - m_dataView->top();
			if (y >= 0 && y < m_dataView->height())
			{
				int i = getHDataPointAt(m_dataView->height(), y);
				*v = m_currSource->getFreqValue(i);
				return true;
			}
			return false;
		}
	}
	//获取指定位置的频率值，如果超出数据视图范围，则返回False。
	inline bool getFreqValueAt(const WRPoint& p, long long* v) const
	{
		if (vertical())
		{
			int x = p.x() - m_dataView->left();
			if (x >= 0 && x < m_dataView->width())
			{
				int i = getVDataPointAt(m_dataView->width(), x);
				*v = m_currSource->getFreqValue(i);
				return true;
			}
			return false;
		}
		else
		{
			int y = p.y() - m_dataView->top();
			if (y >= 0 && y < m_dataView->height())
			{
				int i = getHDataPointAt(m_dataView->height(), y);
				*v = m_currSource->getFreqValue(i);
				return true;
			}
			return false;
		}
	}

	//获取指定数据帧的时间值。
	inline long long getTimeValueAt(int frameIndex) const
	{
		return m_currSource->getTimeValue(frameIndex);
	}
	//获取指定位置的时间值，如果超出数据视图范围，则返回False。
	inline bool getTimeValueAt(int p, long long* v) const
	{
		if (vertical())
		{
			int y = p - m_dataView->top();
			if (y >= 0 && y < m_dataView->height())
			{
				int i = getVDataFrameAt(m_dataView->height(), y);
				*v = m_currSource->getTimeValue(i);
				return true;
			}
			return false;
		}
		else
		{
			int x = p - m_dataView->left();
			if (x >= 0 && x < m_dataView->width())
			{
				int i = getHDataFrameAt(m_dataView->width(), x);
				*v = m_currSource->getTimeValue(i);
				return true;
			}
			return false;
		}
	}
	//获取指定位置的时间值，如果超出数据视图范围，则返回False。
	inline bool getTimeValueAt(const WRPoint& p, long long* v) const
	{
		if (vertical())
		{
			int y = p.y() - m_dataView->top();
			if (y >= 0 && y < m_dataView->height())
			{
				int i = getVDataFrameAt(m_dataView->height(), y);
				*v = m_currSource->getTimeValue(i);
				return true;
			}
			return false;
		}
		else
		{
			int x = p.x() - m_dataView->left();
			if (x >= 0 && x < m_dataView->width())
			{
				int i = getHDataFrameAt(m_dataView->width(), x);
				*v = m_currSource->getTimeValue(i);
				return true;
			}
			return false;
		}
	}

    //添加数据帧线条。
    WRWaterfallDataFrameLineElement* addDataFrameLine(int position);
	//添加数据点线条。
    WRWaterfallDataPointLineElement* addDataPointLine(int position);

    //移除测量元素。
    void remove(WRWaterfallGaugeElement** element);
};

//#pragma warning(pop)

#endif //WRWATERFALLCONTROL
