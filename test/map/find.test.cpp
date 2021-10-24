#include "map_testing.hpp"

int test_map_find(Tester& tester)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    for (unsigned i = 0; i != baseN; ++i) {
        map<unsigned, unsigned>::iterator it = m.find(i);

        assert_expr(it != m.end());
        p_assert_eq(it->first, i);
    }
    
    return 0;
}
