#include "vector_testing.hpp"

int test_vector_erase_one(Tester& tester)
{
	size_t baseN = 424242;
	vector<int> v;

	for (size_t i = 0; i != baseN; ++i) {
		v.push_back(static_cast<int>(i));
	}

	vector<int>::iterator it1 = v.erase(v.begin()), it2 = v.erase(v.end() - 1);

	assert_expr(it1 == v.begin());
	assert_expr(it2 == v.end());

	return 0;
}
