#include "map_testing.hpp"
#include <functional>

TEST(test_map_default_ctor)
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

TEST(test_map_custom_comp_ctor)
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

TEST(test_map_range_ctor)
{
    unsigned baseN = 1000000;

    std::vector<FT_CONTAINER::pair<unsigned, unsigned> > vp;

    for (unsigned i = 0; i != baseN; ++i) {
        vp.push_back(FT_CONTAINER::make_pair(i, i));
    }

    // copy what has been put in the vector, except first and last pairs
    map<unsigned, unsigned> m(vp.begin() + 1, vp.end() - 1);

    unsigned i = 1;

    for (map<unsigned, unsigned>::const_iterator cit = m.begin();
         cit != m.end();
         ++cit) {
        p_assert_eq(cit->first, i);
        p_assert_eq(cit->second, i);
        ++i;
    }

    p_assert_eq(i, baseN - 1);

    return 0;
}

