#include <cstring>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "trace.h"
#include "sig-handler.h"

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

void test(int)
{
    trac::print_trace(std::cout);
    std::cout << std::endl;
}

void test()
{
    test(0);
    trac::print_trace_br();
}

struct base {
    virtual void echo() const
    {
        trac::print_trace_br();
    }

    virtual ~base() {}
};

struct inherit
    : public base
{
    void echo() const
    {
        trac::print_trace_br();
    }
};

int test_divide_by_0()
{
    int x;
    int y = 10;
    memset(&x, 0, sizeof(x));
    return y / x;
}

void access_nul()
{
    char* x;
    memset(&x, 0, sizeof(char*));
    std::cout << std::endl;
    std::cout << *x << std::endl;
    std::cout << std::endl;
}

int main(int, char**)
{
    std::set_terminate(access_nul);
    trac::trace_on_div_0();
    trac::trace_on_seg_fault();

    test();
    print(trac::stacktrace());

    base b;
    inherit i;

    base* p = &b;
    p->echo();
    p = &i;
    p->echo();

    return test_divide_by_0();
}
