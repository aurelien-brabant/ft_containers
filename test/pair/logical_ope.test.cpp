#include "pair_testing.hpp"

int
test_pair_operator_eq(Tester& tester)
{
    pair<int, int> p1(21, 21), p2(21, 21);

    assert_expr(p1 == p2);
    assert_expr(p2 == p1);

    ++p2.second;

    assert_expr((p1 == p2) == false);
    assert_expr((p2 == p1) == false);

    ++p1.first;
    assert_expr((p1 == p2) == false);
    assert_expr((p2 == p1) == false);

    ++p2.first;
    ++p1.second;

    assert_expr(p1 == p2);
    assert_expr(p2 == p1);

    return 0;
}

int
test_pair_operator_neq(Tester& tester)
{
    pair<int, int> p1(21, 21), p2(21, 21);

    assert_expr((p1 != p2) == false);
    assert_expr((p2 != p1) == false);

    ++p2.second;

    assert_expr(p1 != p2);
    assert_expr(p1 != p2);

    ++p1.first;
    assert_expr(p1 != p2);
    assert_expr(p1 != p2);

    ++p2.first;
    ++p1.second;

    assert_expr((p1 != p2) == false);
    assert_expr((p1 != p2) == false);

    return 0;
}

int
test_pair_operator_lt(Tester& tester)
{
    pair<int, int> p(21, 21), p2(21, 21);

    assert_expr((p < p2) == false);
    assert_expr((p2 < p) == false);

    p.first++;

    assert_expr((p < p2) == false);
    assert_expr((p2 < p) == true);

    p2.first++;

    assert_expr((p < p2) == false);
    assert_expr((p2 < p) == false);

    p.second--;

    assert_expr((p < p2) == true);
    assert_expr((p2 < p) == false);

    return 0;
}

int
test_pair_operator_lte(Tester& tester)
{
    pair<int, int> p(21, 21), p2(21, 21);

    assert_expr((p <= p2) == true);
    assert_expr((p2 <= p) == true);

    p.first++;

    assert_expr((p <= p2) == false);
    assert_expr((p2 <= p) == true);

    p2.first++;

    assert_expr((p <= p2) == true);
    assert_expr((p2 <= p) == true);

    p.second--;

    assert_expr((p <= p2) == true);
    assert_expr((p2 <= p) == false);

    return 0;
}

int
test_pair_operator_gt(Tester& tester)
{
    pair<int, int> p(21, 21), p2(21, 21);

    assert_expr((p > p2) == false);
    assert_expr((p2 > p) == false);

    p.first++;

    assert_expr((p > p2) == true);
    assert_expr((p2 > p) == false);

    p2.first++;

    assert_expr((p > p2) == false);
    assert_expr((p2 > p) == false);

    p.second--;

    assert_expr((p > p2) == false);
    assert_expr((p2 > p) == true);

    return 0;
}

int
test_pair_operator_gte(Tester& tester)
{
    pair<int, int> p(21, 21), p2(21, 21);

    assert_expr((p >= p2) == true);
    assert_expr((p2 >= p) == true);

    p.first++;

    assert_expr((p > p2) == true);
    assert_expr((p2 > p) == false);

    p2.first++;

    assert_expr((p >= p2) == true);
    assert_expr((p2 >= p) == true);

    p.second--;

    assert_expr((p > p2) == false);
    assert_expr((p2 > p) == true);

    return 0;
}