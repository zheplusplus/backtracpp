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

int main(int, char**)
{
    test();
    print(trac::stacktrace());

    base b;
    inherit i;

    base* p = &b;
    p->echo();
    p = &i;
    p->echo();

    return 0;

}
