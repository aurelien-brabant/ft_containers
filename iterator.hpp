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
	

	template <typename T, typename Category, bool IsConst = false>
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

			iterator(const iterator & rhs)
			{
				*this = rhs;
			}

			iterator & operator=(iterator const & rhs)
			{
				if (this != &rhs) {
					_p = rhs._p;
				}

				return *this;
			}

			// allow conversion to const_iterator
			operator iterator<const T, Category, true>() const
			{
				return iterator<const T, Category, true>(_p);
			}

			iterator operator++()
			{
				_p++;
				
				return *this;
			}

			iterator operator++(int)
			{
				iterator it(*this);

				operator++();

				return it;
			}

			iterator operator--(void)
			{
				--_p;

				return *this;
			}

			iterator operator--(int)
			{
				iterator it(*this);

				operator--();

				return *this;
			}

			// ACCESS

			reference operator*(void)
			{
				return *_p;
			}

			const T & operator*(void) const
			{
				return  *_p;
			}

			iterator & operator+=(difference_type const n) 
			{
				if (n < 0) {
					_p -= n;
				} else {
					_p += n;
				}

				return *this;
			}

			iterator operator+(difference_type const n)
			{
				return operator+=(n);
			}

			iterator & operator-=(difference_type const n)
			{
				if (n < 0) {
					_p += n;
				} else {
					_p -= n;
				}

				return *this;
			}

			iterator operator-(difference_type const n)
			{
				return operator-=(n);
			}

			difference_type operator-(const iterator<T, Category, false> & rhs)
			{
				return _p - rhs._p;
			}

			difference_type operator-(const iterator<const T, Category, true> & rhs)
			{
				return _p - &(*rhs);
			}

			// COMPARISON OPERATORS

			bool operator==(iterator rhs) const
			{
				return _p == rhs._p;
			}

			bool operator<=(iterator rhs) const
			{
				return _p <= rhs._p;
			}

			bool operator>=(iterator rhs) const
			{
				return _p >= rhs._p;
			}

			bool operator!=(iterator rhs) const
			{
				return _p != rhs._p;
			}

			bool operator<(iterator rhs) const
			{
				return _p < rhs._p;
			}

			bool operator>(iterator rhs) const
			{
				return _p > rhs._p;
			}
	};
}

#endif
