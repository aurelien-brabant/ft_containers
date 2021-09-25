#include "vector_testing.hpp"

int test_vector_back_value(Tester& tester)
{
	vector<int> v(424242, 42);

	v[v.size() - 1] = 21;

	p_assert_eq(v.back(), v[v.size() - 1]);

	return 0;
}

int test_vector_back_same_than_end_minus_one(Tester& tester)
{
	vector<int> v(424242, 42);

	p_assert_eq(&v.back(), &(*(v.end() - 1)));

	return 0;
}
