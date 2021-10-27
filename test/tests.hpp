#ifndef TESTS_HPP
#define TESTS_HPP
#include "castorno/Tester.hpp"
#include "castorno/assert.hpp"

/////////////////////////////////////////////////
// Lexicographical compare
////////////////////////////////////////////////

TEST(test_lc_first1_less_than_first2);
TEST(test_lc_first1_greater_than_first2);
TEST(test_lc_first1_prefix_of_first2);
TEST(test_lc_first2_prefix_of_first1);
TEST(test_lc_first1_empty);
TEST(test_lc_first2_empty);
TEST(test_lc_both_empty);
TEST(test_lc_ranges_equal);
TEST(test_lc_perf_differ_at_last_element);

TEST(test_lc_cmp_first1_less_than_first2);
TEST(test_lc_cmp_first1_greater_than_first2);
TEST(test_lc_cmp_first1_prefix_of_first2);
TEST(test_lc_cmp_first2_prefix_of_first1);
TEST(test_lc_cmp_first1_empty);
TEST(test_lc_cmp_first2_empty);
TEST(test_lc_cmp_both_empty);
TEST(test_lc_cmp_ranges_equal);
TEST(test_lc_cmp_perf_differ_at_last_element);

/////////////////////////////////////////////////
// equal (ranges)
////////////////////////////////////////////////

TEST(test_equal);
TEST(test_unequal_first_element);
TEST(test_unequal_last_element);
TEST(test_equal_first1_smaller);
TEST(test_equal_subrange);
TEST(test_perf_unequal_at_mid);
TEST(test_pred_equal);
TEST(test_pred_unequal_first_element);
TEST(test_pred_unequal_last_element);
TEST(test_pred_equal_first1_smaller);
TEST(test_pred_equal_subrange);
TEST(test_pred_perf_unequal_at_mid);

/////////////////////////////////////////////////
// VECTOR
////////////////////////////////////////////////

TEST(test_vector_construct_n_by_value);
TEST(test_vector_construct_n_with_value);
TEST(test_vector_range_constructor);
TEST(test_vector_range_with_bidirectional_it);
TEST(test_vector_size);
TEST(test_vector_subscript);
TEST(test_vector_at_valid);
TEST(test_vector_at_throws);
TEST(test_vector_at_const_overload);

// vector<T>::iterator

TEST(test_vector_iterator_read_loop);
TEST(test_vector_iterator_read_write_loop);
TEST(test_vector_iterator_difference);
TEST(test_vector_const_iterator_read_only);
TEST(test_vector_iterator_subscript);
TEST(test_vector_iterator_negative_subscript);
TEST(test_vector_iterator_arrow);
TEST(test_vector_iterator_greater_operator);
TEST(test_vector_iterator_greater_or_equal_operator);
TEST(test_vector_iterator_less_operator);
TEST(test_vector_iterator_less_or_equal_operator);
TEST(test_vector_iterator_equality_operator);
TEST(test_vector_iterator_const_compare_to_non_const);

// vector<T>::reverse_iterator

TEST(test_vector_reverse_iterator_loop);
TEST(test_vector_reviter_write);
TEST(test_vector_reviter_to_const_reviter);
TEST(test_vector_capacity);
TEST(test_vector_greater_capacity_reservation);
TEST(test_vector_smaller_capacity_reservation);
TEST(test_vector_push_back);
TEST(test_vector_copy_then_push_back);
TEST(test_vector_copy_constructor);
TEST(test_vector_assignment_operator_grow);
TEST(test_vector_assignment_operator_shrink);
TEST(test_vector_assignement_operator_to_empty);
TEST(test_vector_empty);
TEST(test_vector_front_value);
TEST(test_vector_front_same_than_begin);
TEST(test_vector_back_value);
TEST(test_vector_back_same_than_end_minus_one);
TEST(test_vector_clear);
TEST(test_vector_insert_front);
TEST(test_vector_insert_back);
TEST(test_vector_insert_odd);
TEST(test_vector_insert_range);
TEST(test_vector_insert_empty);
TEST(test_vector_insert_many);
TEST(test_vector_insert_many_back);
TEST(test_vector_assign);
TEST(test_vector_assign_less);
TEST(test_vector_assign_more);
TEST(test_vector_iterator_assign);
TEST(test_vector_data);
TEST(test_vector_erase_one);
TEST(test_vector_erase_range);
TEST(test_vector_erase_empty_range);
TEST(test_vector_erase_range_all);
TEST(test_vector_eq_operator);
TEST(test_vector_uneq_operator);
TEST(test_vector_gt_operator);
TEST(test_vector_gte_operator);
TEST(test_vector_lt_operator);
TEST(test_vector_lte_operator);
TEST(test_vector_swap);
TEST(test_vector_pop_back);
TEST(test_vector_resize_greater);
TEST(test_vector_resize_smaller);
TEST(test_vector_resize_same);

//////////////////////////////////
// REVERSE ITERATOR TESTS;
/////////////////////////////////

TEST(test_riter_construct_default);
TEST(test_riter_construct_from_iterator);
TEST(test_riter_assign);
TEST(test_riter_add_n);
TEST(test_riter_sub_n);
TEST(test_riter_pre_increment);
TEST(test_riter_post_increment);
TEST(test_riter_pre_decrement);
TEST(test_riter_post_decrement);
TEST(test_riter_add_n_self);
TEST(test_riter_sub_n_self);
TEST(test_riter_sub_riter);
TEST(test_riter_gt);
TEST(test_riter_gte);
TEST(test_riter_lt);
TEST(test_riter_lte);
TEST(test_riter_eq);
TEST(test_riter_neq);
TEST(test_stack_default_ctor);
TEST(test_stack_copy_ctor);

/////////////////////////////////////////////////
// pair, make_pair
////////////////////////////////////////////////

TEST(test_pair_default_ctor);
TEST(test_pair_key_value_ctor);
TEST(test_pair_copy_ctor);
TEST(test_pair_assignment_operator);
TEST(test_make_pair);
TEST(test_pair_operator_eq);
TEST(test_pair_operator_neq);
TEST(test_pair_operator_lt);
TEST(test_pair_operator_lte);
TEST(test_pair_operator_gt);
TEST(test_pair_operator_gte);

/////////////////////////////////////////////////
// map
////////////////////////////////////////////////

TEST(test_map_default_ctor);
TEST(test_map_custom_comp_ctor);
TEST(test_map_range_ctor);
TEST(test_map_insert_one);
TEST(test_map_insert_range);
TEST(test_map_find);
TEST(test_map_erase_one);
TEST(test_map_erase_one_alternate);
TEST(test_map_erase_iterator);
TEST(test_map_erase_random_iterator);
TEST(test_map_erase_random_range);
TEST(test_map_insert_one_string);
TEST(test_map_clear);
TEST(test_map_iterator_decrement_end);
TEST(test_map_iterator_decrement_reverse_loop);
TEST(test_map_iterator_prefix_increment);
TEST(test_map_iterator_postfix_increment);
TEST(test_map_iterator_to_const_iterator);
TEST(test_map_iterator_const_instance);
TEST(test_map_lower_bound_one_match_only);
TEST(test_map_lower_bound_find_smallest);
TEST(test_map_lower_bound_not_found);
TEST(test_map_lower_bound_const_overload);
TEST(test_map_lower_bound_const_overload);
TEST(test_map_upper_bound_one_match_only);
TEST(test_map_upper_bound_find_smallest);
TEST(test_map_upper_bound_not_found);
TEST(test_map_upper_bound_const_overload);
TEST(test_map_upper_bound_const_overload);
TEST(test_map_equal_range_begin_to_end);
TEST(test_map_equal_range_perf_not_found);
TEST(test_map_equal_range_const_overload);
TEST(test_map_assignment_operator);
TEST(test_map_copy_constructor);
TEST(test_map_copy_cleared);
TEST(test_map_swap);
TEST(test_map_size);
TEST(test_map_size_empty);
TEST(test_map_subscript_ro);
TEST(test_map_subscript_rw);
TEST(test_map_at_ro);
TEST(test_map_at_rw);
TEST(test_map_at_out_of_range);
TEST(test_map_at_const_overload);
TEST(test_map_empty);
TEST(test_map_riter_random);
TEST(test_map_riter_sequence);

#endif
