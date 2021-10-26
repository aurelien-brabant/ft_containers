#include "map_testing.hpp"

int
test_map_iterator_decrement_end(Tester& tester)
{
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != 10; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    map<unsigned, unsigned>::iterator it = m.end();

    p_assert_eq((--it)->first, 9);

    return 0;
}

int
test_map_iterator_decrement_reverse_loop(Tester& tester)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 100000;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    map<unsigned, unsigned>::iterator it = m.end();

    while (it != m.begin()) {
        p_assert_eq((--it)->first, --baseN);
    }

    return 0;
}

int
test_map_iterator_prefix_increment(Tester& tester)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 10;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    size_t i = 1;
    for (map<unsigned, unsigned>::iterator it = m.begin(); it != m.end();) {
        if (++it != m.end()) {
            p_assert_eq(it->first, i++);
        }
    }

    return 0;
}

int
test_map_iterator_postfix_increment(Tester& tester)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 10;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    size_t i = 0;
    for (map<unsigned, unsigned>::iterator it = m.begin(); it != m.end();) {
        p_assert_eq((it++)->first, i++);
    }

    return 0;
}

int
test_map_iterator_to_const_iterator(Tester& tester)
{
    map<unsigned, unsigned> m;

    map<unsigned, unsigned>::const_iterator cit = m.begin();

    assert_expr(cit == m.end());
    assert_expr(m.end() == cit);

    m.insert(FT_CONTAINER::make_pair(0, 0));

    cit = m.begin();

    assert_expr(cit != m.end());
    assert_expr(m.end() != cit);

    return 0;
}

TEST(test_map_iterator_const_instance)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 100000;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    const map<unsigned, unsigned> cm(m);

    size_t i = 0;
    for (map<unsigned, unsigned>::const_iterator cit = cm.begin();
         cit != cm.end();) {
        p_assert_eq((cit++)->first, i++);
    }
    p_assert_eq(i, baseN);

    return 0;
}
