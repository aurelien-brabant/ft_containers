#include "vector_testing.hpp"

TEST(test_vector_pop_back)
{
    vector<int> v(1);

    v.pop_back();

    assert_expr(v.size() == 0);

    return 0;
}
