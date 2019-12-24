#ifndef COMMAN_H
#define COMMAN_H

#include <QDebug>
#include <QVector>

#ifdef LINUX
#include <unistd.h>
#define msleep(msec) usleep(msec*1000)
#else

#endif

enum OPT_RET
{
    OPT_UNKNOW_ERROR = -1,		// 未知错误
    OPT_SUCCESS = 0,			// 操作成功执行
    OPT_RECV_FAIL,
    OPT_DEV_CONNECT_FAIL,		// 设备连接失败
    OPT_DEV_NOT_CONNECTED,		// 设备尚未连接
    OPT_SEND_COMMAND_FAIL,		// 发送指令失败
    OPT_RECV_ECHO_TIMEOUT,		// 接收回传超时
    OPT_INDEX_OUT_OF_RANGE,		// 下标越界
    OPT_SAVE_FILE_FALL,
    OPT_USB_DATA_FAIL,
    OPT_USB_POINT_ERROR,
    OPT_RBW_PARA_FAIL,			// RBW参数错误
    OPT_POINT_PARA_FAIL,		// 点数参数错误
    OPT_ATT_PARA_FAIL,			// 衰减器参数错误
};
//常量字符
const QString LFCR="\r\n";
const quint16 WAIT_TIME = 100;
const QString SYSTEM_ECHO_ON = "SYSTem:COMMunicate:ECHO ON";

class CComman
{
public:
    CComman();
    static double max(QVector<double> _dataVec,uint64_t & pox);


};
extern volatile bool g_bIsRun;

#endif // COMMAN_H
