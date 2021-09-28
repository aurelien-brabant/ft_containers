#include <string>
#include "vector_testing.hpp"

using std::string;

const size_t baseN = 424242, baseValue = 42, distinctValue = 21;

int test_vector_iterator_read_loop(Tester& tester)
{
	vector<int> v(baseN);

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
	vector<int> v(baseN, baseValue);

	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		*it = distinctValue;
	}
	
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		p_assert_eq(*it, distinctValue);
	}

	return 0;
}

int test_vector_iterator_difference(Tester& tester)
{
	vector<int> v(baseN);

	vector<int>::difference_type diff = v.end() - v.begin();

	p_assert_eq(diff, static_cast<vector<int>::difference_type>(v.size()));

	return 0;
}

/**
 * Implicitly ensure than iterator can be converted to const_iterator
 */

int test_vector_const_iterator_read_only(Tester& tester)
{
	vector<int> vs(baseN, baseValue);

	for (vector<int>::const_iterator cit = vs.begin(); cit != vs.end(); ++cit) {
		p_assert_eq(*cit, 42);
	}

	return 0;
}

int test_vector_iterator_subscript(Tester& tester)
{
	vector<int> v;

	for (int i = 0; i != 10; ++i) {
		v.push_back(i);
	}

	vector<int>::iterator it = v.begin();

	for (int i = 0; i != 10; ++i) {
		p_assert_eq(it[i], i);
	}

	return 0;
}

int test_vector_iterator_negative_subscript(Tester& tester)
{
	vector<int> v;

	for (int i = 0; i != 10; ++i) {
		v.push_back(i);
	}

	vector<int>::iterator it = v.end();

	for (int i = 0; i != 10; ++i) {
		p_assert_eq(it[-10 + i], i);
	}

	return 0;
}

int test_vector_iterator_arrow(Tester& tester)
{
	vector<string> vs;
	
	vs.push_back("");

	assert_expr(vs.begin()->empty() == true);

	return 0;
}

int test_vector_iterator_greater_operator(Tester& tester)
{
	vector<int> v(10);

	assert_expr((v.end() > v.begin()) == true);
	assert_expr((v.begin() > v.end()) == false);

	return 0;
}

int test_vector_iterator_greater_or_equal_operator(Tester& tester)
{
	vector<int> v(10);

	assert_expr((v.end() >= v.begin()) == true);
	assert_expr((v.begin() + v.size() >= v.end()) == true);
	assert_expr((v.begin() + v.size() - 1 >= v.end()) == false);

	return 0;
}

int test_vector_iterator_less_operator(Tester& tester)
{
	vector<int> v(10);

	assert_expr((v.begin() < v.end()) == true);
	assert_expr((v.end() < v.begin()) == false);

	return 0;
}

int test_vector_iterator_less_or_equal_operator(Tester& tester)
{
	vector<int> v(10);

	assert_expr((v.begin() <= v.end()) == true);
	assert_expr((v.begin() + v.size() <= v.end()) == true);
	assert_expr((v.begin() + v.size() + 1 <= v.end()) == false);

	return 0;
}

int test_vector_iterator_equality_operator(Tester& tester)
{
	vector<int> v(10);

	assert_expr(v.end() - v.size() == v.begin());
	assert_expr(!(v.begin() + v.size() + 1 == v.end()));

	return 0;
}

// May not compile if operations are not implemented carefully.

int test_vector_iterator_const_compare_to_non_const(Tester& tester)
{
	vector<int> v;
	vector<int>::iterator it = v.begin();
	vector<int>::const_iterator cit = v.end();

	assert_expr(it == cit);
	assert_expr(it <= cit);
	assert_expr(it >= cit);
	assert_expr(!(it < cit));
	assert_expr(!(it > cit));
	assert_expr(!(it != cit));

	// now, the other way around

	assert_expr(cit == it);
	assert_expr(cit <= it);
	assert_expr(cit >= it);
	assert_expr(!(cit < it));
	assert_expr(!(cit > it));
	assert_expr(!(cit != it));

	return 0;
}
