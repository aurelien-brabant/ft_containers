#include "vector_testing.hpp"

int
test_vector_push_back(Tester& tester)
{
    vector<unsigned> v;

    for (unsigned i = 0; i != 424242; ++i) {
        v.push_back(i);
    }

    for (vector<unsigned>::size_type i = 0; i != v.size(); ++i) {
        p_assert_eq(v[i], i);
    }

    return 0;
}

int
test_vector_copy_then_push_back(Tester& tester)
{
    vector<int> v(10);

    for (int i = 0; i != 10; ++i) {
        v.push_back(i);
    }

    vector<int>::pointer p = new vector<int>::value_type;

    *p = v.front();

    vector<int> tmp = v;

    tmp.push_back(*p);

    p_assert_eq(tmp.back(), v.front());

    delete p;

    return 0;
}
