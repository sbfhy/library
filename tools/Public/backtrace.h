#pragma once

#include <stdio.h>
#include <string>

#include "define_tools_api.h"

namespace Backtrace
{

#if _MSC_VER
#define snprintf _snprintf
#endif

#define STACK_INFO_LEN 1024


TOOLS_API void ShowTraceStack(std::string briefInfo = "");

} // namespace Backtrace
