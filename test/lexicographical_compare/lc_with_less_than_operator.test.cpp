#include "lc_testing.hpp"
#include <vector>

using std::vector;

TEST(test_lc_first1_less_than_first2)
{
    int r1[] = { 2, 4, 5, 1, 3 };
    int r2[] = { 2, 4, 6, 1, 3 };

    bool ret = FT_CONTAINER::lexicographical_compare(
      r1, r1 + sizeof(r1) / sizeof(int), r2, r2 + sizeof(r2) / sizeof(int));

    assert_expr(ret == true);

    return 0;
}

TEST(test_lc_first1_greater_than_first2)
{
    int r1[] = { 2, 4, 6, 1, 3 };
    int r2[] = { 2, 4, 5, 1, 3 };

    bool ret = FT_CONTAINER::lexicographical_compare(
      r1, r1 + sizeof(r1) / sizeof(int), r2, r2 + sizeof(r2) / sizeof(int));

    assert_expr(ret == false);

    return 0;
}

TEST(test_lc_ranges_equal)
{
    int r1[] = { 2, 4, 6, 1, 3 };
    int r2[] = { 2, 4, 6, 1, 3 };

    bool ret = FT_CONTAINER::lexicographical_compare(
      r1, r1 + sizeof(r1) / sizeof(int), r2, r2 + sizeof(r2) / sizeof(int));

    assert_expr(ret == false);

    return 0;
}

TEST(test_lc_first1_prefix_of_first2)
{
    int r1[] = { 2, 4, 5, 1, 3 };
    int r2[] = { 2, 4, 5, 1, 3, 1, 8, 3, 15, 12, 42, 23 };

    bool ret = FT_CONTAINER::lexicographical_compare(
      r1, r1 + sizeof(r1) / sizeof(int), r2, r2 + sizeof(r2) / sizeof(int));

    assert_expr(ret == true);

    return 0;
}

TEST(test_lc_first2_prefix_of_first1)
{
    int r1[] = { 2, 4, 5, 1, 3, 1, 8, 3, 15, 12, 42, 23 };
    int r2[] = { 2, 4, 5, 1, 3 };

    bool ret = FT_CONTAINER::lexicographical_compare(
      r1, r1 + sizeof(r1) / sizeof(int), r2, r2 + sizeof(r2) / sizeof(int));

    assert_expr(ret == false);

    return 0;
}

TEST(test_lc_first1_empty)
{
    int* r1 = 0;
    int r2[] = { 2, 4, 5, 1, 3 };

    bool ret = FT_CONTAINER::lexicographical_compare(
      r1, r1, r2, r2 + sizeof(r2) / sizeof(int));

    assert_expr(ret == true);

    return 0;
}

TEST(test_lc_first2_empty)
{
    int r1[] = { 2, 4, 5, 1, 3 };
    int* r2 = 0;

    bool ret = FT_CONTAINER::lexicographical_compare(
      r1, r1 + sizeof(r1) / sizeof(int), r2, r2);

    assert_expr(ret == false);

    return 0;
}

TEST(test_lc_both_empty)
{
    int *r1 = 0, *r2 = 0;

    bool ret = FT_CONTAINER::lexicographical_compare(r1, r1, r2, r2);

    /* these range compare equal, therefore no one is less than the other */
    assert_expr(ret == false);

    return 0;
}

TEST(test_lc_perf_differ_at_last_element)
{
    vector<int> v1, v2;
    const size_t n = 424242;

    for (size_t i = 0; i != n; ++i) {
        v1.push_back(42);
        v2.push_back(42);
    }
    v2.push_back(42);

    bool ret = FT_CONTAINER::lexicographical_compare(
                 v1.begin(), v1.end(), v2.begin(), v2.end()) == true;

    assert_expr(ret == true);

    return 0;
}
