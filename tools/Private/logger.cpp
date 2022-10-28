#include "logger.h"

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#include <sys/stat.h>
#else
#include <unistd.h>
#include<sys/stat.h>
#include <errno.h>
#endif // _WIN23

#include <string>


namespace Logger
{

FILE *fd_log = nullptr;

bool Mkdir(const char* dir)
{
#ifdef _WIN32
    // _mkdir不能创建多级目录，这里只能创建单级目录
    if (0 != _access(dir, 00) 
        && 0 != _mkdir(dir)) {
#else
        if (0 != access(dir, F_OK) 
            && 0 != mkdir(dir, S_IRWXU | S_IRGRP | S_IROTH) 
            && errno != EEXIST) {
#endif // _WIN32
            printf("创建目录%s失败\n", dir);
            return false;
            }
        else {
            printf("创建目录%s成功\n", dir);
        }
        return true;
        }

    int LogInit(std::string logDir)
    {
        int ret = -1;

        if (!Mkdir(logDir.c_str())) 
            return ret;

        char logName[128];
        time_t timer = time(NULL); // 当前时间
        strftime(logName, 128, "%Y%m%d-%H-%M-%S.log", localtime(&timer));

        std::string logPath = logDir + '/' + logName;

        if( (fd_log = fopen(logPath.c_str(), "a+")) == nullptr) {
            printf("open file %s 失败!\n", logPath.c_str());
        }
        else {
            Log("open file %s 成功!", logPath.c_str());
            ret = 0;
        }
        return ret;
    }

    void LogEnd()
    {
        if (nullptr == fd_log)
            return ;
        Log("LogEnd");
        fclose(fd_log);
    }

    void LogPrintf(const char *fmt, ...)
    {
        if (nullptr == fd_log)
            return ;

        char message[MAX_LEN];
        time_t timer = time(NULL); // 当前时间.
        const int szTimerFormat = 21;
        strftime(message, szTimerFormat+1, "[%Y-%m-%d %H:%M:%S]", localtime(&timer));

        va_list args;
        va_start(args, fmt);
        vsnprintf(message + szTimerFormat, MAX_LEN - szTimerFormat, fmt, args);
        va_end(args);

        strcat(message, "\n");
        printf("%s", message);

        size_t sz_fwrite = fwrite(message, strlen(message), 1, fd_log);
        if (sz_fwrite != 1) {
            perror("LogPrintf error");
            return ;
        }
        fflush(fd_log);
    }

} // namespace Logger
