#include "pair_testing.hpp"
#include <string>

TEST(test_pair_default_ctor)
{
    pair<int, std::string> p;

    assert_expr(p.first == int());
    assert_expr(p.second == std::string());

    return 0;
}

TEST(test_pair_key_value_ctor)
{
    pair<std::string, int> p("42", 42);

    p_assert_eq(p.first, "42");
    p_assert_eq(p.second, 42);

    return 0;
}

TEST(test_pair_copy_ctor)
{
    pair<std::string, int> p("42", 42), p2(p);

    assert_expr(p.first == p2.first);
    assert_expr(p.second == p2.second);

    return 0;
}

TEST(test_pair_assignment_operator)
{
    pair<std::string, int> p("42", 42), p2("21", 21);

    p = p2;
    p2 = p;

    p_assert_eq(p.first, "21");
    p_assert_eq(p.second, 21);

    p_assert_eq(p2.first, "21");
    p_assert_eq(p2.second, 21);

    return 0;
}
