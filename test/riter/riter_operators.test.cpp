#include "riter_testing.hpp"

int test_iter_add_n(Tester& tester)
{
	const std::vector<int> v(42);
	std::vector<int>::difference_type n = 21;

	std::vector<int>::const_iterator cit = v.end();
	reverse_iterator<std::vector<int>::const_iterator> crit(cit);

	crit = crit + n;

	assert_expr(crit.base() == cit - n);

	return 0;
}
