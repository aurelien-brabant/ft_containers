#include "vector_testing.hpp"

int test_vector_construct(Tester& tester)
{
	(void)tester;

	vector<int> v, v1(10000), v2(100000, 42);

	return 0;
}
