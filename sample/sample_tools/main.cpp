#include "logger.h"
#include "backtrace.h"

int main()
{
    Logger::LogInit("log");

    Logger::Log("测试日志格式化输出 %d", 999);
    Backtrace::ShowTraceStack("测试堆栈打印");

    Logger::LogEnd();

    return 0;
}