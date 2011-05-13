#ifndef __BACKTRACPP_TRACE_H__
#define __BACKTRACPP_TRACE_H__

#include <vector>

#include "demangle.h"

namespace trac {

    std::vector<frame> stacktrace();

}

#endif /* __BACKTRACPP_TRACE_H__ */
