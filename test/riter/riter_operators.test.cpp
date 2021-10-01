#include "riter_testing.hpp"

int test_riter_add_n(Tester& tester)
{
	const std::vector<int> v(42);
	std::vector<int>::difference_type n = 21;

	std::vector<int>::const_iterator cit = v.end();
	reverse_iterator<std::vector<int>::const_iterator> crit(cit);

	crit = crit + n;

	assert_expr(crit.base() == cit - n);

	return 0;
}

int test_riter_add_n_self(Tester& tester)
{
	const std::vector<int> v(42);
	std::vector<int>::difference_type n = 21;

	std::vector<int>::const_iterator cit = v.end();
	reverse_iterator<std::vector<int>::const_iterator> crit(cit);

	crit += n;

	assert_expr(crit.base() == cit - n);

	return 0;
}

int test_riter_sub_n(Tester& tester)
{
	const std::vector<int> v(42);
	std::vector<int>::difference_type n = 21;

	std::vector<int>::const_iterator cit = v.begin();
	reverse_iterator<std::vector<int>::const_iterator> crit(cit);

	crit = crit - n;

	assert_expr(crit.base() == cit + n);

	return 0;
}

int test_riter_sub_n_self(Tester& tester)
{
	const std::vector<int> v(42);
	std::vector<int>::difference_type n = 21;

	std::vector<int>::const_iterator cit = v.begin();
	reverse_iterator<std::vector<int>::const_iterator> crit(cit);

	crit -= n;

	assert_expr(crit.base() == cit + n);

	return 0;
}

int test_riter_pre_increment(Tester& tester)
{
	std::vector<int> v(42);
	
	reverse_iterator<std::vector<int>::iterator> rit(v.end());

	for (std::vector<int>::size_type i = 0; i != v.size();) {
		assert_eq((++rit).base(), v.end() - ++i);
	}

	return 0;
}

int test_riter_post_increment(Tester& tester)
{
	std::vector<int> v(42);
	
	reverse_iterator<std::vector<int>::iterator> rit(v.end());

	for (std::vector<int>::size_type i = 0; i != v.size();) {
		assert_eq((rit++).base(), v.end() - i++);
	}

	return 0;
}

int test_riter_pre_decrement(Tester& tester)
{
	std::vector<int> v(42);
	
	reverse_iterator<std::vector<int>::iterator> rit(v.begin());

	for (std::vector<int>::size_type i = 0; i != v.size();) {
		assert_eq((--rit).base(), v.begin() + ++i);
	}

	return 0;
}

int test_riter_post_decrement(Tester& tester)
{
	std::vector<int> v(42);
	
	reverse_iterator<std::vector<int>::iterator> rit(v.begin());

	for (std::vector<int>::size_type i = 0; i != v.size();) {
		assert_eq((rit--).base(), v.begin() + i++);
	}

	return 0;
}

int test_riter_sub_riter(Tester& tester)
{
	std::vector<int> v(21);
	reverse_iterator<std::vector<int>::iterator> rbegin(v.end()), rend(v.begin());

	std::vector<int>::difference_type n = rend - rbegin;

	p_assert_eq(n, static_cast<std::vector<int>::difference_type>(v.size()));
	
	return 0;
}
