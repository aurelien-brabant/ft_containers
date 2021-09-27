#include <string>
#include "vector_testing.hpp"

using std::string;

static const size_t baseN = 424242;
static const string baseStringValue = "42";

int test_vector_copy_constructor(Tester& tester)
{
	vector<string> v(baseN, baseStringValue), v2(v);

	assert_range_eq(v.begin(), v.end(), v2.begin(), v2.end());

	return 0;
}

int test_vector_assignment_operator_grow(Tester& tester)
{
	const string distinctStringValue = "21";
	vector<string> v(baseN, baseStringValue), v2(baseN / 42, distinctStringValue);

	v2 = v;

	assert_range_eq(v.begin(), v.end(), v2.begin(), v2.end());

	return 0;
}

int test_vector_assignment_operator_shrink(Tester& tester)
{
	const string distinctStringValue = "21";
	vector<string> v(baseN, baseStringValue), v2(baseN / 42, distinctStringValue);

	v = v2;

	assert_range_eq(v.begin(), v.end(), v2.begin(), v2.end());

	return 0;
}

int test_vector_assignement_operator_to_empty(Tester& tester)
{
	vector<string> v(baseN, baseStringValue), v2;

	v = v2;

	assert_range_eq(v.begin(), v.end(), v2.begin(), v2.end());
	assert_expr(v.empty() && v2.empty());

	return 0;
}
