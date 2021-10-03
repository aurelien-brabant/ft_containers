#include "vector_testing.hpp"

int test_vector_erase_one(Tester& tester)
{
	size_t baseN = 424242;
	vector<int> v;

	for (size_t i = 0; i != baseN; ++i) {
		v.push_back(static_cast<int>(i));
	}

	vector<int>::iterator it1 = v.erase(v.begin()), it2 = v.erase(v.end() - 1), it3 = v.erase(v.begin() + (baseN / 2));

	assert_expr(it1 == v.begin());
	assert_expr(it2 == v.end() + 1); // invalidated
	assert_expr(it3 == v.begin() + (baseN / 2));

	assert_expr(v.size() == baseN - 3);

	for (vector<int>::size_type i = 0; i != v.size(); ++i) {
		if (i < baseN / 2) {
			p_assert_eq(v[i], static_cast<int>(i + 1));
		} else if (i == baseN - 1) {
			p_assert_eq(v[i], static_cast<int>(baseN - 2));
		} else {
			p_assert_eq(v[i], static_cast<int>(i + 2));
		}
	}

	return 0;
}
