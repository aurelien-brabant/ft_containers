#pragma once

namespace ft {

	template <typename T1, typename T2>
	class pair {
		public:
			typedef T1 first_type;
			typedef T2 second_type;

			T1 first;
			T2 second;

			pair(void): first(), second() {}

			pair(const pair& other)
			{
				*this = other;
			}

			template <typename U1, typename U2>
			pair(const pair<U1, U2>& other): first(other.first), second(other.second)
			{
			}

			pair& operator=(const pair& rhs)
			{
				if (this != &rhs) {
					first = rhs.first;
					second = rhs.second;
				}

				return *this;
			}
	};

}
