#include <stdexcept>
#include <iostream>
#include "Tester.hpp"
#include "vector.hpp"
#include "assert.hpp"
#include "tests.hpp"

int main(int argc, char **argv)
{
	(void)argc;

	const std::string riterSuiteName("reverse iterator");
	const std::string vectorSuiteName("vector");

	Tester tester(*argv);

	tester.registerTest(vectorSuiteName, "construct n by value", test_vector_construct_n_by_value);
	tester.registerTest(vectorSuiteName, "construct n with value", test_vector_construct_n_with_value);

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

	tester.registerTest(vectorSuiteName, "const_iterator loop", test_vector_reverse_iterator_loop);

	tester.registerTest(vectorSuiteName, "capacity()", test_vector_capacity);
	tester.registerTest(vectorSuiteName, "reserve(n) (n > capacity())", test_vector_greater_capacity_reservation);
	tester.registerTest(vectorSuiteName, "reserve(n) (n <= capacity())", test_vector_smaller_capacity_reservation);

	tester.registerTest(vectorSuiteName, "push_back()", test_vector_push_back);

	tester.registerTest(vectorSuiteName, "empty()", test_vector_empty);
	
	tester.registerTest(vectorSuiteName, "front()", test_vector_front_value);
	tester.registerTest(vectorSuiteName, "&front() == &(*begin())", test_vector_front_same_than_begin);

	tester.registerTest(vectorSuiteName, "back()", test_vector_back_value);
	tester.registerTest(vectorSuiteName, "&back() == &(*(end() - 1))", test_vector_back_same_than_end_minus_one);

	tester.registerTest(vectorSuiteName,"clear()", test_vector_clear);

	tester.registerTest(vectorSuiteName, "insert front", test_vector_insert_front);
	tester.registerTest(vectorSuiteName, "insert back", test_vector_insert_back);
	tester.registerTest(vectorSuiteName, "insert before each odd nb", test_vector_insert_odd);
	tester.registerTest(vectorSuiteName, "insert in empty vector", test_vector_insert_empty);
	tester.registerTest(vectorSuiteName, "insert range", test_vector_insert_range);

	try {
		tester.runAllSuites();
	} catch (std::exception &e) {
		std::cerr << e.what() << "\n";
	}

	return 0;
}
