#include "vector_testing.hpp"

int
test_vector_pop_back(Tester& tester)
{
    vector<int> v(1);

    v.pop_back();

    assert_expr(v.size() == 0);

    return 0;
}
