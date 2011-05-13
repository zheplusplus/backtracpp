#include <gtest/gtest.h>

#include "../demangle.h"

TEST(Demangle, CppFrame)
{
    trac::frame frame(trac::demangle("module-name(_Z1dv+0x22) [0x40000000]"));
    EXPECT_EQ("module-name", frame.module);
    EXPECT_EQ(0x40000000, frame.address);
    EXPECT_EQ("d()", frame.func);
    EXPECT_EQ(0x22, frame.offset);
}

TEST(Demangle, CFrame)
{
    trac::frame frame(trac::demangle("module-name(main+0xcc) [0xabcdef0]"));
    EXPECT_EQ("module-name", frame.module);
    EXPECT_EQ(0xabcdef0, frame.address);
    EXPECT_EQ("main", frame.func);
    EXPECT_EQ(0xcc, frame.offset);
}

TEST(Demangle, FrameNameMissing)
{
    trac::frame frame(trac::demangle("module-name() [0x12345678]"));
    EXPECT_EQ("module-name", frame.module);
    EXPECT_EQ(0x12345678, frame.address);
    EXPECT_EQ("", frame.func);
    EXPECT_EQ(0, frame.offset);
}
