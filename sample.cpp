#include <iostream>
#include <algorithm>

#include "trace.h"

struct printer {
    void operator()(trac::frame const& frame) const
    {
        std::cout << frame.str() << std::endl;
    }
};

static void print(std::vector<trac::frame> const& frames)
{
    std::for_each(frames.begin(), frames.end(), printer());
}

void test_0()
{
    print(trac::stacktrace());
    std::cout << std::endl;
}

void test_1()
{
    test_0();
    print(trac::stacktrace());
    std::cout << std::endl;
}

int main()
{
    test_1();
    print(trac::stacktrace());
    return 0;

}
