#include "tests.hpp"
#include "castorno/Tester.hpp"
#include "castorno/assert.hpp"
#include "map.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "vector.hpp"
#include <iostream>
#include <stdexcept>

int
main(int argc, char** argv)
{
    (void)argc;

    const std::string lcSuiteName("lexicographical compare");
    const std::string equalSuiteName("equal (ranges)");
    const std::string riterSuiteName("reverse iterator");
    const std::string vectorSuiteName("vector");
    const std::string stackSuiteName("stack");
    const std::string pairSuiteName("pair");
    const std::string mapSuiteName("map");

    Tester tester(*argv);

    tester.registerTest(
      lcSuiteName, "first1 less than first2", test_lc_first1_less_than_first2);
    tester.registerTest(lcSuiteName,
                        "first1 greater than first2",
                        test_lc_first1_greater_than_first2);
    tester.registerTest(
      lcSuiteName, "first1 prefix of first2", test_lc_first1_prefix_of_first2);
    tester.registerTest(
      lcSuiteName, "first2 prefix of first1", test_lc_first2_prefix_of_first1);
    tester.registerTest(lcSuiteName, "equal ranges", test_lc_ranges_equal);
    tester.registerTest(lcSuiteName, "first1 empty", test_lc_first1_empty);
    tester.registerTest(lcSuiteName, "first2 empty", test_lc_first2_empty);
    tester.registerTest(lcSuiteName, "both empty ranges", test_lc_both_empty);
    tester.registerTest(lcSuiteName,
                        "perf test, first1 less than first2",
                        test_lc_perf_differ_at_last_element);
    tester.registerTest(lcSuiteName,
                        "(cmp) first1 less than first2",
                        test_lc_cmp_first1_less_than_first2);
    tester.registerTest(lcSuiteName,
                        "(cmp) first1 greater than first2",
                        test_lc_cmp_first1_greater_than_first2);
    tester.registerTest(lcSuiteName,
                        "(cmp) first1 prefix of first2",
                        test_lc_cmp_first1_prefix_of_first2);
    tester.registerTest(lcSuiteName,
                        "(cmp) first2 prefix of first1",
                        test_lc_cmp_first2_prefix_of_first1);
    tester.registerTest(
      lcSuiteName, "(cmp) equal ranges", test_lc_cmp_ranges_equal);
    tester.registerTest(
      lcSuiteName, "(cmp) first1 empty", test_lc_cmp_first1_empty);
    tester.registerTest(
      lcSuiteName, "(cmp) first2 empty", test_lc_cmp_first2_empty);
    tester.registerTest(
      lcSuiteName, "(cmp) both empty ranges", test_lc_cmp_both_empty);
    tester.registerTest(lcSuiteName,
                        "(cmp) perf test, first1 less than first2",
                        test_lc_cmp_perf_differ_at_last_element);

    tester.registerTest(equalSuiteName, "equal ranges", test_equal);
    tester.registerTest(equalSuiteName,
                        "unequal ranges (first elem)",
                        test_unequal_first_element);
    tester.registerTest(
      equalSuiteName, "unequal ranges (last elem)", test_unequal_last_element);
    tester.registerTest(
      equalSuiteName, "equal ranges first1 smaller", test_equal_first1_smaller);
    tester.registerTest(equalSuiteName, "equal subrange", test_equal_subrange);
    tester.registerTest(equalSuiteName,
                        "perf test, unequal at midrange",
                        test_perf_unequal_at_mid);

    tester.registerTest(equalSuiteName, "(pred) equal ranges", test_pred_equal);
    tester.registerTest(equalSuiteName,
                        "(pred) unequal ranges (first elem)",
                        test_pred_unequal_first_element);
    tester.registerTest(equalSuiteName,
                        "(pred) unequal ranges (last elem)",
                        test_pred_unequal_last_element);
    tester.registerTest(equalSuiteName,
                        "(pred) equal ranges first1 smaller",
                        test_pred_equal_first1_smaller);
    tester.registerTest(
      equalSuiteName, "(pred) equal subrange", test_pred_equal_subrange);
    tester.registerTest(equalSuiteName,
                        "(pred) perf test, unequal at midrange",
                        test_pred_perf_unequal_at_mid);

    tester.registerTest(
      riterSuiteName, "default CTOR", test_riter_construct_default);
    tester.registerTest(
      riterSuiteName, "iterator CTOR", test_riter_construct_from_iterator);
    tester.registerTest(riterSuiteName, "operator=", test_riter_assign);
    tester.registerTest(
      riterSuiteName, "operator+ (difference_type)", test_riter_add_n);
    tester.registerTest(
      riterSuiteName, "operator+= (difference_type)", test_riter_add_n_self);
    tester.registerTest(
      riterSuiteName, "operator- (difference_type)", test_riter_sub_n);
    tester.registerTest(
      riterSuiteName, "operator-= (difference_type)", test_riter_sub_n_self);
    tester.registerTest(
      riterSuiteName, "operator++ (pre)", test_riter_pre_increment);
    tester.registerTest(
      riterSuiteName, "operator++ (post)", test_riter_post_increment);
    tester.registerTest(
      riterSuiteName, "operator-- (pre)", test_riter_pre_decrement);
    tester.registerTest(
      riterSuiteName, "operator-- (post)", test_riter_post_decrement);
    tester.registerTest(
      riterSuiteName, "operator- (iterators)", test_riter_sub_riter);
    tester.registerTest(riterSuiteName, "operator>", test_riter_gt);
    tester.registerTest(riterSuiteName, "operator>=", test_riter_gte);
    tester.registerTest(riterSuiteName, "operator<", test_riter_lt);
    tester.registerTest(riterSuiteName, "operator<=", test_riter_lte);
    tester.registerTest(riterSuiteName, "operator==", test_riter_eq);
    tester.registerTest(riterSuiteName, "operator!=", test_riter_neq);

    tester.registerTest(vectorSuiteName,
                        "construct n by value",
                        test_vector_construct_n_by_value);
    tester.registerTest(vectorSuiteName,
                        "construct n with value",
                        test_vector_construct_n_with_value);
    tester.registerTest(
      vectorSuiteName, "construct with range", test_vector_range_constructor);
    tester.registerTest(vectorSuiteName,
                        "construct with range, using bidirect_it",
                        test_vector_range_with_bidirectional_it);

    tester.registerTest(
      vectorSuiteName, "copy constructor", test_vector_copy_constructor);

    tester.registerTest(vectorSuiteName,
                        "operator= (growth)",
                        test_vector_assignment_operator_grow);
    tester.registerTest(vectorSuiteName,
                        "operator= (shrink)",
                        test_vector_assignment_operator_shrink);
    tester.registerTest(vectorSuiteName,
                        "operator= (to empty)",
                        test_vector_assignement_operator_to_empty);

    tester.registerTest(vectorSuiteName, "size()", test_vector_size);

    tester.registerTest(vectorSuiteName, "operator[]", test_vector_subscript);

    tester.registerTest(vectorSuiteName, "valid at()", test_vector_at_valid);
    tester.registerTest(
      vectorSuiteName, "throwing at()", test_vector_at_throws);
    tester.registerTest(
      vectorSuiteName, "at const overload", test_vector_at_const_overload);

    tester.registerTest(
      vectorSuiteName, "iterator read loop", test_vector_iterator_read_loop);
    tester.registerTest(vectorSuiteName,
                        "iterator write loop",
                        test_vector_iterator_read_write_loop);
    tester.registerTest(
      vectorSuiteName, "iterator difference", test_vector_iterator_difference);
    tester.registerTest(vectorSuiteName,
                        "const_iterator loop",
                        test_vector_const_iterator_read_only);
    tester.registerTest(vectorSuiteName,
                        "iterator [n] operator (n >= 0)",
                        test_vector_iterator_subscript);
    tester.registerTest(vectorSuiteName,
                        "iterator [n] operator (n < 0)",
                        test_vector_iterator_negative_subscript);
    tester.registerTest(
      vectorSuiteName, "iterator -> operator", test_vector_iterator_arrow);
    tester.registerTest(vectorSuiteName,
                        "iterator > operator",
                        test_vector_iterator_greater_operator);
    tester.registerTest(vectorSuiteName,
                        "iterator >= operator",
                        test_vector_iterator_greater_or_equal_operator);
    tester.registerTest(vectorSuiteName,
                        "iterator < operator",
                        test_vector_iterator_less_operator);
    tester.registerTest(vectorSuiteName,
                        "iterator <= operator",
                        test_vector_iterator_less_or_equal_operator);
    tester.registerTest(vectorSuiteName,
                        "iterator == operator",
                        test_vector_iterator_equality_operator);
    tester.registerTest(vectorSuiteName,
                        "compare const and non-const iterator",
                        test_vector_iterator_const_compare_to_non_const);

    tester.registerTest(vectorSuiteName,
                        "reverse iterator loop read",
                        test_vector_reverse_iterator_loop);
    tester.registerTest(vectorSuiteName,
                        "reverse iterator loop write",
                        test_vector_reviter_write);
    tester.registerTest(vectorSuiteName,
                        "reverse iterator to const_reverse_iterator",
                        test_vector_reviter_to_const_reviter);

    tester.registerTest(vectorSuiteName, "capacity()", test_vector_capacity);
    tester.registerTest(vectorSuiteName,
                        "reserve(n) (n > capacity())",
                        test_vector_greater_capacity_reservation);
    tester.registerTest(vectorSuiteName,
                        "reserve(n) (n <= capacity())",
                        test_vector_smaller_capacity_reservation);

    tester.registerTest(vectorSuiteName, "push_back()", test_vector_push_back);
    tester.registerTest(vectorSuiteName,
                        "copy CTOR then push_back()",
                        test_vector_copy_then_push_back);

    tester.registerTest(vectorSuiteName, "empty()", test_vector_empty);

    tester.registerTest(vectorSuiteName, "front()", test_vector_front_value);
    tester.registerTest(vectorSuiteName,
                        "&front() == &(*begin())",
                        test_vector_front_same_than_begin);

    tester.registerTest(vectorSuiteName, "back()", test_vector_back_value);
    tester.registerTest(vectorSuiteName,
                        "&back() == &(*(end() - 1))",
                        test_vector_back_same_than_end_minus_one);

    tester.registerTest(vectorSuiteName, "clear()", test_vector_clear);

    tester.registerTest(
      vectorSuiteName, "insert front", test_vector_insert_front);
    tester.registerTest(
      vectorSuiteName, "insert back", test_vector_insert_back);
    tester.registerTest(
      vectorSuiteName, "insert before each odd nb", test_vector_insert_odd);
    tester.registerTest(
      vectorSuiteName, "insert in empty vector", test_vector_insert_empty);
    tester.registerTest(
      vectorSuiteName, "insert range", test_vector_insert_range);
    tester.registerTest(
      vectorSuiteName, "insert many", test_vector_insert_many);
    tester.registerTest(
      vectorSuiteName, "insert many back", test_vector_insert_many_back);

    tester.registerTest(vectorSuiteName, "assign fill", test_vector_assign);
    tester.registerTest(
      vectorSuiteName, "assign less", test_vector_assign_less);
    tester.registerTest(
      vectorSuiteName, "assign more", test_vector_assign_more);
    tester.registerTest(
      vectorSuiteName, "assign range", test_vector_iterator_assign);

    tester.registerTest(vectorSuiteName, "data()", test_vector_data);

    tester.registerTest(vectorSuiteName, "erase one", test_vector_erase_one);
    tester.registerTest(
      vectorSuiteName, "erase range", test_vector_erase_range);
    tester.registerTest(
      vectorSuiteName, "erase empty range", test_vector_erase_empty_range);
    tester.registerTest(
      vectorSuiteName, "erase range all elements", test_vector_erase_range_all);

    tester.registerTest(vectorSuiteName, "operator==", test_vector_eq_operator);
    tester.registerTest(
      vectorSuiteName, "operator!=", test_vector_uneq_operator);
    tester.registerTest(vectorSuiteName, "operator>", test_vector_gt_operator);
    tester.registerTest(
      vectorSuiteName, "operator>=", test_vector_gte_operator);
    tester.registerTest(vectorSuiteName, "operator<", test_vector_lt_operator);
    tester.registerTest(
      vectorSuiteName, "operator<=", test_vector_lte_operator);

    tester.registerTest(vectorSuiteName,
                        "swap (member and std:: specialization)",
                        test_vector_swap);

    tester.registerTest(vectorSuiteName, "pop_back()", test_vector_pop_back);

    tester.registerTest(
      vectorSuiteName, "resize (n > size())", test_vector_resize_greater);
    tester.registerTest(
      vectorSuiteName, "resize (n < size())", test_vector_resize_smaller);
    tester.registerTest(
      vectorSuiteName, "resize (n == size())", test_vector_resize_same);

    tester.registerTest(
      stackSuiteName, "default constructor", test_stack_default_ctor);
    tester.registerTest(
      stackSuiteName, "copy constructor", test_stack_copy_ctor);

    tester.registerTest(pairSuiteName, "default CTOR", test_pair_default_ctor);
    tester.registerTest(
      pairSuiteName, "key value CTOR", test_pair_key_value_ctor);
    tester.registerTest(pairSuiteName, "copy CTOR", test_pair_copy_ctor);
    tester.registerTest(
      pairSuiteName, "assignment operator", test_pair_assignment_operator);
    tester.registerTest(pairSuiteName, "make_pair", test_make_pair);
    tester.registerTest(pairSuiteName, "operator==", test_pair_operator_eq);
    tester.registerTest(pairSuiteName, "operator!=", test_pair_operator_neq);
    tester.registerTest(pairSuiteName, "operator<", test_pair_operator_lt);
    tester.registerTest(pairSuiteName, "operator<=", test_pair_operator_lte);
    tester.registerTest(pairSuiteName, "operator>", test_pair_operator_gt);
    tester.registerTest(pairSuiteName, "operator>=", test_pair_operator_gte);

    tester.registerTest(mapSuiteName, "default CTOR", test_map_default_ctor);
    tester.registerTest(
      mapSuiteName, "custom cmp CTOR", test_map_custom_comp_ctor);
    tester.registerTest(
      mapSuiteName, "copy assignment", test_map_assignment_operator);
    tester.registerTest(mapSuiteName, "copy CTOR", test_map_copy_constructor);
    tester.registerTest(mapSuiteName, "copy cleared", test_map_copy_cleared);
    tester.registerTest(mapSuiteName, "insert one", test_map_insert_one);
    tester.registerTest(
      mapSuiteName, "insert one std::string", test_map_insert_one_string);
    tester.registerTest(mapSuiteName, "insert range", test_map_insert_range);
    tester.registerTest(mapSuiteName, "find one", test_map_find);
    tester.registerTest(mapSuiteName, "erase one", test_map_erase_one);
    tester.registerTest(
      mapSuiteName, "erase one alt", test_map_erase_one_alternate);
    tester.registerTest(
      mapSuiteName, "erase iterator", test_map_erase_iterator);
    tester.registerTest(mapSuiteName, "clear", test_map_clear);
    tester.registerTest(mapSuiteName,
                        "iterator prefix decrement end",
                        test_map_iterator_decrement_end);
    tester.registerTest(mapSuiteName,
                        "iterator prefix decrement reverse loop",
                        test_map_iterator_decrement_reverse_loop);
    tester.registerTest(mapSuiteName,
                        "iterator prefix increment",
                        test_map_iterator_prefix_increment);
    tester.registerTest(mapSuiteName,
                        "iterator postfix increment",
                        test_map_iterator_postfix_increment);
    tester.registerTest(mapSuiteName,
                        "iterator to const_iterator",
                        test_map_iterator_to_const_iterator);
    tester.registerTest(mapSuiteName,
                        "lower_bound one match only",
                        test_map_lower_bound_one_match_only);
    tester.registerTest(mapSuiteName,
                        "lower bound smallest match",
                        test_map_lower_bound_find_smallest);
    tester.registerTest(
      mapSuiteName, "lower bound not found", test_map_lower_bound_not_found);
    tester.registerTest(mapSuiteName,
                        "lower bound const overload",
                        test_map_lower_bound_const_overload);
    tester.registerTest(mapSuiteName,
                        "upper_bound one match only",
                        test_map_upper_bound_one_match_only);
    tester.registerTest(mapSuiteName,
                        "upper bound smallest match",
                        test_map_upper_bound_find_smallest);
    tester.registerTest(
      mapSuiteName, "upper bound not found", test_map_upper_bound_not_found);
    tester.registerTest(mapSuiteName,
                        "upper bound const overload",
                        test_map_upper_bound_const_overload);
    tester.registerTest(mapSuiteName,
                        "equal_range begin to end",
                        test_map_equal_range_begin_to_end);
    tester.registerTest(mapSuiteName,
                        "equal range perf not found",
                        test_map_equal_range_perf_not_found);
    tester.registerTest(mapSuiteName,
                        "equal range const overload",
                        test_map_equal_range_const_overload);

    if (argc > 1) {
        bool ret = true;

        for (int i = 1; i != argc; ++i) {
            ret = tester.runSuite(argv[i]);
        }

        return ret;
    }

    return tester.runAllSuites() ? 0 : 1;
}
