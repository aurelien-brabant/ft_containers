#include "vector_testing.hpp"
#include <sstream>
#include <string>

using std::ostringstream;
using std::string;

int
test_vector_erase_one(Tester& tester)
{
    size_t baseN = 424242;
    vector<int> v;

    for (size_t i = 0; i != baseN; ++i) {
        v.push_back(static_cast<int>(i));
    }

    vector<int>::iterator it1 = v.erase(v.begin()), it2 = v.erase(v.end() - 1),
                          it3 = v.erase(v.begin() + (baseN / 2));

    assert_expr(it1 == v.begin());
    assert_expr(it2 == v.end() + 1); // invalidated
    assert_expr(it3 == v.begin() + (baseN / 2));

    assert_expr(v.size() == baseN - 3);

    for (vector<int>::size_type i = 0; i != v.size(); ++i) {
        if (i < baseN / 2) {
            p_assert_eq(v[i], static_cast<int>(i + 1));
        } else if (i == baseN - 1) {
            p_assert_eq(v[i], static_cast<int>(baseN - 2));
        } else {
            p_assert_eq(v[i], static_cast<int>(i + 2));
        }
    }

    return 0;
}

int
test_vector_erase_range(Tester& tester)
{
    size_t baseN = 424242, pos1 = baseN / 4, pos2 = baseN / 2;

    vector<string> vs;
    ostringstream oss;

    for (size_t i = 0; i != baseN; ++i) {
        oss << i;
        vs.push_back(oss.str());
        oss.str("");
    }

    vector<string>::size_type old_size = vs.size();

    vector<string>::const_iterator cit_before = vs.begin() + pos2;
    vector<string>::const_iterator cit =
      vs.erase(vs.begin() + pos1, vs.begin() + pos2);

    assert_expr(vs.size() == old_size - (pos2 - pos1));
    assert_expr(cit == cit_before - (pos2 - pos1));

    for (vector<string>::size_type i = 0; i != vs.size(); ++i) {
        if (i < pos1) {
            oss << i;
        } else {
            oss << (i + (pos2 - pos1));
        }
        p_assert_eq(vs[i], oss.str());
        oss.str("");
    }

    return 0;
}

/**
 * When an empty range is given, the first iterator should not be dereferenced.
 */

int
test_vector_erase_empty_range(Tester& tester)
{
    vector<int> v(42);

    vector<int>::size_type old_size = v.size();

    vector<int>::iterator begin = v.end(), last = v.end(),
                          ret = v.erase(begin, last);

    assert_expr(ret == last);
    assert_expr(old_size == v.size()); /* size should not have changed */

    return 0;
}

int
test_vector_erase_range_all(Tester& tester)
{
    vector<int> v(42);

    vector<int>::const_iterator ret = v.erase(v.begin(), v.end());

    assert_expr(v.size() == 0);
    assert_expr(ret == v.end());

    return 0;
}
