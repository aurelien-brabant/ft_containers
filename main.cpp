#include <iostream>
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"

using std::cout;
using ft::vector;

int main(void)
{
	{
		vector<int> eiv, eiv2(10);

		cout << "empty vector's length: " << eiv.size() << "\n";
		cout << "empty vector's cap: " << eiv.capacity() << "\n";

		eiv.push_back(10);
		eiv.push_back(42);

		for (vector<int>::size_type i = 0; i != eiv.size(); ++i) {
			cout << eiv[i] << "\n";
		}

		for (vector<int>::size_type i = 0; i != eiv2.size(); ++i) {
			cout << eiv2[i] << "\n";
		}
	}

	return 0;
}
