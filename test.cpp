#include "algorithm.hpp"
#include "vector.hpp"
#include <iterator>
#include <vector>

using ft::vector;

int
main(void)
{
    ft::vector<int> v(1);

    ft::vector<int>::const_iterator cit = v.begin();

    *cit = 42;

    return 0;
}
