#include "vector_testing.hpp"

int
test_vector_front_value(Tester& tester)
{
    vector<int> v(424242, 42);

    v[0] = 21;

    p_assert_eq(v.front(), v[0]);

    return 0;
}

int
test_vector_front_same_than_begin(Tester& tester)
{
    vector<int> v(424242, 42);

    p_assert_eq(&v.front(), &(*v.begin()));

    return 0;
}
