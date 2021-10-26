#include "map_testing.hpp"

TEST(test_map_at_ro)
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

TEST(test_map_at_rw)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    for (unsigned i = 0; i != baseN; ++i) {
        m.at(i) *= 2;
    }

    for (unsigned i = 0; i != baseN; ++i) {
        map<unsigned, unsigned>::mapped_type& n = m.at(i);
        p_assert_eq(n, i * 2);
    }

    return 0;
}

TEST(test_map_at_out_of_range)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    m.at(0);
    m.at(baseN - 1);
    assert_throw(std::out_of_range, m.at(baseN));

    return 0;
}

TEST(test_map_at_const_overload)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    const map<unsigned, unsigned> cm(m);

    for (unsigned i = 0; i != baseN; ++i) {
        const map<unsigned, unsigned>::mapped_type& n = cm.at(i);

        p_assert_eq(n, i);
    }

    return 0;
}
