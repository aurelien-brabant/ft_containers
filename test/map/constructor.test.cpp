#include "map_testing.hpp"
#include <functional>

int
test_map_default_ctor(Tester& tester)
{
    map<std::string, int> m;

    std::string s1("ab"), s2("abc");

    map<std::string, int>::value_type p1(s1, 5), p2(s2, 8);

    assert_expr(m.key_comp()(s1, s2) == true);
    assert_expr(m.key_comp()(s2, s1) == false);

    assert_expr(m.value_comp()(p1, p2) == true);
    assert_expr(m.value_comp()(p2, p1) == false);

    return 0;
}

int
test_map_custom_comp_ctor(Tester& tester)
{
    std::greater<std::string> greaterCmp;
    map<std::string, int, std::greater<std::string> > m(greaterCmp);

    std::string s1("ab"), s2("abc");

    map<std::string, int>::value_type p1(s1, 5), p2(s2, 8);

    assert_expr(m.key_comp()(s1, s2) == false);
    assert_expr(m.key_comp()(s2, s1) == true);

    assert_expr(m.value_comp()(p1, p2) == false);
    assert_expr(m.value_comp()(p2, p1) == true);

    return 0;
}