#include "../lib/some_lib.hpp"
#include <gtest/gtest.h>

TEST(SomeLib, CheckConstruct)
{
    some_lib lib_(5);
    ASSERT_EQ(lib_.Get_value(), 5);
}

TEST(SomeLib, SetNewValue)
{
    some_lib lib_(0);
    lib_.Set_value(456);

    ASSERT_EQ(lib_.Get_value(), 456);
}
