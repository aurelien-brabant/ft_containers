#include "vector_testing.hpp"

int test_vector_capacity(Tester& tester)
{
	vector<int> v(1000);

	assert_expr(v.size() <= v.capacity());

	return 0;
}

int test_vector_greater_capacity_reservation(Tester& tester)
{
	vector<int> v(42);

	v.reserve(1000);

	assert_expr(v.capacity() >= 1000);

	return 0;
}

/**
 * Smaller or equal new capacity should not alter vector's capacity.
 */

int test_vector_smaller_capacity_reservation(Tester& tester)
{
	vector<int> v(42);
	
	vector<int>::size_type oldCap = v.capacity();

	v.reserve(41);
	assert_expr(v.capacity() == oldCap);

	v.reserve(42);
	assert_expr(v.capacity() == oldCap);

	return 0;
}
