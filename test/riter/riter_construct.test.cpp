#include "riter_testing.hpp"

int
test_riter_construct_default(Tester& tester)
{
    reverse_iterator<std::vector<int>::iterator> rit;

    (void)tester;

    return 0;
}

int
test_riter_construct_from_iterator(Tester& tester)
{
    std::vector<int> v;

    for (int i = 0; i != 42; ++i) {
        v.push_back(i);
    }

    reverse_iterator<std::vector<int>::iterator> rbegin(v.end()),
      rend(v.begin());

    int i = 42;
    while (rbegin != rend) {
        p_assert_eq(*rbegin++, --i);
    }

    return 0;
}
