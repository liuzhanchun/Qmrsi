#pragma once
#ifndef WRDIRMAPDATAPALETTE
#define WRDIRMAPDATAPALETTE

#include <WRCharting/WRGlobal.h>
#include <WRCharting/WRColor.h>
#include <QRgb>
#include <QAtomicInt>

//#pragma warning(push)
//#pragma warning(disable:4251)

//表示向频图数据调色板。
class WRCHARTING_CLASS WRDirMapDataPalette
{
	friend class WRDirMapDataViewElement;

private:
    //引用计数。
    QAtomicInt m_refCnt;
    //颜色表。
    QRgb m_table[256];
    //颜色集合。
    WRColor* m_list;
    //颜色数量。
    int m_size;
	
    //初始化颜色表。
    void initialize(void);

    //初始化默认颜色表。
    inline WRDirMapDataPalette()
        : m_refCnt(1)
    {
        //基本信息
        m_size = 6;
        m_list = new WRColor[6];
        {
            m_list[0] = WRColor(0x00, 0x00, 0x00);	//Black
            m_list[1] = WRColor(0x00, 0x00, 0xFF);	//Blue
            m_list[2] = WRColor(0x80, 0x00, 0x80);	//Purple
            m_list[3] = WRColor(0xFF, 0x00, 0x00);	//Red
            m_list[4] = WRColor(0xFF, 0xFF, 0x80);
            m_list[5] = WRColor(0xFF, 0xFF, 0xFF);   //White
        }
        //初始颜色表
        initialize();
    }
    //清理当前对象所占用的相关资源。
    ~WRDirMapDataPalette();

	//禁用复制构造函数。
	WRDirMapDataPalette(const WRDirMapDataPalette& other);
	//禁用赋值操作符。
	WRDirMapDataPalette& operator=(const WRDirMapDataPalette& other);

public:
    //初始化色彩。
    inline WRDirMapDataPalette(const WRColor* list, int size)
        : m_refCnt(1)
    {
        //基本信息
        m_size = size;
        m_list = new WRColor[size];
        for(int i = 0; i < size; ++i)
        {
			m_list[i].update(list[i]);
		}
        //初始颜色表
        initialize();
	}

    //添加对象引用。
    inline void addRef(void)
    {
        m_refCnt.ref();
    }
    //释放对象引用, 如果引用计数为0，则删除对象，返回True，否则返回False。
    inline bool release(void)
    {
        if (!m_refCnt.deref())
        {
            delete this;
            return true;
        }
        return false;
    }

    //获取颜色数量。
    inline int count(void) const
    {
        return m_size;
    }
    //获取指定索引处的颜色。
    inline const WRColor& color(int index) const
    {
        return m_list[index];
    }
    //获取指定索引处的颜色。
    inline const WRColor& operator[] (int index) const
    {
        return m_list[index];
    }

public:
    //获取默认调色板。
    static WRDirMapDataPalette* defaultPalette(void);
};

//#pragma warning(pop)

#endif //WRDIRMAPDATAPALETTE
