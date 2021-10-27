#include "stack_testing.hpp"

TEST(test_stack_size)
{
    stack<int> si;

    p_assert_eq(si.size(), 0);

    si.push(42);
    p_assert_eq(si.size(), 1);

    si.push(42);
    p_assert_eq(si.size(), 2);

    si.pop();
    si.pop();
    p_assert_eq(si.size(), 0);

    return 0;
}
