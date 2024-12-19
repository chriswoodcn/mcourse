//xlog.h
#ifndef XLOG_H
#define XLOG_H
//__declspec(dllexport)
//__declspec(dllexport) ����XLog��ĺ�����lib�ļ���
// xlog���ļ����� dllexport
// test_xlog ���� dllimport
#ifndef _WIN32 //linux mac unix Android
    #define XCPP_API
#else //windows
    #ifdef xlog_STATIC  //��̬��
        #define XCPP_API
    #else               //��̬��
        #ifdef xlog_EXPORTS
            #define XCPP_API __declspec(dllexport) //����Ŀ����
        #else
            #define XCPP_API __declspec(dllimport) //���ÿ���Ŀ����
        #endif
    #endif
#endif
class XCPP_API XLog
{
public:
	XLog();
};
#endif
/*
102cmake_lib/
������ CMakeLists.txt
������ test_xlog
��?? ������ CMakeLists.txt
��?? ������ test_xlog.cpp
������ xlog
    ������ CMakeLists.txt
    ������ xlog.cpp
    ������ xlog.h

*/