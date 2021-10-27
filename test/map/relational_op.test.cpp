#include "map_testing.hpp"

TEST(test_map_eq_op)
{
    map<int, std::string> m1, m2;

    assert_expr(m1 == m2);
    assert_expr(m2 == m1);

    m1[0] = "hey";

    assert_expr(!(m1 == m2));
    assert_expr(!(m2 == m1));

    m2[0] = "hello";

    assert_expr(!(m1 == m2));
    assert_expr(!(m2 == m1));

    m2[0] = "hey";

    assert_expr(m1 == m2);
    assert_expr(m2 == m1);

    m2[1] = "hey";

    assert_expr(!(m1 == m2));
    assert_expr(!(m2 == m1));

    return 0;
}

TEST(test_map_neq_op)
{
    map<int, std::string> m1, m2;

    assert_expr(!(m1 != m2));
    assert_expr(!(m2 != m1));

    m1[0] = "hey";

    assert_expr(m1 != m2);
    assert_expr(m2 != m1);

    m2[0] = "hello";

    assert_expr(m1 != m2);
    assert_expr(m2 != m1);

    m2[0] = "hey";

    assert_expr(!(m1 != m2));
    assert_expr(!(m2 != m1));

    m2[1] = "hey";

    assert_expr(m1 != m2);
    assert_expr(m2 != m1);

    return 0;
}

TEST(test_map_gt_op)
{
    map<int, std::string> m1, m2;

    assert_expr(!(m1 > m2));
    assert_expr(!(m1 > m2));

    m1[0] = "hey";

    assert_expr(m1 > m2);
    assert_expr(!(m2 > m1));

    m2[0] = "hello";

    // 'y' > 'l' therefore m1 > m1

    assert_expr(m1 > m2);
    assert_expr(!(m2 > m1));

    m2[0] = "hey";

    assert_expr(!(m1 > m2));
    assert_expr(!(m1 > m2));

    m2[1] = "hey";

    assert_expr(!(m1 > m2));
    assert_expr(m2 > m1);

    return 0;
}

TEST(test_map_lt_op)
{
    map<int, std::string> m1, m2;

    assert_expr(!(m1 < m2));
    assert_expr(!(m1 < m2));

    m1[0] = "hey";

    assert_expr(!(m1 < m2));
    assert_expr(m2 < m1);

    m2[0] = "hello";

    // 'y' > 'l' therefore m1 > m1

    assert_expr(!(m1 < m2));
    assert_expr(m2 < m1);

    m2[0] = "hey";

    assert_expr(!(m1 < m2));
    assert_expr(!(m1 < m2));

    m2[1] = "hey";

    assert_expr(m1 < m2);
    assert_expr(!(m2 < m1));

    return 0;
}

TEST(test_map_gte_op)
{
    map<int, std::string> m1, m2;

    assert_expr(m1 >= m2);
    assert_expr(m1 >= m2);

    m1[0] = "hey";

    assert_expr(m1 >= m2);
    assert_expr(!(m2 >= m1));

    m2[0] = "hello";

    // 'y' > 'l' therefore m1 > m1

    assert_expr(m1 >= m2);
    assert_expr(!(m2 >= m1));

    m2[0] = "hey";

    assert_expr(m1 >= m2);
    assert_expr(m1 >= m2);

    m2[1] = "hey";

    assert_expr(!(m1 >= m2));
    assert_expr(m2 >= m1);

    return 0;
}

TEST(test_map_lte_op)
{
    map<int, std::string> m1, m2;

    assert_expr(m1 <= m2);
    assert_expr(m1 <= m2);

    m1[0] = "hey";

    assert_expr(!(m1 <= m2));
    assert_expr(m2 <= m1);

    m2[0] = "hello";

    // 'y' > 'l' therefore m1 > m1

    assert_expr(!(m1 <= m2));
    assert_expr(m2 <= m1);

    m2[0] = "hey";

    assert_expr(m1 <= m2);
    assert_expr(m1 <= m2);

    m2[1] = "hey";

    assert_expr(m1 <= m2);
    assert_expr(!(m2 <= m1));

    return 0;
}
