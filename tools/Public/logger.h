#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <string>

#include "define_tools_api.h"

namespace Logger
{

#define MAX_LEN 1024

    //此宏展开后，类似于printf("%d" "%d", 1, 2); 谨记 printf("%d""%d", 1, 1) 是不合理的需要在两个"" "" 中间空一格, 不需要使用 ## 连接符
#define Log(fmt,...) \
    LogPrintf("[%s:%d] " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LogStr(fmt) \
    LogPrintf("[%s:%d] %s", __FUNCTION__, __LINE__, fmt)
 
 
    TOOLS_API int LogInit(std::string logDir = "");
 
    TOOLS_API void LogEnd();
 
    TOOLS_API void LogPrintf(const char *fmt, ...);
    
} // namespace Logger
