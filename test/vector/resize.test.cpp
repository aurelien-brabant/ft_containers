#include "vector_testing.hpp"

int test_vector_resize_greater(Tester& tester)
{
	size_t baseN = 42, resizeN = baseN * 10000;
	vector<int> v;

	for (size_t i = 0; i != baseN; ++i) {
		v.push_back(static_cast<int>(i));
	}

	v.resize(resizeN);

	assert_expr(v.size() == resizeN);
	assert_expr(v.capacity() >= resizeN);

	for (vector<int>::size_type i = 0; i != v.size(); ++i) {
		p_assert_eq(v[i], i < baseN ? static_cast<int>(i) : int());
	}

	return 0;
}

int test_vector_resize_smaller(Tester& tester)
{
	size_t baseN = 424242, resizeN = baseN / 2;
	vector<int> v;

	for (size_t i = 0; i != baseN; ++i) {
		v.push_back(static_cast<int>(i));
	}

	v.resize(resizeN);

	assert_expr(v.size() == resizeN);
	assert_expr(v.capacity() >= resizeN);

	for (vector<int>::size_type i = 0; i != v.size(); ++i) {
		p_assert_eq(v[i], static_cast<int>(i));
	}

	return 0;
}

int test_vector_resize_same(Tester& tester)
{
	size_t baseN = 42, resizeN = baseN;
	vector<int> v;

	for (size_t i = 0; i != baseN; ++i) {
		v.push_back(static_cast<int>(i));
	}

	v.resize(resizeN);

	assert_expr(v.size() == resizeN);
	assert_expr(v.capacity() >= resizeN);

	for (vector<int>::size_type i = 0; i != v.size(); ++i) {
		p_assert_eq(v[i], static_cast<int>(i));
	}

	return 0;
}
