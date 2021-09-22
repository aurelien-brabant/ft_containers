#ifndef ITERATOR_TRAITS
# define ITERATOR_TRAITS
# include <iterator>

namespace ft
{
	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template <typename Category, typename T>
	class iterator
	{
		T * _p;

		public:
			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T *				pointer;
			typedef T &				reference;
			typedef Category		iterator_category;

			iterator(T * p): _p(p)
			{
			}

			// COPY MANAGEMENT

			iterator(iterator const & rhs)
			{
				*this = rhs;
			}

			iterator & operator=(iterator const & rhs)
			{
				if (this != &rhs) {
					_p = rhs._p;
				}
			}

			reference operator++()
			{
				++_p;
				
				return *this;
			}

			value_type operator+=(int)
			{
				iterator it(*this);

				operator++();

				return it;
			}

			reference operator--()
			{
				--_p;

				return *this;
			}

			reference operator--(int)
			{
				iterator it(*this);

				operator--();

				return *this;
			}

			// ACCESS

			reference operator*(pointer p)
			{
				return *p;
			}

			iterator & operator+=(difference_type n)
			{
				if (n < 0) {
					_p -= n;
				} else {
					_p += n;
				}

				return *this;
			}

			iterator operator+(difference_type n)
			{
				iterator tmp(*this);

				operator+=(n);

				return tmp;
			}

			iterator & operator-=(difference_type n)
			{
				if (n < 0) {
					_p += n;
				} else {
					_p -= n;
				}

				return *this;
			}

			iterator operator-(difference_type n)
			{
				iterator tmp(*this);

				operator-=(n);

				return tmp;
			}

			// COMPARISON OPERATORS

			bool operator==(iterator & rhs)
			{
				return _p == rhs._p;
			}

			bool operator<=(iterator & rhs)
			{
				return _p <= rhs._p;
			}

			bool operator>=(iterator & rhs)
			{
				return _p >= rhs._p;
			}

			bool operator!=(iterator & rhs)
			{
				return _p != rhs._p;
			}

			bool operator<(iterator & rhs)
			{
				return _p < rhs._p;
			}

			bool operator>(iterator & rhs)
			{
				return _p > rhs._p;
			}
	};
}

#endif
