#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include "vector_testing.hpp"

using std::string;
using std::ostringstream;

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

int test_vector_range_constructor(Tester& tester)
{
	const size_t baseN = 42;
	vector<const char*> range;
	ostringstream oss;

	for (size_t i = 0; i != baseN; ++i) {
		oss << i;
		range.push_back(strdup(oss.str().c_str()));
		oss.str("");
	}

	std::cout << "range[0] " << range[0] << "\n";

	vector<string> v(range.begin(), range.end());

	for (vector<string>::size_type i = 0; i != v.size(); ++i) {
		oss << i;
		p_assert_eq(v[i], oss.str());
		oss.str("");
		free((void *)range[i]);
	}

	return 0;
}
