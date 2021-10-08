#include "vector.hpp"
#include <vector>
#include <iterator>

using ft::vector;

int main(void)
{
	vector<int> v(42);

	vector<int>::const_reverse_iterator crit = ft::reverse_iterator<vector<int>::iterator>(v.begin());

	return 0;
}
