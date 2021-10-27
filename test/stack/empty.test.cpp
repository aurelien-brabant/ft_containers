#include "stack_testing.hpp"

TEST(test_stack_empty)
{
    stack<int> si;

    assert_expr(si.empty() == true);

    si.push(42);
    assert_expr(si.empty() == false);

    si.pop();
    assert_expr(si.empty() == true);

    return 0;
}
