#include "vector_testing.hpp"

int test_vector_push_back(Tester& tester)
{
	vector<unsigned> v;

	for (unsigned i = 0; i != 424242; ++i) {
		v.push_back(i);
	}

	for (vector<unsigned>::size_type i = 0; i != v.size(); ++i) {
		p_assert_eq(v[i], i);
	}

	return 0;
}
