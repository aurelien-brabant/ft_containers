#include "vector_testing.hpp"

const size_t rangeSize = 424242;

TEST(test_vector_reverse_iterator_loop)
{
    vector<int> v(rangeSize);

    for (size_t i = 0; i != rangeSize; ++i) {
        v[i] = static_cast<int>(i);
    }

    size_t n = rangeSize;

    for (vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend();
         ++rit) {
        p_assert_eq(*rit, static_cast<int>(--n));
    }

    return 0;
}

TEST(test_vector_reviter_write)
{
    vector<int> v;

    for (size_t i = 0; i != rangeSize; ++i) {
        v.push_back(i);
    }

    for (vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend();
         ++rit) {
        *rit *= 2;
    }

    for (vector<int>::size_type i = 0; i != v.size(); ++i) {
        p_assert_eq(v[i], static_cast<int>(i * 2));
    }

    return 0;
}

/* ensures reverse_iterator can be converted to const_reverse_iterator */

TEST(test_vector_reviter_to_const_reviter)
{
    vector<int> v;

    for (size_t i = 0; i != rangeSize; ++i) {
        v.push_back(i);
    }

    size_t i = 0;
    for (vector<int>::const_reverse_iterator crit = v.rbegin();
         crit != v.rend();
         ++crit) {
        p_assert_eq(v[i], static_cast<int>(i));
        ++i;
    }

    return 0;
}

TEST(test_vector_reviter_to_const_operations)
{
    vector<int> v(10);

    vector<int>::reverse_iterator rit = v.rbegin();
    vector<int>::const_reverse_iterator crit = v.rbegin();

    assert_expr(rit == crit);
    assert_expr(rit <= crit);
    assert_expr(rit >= crit);
    assert_expr(!(rit < crit));
    assert_expr(!(rit > crit));

    assert_expr(crit == rit);
    assert_expr(crit <= rit);
    assert_expr(crit >= rit);
    assert_expr(!(crit < rit));
    assert_expr(!(crit > rit));

    return 0;
}
