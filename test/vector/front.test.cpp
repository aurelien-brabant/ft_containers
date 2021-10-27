#include "vector_testing.hpp"

TEST(test_vector_front_value)
{
    vector<int> v(424242, 42);

    v[0] = 21;

    p_assert_eq(v.front(), v[0]);

    return 0;
}

TEST(test_vector_front_same_than_begin)
{
    vector<int> v(424242, 42);

    p_assert_eq(&v.front(), &(*v.begin()));

    return 0;
}
