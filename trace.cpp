#include <execinfo.h>
#include <cstdlib>
#include <list>
#include <stdexcept>

#include "trace.h"

using namespace trac;

static int const MAX_FRAMES = 256;

namespace {

    struct auto_strings {
        explicit auto_strings(char** strings)
            : _strings(strings)
        {}

        ~auto_strings()
        {
            free(_strings);
        }

        char const* const* get() const
        {
            return _strings;
        }
    private:
        char** const _strings;
    };

}

static std::list<frame> package(char const* const* strings, int size)
{
    std::list<frame> result;
    for (int i = 0; i < size; ++i) {
        result.push_back(demangle(strings[i]));
    }
    return result;
}

std::vector<frame> trac::stacktrace()
{
    void* buffer[MAX_FRAMES];
    int nptrs = backtrace(buffer, MAX_FRAMES);
    auto_strings strings(backtrace_symbols(buffer, nptrs));
    if (NULL == strings.get()) {
        throw std::runtime_error("backtrace_symbols error");
    }
    std::list<frame> frames(package(strings.get(), nptrs));
    return std::vector<frame>(frames.begin(), frames.end());
}
