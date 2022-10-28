# 1 概述
简单整理的一些轮子，打包成库使用。   

# 2 sample
## 2.1 sample_tools
tools 的样例，测试了一下日志和堆栈打印。  

* win10 样例测试结果：  
```
创建目录log成功
[2022-10-28 16:46:19][Logger::LogInit:58] open file log/20221028-16-46-19.log 成功!
[2022-10-28 16:46:19][main:8] 测试日志格式化输出 999
[2022-10-28 16:46:19][Backtrace::ShowTraceStack:66] [backtrace] 测试堆栈打印
                at C:\myspace\git\mylibrary\tools\Private\backtrace.cpp:30 ]
                at C:\myspace\git\mylibrary\sample\sample_tools\main.cpp:11 ]
                at d:\a01\_work\12\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl:79 ]
                at d:\a01\_work\12\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl:288 ]
                at d:\a01\_work\12\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl:331 ]
                at d:\a01\_work\12\s\src\vctools\crt\vcstartup\src\startup\exe_main.cpp:17 ]
        [ BaseThreadInitThunk() (0xbaf57020)
        [ RtlUserThreadStart() (0xbb3a2630)

[2022-10-28 16:46:19][Logger::LogEnd:68] LogEnd
```

* centos8 样例测试结果：  
```
[2022-10-28 16:49:38][LogInit:58] open file log/20221028-16-49-38.log 成功!
[2022-10-28 16:49:38][main:8] 测试日志格式化输出 999
[2022-10-28 16:49:38][ShowTraceStack:94] [backtrace] 测试堆栈打印
    /data/hy/test/mylibrary/build/bin/Tools.so(_ZN9Backtrace14ShowTraceStackENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0x143) [0x7faa9058e74c]
    ./bin/SampleTools(main+0x99) [0x400c5f]
    /lib64/libc.so.6(__libc_start_main+0xf3) [0x7faa8f8bc493]
    ./bin/SampleTools(_start+0x2e) [0x400b0e]

[2022-10-28 16:49:38][LogEnd:68] LogEnd
```

# 3 tools
## 3.1 logger
c++日志打印，以当前时间新建日志文件，打日志到文件中。  

## 3.2 backtrace
c++堆栈打印，打印堆栈到日志文件中。  
在不适合用断点的情况下使用。  
