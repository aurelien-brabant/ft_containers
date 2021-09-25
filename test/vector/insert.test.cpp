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
