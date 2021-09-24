#include "vector_testing.hpp"

int test_vector_subscript(Tester& tester)
{
	vector<unsigned> v(10, 42);

	for (size_t i = 1; i != v.size() - 1; ++i) {
		v[i] = i;
	}

	for (size_t i = 0; i != v.size(); ++i) {
		p_assert_eq(v[i], i == 0 || i == v.size() - 1 ? 42 : i);
	}

	return 0;
}
