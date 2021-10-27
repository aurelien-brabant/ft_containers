#include "vector_testing.hpp"

TEST(test_vector_eq_operator)
{
    vector<int> v1, v2;

    for (size_t i = 0; i != 42; ++i) {
        v1.push_back(static_cast<int>(i));
        v2.push_back(static_cast<int>(i));
    }

    assert_expr(v1 == v2);

    v2.push_back(42);

    assert_expr(v1 == v2 == false);

    return 0;
}

TEST(test_vector_uneq_operator)
{
    vector<int> v1, v2;

    for (size_t i = 0; i != 42; ++i) {
        v1.push_back(static_cast<int>(i));
        v2.push_back(static_cast<int>(i));
    }

    assert_expr(v1 != v2 == false);

    v2.push_back(42);

    assert_expr(v1 != v2);

    return 0;
}

TEST(test_vector_gt_operator)
{
    vector<int> v1, v2;

    assert_expr(v1 > v2 == false);
    assert_expr(v2 > v1 == false);

    v1.push_back(42);
    assert_expr(v1 > v2 == true);
    assert_expr(v2 > v1 == false);

    v2.push_back(84);

    assert_expr(v2 > v1 == true);
    assert_expr(v1 > v2 == false);

    return 0;
}

TEST(test_vector_gte_operator)
{
    vector<int> v1, v2;

    assert_expr(v1 >= v2 == true);

    v1.push_back(42);

    assert_expr(v1 >= v2 == true);
    assert_expr(v2 >= v1 == false);

    v2.push_back(84);

    assert_expr(v2 >= v1 == true);
    assert_expr(v1 >= v2 == false);

    v2[0] = 42;

    assert_expr(v1 >= v2 == true);
    assert_expr(v2 >= v1 == true);

    return 0;
}

TEST(test_vector_lt_operator)
{
    vector<int> v1, v2;

    assert_expr(v1 < v2 == false);
    assert_expr(v2 < v1 == false);

    v1.push_back(42);

    assert_expr(v2 < v1 == true);
    assert_expr(v1 < v2 == false);

    v2.push_back(84);

    assert_expr(v1 < v2 == true);
    assert_expr(v2 < v1 == false);

    v2[0] = 42;

    assert_expr(v1 < v2 == false);
    assert_expr(v2 < v1 == false);

    return 0;
}

TEST(test_vector_lte_operator)
{
    vector<int> v1, v2;

    assert_expr(v1 <= v2 == true);
    assert_expr(v2 <= v1 == true);

    v1.push_back(42);

    assert_expr(v1 <= v2 == false);
    assert_expr(v2 <= v1 == true);

    v2.push_back(84);

    assert_expr(v1 <= v2 == true);
    assert_expr(v2 <= v1 == false);

    v2[0] = 42;

    assert_expr(v1 <= v2 == true);
    assert_expr(v2 <= v1 == true);

    return 0;
}
