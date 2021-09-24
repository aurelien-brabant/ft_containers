#include "Tester.hpp"
#include "vector.hpp"
#include "assert.hpp"

using ft::vector;

int init_vector(Tester& tester)
{
	(void)tester;

	vector<int> v, v1(10000), v2(100000, 42);

	return 0;
}

int	test_size(Tester& tester)
{
	vector<int> v1(5), v2(0), v3(42);

	p_assert_eq(v1.size(), 5);
	p_assert_eq(v2.size(), 0);
	p_assert_eq(v3.size(), 42);

	return 0;
}

int	iterate_with_index(Tester& tester)
{
	vector<int> v1(10000, 21);

	for (vector<int>::size_type i = 0; i != v1.size(); ++i) {
		p_assert_eq(v1[i], 21);
	}

	return 0;
}

int main(void)
{
	Tester tester;

	tester.registerTest("vector", "construct vectors", &init_vector);
	tester.registerTest("vector", "size() member function", &test_size);
	tester.registerTest("vector", "iteration with index", &iterate_with_index);

	tester.runAllSuites();

	return 0;
}
