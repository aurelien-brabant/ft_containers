#include "riter_testing.hpp"

int
test_riter_assign(Tester& tester)
{
    std::vector<int> v(10);

    reverse_iterator<std::vector<int>::iterator> rit1(v.end()), rit2;

    rit2 = rit1;

    assert_expr(rit1.base() == rit2.base());

    return 0;
}
