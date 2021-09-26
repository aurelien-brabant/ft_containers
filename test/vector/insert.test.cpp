#include <string>
#include "vector_testing.hpp"

/**
 * Inserting at the front of a vector is an expensive operation.
 * Time complexity being O(n), where n is the current vector's size at insertion time,
 * using a too big baseN may take a while to be processed.
 */

int test_vector_insert_front(Tester& tester)
{
	const size_t nbToInsert = 4242, baseN = 42;
	std::string baseStringValue("42");
	vector<std::string> v(baseN, baseStringValue);

	for (int i = 0; i != nbToInsert; ++i) {
		v.insert(v.begin(), "21");
	}

	for (vector<std::string>::size_type i = 0; i != v.size(); ++i) {
		if (i < v.size() - baseN) {
			p_assert_eq(v[i], "21");
		} else {
			p_assert_eq(v[i], baseStringValue);
		}
	}

	return 0;
}

int test_vector_insert_back(Tester& tester)
{
	const size_t nbToInsert = 424242, baseN = 42;
	int baseNumberValue = 42;
	vector<int> v(baseN, baseNumberValue);

	for (int i = 0; i != nbToInsert; ++i) {
		v.insert(v.end(), i);
	}

	for (vector<int>::size_type i = 0; i != v.size(); ++i) {
		if (i < baseN) {
			p_assert_eq(v[i], baseNumberValue);
		} else {
			p_assert_eq(v[i], static_cast<int>(i - baseN));
		}
	}

	return 0;
}

int test_vector_insert_odd(Tester& tester)
{
	const size_t baseN = 4242;
	int baseNumberValue = 42, insertedNumberValue = 21;
	vector<int> v(baseN, baseNumberValue);

	for (vector<int>::size_type i = 0; i != v.size(); ++i) {
		if (i % 2) {
			v.insert(v.begin() + i, insertedNumberValue);
		}
	}

	for (vector<int>::size_type i = 0; i != v.size(); ++i) {
		if (i % 2) {
			p_assert_eq(v[i], insertedNumberValue);
		}
	}
	
	return 0;
}

int test_vector_insert_range(Tester& tester)
{
	const size_t rangeSize = 424242, baseN = 42, insertPos = 3;
	int baseNumberValue = 42;

	vector<int> range;

	for (vector<int>::size_type i = 0; i != rangeSize; ++i) {
		range.push_back(i);
	}

	vector<int> base(baseN, baseNumberValue);

	base.insert(base.begin() + insertPos, range.begin(), range.end());

	for (vector<int>::size_type i = 0; i != base.size(); ++i) {
		if (i >= insertPos && i < insertPos + rangeSize) {
			p_assert_eq(base[i], static_cast<int>(i - insertPos));
		} else {
			p_assert_eq(base[i], baseNumberValue);
		}
	}

	return 0;
}
