#include <string>
#include "vector_testing.hpp"

using std::string;

int test_vector_iterator_read_loop(Tester& tester)
{
	vector<int> v(1000);

	for (vector<int>::size_type i = 0; i != v.size(); ++i) {
		v[i] = i;
	}

	vector<int>::size_type i = 0;
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		p_assert_eq(*it, static_cast<int>(i++));
	}

	return 0;
}

int test_vector_iterator_read_write_loop(Tester& tester)
{
	vector<int> v(1000, 42);

	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		*it = 21;
	}
	
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		p_assert_eq(*it, 21);
	}

	return 0;
}

int test_vector_iterator_difference(Tester& tester)
{
	vector<int> v(42);

	vector<int>::difference_type diff = v.end() - v.begin();

	p_assert_eq(diff, static_cast<vector<int>::difference_type>(v.size()));

	return 0;
}

/**
 * Implicitly ensure than iterator can be converted to const_iterator
 */

int test_vector_const_iterator_read_only(Tester& tester)
{
	vector<string> vs(42, "forty two");

	for (vector<string>::const_iterator cit = vs.begin(); cit != vs.end(); ++cit) {
		p_assert_eq(*cit, "forty two");
	}

	return 0;
}
