#include "map_testing.hpp"

TEST(test_map_empty)
{
    map<unsigned, unsigned> m;

    {
        const map<unsigned, unsigned> cm(m);
        assert_expr(cm.empty() == true);
    }

    m.insert(FT_CONTAINER::make_pair(0, 0));

    {
        const map<unsigned, unsigned> cm(m);
        assert_expr(cm.empty() == false);
    }

    m.erase(0);

    {
        const map<unsigned, unsigned> cm(m);
        assert_expr(cm.empty() == true);
    }

    return 0;
}
