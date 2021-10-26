#include "map_testing.hpp"

TEST(test_map_subscript_ro)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    for (unsigned i = 0; i != baseN; ++i) {
        map<unsigned, unsigned>::mapped_type& n = m[i];

        p_assert_eq(n, i);
    }

    return 0;
}

TEST(test_map_subscript_rw)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    for (unsigned i = 0; i != baseN; ++i) {
        m[i] *= 2;
    }

    for (unsigned i = 0; i != baseN; ++i) {
        map<unsigned, unsigned>::mapped_type& n = m[i];

        p_assert_eq(n, i * 2);
    }

    return 0;
}
