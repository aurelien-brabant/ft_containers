#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"

using std::cout;
using std::string;
using ft::vector;

int main(void)
{
	/*
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

	{
		vector<string> vs(1, "hello");

		for (unsigned i = 0; i != 100; ++i) {
			vs.push_back("42");
		}

		cout << "vs size: " << vs.size() << "\n";
	}
	*/

	// Test copy

	{
		vector<unsigned> v1(10, 21); // vector that contains 10 elements, each one initialized to 21.
		vector<unsigned> v2(2, 42);

		v1 = v2;

		vector<string> vs(10, "42");

		vector<string>::const_iterator cit(vs.begin());

		while (cit != vs.end()) {
			cout << *cit << "\n";
			++cit;
		}

	//		for (vector<unsigned>::const_iterator it = v3.begin(); it != v3.end(); ++it) {
	//		cout << *it << "\n";
	//	}
	}

	return 0;
}
