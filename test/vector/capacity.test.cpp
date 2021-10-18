#include "vector_testing.hpp"

const size_t baseN = 424242;

int
test_vector_capacity(Tester& tester)
{
    vector<int> v(baseN);

    assert_expr(v.size() <= v.capacity());

    return 0;
}

int
test_vector_greater_capacity_reservation(Tester& tester)
{
    vector<int> v(baseN);

    v.reserve(v.size() * 2);

    assert_expr(v.capacity() >= v.size() * 2);

    return 0;
}

/**
 * Smaller or equal new capacity should not alter vector's capacity.
 */

int
test_vector_smaller_capacity_reservation(Tester& tester)
{
    vector<int> v(baseN);

    vector<int>::size_type oldCap = v.capacity();

    v.reserve(v.size());
    assert_expr(v.capacity() == oldCap);

    v.reserve(v.size() - 1);
    assert_expr(v.capacity() == oldCap);

    return 0;
}
