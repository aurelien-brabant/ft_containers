#include "vector_testing.hpp"
#include <cstdlib>
#include <cstring>
#include <list>
#include <sstream>
#include <string>

using std::ostringstream;
using std::string;

TEST(test_vector_construct_n_by_value)
{
    const size_t baseN = 424242;
    vector<string> vs(baseN);

    for (size_t i = 0; i != baseN; ++i) {
        p_assert_eq(vs[i], string());
    }

    return 0;
}

TEST(test_vector_construct_n_with_value)
{
    const size_t baseN = 424242;
    const string baseString = "42";
    vector<string> vs(baseN, baseString);

    for (size_t i = 0; i != baseN; ++i) {
        p_assert_eq(vs[i], baseString);
    }

    return 0;
}

TEST(test_vector_range_constructor)
{
    const size_t baseN = 42;
    vector<const char*> range;
    ostringstream oss;

    for (size_t i = 0; i != baseN; ++i) {
        oss << i;
        range.push_back(strdup(oss.str().c_str()));
        oss.str("");
    }

    vector<string> v(range.begin(), range.end());

    assert_expr(v.size() == static_cast<vector<string>::size_type>(
                              range.end() - range.begin()));

    for (vector<string>::size_type i = 0; i != v.size(); ++i) {
        oss << i;
        p_assert_eq(v[i], oss.str());
        oss.str("");
        free((void*)range[i]);
    }

    return 0;
}

// std::list iterators are bidirectional only.
// This should work and compile.

TEST(test_vector_range_with_bidirectional_it)
{
    std::list<short> l;

    for (short i = 0; i != 42; ++i) {
        l.push_back(i);
    }

    vector<int> v(l.begin(), l.end());

    assert_expr(v.size() == l.size());

    for (vector<int>::size_type i = 0; i != v.size(); ++i) {
        p_assert_eq(v[i], static_cast<int>(i));
    }

    return 0;
}
