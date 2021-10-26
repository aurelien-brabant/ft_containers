#include "map_testing.hpp"

TEST(test_map_assignment_operator)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 1000000;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    map<unsigned, unsigned> mCopy = m, *mptr = &mCopy;

    // test self-alignment
    mCopy = *mptr;

    p_assert_eq(mCopy.size(), m.size());

    // ensure a deep copy has been performed

    for (map<unsigned, unsigned>::iterator it = m.begin(); it != m.end();
         ++it) {
        it->second = 0;
    }

    size_t i = 0;
    for (map<unsigned, unsigned>::iterator it = mCopy.begin();
         it != mCopy.end();
         ++it) {
        p_assert_eq(it->second, i++);
    }

    p_assert_eq(i, baseN);

    return 0;
}

TEST(test_map_copy_constructor)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 1000000;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    map<unsigned, unsigned> mCopy(m);

    p_assert_eq(mCopy.size(), m.size());

    // ensure a deep copy has been performed

    for (map<unsigned, unsigned>::iterator it = m.begin(); it != m.end();
         ++it) {
        it->second = 0;
    }

    size_t i = 0;
    for (map<unsigned, unsigned>::iterator it = mCopy.begin();
         it != mCopy.end();
         ++it) {
        p_assert_eq(it->second, i++);
    }

    p_assert_eq(i, baseN);

    return 0;
}

TEST(test_map_copy_cleared)
{
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != 42; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
    }

    m.clear();

    map<unsigned, unsigned> mCopy(m);

    p_assert_eq(mCopy.size(), 0);
    assert_expr(mCopy.begin() == mCopy.end());

    return 0;
}

