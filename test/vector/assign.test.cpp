#include "vector_testing.hpp"

int test_vector_assign(Tester& tester)
{
	const size_t baseN = 424242;

	vector<int> v(baseN);

	v.assign(baseN, 42);

	for (vector<int>::size_type i = 0; i != v.size(); ++i) {
		p_assert_eq(v[i], 42);
	}
	
	return 0;
}

int test_vector_iterator_assign(Tester& tester)
{
	const size_t baseN = 424242;
	vector<int> v(baseN), pool;

	for (size_t i = 0; i < baseN / 2; ++i) {
		pool.push_back(static_cast<int>(i));
	}

	v.assign(pool.begin(), pool.end());

	for (vector<int>::size_type i = 0; i != v.size(); ++i) {
		if (i < baseN / 2) {
			p_assert_eq(v[i], static_cast<int>(i));
		} else {
			p_assert_eq(v[i], 0);
		}
	}

	return 0;
}
