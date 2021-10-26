#include "map_testing.hpp"

TEST(test_map_size)
{
    unsigned baseN = 10000;
    map<unsigned, unsigned> m;

    for (unsigned i = 0; i != baseN; ++i) {
        m.insert(FT_CONTAINER::make_pair(i, i));
        p_assert_eq(m.size(), i + 1);
    }

    return 0;
}

TEST(test_map_size_empty)
{
    map<unsigned, unsigned> m;

    p_assert_eq(m.size(), 0);

    return 0;
}
