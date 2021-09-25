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

	tester.registerTest(vectorSuiteName, "copy constructor", test_vector_copy_constructor);

	tester.registerTest(vectorSuiteName, "operator= (growth)", test_vector_assignment_operator_grow);
	tester.registerTest(vectorSuiteName, "operator= (shrink)", test_vector_assignment_operator_shrink);
	tester.registerTest(vectorSuiteName, "operator= (to empty)", test_vector_assignement_operator_to_empty);

	tester.registerTest(vectorSuiteName, "size()", test_vector_size);

	tester.registerTest(vectorSuiteName, "operator[]", test_vector_subscript);

	tester.registerTest(vectorSuiteName, "valid at()", test_vector_at_valid);
	tester.registerTest(vectorSuiteName, "throwing at()", test_vector_at_throws);

	tester.registerTest(vectorSuiteName, "iterator read loop", test_vector_iterator_read_loop);
	tester.registerTest(vectorSuiteName, "iterator write loop", test_vector_iterator_read_write_loop);
	tester.registerTest(vectorSuiteName, "iterator difference", test_vector_iterator_difference);
	tester.registerTest(vectorSuiteName, "const_iterator loop", test_vector_const_iterator_read_only);

	tester.registerTest(vectorSuiteName, "capacity()", test_vector_capacity);
	tester.registerTest(vectorSuiteName, "reserve(n) (n > capacity())", test_vector_greater_capacity_reservation);
	tester.registerTest(vectorSuiteName, "reserve(n) (n <= capacity())", test_vector_smaller_capacity_reservation);

	tester.registerTest(vectorSuiteName, "push_back()", test_vector_push_back);

	tester.registerTest(vectorSuiteName, "empty()", test_vector_empty);
	
	tester.registerTest(vectorSuiteName, "front()", test_vector_front_value);
	tester.registerTest(vectorSuiteName, "&front() == &(*begin())", test_vector_front_same_than_begin);

	tester.registerTest(vectorSuiteName, "back()", test_vector_back_value);
	tester.registerTest(vectorSuiteName, "&back() == &(*(end() - 1))", test_vector_back_same_than_end_minus_one);

	tester.runAllSuites();

	return 0;
}