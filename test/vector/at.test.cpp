#include "vector_testing.hpp"

int test_vector_at_valid(Tester& tester)
{
	(void)tester;
	vector<long> v(10);

	for (vector<long>::size_type i = 0; i != v.size(); ++i) {
		v.at(i) = i;
	}

	for (vector<long>::size_type i = 0; i != v.size(); ++i) {
		p_assert_eq(v.at(i), static_cast<long>(i));
	}

	return 0;
}

int test_vector_at_throws(Tester& tester)
{
	vector<long> v(10);

	v.at(2);
	v.at(5);
	assert_throw(std::out_of_range, v.at(v.size()));

	return 0;
}
