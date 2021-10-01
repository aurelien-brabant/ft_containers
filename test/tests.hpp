#ifndef TESTS_HPP
# define TESTS_HPP
# include "castorno/Tester.hpp"

/////////////////////////////////////////////////
// VECTOR
////////////////////////////////////////////////

int test_vector_construct_n_by_value(Tester& tester);
int test_vector_construct_n_with_value(Tester& tester);

int	test_vector_size(Tester& tester);

int test_vector_subscript(Tester& tester);

int test_vector_at_valid(Tester& tester);
int test_vector_at_throws(Tester& tester);

// vector<T>::iterator

int test_vector_iterator_read_loop(Tester& tester);
int test_vector_iterator_read_write_loop(Tester& tester);
int test_vector_iterator_difference(Tester& tester);
int test_vector_const_iterator_read_only(Tester& tester);
int test_vector_iterator_subscript(Tester& tester);
int test_vector_iterator_negative_subscript(Tester& tester);
int test_vector_iterator_arrow(Tester& tester);
int test_vector_iterator_greater_operator(Tester& tester);
int test_vector_iterator_greater_or_equal_operator(Tester& tester);
int test_vector_iterator_less_operator(Tester& tester);
int test_vector_iterator_less_or_equal_operator(Tester& tester);
int test_vector_iterator_equality_operator(Tester& tester);
int test_vector_iterator_const_compare_to_non_const(Tester& tester);

// vector<T>::reverse_iterator

int test_vector_reverse_iterator_loop(Tester& tester);
int test_vector_reviter_write(Tester& tester);
int test_vector_reviter_to_const_reviter(Tester& tester);

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
int test_vector_insert_empty(Tester& tester);

//////////////////////////////////
// REVERSE ITERATOR TESTS
/////////////////////////////////

int test_riter_construct_default(Tester& tester);
int test_riter_construct_from_iterator(Tester& tester);
int test_riter_assign(Tester& tester);
int test_riter_add_n(Tester& tester);
int test_riter_sub_n(Tester& tester);
int test_riter_pre_increment(Tester& tester);
int test_riter_post_increment(Tester& tester);
int test_riter_pre_decrement(Tester& tester);
int test_riter_add_n_self(Tester& tester);
int test_riter_sub_n_self(Tester& tester);
int test_riter_sub_riter(Tester& tester);

# endif
