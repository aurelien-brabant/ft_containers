#include "vector_testing.hpp"

int test_vector_copy_constructor(Tester& tester)
{
	vector<int> v(424242, 42), v2(v);

	assert_range_eq(v.begin(), v.end(), v2.begin(), v2.end());

	return 0;
}

int test_vector_assignment_operator_grow(Tester& tester)
{
	vector<int> v(424242, 42), v2(42, 21);

	v2 = v;

	assert_range_eq(v.begin(), v.end(), v2.begin(), v2.end());

	return 0;
}

int test_vector_assignment_operator_shrink(Tester& tester)
{
	vector<int> v(424242, 42), v2(42, 21);

	v = v2;

	assert_range_eq(v.begin(), v.end(), v2.begin(), v2.end());

	return 0;
}

int test_vector_assignement_operator_to_empty(Tester& tester)
{
	vector<int> v(424242, 42), v2;

	v = v2;

	assert_range_eq(v.begin(), v.end(), v2.begin(), v2.end());
	assert_expr(v.empty() && v2.empty());

	return 0;
}
