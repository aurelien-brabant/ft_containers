#ifndef ITERATOR_TRAITS
# define ITERATOR_TRAITS
# include <iterator>
# include <iostream>

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

	template <class Iter>
	class reverse_iterator
	{
		Iter _iter;

		public:

	//hhj	typedef iterator_type      Iter;
//		typedef iterator_category  ft::iterator_traits<Iter>::iterator_category;
//		typedef value_type         ft::iterator_traits<Iter>::value_type;

		explicit reverse_iterator(Iter iter): _iter(iter) {}

		reverse_iterator(const reverse_iterator& rhs): _iter(rhs._iter) {}

		reverse_iterator& operator=(const reverse_iterator& rhs)
		{
			if (this != &rhs) {
				_iter = rhs._iter;
			}
		}

		/* operator* */

	    typename Iter::value_type& operator*()
		{
			return *_iter;
		}

		/* ++, +=, + */

		reverse_iterator& operator++(void) { --_iter; return *this; };
		reverse_iterator operator++(int) {
			Iter tmp = _iter--;
		
			return reverse_iterator(tmp);
		}
		reverse_iterator operator+(typename ft::iterator_traits<Iter>::difference_type n)
		{
			return reverse_iterator(_iter - n);
		}
		reverse_iterator operator+=(typename ft::iterator_traits<Iter>::difference_type n)
		{
			_iter -= n;
			return *this;
		}

		/* --, -=, - */

		reverse_iterator& operator--(void) { ++_iter; return *this; };
		reverse_iterator operator--(int) { return reverse_iterator(_iter++); };
		reverse_iterator operator-(typename ft::iterator_traits<Iter>::difference_type n)
		{
			return reverse_iterator(_iter + n);
		}
		reverse_iterator operator-=(typename ft::iterator_traits<Iter>::difference_type n)
		{
			_iter += n;
			return *this;
		}

		/* logical operators - basically <, <=, >, >= are doing the opposite of what they're normally doing */
		bool operator!=(const reverse_iterator& rhs) { return _iter != rhs._iter; }
		bool operator==(const reverse_iterator& rhs) { return _iter != rhs._iter; }
		bool operator>=(const reverse_iterator& rhs) { return _iter <= rhs._iter; }
		bool operator<=(const reverse_iterator& rhs) { return _iter >= rhs._iter; }
		bool operator>(const reverse_iterator& rhs) { return _iter < rhs._iter; }
		bool operator<(const reverse_iterator& rhs) { return _iter > rhs._iter; }
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

			iterator& operator++()
			{
				_p++;
				
				return *this;
			}

			iterator& operator++(int)
			{
				iterator it(*this);

				operator++();

				return it;
			}

			iterator& operator--(void)
			{
				--_p;

				return *this;
			}

			iterator operator--(int)
			{
				iterator it(*this);

				operator--();

				return it;
			}

			// ACCESS

			reference operator*(void)
			{
				return *_p;
			}

			const T& operator*(void) const
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

			/**
			 * operator* is used on rhs to get the internal pointer as rhs
			 * is not of the same type than *this in that case.
			 */
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
