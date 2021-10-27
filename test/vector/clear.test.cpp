#include "vector_testing.hpp"

TEST(test_vector_clear)
{
    vector<int> v(424242);

    v.clear();

    p_assert_eq(v.size(), 0);
    assert_expr(v.empty());

    return 0;
}
