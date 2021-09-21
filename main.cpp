#include <iostream>
#include <memory>
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"

using std::cout;
using ft::vector;

int main(void)
{
	{
		std::allocator<int> alloc;

		vector<int> v1, v2(10), v3(10, 42), v4(10, 42, alloc);

		cout << "vector 1\n";
		for (vector<int>::size_type i = 0; i != v1.size(); ++i) {
			cout << v1[i] << "\n";
		}

		cout << "vector 2\n";
		for (vector<int>::size_type i = 0; i != v2.size(); ++i) {
			cout << v2[i] << "\n";
		}

		cout << "vector 3\n";
		for (vector<int>::size_type i = 0; i != v3.size(); ++i) {
			cout << v3[i] << "\n";
		}

		cout << "vector 4\n";
		for (vector<int>::size_type i = 0; i != v4.size(); ++i) {
			cout << v4[i] << "\n";
		}
	}

	return 0;
}
