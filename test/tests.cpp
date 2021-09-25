#include "Tester.hpp"
#include "vector.hpp"
#include "assert.hpp"
#include "tests.hpp"

using TEST_VECTOR;

int main(void)
{

	const std::string vectorSuiteName("vector");

	Tester tester;

	tester.registerTest(vectorSuiteName, "constructors", test_vector_construct);
	tester.registerTest(vectorSuiteName, "size()", test_vector_size);
	tester.registerTest(vectorSuiteName, "operator[]", test_vector_subscript);
	tester.registerTest(vectorSuiteName, "valid at()", test_vector_at_valid);
	tester.registerTest(vectorSuiteName, "throwing at()", test_vector_at_throws);
	tester.registerTest(vectorSuiteName, "iterator read loop", test_vector_iterator_read_loop);
	tester.registerTest(vectorSuiteName, "iterator write loop", test_vector_iterator_read_write_loop);
	tester.registerTest(vectorSuiteName, "iterator difference", test_vector_iterator_difference);
	tester.registerTest(vectorSuiteName, "const_iterator loop", test_vector_const_iterator_read_only);


	tester.runAllSuites();

	return 0;
}
