#include "pair_testing.hpp"

TEST(test_make_pair)
{
    pair<std::string, std::string> p = make_pair("42", "21");

    p_assert_eq(p.first, "42");
    p_assert_eq(p.second, "21");

    return 0;
}
