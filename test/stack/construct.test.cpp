#include "stack_testing.hpp"

int
test_stack_default_ctor(Tester& tester)
{
    stack<int, vector<int> > s;

    assert_expr(s.size() == 0);
    assert_expr(s.empty());

    return 0;
}

int
test_stack_copy_ctor(Tester& tester)
{
    vector<int> v;
    size_t baseN = 42;

    for (unsigned i = 0; i != baseN; ++i) {
        v.push_back(i);
    }

    stack<int, vector<int> > s(v);

    assert_expr(s.size() == v.size());

    for (vector<int>::const_reverse_iterator rite = v.rbegin();
         rite != v.rend();
         ++rite) {
        p_assert_eq(s.top(), *rite);
        s.pop();
    }

    assert_expr(s.size() == 0);

    return 0;
}
