#pragma once


#ifdef _WIN32
    #define TOOLS_API __declspec(dllimport)
#else 
    #define TOOLS_API __attribute__ ((visibility ("default")))
#endif
