#ifndef TESTS_HPP
# define TESTS_HPP
# include "Tester.hpp"

/////////////////////////////////////////////////
// VECTOR
////////////////////////////////////////////////

int test_vector_construct(Tester& tester);

int	test_vector_size(Tester& tester);

int test_vector_subscript(Tester& tester);

int test_vector_at_valid(Tester& tester);
int test_vector_at_throws(Tester& tester);

int test_vector_iterator_read_loop(Tester& tester);
int test_vector_iterator_read_write_loop(Tester& tester);
int test_vector_iterator_difference(Tester& tester);
int test_vector_const_iterator_read_only(Tester& tester);

int test_vector_capacity(Tester& tester);
int test_vector_greater_capacity_reservation(Tester& tester);
int test_vector_smaller_capacity_reservation(Tester& tester);

int test_vector_push_back(Tester& tester);

int test_vector_copy_constructor(Tester& tester);
int test_vector_assignment_operator_grow(Tester& tester);
int test_vector_assignment_operator_shrink(Tester& tester);
int test_vector_assignement_operator_to_empty(Tester& tester);

int test_vector_empty(Tester& tester);

int test_vector_front_value(Tester& tester);
int test_vector_front_same_than_begin(Tester& tester);

int test_vector_back_value(Tester& tester);
int test_vector_back_same_than_end_minus_one(Tester& tester);

int test_vector_clear(Tester& tester);

int test_vector_insert_front(Tester& tester);
int test_vector_insert_back(Tester& tester);
int test_vector_insert_odd(Tester& tester);
int test_vector_insert_range(Tester& tester);

# endif
