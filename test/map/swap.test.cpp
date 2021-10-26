#include "map_testing.hpp"

TEST(test_map_swap)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m1, m2;

    for (unsigned i = 0; i != baseN / 2; ++i) {
        m1.insert(FT_CONTAINER::make_pair(i, i));
    }

    for (unsigned i = baseN / 2; i != baseN; ++i) {
        m2.insert(FT_CONTAINER::make_pair(i, i));
    }
    m2.insert(FT_CONTAINER::make_pair(baseN, baseN));

    assert_expr(m2.size() > m1.size());

    map<unsigned, unsigned>::const_iterator first1 = m1.begin(),
                                            first2 = m2.begin();

    m1.swap(m2);
    assert_expr(m1.size() > m2.size());

    unsigned i = baseN / 2;

    for (map<unsigned, unsigned>::const_iterator cit1 = m1.begin(),
                                                 first2Copy = first2;
         cit1 != m1.end();
         ++cit1) {
        assert_expr(cit1 == first2Copy);
        p_assert_eq(cit1->first, i);
        p_assert_eq(cit1->second, i);
        ++i;
        ++first2Copy;
    }

    p_assert_eq(i, baseN + 1);

    i = 0;
    for (map<unsigned, unsigned>::const_iterator cit2 = m2.begin(),
                                                 first1Copy = first1;
         cit2 != m2.end();
         ++cit2) {
        assert_expr(cit2 == first1Copy);
        p_assert_eq(cit2->first, i);
        p_assert_eq(cit2->second, i);
        ++first1Copy;
        ++i;
    }

    p_assert_eq(i, baseN / 2);

    std::swap(m1, m2);

    i = 0;

    for (map<unsigned, unsigned>::const_iterator cit1 = m1.begin();
         cit1 != m1.end();
         ++cit1) {
        assert_expr(cit1 == first1);
        p_assert_eq(cit1->first, i);
        p_assert_eq(cit1->second, i);
        ++i;
        ++first1;
    }

    p_assert_eq(i, baseN / 2);

    for (map<unsigned, unsigned>::const_iterator cit2 = m2.begin();
         cit2 != m2.end();
         ++cit2) {
        assert_expr(cit2 == first2);
        p_assert_eq(cit2->first, i);
        p_assert_eq(cit2->second, i);
        ++i;
        ++first2;
    }

    p_assert_eq(i, baseN + 1);

    return 0;
}
