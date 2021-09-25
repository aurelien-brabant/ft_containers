#ifndef TESTS_HPP
# define TESTS_HPP

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

# endif
