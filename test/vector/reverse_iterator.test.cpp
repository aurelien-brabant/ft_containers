#include "vector_testing.hpp"

const size_t rangeSize = 424242;

int test_vector_reverse_iterator_loop(Tester& tester)
{
	vector<int> v(rangeSize);

	for (size_t i = 0; i != rangeSize; ++i) {
		v[i] = static_cast<int>(i);
	}

	size_t n = rangeSize;
	
	for (vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); ++rit) {
		p_assert_eq(*rit, static_cast<int>(--n));
	}

	return 0;
}
