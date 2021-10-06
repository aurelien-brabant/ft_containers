#include "vector_testing.hpp"

int test_vector_at_valid(Tester& tester)
{
	const size_t baseN = 424242;
	vector<long> v(baseN);

	for (vector<long>::size_type i = 0; i != v.size(); ++i) {
		v.at(i) = i;
	}

	for (vector<long>::size_type i = 0; i != v.size(); ++i) {
		p_assert_eq(v.at(i), static_cast<long>(i));
	}

	return 0;
}

int test_vector_at_const_overload(Tester& tester)
{
	const vector<int> v(1);

	p_assert_eq(v.at(0), int());
	
	return 0;
}

int test_vector_at_throws(Tester& tester)
{
	vector<long> v, v2(10);

	assert_throw(std::out_of_range, v.at(0));
	assert_throw(std::out_of_range, v.at(10));

	return 0;
}
