#include "backtrace.h"

#ifdef _WIN32
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "DbgHelp.lib")
#else
#include <execinfo.h>
#endif // _WIN32

#include <string.h>

#include "logger.h"

namespace Backtrace
{

#ifdef _WIN32

void ShowTraceStack(std::string briefInfo)
{
    static const int MAX_STACK_FRAMES = 12;
    void *pStack[MAX_STACK_FRAMES];
    static char szFrameInfo[STACK_INFO_LEN];

    std::string ret = std::string("[backtrace] ") + briefInfo + '\n';

    HANDLE process = GetCurrentProcess();
    SymInitialize(process, NULL, TRUE);
    WORD frames = CaptureStackBackTrace(0, MAX_STACK_FRAMES, pStack, NULL);

    for (WORD i = 0; i < frames; ++i) {
        DWORD64 address = (DWORD64)(pStack[i]);

        DWORD64 displacementSym = 0;
        char buffer[sizeof(SYMBOL_INFO)+MAX_SYM_NAME * sizeof(TCHAR)];
        PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
        pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        pSymbol->MaxNameLen = MAX_SYM_NAME;

        DWORD displacementLine = 0;
        IMAGEHLP_LINE64 line;
        // SymSetOptions(SYMOPT_LOAD_LINES);
        line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

        bool bSymFromAddr = SymFromAddr(process, address, &displacementSym, pSymbol);
        bool bSymGetLineFromAddr64 = SymGetLineFromAddr64(process, address, &displacementLine, &line);
        if (bSymFromAddr)
        {
            snprintf(szFrameInfo, sizeof(szFrameInfo), "\t[ %s() (0x%x)\n", 
                pSymbol->Name, pSymbol->Address);
        }
        if (bSymGetLineFromAddr64)
        {
            snprintf(szFrameInfo, sizeof(szFrameInfo), "\t\tat %s:%d ]\n", 
                line.FileName, line.LineNumber);
        }
        if (!bSymFromAddr && !bSymGetLineFromAddr64)
        {
            snprintf(szFrameInfo, sizeof(szFrameInfo), "\terror: %d\n", GetLastError());
        }

        ret += szFrameInfo;
    }

    Logger::LogStr(ret.c_str());
}

#else // _WIN32

void ShowTraceStack(std::string briefInfo)
{
    std::string ret = std::string("[backtrace] ") + briefInfo + '\n';

    int BT_BUF_SIZE = 32;
    int nptrs;
    void *buffer[BT_BUF_SIZE];
    char **strings;

    nptrs = backtrace(buffer, BT_BUF_SIZE);
    strings = backtrace_symbols(buffer, nptrs);

    if (strings == nullptr) {
        perror("backtrace_symbols");
        printf("backtrace_symbols error\n");
        return ;
    }

    for (int i = 0; i < nptrs; ++i) {
        ret = ret + '\t' + strings[i] + '\n';
    }
    free(strings);
    
    Logger::LogStr(ret.c_str());
}

#endif // _WIN32


} // namespace Backtrace
