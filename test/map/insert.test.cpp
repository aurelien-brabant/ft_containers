#include "map_testing.hpp"
#include <fstream>

int
test_map_insert_one(Tester& tester)
{
    map<unsigned, unsigned> m;
    unsigned baseN = 1000000;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(make_pair(i, i));
    }

    p_assert_eq(m.size(), baseN);

    size_t i = 0;
    for (map<unsigned, unsigned>::const_iterator cit = m.begin();
         cit != m.end();
         ++cit) {
        p_assert_eq(cit->first, i);
        p_assert_eq(cit->second, i);
        ++i;
    }

    return 0;
}

int
test_map_insert_range(Tester& tester)
{
    unsigned baseN = 100000;

    std::vector<pair<unsigned, unsigned> > v;

    for (unsigned i = 0; i != baseN; ++i) {
        v.push_back(make_pair(i, i));
    }

    map<unsigned, unsigned> m;

    m.insert(++v.begin(), --v.end());

    p_assert_eq(m.size(), v.size() - 2);

    size_t i = 1;
    for (map<unsigned, unsigned>::const_iterator cit = m.begin();
         cit != m.end();
         ++cit) {
        p_assert_eq(cit->first, i);
        p_assert_eq(cit->second, i);
        ++i;
    }

    p_assert_eq(i, baseN - 1);

    return 0;
}

int
test_map_insert_one_string(Tester& tester)
{
    unsigned baseN = 1000000;
    std::ostringstream oss;
    map<std::string, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        oss << i;
        m.insert(FT_CONTAINER::make_pair(oss.str(), i));
        oss.str("");
    }

    p_assert_eq(m.size(), baseN);

    return 0;
}
