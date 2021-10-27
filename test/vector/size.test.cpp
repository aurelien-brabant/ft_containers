#include "vector_testing.hpp"

TEST(test_vector_size)
{
    vector<int> v1(5), v2(0), v3(42);

    p_assert_eq(v1.size(), 5);
    p_assert_eq(v2.size(), 0);
    p_assert_eq(v3.size(), 42);

    return 0;
}
