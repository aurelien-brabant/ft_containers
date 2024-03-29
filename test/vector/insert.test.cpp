#include "vector_testing.hpp"
#include <sstream>
#include <string>

using std::ostringstream;
using std::string;

/**
 * Inserting at the front of a vector is an expensive operation.
 * Time complexity being O(n), where n is the current vector's size at insertion
 * time, using a too big baseN may take a while to be processed.
 */

TEST(test_vector_insert_front)
{
    const size_t nbToInsert = 4242, baseN = 42;
    string baseStringValue("42");
    vector<string> v(baseN, baseStringValue);
    ostringstream oss;

    for (int i = 0; i != nbToInsert; ++i) {
        oss << i;
        v.insert(v.begin(), oss.str());
        oss.str("");
    }

    for (vector<string>::size_type i = 0; i != v.size(); ++i) {
        if (i < v.size() - baseN) {
            oss << nbToInsert - i - 1;
            p_assert_eq(v[i], oss.str());
            oss.str("");
        } else {
            p_assert_eq(v[i], baseStringValue);
        }
    }

    return 0;
}

TEST(test_vector_insert_back)
{
    const size_t nbToInsert = 424242, baseN = 42;
    string baseStringValue = "42";
    vector<string> v(baseN, baseStringValue);
    ostringstream oss;

    for (int i = 0; i != nbToInsert; ++i) {
        oss << i;
        v.insert(v.end(), oss.str());
        oss.str("");
    }

    for (vector<string>::size_type i = 0; i != v.size(); ++i) {
        if (i < baseN) {
            p_assert_eq(v[i], baseStringValue);
        } else {
            oss << (i - baseN);
            p_assert_eq(v[i], oss.str());
            oss.str("");
        }
    }

    return 0;
}

TEST(test_vector_insert_odd)
{
    const size_t baseN = 4242;
    string baseStringValue = "42", insertedStringValue = "21";
    vector<string> v(baseN, baseStringValue);

    for (vector<string>::size_type i = 0; i != v.size(); ++i) {
        if (i % 2) {
            v.insert(v.begin() + i, insertedStringValue);
        }
    }

    for (vector<string>::size_type i = 0; i != v.size(); ++i) {
        if (i % 2) {
            p_assert_eq(v[i], insertedStringValue);
        }
    }

    return 0;
}

TEST(test_vector_insert_range)
{
    const size_t rangeSize = 424242, baseN = 42, insertPos = 3;
    string baseStringValue;
    ostringstream oss;
    vector<string> range;

    for (vector<string>::size_type i = 0; i != rangeSize; ++i) {
        oss << i;
        range.push_back(oss.str());
        oss.str("");
    }

    vector<string> base(baseN, baseStringValue);

    base.insert(base.begin() + insertPos, range.begin(), range.end());

    for (vector<string>::size_type i = 0; i != base.size(); ++i) {
        if (i >= insertPos && i < insertPos + rangeSize) {
            oss << i - insertPos;
            p_assert_eq(base[i], oss.str());
            oss.str("");
        } else {
            p_assert_eq(base[i], baseStringValue);
        }
    }

    return 0;
}

TEST(test_vector_insert_empty)
{
    vector<int> v;

    v.insert(v.begin(), 42);

    p_assert_eq(*v.begin(), 42);

    return 0;
}

TEST(test_vector_insert_many)
{
    size_t baseN = 424242, ipos = baseN / 2, count = 42;
    vector<int> v(baseN, 42);

    v.insert(v.begin() + ipos, count, 21);

    assert_expr(v.size() == baseN + count);

    for (vector<int>::size_type i = 0; i != v.size(); ++i) {
        p_assert_eq(v[i], i >= ipos && i < ipos + count ? 21 : 42);
    }

    return 0;
}

TEST(test_vector_insert_many_back)
{
    vector<int> v;

    for (int i = 0; i != 10; ++i) {
        v.push_back(i);
    }

    v.insert(v.end(), 5, 42);

    if (v.size() != 15) {
        tester.error << "size(): got " << v.size() << " while expecting " << 15;
        return 1;
    }

    for (vector<int>::size_type i = 0; i != v.size(); ++i) {
        p_assert_eq(v[i], i >= 10 ? 42 : static_cast<int>(i));
    }

    return 0;
}
