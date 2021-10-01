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

			iterator(void): _p() {}

			explicit iterator(pointer p): _p(p) {}

			iterator(const iterator& rhs) { *this = rhs; }

			iterator & operator=(const iterator& rhs)
			{
				if (this != &rhs) {
					_p = rhs._p;
				}

				return *this;
			}

			/* allow conversion from iterator to const_iterator */

			operator iterator<const T, Category, true>() const
			{
				return iterator<const T, Category, true>(_p);
			}

			reference operator[](int i) { return _p[i]; }

			pointer operator->(void) { return _p; }

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

		    reference operator*(void) const
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
				return iterator(_p + n);
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

			iterator operator-(difference_type const n) const
			{
				return iterator(_p - n);
			}

			/* Difference between const and non-const iterators should be allowed */

			difference_type operator-(const iterator<T, Category, false> & rhs) const
			{
				return _p - &(*rhs);
			}

			difference_type operator-(const iterator<const T, Category, true> & rhs) const
			{
				return _p - &(*rhs);
			}

			// COMPARISON OPERATORS
			
			// compare *this with iterator

			bool operator==(iterator<T, Category, false> rhs) const { return _p == &(*rhs); }
			bool operator!=(iterator<T, Category, false> rhs) const { return _p != &(*rhs); }
			bool operator<=(iterator<T, Category, false> rhs) const { return _p <= &(*rhs); }
			bool operator>=(iterator<T, Category, false> rhs) const { return _p >= &(*rhs); }
			bool operator<(iterator<T, Category, false> rhs) const { return _p < &(*rhs); }
			bool operator>(iterator<T, Category, false> rhs) const { return _p > &(*rhs); }

			// compare *this with const_iterator

			bool operator==(iterator<const T, Category, true> rhs) const { return _p == &(*rhs); }
			bool operator!=(iterator<const T, Category, true> rhs) const { return _p != &(*rhs); }
			bool operator<=(iterator<const T, Category, true> rhs) const { return _p <= &(*rhs); }
			bool operator>=(iterator<const T, Category, true> rhs) const { return _p >= &(*rhs); }
			bool operator<(iterator<const T, Category, true> rhs) const { return _p < &(*rhs); }
			bool operator>(iterator<const T, Category, true> rhs) const { return _p > &(*rhs); }
	};

	template <class Iter>
	class reverse_iterator
	{
		Iter _iter;

		public:
			typedef          Iter                                          iterator_type;
			typedef typename ft::iterator_traits<Iter>::difference_type    difference_type;
			typedef typename ft::iterator_traits<Iter>::value_type         value_type;
			typedef typename ft::iterator_traits<Iter>::pointer            pointer;
			typedef typename ft::iterator_traits<Iter>::reference          reference;
			typedef typename ft::iterator_traits<Iter>::iterator_category  iterator_category;

		public:
			explicit reverse_iterator(Iter iter = Iter()): _iter(iter) {}

			template <typename U>
			reverse_iterator(const reverse_iterator<U>& other): _iter(other.base()) {}

			template <typename U>
			reverse_iterator& operator=(const reverse_iterator<U>& other) {
				if (this != &other) {
					_iter = other.base();
				}
			}

			iterator_type base(void) const
			{
				return _iter;
			}

			/* operator* */

			typename Iter::value_type& operator*()
			{
				return *(_iter - 1);
			}

			/* ++, +=, + */

			reverse_iterator& operator++(void)
			{
				--_iter;
				return *this;
			};

			reverse_iterator operator++(int)
			{
				Iter tmp = _iter--;
			
				return reverse_iterator(tmp);
			}

			reverse_iterator operator+(difference_type n)
			{
				return reverse_iterator(_iter - n);
			}

			reverse_iterator operator+=(difference_type n)
			{
				_iter -= n;
				return *this;
			}

			/* --, -=, - */

			reverse_iterator& operator--(void) { ++_iter; return *this; }

			reverse_iterator operator--(int) { return reverse_iterator(_iter++); };
			
			reverse_iterator operator-(difference_type n)
			{
				return reverse_iterator(_iter + n);
			}

			reverse_iterator operator-=(difference_type n)
			{
				_iter += n;
				return *this;
			}
	};

	/* reverse_iterator non-members */

	template <typename Iter1, typename Iter2>
	bool operator==(const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs) { return lhs.base() == rhs.base(); }

	template <typename Iter1, typename Iter2>
	bool operator!=(const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs) { return lhs.base() != rhs.base(); }
	
	template <typename Iter1, typename Iter2>
	bool operator>=(const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs) { return lhs.base() <= rhs.base(); }

	template <typename Iter1, typename Iter2>
	bool operator<=(const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs) { return lhs.base() >= rhs.base(); }

	template <typename Iter1, typename Iter2>
	bool operator>(ft::reverse_iterator<Iter1>& lhs, ft::reverse_iterator<Iter2>& rhs) { return lhs.base() < rhs.base(); }

	template <typename Iter1, typename Iter2>
	bool operator<(ft::reverse_iterator<Iter1>& lhs, ft::reverse_iterator<Iter2>& rhs) { return lhs.base() > rhs.base(); }

	template <typename Iter>
	reverse_iterator<Iter> operator+(const ft::reverse_iterator<Iter>& lhs, typename Iter::difference_type n) { return reverse_iterator<Iter>(lhs.base() - n); }

	template <typename Iter>
	typename reverse_iterator<Iter>::difference_type operator-(const ft::reverse_iterator<Iter>& lhs, const ft::reverse_iterator<Iter>& rhs) { return rhs.base() - lhs.base(); }
}

#endif
