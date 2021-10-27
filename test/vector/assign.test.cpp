#include "vector_testing.hpp"
#include <sstream>
#include <string>

using std::ostringstream;
using std::string;

TEST(test_vector_assign)
{
    const size_t baseN = 424242;

    vector<string> v(baseN);

    v.assign(baseN, "42");

    for (vector<int>::size_type i = 0; i != v.size(); ++i) {
        p_assert_eq(v[i], "42");
    }

    return 0;
}

TEST(test_vector_assign_less)
{
    vector<int> v(42);

    v.assign(21, 21);

    assert_expr(v.size() == 21);

    for (vector<int>::size_type i = 0; i != v.size(); ++i) {
        p_assert_eq(v[i], 21);
    }

    return 0;
}

TEST(test_vector_assign_more)
{
    vector<int> v(21);

    v.assign(42, 42);

    assert_expr(v.size() == 42);

    for (vector<int>::size_type i = 0; i != v.size(); ++i) {
        p_assert_eq(v[i], 42);
    }

    return 0;
}

TEST(test_vector_iterator_assign)
{
    const size_t baseN = 424242;
    vector<string> v(baseN), pool;
    ostringstream oss;

    for (size_t i = 0; i < baseN / 2; ++i) {
        oss << i;
        pool.push_back(oss.str());
        oss.str("");
    }

    v.assign(pool.begin(), pool.end());

    for (vector<int>::size_type i = 0; i != v.size(); ++i) {
        if (i < baseN / 2) {
            oss << i;
            p_assert_eq(v[i], oss.str());
            oss.str("");
        } else {
            p_assert_eq(v[i], string());
        }
    }

    return 0;
}
