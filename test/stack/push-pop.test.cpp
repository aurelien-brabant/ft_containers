#include "stack_testing.hpp"

TEST(test_stack_push_pop_top)
{
    unsigned baseN = 1000000;
    std::vector<int> vi;
    stack<int> si;

    for (unsigned i = 0; i != baseN; ++i) {
        vi.push_back(i);
    }

    for (std::vector<int>::const_iterator cit = vi.begin(); cit != vi.end();
         ++cit) {
        si.push(*cit);
    }

    for (std::vector<int>::const_reverse_iterator rcit = vi.rbegin();
         rcit != vi.rend();
         ++rcit) {
        p_assert_eq(si.top(), *rcit);
        si.pop();
    }

    return 0;
}
