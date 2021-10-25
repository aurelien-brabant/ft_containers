#include "map_testing.hpp"

int
test_map_erase_one(Tester& tester)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    for (unsigned i = 0; i != baseN; ++i) {
        assert_expr(m.erase(i) == 1);
    }

    p_assert_eq(m.size(), 0);

    // elements should have been properly deleted, thus erase must return 0
    for (unsigned i = 0; i != baseN; ++i) {
        assert_expr(m.erase(i) == 0);
    }

    return 0;
}

int
test_map_erase_one_alternate(Tester& tester)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    // erase even keys only
    for (unsigned i = 0; i < baseN; i += 2) {
        assert_expr(m.erase(i) == 1);
    }

    size_t erasedEvenNumbers = baseN / 2;

    assert_expr(m.size() == baseN - erasedEvenNumbers);

    unsigned i = 1;
    for (map<unsigned, unsigned>::const_iterator cit = m.begin();
         cit != m.end();
         ++cit) {
        p_assert_eq(cit->first, i);
        i += 2;
    }

    return 0;
}

int
test_map_erase_iterator(Tester& tester)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    for (map<unsigned, unsigned>::iterator it = m.begin(); it != m.end();) {
        m.erase(it++); // testing post incrementation. incremented iterator's
                       // memory location shouldn't be invalidated.
    }

    assert_expr(m.size() == 0);

    return 0;
}
