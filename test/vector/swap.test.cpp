#include <algorithm>
#include "vector_testing.hpp"

int test_vector_swap(Tester& tester)
{
	vector<int> v1, v2;

	v1.push_back(42);
	v2.push_back(42);
	v2.push_back(21);

	vector<int>::const_iterator first1(v1.begin()), first2(v2.begin());

	vector<int>::size_type
		v1_old_cap = v1.capacity(), v1_old_len = v1.size(),
		v2_old_cap = v2.capacity(), v2_old_len = v2.size();

	vector<int>::pointer
		v1_old_data = v1.data(), v2_old_data = v2.data();

	v1.swap(v2);

	assert_expr(v1.size() == 2);
	assert_expr(v2.size() == 1);

	assert_expr(v2.capacity() == v1_old_cap);
	assert_expr(v1.capacity() == v2_old_cap);

	assert_expr(v2.size() == v1_old_len);
	assert_expr(v1.size() == v2_old_len);

	assert_expr(v1.data() == v2_old_data);
	assert_expr(v2.data() == v1_old_data);

	for (vector<int>::const_iterator cit = v1.begin(), old = first2; cit != v1.end(); ++cit, ++old) {
		assert_expr(cit == old);
	}

	for (vector<int>::const_iterator cit = v2.begin(), old = first1; cit != v2.end(); ++cit, ++old) {
		assert_expr(cit == old);
	}

	std::swap(v1, v2);

	assert_expr(v1.data() == v1_old_data);
	assert_expr(v2.data() == v2_old_data);

	return 0;
}
