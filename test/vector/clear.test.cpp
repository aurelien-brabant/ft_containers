#include "vector_testing.hpp"

int
test_vector_clear(Tester& tester)
{
    vector<int> v(424242);

    v.clear();

    p_assert_eq(v.size(), 0);
    assert_expr(v.empty());

    return 0;
}
