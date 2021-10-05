#include <vector>
#include "equal_testing.hpp"

using std::vector;

int test_equal(Tester& tester)
{
	int r1[] = { 1, 2, 8, 4, 3, 1, 7 };
	int r2[] = { 1, 2, 8, 4, 3, 1, 7 };

	bool ret = FT_CONTAINER::equal(r1, r1 + sizeof(r1) / sizeof(int), r2);

	assert_expr(ret == true);

	return 0;
}

int test_unequal_first_element(Tester& tester)
{
	int r1[] = { 8, 2, 8, 4, 3, 1, 7 };
	int r2[] = { 1, 2, 8, 4, 3, 1, 7 };

	bool ret = FT_CONTAINER::equal(r1, r1 + sizeof(r1) / sizeof(int), r2);

	assert_expr(ret == false);

	return 0;
}

int test_unequal_last_element(Tester& tester)
{
	int r1[] = { 1, 2, 8, 4, 3, 1, 9 };
	int r2[] = { 1, 2, 8, 4, 3, 1, 7 };

	bool ret = FT_CONTAINER::equal(r1, r1 + sizeof(r1) / sizeof(int), r2);

	assert_expr(ret == false);

	return 0;
}

int test_equal_first1_smaller(Tester& tester)
{
	int r1[] = { 1, 2, 8, 4, 3, 1 };
	int r2[] = { 1, 2, 8, 4, 3, 1, 7 };

	bool ret = FT_CONTAINER::equal(r1, r1 + sizeof(r1) / sizeof(int), r2);

	assert_expr(ret == true);

	return 0;
}

int test_equal_subrange(Tester& tester)
{
	int r1[] = { 1, 2, 8, 4, 3, 1 };
	int r2[] = { 8, 5, 2, 4, 1, 2, 8, 4, 3, 1 };

	bool ret = FT_CONTAINER::equal(r1, r1 + sizeof(r1) / sizeof(int), r2 + 4);

	assert_expr(ret == true);

	return 0;
}

int test_perf_unequal_at_mid(Tester& tester)
{
	vector<int> v1, v2;
	const size_t n = 424242;

	for (size_t i = 0; i != n; ++i) {
		v1.push_back(i == n / 2 ? 21 : 42);
		v2.push_back(42);
	}

	bool ret = FT_CONTAINER::equal(v1.begin(), v1.end(), v2.begin());

	assert_expr(ret == false);

	return 0;
}