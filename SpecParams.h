#ifndef SPECPARAMS
#define SPECPARAMS

//表示频谱参数。
struct SpecParams
{
    //频率起止。
    long long freqBegin;
    //频率终止。
    long long freqEnd;
    //数据长度。
    int dataSize;
    //偏移值。
    short offValue;
    //最小值。
    unsigned char minValue;
    //最大值。
    unsigned char  maxValue;
    //是否封闭。
    bool isClosed;

    //获取指定索引处的频率。
    long long getFreqValue(int pointIndex)
    {
        if (isClosed)
        {
            return freqBegin + pointIndex * (freqEnd - freqBegin) / (dataSize - 1);
        }
        else
        {
            return freqBegin + pointIndex * (freqEnd - freqBegin) / dataSize;
        }
    }

    bool initilize(const char* buf)
    {
        const char* p = &buf[32];
        freqBegin = *(long long*)p;
        freqEnd = *((long long*)p + 1);
        dataSize = *(int*)(p + 16);
        minValue = *(unsigned char*)(p + 20);
        maxValue = *(unsigned char*)(p + 21);
        offValue = *(short*)(p + 22);
        isClosed = *(int*)(p + 24) != 0;

        return true;
    }
};

#endif // SPECPARAMS
