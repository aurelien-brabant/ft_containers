#include "map_testing.hpp"

template<typename K, typename V>
static bool
compare_it_rit(Tester& tester, const map<K, V>& m)
{
    (void)tester;
    typename map<K, V>::const_iterator cit = m.end();
    typename map<K, V>::const_reverse_iterator rcit = m.rbegin();

    while (rcit != m.rend()) {
		--cit;
        if (!(rcit->first == cit->first)) {
            return false;
        }
        ++rcit;
    }

    cit = m.begin();
    rcit = m.rend();

    while (rcit != m.rbegin()) {
        --rcit;
        if (!(rcit->first == cit->first)) {
            return false;
        }
		++cit;
    }

    return true;
}

TEST(test_map_riter_random)
{
    map<int, std::string> m;

    m[1] = "hey";
    m[8] = "ho";
    m[-42] = "order";
    m[42] = "federation";
    m[64] = "ho ho ho";
    m[-456] = "pabo";
    m[445] = "pablo";

    assert_expr(compare_it_rit(tester, m));

    return 0;
}

TEST(test_map_riter_sequence)
{
    unsigned baseN = 100000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m[i] = i;
    }

	(void) tester;
    assert_expr(compare_it_rit(tester, m));

    return 0;
}
