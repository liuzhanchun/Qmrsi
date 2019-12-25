#pragma once
#ifndef WRCHARTTEXT
#define WRCHARTTEXT

#include <stdio.h>
#include <string.h>
#include <qstring.h>

//#pragma warning(push)
//#pragma warning(disable:4996)

namespace WRText
{
    //对字符序列进行转换复制。
    inline void copy(char* pStr, QChar* pBuf, int nLen)
    {
        for(int i = 0; i < nLen; ++i)
        {
            pBuf[i] = pStr[i];
        }
    }

	//去掉小数点后的0值。
    inline int trimDecimal(char* pBuf, int nLen)
	{
        for (int i = nLen - 1; i >= 0; --i)
		{
			if (pBuf[i] == '.')
			{
				--nLen;
				break;
			}
			if (pBuf[i] == '0')
			{
				--nLen;
			}
			else
			{
				break;
			}
		}
		return nLen;
	}

	//将指定的值格式化字符串。
    inline int toString(double fVal, char* pBuf, bool trim = true)
	{
        int len = sprintf(pBuf, "%.6f", fVal);
		if (trim)
		{
			len = trimDecimal(pBuf, len);
		}
		return len;
	}

	//将指定的时间值格式化字符串。
    inline int toTimeString(long long lVal, char* pBuf)
	{
		int hours = (int)((lVal / 36000000000LL) % 24);
		int minutes = (int)((lVal / 600000000LL) % 60);
		int seconds = (int)((lVal / 10000000LL) % 60);
		int others = (int)((lVal / 10LL) % 1000000);
        return sprintf(pBuf, "%.2d:%.2d:%.2d.%.6d", hours, minutes, seconds, others);
	}

	//将指定的频率值格式化字符串。
    inline int toFreqString(long long lVal, char* pBuf, bool trim = true)
	{
		if (lVal < 1000LL)
		{
            return sprintf(pBuf, "%dHz", (int)lVal);//Hz
		}
		else if (lVal < 1000000LL)
		{
			if (trim)
			{
                int len = sprintf(pBuf, "%.3f", lVal / 1000.0);//kHz
				len = trimDecimal(pBuf, len);
                strcpy(pBuf + len, "kHz");
				return len + 3;
			}
			else
			{
                return sprintf(pBuf, "%.3fkHz", lVal / 1000.0);//kHz
			}
		}
		else if (lVal < 1000000000LL)
		{
			if (trim)
			{
                int len = sprintf(pBuf, "%.6f", lVal / 1000000.0);//MHz
				len = trimDecimal(pBuf, len);
                strcpy(pBuf + len, "MHz");
				return len + 3;
			}
			else
			{
                return sprintf(pBuf, "%.6fMHz", lVal / 1000000.0);//MHzl
			}
		}
		else
		{
			if (trim)
			{
                int len = sprintf(pBuf, "%.9f", lVal / 1000000000.0);//GHz
				len = trimDecimal(pBuf, len);
                strcpy(pBuf + len, "GHz");
				return len + 3;
			}
			else
			{
                return sprintf(pBuf, "%.9fGHz", lVal / 1000000000.0);//GHz
			}
		}
	}
}

//#pragma warning(pop)

#endif //WRCHARTTEXT
