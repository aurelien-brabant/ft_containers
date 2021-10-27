#include "map_testing.hpp"

TEST(test_map_erase_one)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    for (unsigned i = 0; i != baseN; ++i) {
        assert_expr(m.erase(i) == 1);
    }

    p_assert_eq(m.size(), 0);

    // elements should have been properly deleted, thus erase must return 0
    for (unsigned i = 0; i != baseN; ++i) {
        assert_expr(m.erase(i) == 0);
    }

    return 0;
}

TEST(test_map_erase_one_alternate)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    // erase even keys only
    for (unsigned i = 0; i < baseN; i += 2) {
        assert_expr(m.erase(i) == 1);
    }

    size_t erasedEvenNumbers = baseN / 2;

    assert_expr(m.size() == baseN - erasedEvenNumbers);

    unsigned i = 1;
    for (map<unsigned, unsigned>::const_iterator cit = m.begin();
         cit != m.end();
         ++cit) {
        p_assert_eq(cit->first, i);
        i += 2;
    }

    return 0;
}

TEST(test_map_erase_iterator)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    for (map<unsigned, unsigned>::iterator it = m.begin(); it != m.end();) {
        m.erase(it++); // testing post incrementation. incremented iterator's
                       // memory location shouldn't be invalidated.
    }

    assert_expr(m.size() == 0);

    return 0;
}

TEST(test_map_erase_random_iterator)
{
    map<int, std::string> m;

    m[2] = "hello";
    m[4] = "world";
    m[-45] = "lol";
    m[42] = "how funny";
    m[1] = "hope";
    m[456] = "balanced";
    m[69] = "uwu";
    m[96] = "wuw";
    m[210] = "rip";
    m[8] = "eight";
    m[80] = "eighty";
    m[21] = "divided by two";

    m[21] = "already there";
    m[7] = "seven";
    m[0] = "zero";
    m[-42] = "riztor";

    const map<int, std::string> cm(m);

    // erase values with even keys only
    for (map<int, std::string>::iterator it = m.begin(); it != m.end();) {
        if (it->first % 2 == 0) {
            m.erase(it++);
        } else {
            ++it;
        }
    }

    map<int, std::string>::const_iterator cmcit = cm.begin(), cit = m.begin();

    while (cmcit != cm.end()) {
        if (cmcit->first % 2 == 0) {
            ++cmcit;
        } else {
            assert_eq(*cit, *cmcit);
            ++cit;
            ++cmcit;
        }
    }

    return 0;
}

TEST(test_map_erase_random_range)
{
    map<int, std::string> m;

    m[2] = "hello";
    m[4] = "world";
    m[-45] = "lol";
    m[42] = "how funny";
    m[1] = "hope";
    m[456] = "balanced";
    m[69] = "uwu";
    m[96] = "wuw";
    m[210] = "rip";
    m[8] = "eight";
    m[80] = "eighty";
    m[21] = "divided by two";

    m[21] = "already there";
    m[7] = "seven";
    m[0] = "zero";
    m[-42] = "riztor";

    const map<int, std::string> cm(m);

    m.erase(m.find(0), m.find(96));

    map<int, std::string>::const_iterator cmcit = cm.begin(), cit = m.begin();

    while (cmcit != cm.end()) {
        if (cmcit->first >= 0 && cmcit->first < 96) {
            ++cmcit; // skip that one as it should no longer be present in the
                     // original map
        } else {
            // ensure this element has been left as it is
            p_assert_eq(cit->first, cmcit->first);
            ++cit;
            ++cmcit;
        }
    }

    return 0;
}
