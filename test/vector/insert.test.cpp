#include "vector_testing.hpp"

/**
 * Inserting at the front of a vector is an expensive operation.
 * Time complexity being O(n), where n is the current vector's size at insertion time,
 * using a too big baseN may take a while to be processed.
 */

int test_vector_insert_front(Tester& tester)
{
	const size_t nbToInsert = 4242, baseN = 42;
	int baseNumberValue = 42;
	vector<int> v(baseN, baseNumberValue);

	for (int i = 0; i != nbToInsert; ++i) {
		vector<int>::iterator it = v.insert(v.begin(), i);
		assert_eq(it, v.begin());
	}

	for (vector<int>::size_type i = 0; i != v.size(); ++i) {
		if (i < v.size() - baseN) {
			p_assert_eq(v[i], static_cast<int>(nbToInsert - i - 1));
		} else {
			p_assert_eq(v[i], baseNumberValue);
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
		vector<int>::iterator it = v.insert(v.end(), i);
		assert_eq(it, v.end() - 1);
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
			vector<int>::iterator it = v.insert(v.begin() + i, insertedNumberValue);
			assert_eq(it, v.begin() + i);
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

	vector<int>::iterator it = base.insert(base.begin() + insertPos, range.begin(), range.end());
	assert_eq(it, base.begin() + insertPos);

	for (vector<int>::size_type i = 0; i != base.size(); ++i) {
		if (i >= insertPos && i < insertPos + rangeSize) {
			p_assert_eq(base[i], static_cast<int>(i - insertPos));
		} else {
			p_assert_eq(base[i], baseNumberValue);
		}
	}

	return 0;
}