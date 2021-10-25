#include "map_testing.hpp"

int
test_map_clear(Tester& tester)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    m.clear();

    p_assert_eq(m.size(), 0);

    size_t i = 0;
    for (map<unsigned, unsigned>::const_iterator cit = m.begin();
         cit != m.end();
         ++cit) {
        ++i;
    }

    p_assert_eq(i, 0);

    return 0;
}
