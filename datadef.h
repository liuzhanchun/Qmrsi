#ifndef DATADEF_H
#define DATADEF_H
#include <synchapi.h>
#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

const int 	RXNONE=0;
const int 	RXFFM = 1;
const int 	RXMSCAN = 2;
const int 	RXPSCAN = 3;
const int 	RXFSCAN = 4;
const int   RXDFIND = 5;
const int   RXIQ = 6;
const int   RXFPSCAN = 7;
const int   RXDDC = 8;
const int   RXTDOA = 9;
const int   RXMultiCH = 10;
const int   RXAirControlHand = 11;
const int   RXPSCANMULT = 12;
const int   SYSRESP = 101;      // 打频响


#pragma pack ( push, 1 )

struct FILE_HEAD //文件头
{
    char cVer;            //文件版本号
    int nFileLen;         //整个文件长度, 等于sizeof(要存的结构体)
    int nSaveTime;        //最后保存文件时间, 自1970年的秒数
    unsigned char ucCRC;  //后面所有字节的和 & 0xff
};
struct STRUCT_GENERIC_DATA
{
    unsigned int tag;
    unsigned int version;
    unsigned int time_s;
    unsigned int time_ns;
    unsigned int length;
};
struct STRUCT_ITU_DATA
{
    __int64 freq;//频率
    __int64 betabw;//beta%测量带宽值
    __int64 xdbbw; //xdB测量带宽值
    float am;//调幅度
    float am_pos; //正调幅度
    float am_neg; //负调幅度
    float fm;//调频频偏
    float fm_pos; //正调频频偏
    float fm_neg; //负调频频偏
    float pm; //调相角度
    float pm_pos; //调相最大角度
    float pm_neg; //调相最小角度
    int mod;//调制识别结果,值从-1开始依次对应Error, AM, FM, 2FSK, 4FSK, 2PSK, 4PSK, 2ASK, 4ASK, DSB, CW, VSB, Noise, UnKnown
};

struct WaveStatus
{
    __int64 StartFreq;
    __int64 StopFreq;
    __int64 Step; //扫描步进频率
    __int64 total; //扫描步进频率
    double RBW;
    double Ref;
    double Div;
    int Att;
    bool Ampli;
    int attif;
    int attrf;
    int amp;
    int rbw;
    int count;
    double scope;
    int fieldcount;
};
#pragma pack ( pop )

#endif // DATADEF_H
