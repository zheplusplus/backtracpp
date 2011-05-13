#include <cxxabi.h>
#include <cstdlib>
#include <stdexcept>
#include <sstream>

#include "demangle.h"

using namespace trac;

namespace {

    struct auto_string {
        explicit auto_string(char* string)
            : _string(string)
        {}

        ~auto_string()
        {
            free(_string);
        }

        char const* get() const
        {
            return _string;
        }
    private:
        char* const _string;
    };

}

static std::string demangle_func_name(std::string const& name)
{
    int status = -1;
    auto_string demangled_name(abi::__cxa_demangle(name.c_str(), NULL, NULL, &status));
    switch (status) {
    case -1:
        throw std::bad_alloc();
    case -2:
        return name;
    default:
        return std::string(demangled_name.get());
    }
}

static int hex_from_str(std::string const& str)
{
    int result = 0;
    for (std::string::const_iterator i = str.begin(); str.end() != i; ++i) {
        result *= 16;
        if ('0' <= *i && *i <= '9') {
            result += (*i - '0');
        } else {
            result += (*i - 'a') + 10;
        }
    }
    return result;
}

static std::string::const_iterator module_name(std::string::const_iterator iter)
{
    while ('(' != *iter++)
        ;
    return iter;
}

static std::string::const_iterator func_name(std::string::const_iterator iter)
{
    for (; '+' != *iter && ')' != *iter; ++iter)
        ;
    return iter;
}

static std::string::const_iterator func_offset(std::string::const_iterator iter)
{
    while (')' != *iter++)
        ;
    return iter;
}

static std::string::const_iterator func_addr(std::string::const_iterator iter)
{
    while (']' != *iter++)
        ;
    return iter;
}

std::string frame::str() const
{
    std::stringstream ss;
    ss << std::hex << module << ' ' << address << ' ' << func << ' ' << offset;
    return ss.str();
}

frame trac::demangle(std::string const& frame_info)
{
    std::string::const_iterator end = frame_info.begin();
    std::string::const_iterator begin = end;

    end = module_name(end) - 1;
    std::string module(begin, end);
    ++end;
    begin = end;

    end = func_name(end);
    std::string func(demangle_func_name(std::string(begin, end)));
    ++end;
    begin = end;

    int offset = 0;
    if (' ' != *end) {
        end = func_offset(end) - 1;
        offset = hex_from_str(std::string(begin + 2, end));
        while ('[' != *end++)
            ;
        begin = end;
    }

    end = func_addr(end) - 1;
    int address = hex_from_str(std::string(begin + 2, end));

    return frame(module, address, func, offset);
}
