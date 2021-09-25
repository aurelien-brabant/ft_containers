#include "vector_testing.hpp"

int test_vector_empty(Tester& tester)
{
	vector<unsigned> v1, v2(1), v3, v4(2), v5;

	assert_expr(v1.empty());
	assert_expr_not(v2.empty());
	assert_expr(v3.empty());
	assert_expr_not(v4.empty());
	assert_expr(v5.empty());

	return 0;
}
