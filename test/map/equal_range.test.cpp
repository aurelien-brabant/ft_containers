#include "map_testing.hpp"

int
test_map_equal_range_begin_to_end(Tester& tester)
{
    map<unsigned, unsigned> m;

    m.insert(FT_CONTAINER::make_pair(21, 21));
    m.insert(FT_CONTAINER::make_pair(42, 42));

    FT_CONTAINER::pair<map<unsigned, unsigned>::iterator,
                       map<unsigned, unsigned>::iterator>
      range = m.equal_range(21);

    assert_expr(range.first == m.begin());
    assert_expr(range.second == --m.end());

    return 0;
}

int
test_map_equal_range_perf_not_found(Tester& tester)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 1000000;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    FT_CONTAINER::pair<map<unsigned, unsigned>::iterator,
                       map<unsigned, unsigned>::iterator>
      range = m.equal_range(baseN);

    assert_expr(range.first == m.end());
    assert_expr(range.second == m.end());

    return 0;
}

int
test_map_equal_range_const_overload(Tester& tester)
{
    const map<unsigned, unsigned> m;

    FT_CONTAINER::pair<map<unsigned, unsigned>::const_iterator,
                       map<unsigned, unsigned>::const_iterator>
      range = m.equal_range(0);

    assert_expr(range.first == m.end());
    assert_expr(range.second == m.end());

    return 0;
}
