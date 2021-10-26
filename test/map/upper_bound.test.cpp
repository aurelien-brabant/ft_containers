#include "map_testing.hpp"

int
test_map_upper_bound_one_match_only(Tester& tester)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 100000;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    map<unsigned, unsigned>::iterator it = m.upper_bound(baseN - 2);

    assert_expr(it != m.end());

    p_assert_eq(it->first, baseN - 1);

    return 0;
}

int
test_map_upper_bound_find_smallest(Tester& tester)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 100000;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    map<unsigned, unsigned>::iterator it = m.upper_bound(baseN / 2);

    assert_expr(it != m.end());

    p_assert_eq(it->first, baseN / 2 + 1);

    return 0;
}

int
test_map_upper_bound_not_found(Tester& tester)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 100000;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    map<unsigned, unsigned>::iterator it = m.upper_bound(baseN);

    assert_expr(it == m.end());

    return 0;
}

int
test_map_upper_bound_const_overload(Tester& tester)
{
    const map<unsigned, unsigned> cm;

    map<unsigned, unsigned>::const_iterator cit = cm.upper_bound(0);

    assert_expr(cit == cm.end());

    return 0;
}
