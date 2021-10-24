#include "map_testing.hpp"

int test_map_insert_one(Tester& tester)
{
    (void) tester;
    map<unsigned, unsigned> m;
    unsigned baseN = 1000000;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    p_assert_eq(m.size(), baseN);

    return 0;
}

int test_map_insert_range(Tester& tester)
{
    unsigned baseN = 10000;

    std::vector<pair<unsigned, unsigned> > v;

    for (unsigned i = 0; i != baseN; ++i) {
        v.push_back(make_pair(i, 0));
    }

    map<unsigned, unsigned> m;

    m.insert(++v.begin(), --v.end());

    p_assert_eq(m.size(), v.size() - 2);

    return 0;
}
