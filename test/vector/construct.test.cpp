#include <string>
#include "vector_testing.hpp"

using std::string;

int test_vector_construct_n_by_value(Tester& tester)
{
	const size_t baseN = 424242;
	vector<string> vs(baseN);

	for (size_t i = 0; i != baseN; ++i) {
		p_assert_eq(vs[i], string());
	}

	return 0;
}

int test_vector_construct_n_with_value(Tester& tester)
{
	const size_t baseN = 424242;
	const string baseString = "42";
	vector<string> vs(baseN, baseString);

	for (size_t i = 0; i != baseN; ++i) {
		p_assert_eq(vs[i], baseString);
	}

	return 0;
}
