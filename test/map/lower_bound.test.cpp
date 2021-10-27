#include "map_testing.hpp"

TEST(test_map_lower_bound_one_match_only)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 100000;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    map<unsigned, unsigned>::iterator it = m.lower_bound(baseN - 1);

    assert_expr(it != m.end());

    p_assert_eq(it->first, baseN - 1);

    return 0;
}

TEST(test_map_lower_bound_find_smallest)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 100000;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    map<unsigned, unsigned>::iterator it = m.lower_bound(baseN / 2);

    assert_expr(it != m.end());

    p_assert_eq(it->first, baseN / 2);

    return 0;
}

TEST(test_map_lower_bound_not_found)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 100000;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    map<unsigned, unsigned>::iterator it = m.lower_bound(baseN);

    assert_expr(it == m.end());

    return 0;
}

TEST(test_map_lower_bound_const_overload)
{
    const map<unsigned, unsigned> cm;

    map<unsigned, unsigned>::const_iterator cit = cm.lower_bound(0);

    assert_expr(cit == cm.end());

    return 0;
}
