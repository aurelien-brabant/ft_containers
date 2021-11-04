#include "map_testing.hpp"

TEST(test_map_greater_cmp)
{
    map<unsigned, std::string, std::greater<unsigned> > m;

    m[1] = "Hello";
    m[4] = "World";

    p_assert_eq(m.begin()->second, "World");

    return 0;
}

TEST(test_map_equal_cmp)
{
    map<unsigned, std::string, std::equal_to<unsigned> > m;

    m[4] = "Hello";
    m[8] = "World";
    m[12] = "Hey";

    p_assert_eq(m.size(), 1);
    p_assert_eq(m.begin()->second, "Hey");

    return 0;
}
