// xlog.h
#ifndef XLOG_H
#define XLOG_H

#ifndef _WIN32
  //unix平台什么都不做
  #define XCPP_API 
#else
  //win32平台根据xlog_EXPORTS标识进行不同定义
  #ifdef xlog_EXPORTS
    #define XCPP_API __declspec(dllexport) //库项目调用
  #else
    #define XCPP_API __declspec(dllimport) //其他目标调用
  #endif
#endif
class XCPP_API XLog {
public:
  XLog();
};
#endif