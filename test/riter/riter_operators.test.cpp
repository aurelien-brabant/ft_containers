#include "riter_testing.hpp"

TEST(test_riter_add_n)
{
    const std::vector<int> v(42);
    std::vector<int>::difference_type n = 21;

    std::vector<int>::const_iterator cit = v.end();
    reverse_iterator<std::vector<int>::const_iterator> crit(cit);

    crit = crit + n;

    assert_expr(crit.base() == cit - n);

    return 0;
}

TEST(test_riter_add_n_self)
{
    const std::vector<int> v(42);
    std::vector<int>::difference_type n = 21;

    std::vector<int>::const_iterator cit = v.end();
    reverse_iterator<std::vector<int>::const_iterator> crit(cit);

    crit += n;

    assert_expr(crit.base() == cit - n);

    return 0;
}

TEST(test_riter_sub_n)
{
    const std::vector<int> v(42);
    std::vector<int>::difference_type n = 21;

    std::vector<int>::const_iterator cit = v.begin();
    reverse_iterator<std::vector<int>::const_iterator> crit(cit);

    crit = crit - n;

    assert_expr(crit.base() == cit + n);

    return 0;
}

TEST(test_riter_sub_n_self)
{
    const std::vector<int> v(42);
    std::vector<int>::difference_type n = 21;

    std::vector<int>::const_iterator cit = v.begin();
    reverse_iterator<std::vector<int>::const_iterator> crit(cit);

    crit -= n;

    assert_expr(crit.base() == cit + n);

    return 0;
}

TEST(test_riter_pre_increment)
{
    std::vector<int> v(42);

    reverse_iterator<std::vector<int>::iterator> rit(v.end());

    for (std::vector<int>::size_type i = 0; i != v.size();) {
        assert_eq((++rit).base(), v.end() - ++i);
    }

    return 0;
}

TEST(test_riter_post_increment)
{
    std::vector<int> v(42);

    reverse_iterator<std::vector<int>::iterator> rit(v.end());

    for (std::vector<int>::size_type i = 0; i != v.size();) {
        assert_eq((rit++).base(), v.end() - i++);
    }

    return 0;
}

TEST(test_riter_pre_decrement)
{
    std::vector<int> v(42);

    reverse_iterator<std::vector<int>::iterator> rit(v.begin());

    for (std::vector<int>::size_type i = 0; i != v.size();) {
        assert_eq((--rit).base(), v.begin() + ++i);
    }

    return 0;
}

TEST(test_riter_post_decrement)
{
    std::vector<int> v(42);

    reverse_iterator<std::vector<int>::iterator> rit(v.begin());

    for (std::vector<int>::size_type i = 0; i != v.size();) {
        assert_eq((rit--).base(), v.begin() + i++);
    }

    return 0;
}

TEST(test_riter_sub_riter)
{
    std::vector<int> v(21);
    reverse_iterator<std::vector<int>::iterator> rbegin(v.end()),
      rend(v.begin());

    std::vector<int>::difference_type n = rend - rbegin;

    p_assert_eq(n, static_cast<std::vector<int>::difference_type>(v.size()));

    return 0;
}

TEST(test_riter_gt)
{
    std::vector<int> v(21);

    reverse_iterator<std::vector<int>::iterator> rbegin(v.end()),
      rend(v.begin());

    assert_expr(rend > rbegin);

    return 0;
}

TEST(test_riter_gte)
{
    std::vector<int> v(21);

    reverse_iterator<std::vector<int>::iterator> rbegin(v.end()),
      rend(v.begin());

    assert_expr(rend >= rbegin);
    assert_expr(rend >= rend);

    return 0;
}

TEST(test_riter_lt)
{
    std::vector<int> v(21);

    reverse_iterator<std::vector<int>::iterator> rbegin(v.end()),
      rend(v.begin());

    assert_expr(rbegin < rend);

    return 0;
}

TEST(test_riter_lte)
{
    std::vector<int> v(21);

    reverse_iterator<std::vector<int>::iterator> rbegin(v.end()),
      rend(v.begin());

    assert_expr(rbegin <= rend);
    assert_expr(rbegin <= rbegin);

    return 0;
}

TEST(test_riter_eq)
{
    std::vector<int> v(21), v2(42);

    reverse_iterator<std::vector<int>::iterator> rend(v.begin()),
      rend2(v2.begin());

    assert_expr(rend == rend && rend2 == rend2);
    assert_expr_not(rend2 == rend);

    return 0;
}

TEST(test_riter_neq)
{
    std::vector<int> v(21), v2(42);

    reverse_iterator<std::vector<int>::iterator> rend(v.begin()),
      rend2(v2.begin());

    assert_expr(rend != rend2);
    assert_expr_not(rend != rend);

    return 0;
}
