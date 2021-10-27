#ifndef ITERATOR_TRAITS
#define ITERATOR_TRAITS
#include "type_traits.hpp"
#include <iostream>
#include <iterator>

namespace ft {
// iterator traits {{{
template<class Iter>
struct iterator_traits
{
    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;
    typedef typename Iter::iterator_category iterator_category;
};
// }}}

// distance {{{

/* This is a very naive implementation of distance, not taking benefit of
 * iterator tags */

template<typename InputIt>
typename iterator_traits<InputIt>::difference_type
distance(InputIt first, InputIt last)
{
    typename iterator_traits<InputIt>::difference_type n = 0;

    while (first++ != last)
        ++n;

    return n;
}

// }}}

// normal iterator - random access {{{

// TODO: use SFINAE to filter available operators depending on iterator's
// category
template<typename T, typename Category, bool IsConst = false>
class iterator
{
    T* _p;

  public:
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef Category iterator_category;

    iterator(void)
      : _p()
    {}

    explicit iterator(pointer p)
      : _p(p)
    {}

    iterator(const iterator& rhs) { *this = rhs; }

    iterator& operator=(const iterator& rhs)
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

    reference operator[](int i) const { return _p[i]; }

    pointer operator->(void) { return _p; }

    iterator& operator++()
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

    reference operator*(void) { return *_p; }

    reference operator*(void) const { return *_p; }

    iterator& operator+=(difference_type n)
    {
        if (n < 0) {
            _p -= n;
        } else {
            _p += n;
        }

        return *this;
    }

    iterator operator+(difference_type n) const { return iterator(_p + n); }

    iterator& operator-=(difference_type n)
    {
        if (n < 0) {
            _p += n;
        } else {
            _p -= n;
        }

        return *this;
    }

    iterator operator-(difference_type n) const { return iterator(_p - n); }

    /* Difference between const and non-const iterators should be allowed */

    difference_type operator-(const iterator<T, Category, false>& rhs) const
    {
        return _p - &(*rhs);
    }

    difference_type operator-(
      const iterator<const T, Category, true>& rhs) const
    {
        return _p - &(*rhs);
    }

    // COMPARISON OPERATORS

    // compare *this with iterator

    bool operator==(iterator<T, Category, false> rhs) const
    {
        return _p == &(*rhs);
    }
    bool operator!=(iterator<T, Category, false> rhs) const
    {
        return _p != &(*rhs);
    }
    bool operator<=(iterator<T, Category, false> rhs) const
    {
        return _p <= &(*rhs);
    }
    bool operator>=(iterator<T, Category, false> rhs) const
    {
        return _p >= &(*rhs);
    }
    bool operator<(iterator<T, Category, false> rhs) const
    {
        return _p < &(*rhs);
    }
    bool operator>(iterator<T, Category, false> rhs) const
    {
        return _p > &(*rhs);
    }

    bool operator==(iterator<const T, Category, true> rhs) const
    {
        return _p == &(*rhs);
    }
    bool operator!=(iterator<const T, Category, true> rhs) const
    {
        return _p != &(*rhs);
    }
    bool operator<=(iterator<const T, Category, true> rhs) const
    {
        return _p <= &(*rhs);
    }
    bool operator>=(iterator<const T, Category, true> rhs) const
    {
        return _p >= &(*rhs);
    }
    bool operator<(iterator<const T, Category, true> rhs) const
    {
        return _p < &(*rhs);
    }
    bool operator>(iterator<const T, Category, true> rhs) const
    {
        return _p > &(*rhs);
    }
};

template<typename T, typename Category, bool IsConst>
iterator<T, Category, IsConst>
operator+(typename iterator<T, Category, IsConst>::difference_type lhs,
          const iterator<T, Category, IsConst>& rhs)
{
    return iterator<T, Category, IsConst>(rhs + lhs);
}

/*
template <typename T, typename Category, bool IsConst, bool IsConst2>
bool operator==(const iterator<const T, Category, IsConst>& lhs, const
iterator<const T, Category, IsConst2>& rhs) { return &(*lhs) == &(*rhs); }

template <typename T, typename Category, bool IsConst, bool IsConst2>
bool operator!=(const iterator<const T, Category, IsConst>& lhs, const
iterator<T, Category, IsConst2>& rhs) { return &(*lhs) != &(*rhs); }

template <typename T, typename Category, bool IsConst, bool IsConst2>
bool operator>=(const iterator<const T, Category, IsConst>& lhs, const
iterator<T, Category, IsConst2>& rhs) { return &(*lhs) >= &(*rhs); }

template <typename T, typename Category, bool IsConst, bool IsConst2>
bool operator<=(const iterator<const T, Category, IsConst>& lhs, const
iterator<T, Category, IsConst2>& rhs) { return &(*lhs) <= &(*rhs); }

template <typename T, typename Category, bool IsConst, bool IsConst2>
bool operator>(const iterator<const T, Category, IsConst>& lhs, const
iterator<T, Category, IsConst2>& rhs) { return &(*lhs) > &(*rhs); }

template <typename T, typename Category, bool IsConst, bool IsConst2>
bool operator<(const iterator<const T, Category, IsConst>& lhs, const
iterator<T, Category, IsConst2>& rhs) { return &(*lhs) < &(*rhs); }
*/

// }}}

// reverse iterator {{{

template<class Iter>
class reverse_iterator
{
  protected:
    Iter current;

  public:
    typedef Iter iterator_type;
    typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
    typedef typename ft::iterator_traits<Iter>::value_type value_type;
    typedef typename ft::iterator_traits<Iter>::pointer pointer;
    typedef typename ft::iterator_traits<Iter>::reference reference;
    typedef
      typename ft::iterator_traits<Iter>::iterator_category iterator_category;

  public:
    explicit reverse_iterator(Iter iter = Iter())
      : current(iter)
    {}

    template<typename U>
    reverse_iterator(const reverse_iterator<U>& other)
      : current(other.base())
    {}

    template<typename U>
    reverse_iterator& operator=(const reverse_iterator<U>& other)
    {
        current = other.base();
        return *this;
    }

    iterator_type base(void) const { return current; }

    /* operator* */

    value_type& operator*(void) const
    {
        Iter tmp = current;

        return *--tmp;
    }

    value_type& operator*(void)
    {
        Iter tmp = current;

        return *--tmp;
    }

    pointer operator->(void) { return &operator*(); }

    const value_type* operator->(void) const { return &operator*(); }

    // access
    value_type& subscript(size_t i, ft::true_type isRandom)
    {
        (void)isRandom;
        return *(current - i - 1);
    }

    const value_type& subscript(size_t i, ft::true_type isRandom) const
    {
        (void)isRandom;
        return *(current - i - 1);
    }

    value_type& operator[](size_t i) const
    {
        return subscript(
          i, ft::is_same<iterator_category, std::random_access_iterator_tag>());
    }

    value_type& operator[](size_t i)
    {
        return subscript(
          i, ft::is_same<iterator_category, std::random_access_iterator_tag>());
    }

    /* ++, +=, + */

    reverse_iterator& operator++(void)
    {
        --current;
        return *this;
    };

    reverse_iterator operator++(int)
    {
        Iter tmp = current--;

        return reverse_iterator(tmp);
    }

    reverse_iterator add(difference_type n, ft::true_type isRandom) const
    {
        (void)isRandom;
        return reverse_iterator(current - n);
    }

    reverse_iterator operator+(difference_type n) const
    {
        return add(
          n, ft::is_same<iterator_category, std::random_access_iterator_tag>());
    }

    reverse_iterator& selfAdd(difference_type n, ft::true_type isRandom)
    {
        (void)isRandom;
        current -= n;
        return *this;
    }

    reverse_iterator operator+=(difference_type n)
    {
        return selfAdd(
          n, ft::is_same<iterator_category, std::random_access_iterator_tag>());
    }

    /* --, -=, - */

    reverse_iterator& operator--(void)
    {
        ++current;
        return *this;
    }

    reverse_iterator operator--(int) { return reverse_iterator(current++); };

    reverse_iterator minus(difference_type n, ft::true_type isRandom) const
    {
        (void)isRandom;
        return reverse_iterator(current + n);
    }

    reverse_iterator operator-(difference_type n) const
    {
        return minus(
          n, ft::is_same<iterator_category, std::random_access_iterator_tag>());
    }

    reverse_iterator& selfMinus(difference_type n, ft::true_type isRandom)
    {
        (void)isRandom;
        current += n;
        return *this;
    }

    reverse_iterator operator-=(difference_type n)
    {
        return selfMinus(
          n, ft::is_same<iterator_category, std::random_access_iterator_tag>());
    }
};

// non-member logical operators {{{

template<typename Iter1, typename Iter2>
bool
operator==(const ft::reverse_iterator<Iter1>& lhs,
           const ft::reverse_iterator<Iter2>& rhs)
{
    return lhs.base() == rhs.base();
}

template<typename Iter1, typename Iter2>
bool
operator!=(const ft::reverse_iterator<Iter1>& lhs,
           const ft::reverse_iterator<Iter2>& rhs)
{
    return lhs.base() != rhs.base();
}

template<typename Iter1, typename Iter2>
bool
operator>=(const ft::reverse_iterator<Iter1>& lhs,
           const ft::reverse_iterator<Iter2>& rhs)
{
    return lhs.base() <= rhs.base();
}

template<typename Iter1, typename Iter2>
bool
operator<=(const ft::reverse_iterator<Iter1>& lhs,
           const ft::reverse_iterator<Iter2>& rhs)
{
    return lhs.base() >= rhs.base();
}

template<typename Iter1, typename Iter2>
bool
operator>(const ft::reverse_iterator<Iter1>& lhs,
          const ft::reverse_iterator<Iter2>& rhs)
{
    return lhs.base() < rhs.base();
}

template<typename Iter1, typename Iter2>
bool
operator<(const ft::reverse_iterator<Iter1>& lhs,
          const ft::reverse_iterator<Iter2>& rhs)
{
    return lhs.base() > rhs.base();
}

template<typename Iter>
ft::reverse_iterator<Iter>
operator-(typename ft::reverse_iterator<Iter>::difference_type lhs,
          const ft::reverse_iterator<Iter>& rhs)
{
    return rhs - lhs;
}

template<typename Iter>
ft::reverse_iterator<Iter>
operator+(typename ft::reverse_iterator<Iter>::difference_type lhs,
          const ft::reverse_iterator<Iter>& rhs)
{
    return rhs + lhs;
}

// }}}

// other non-member {{{

template<typename Iter>
reverse_iterator<Iter>
operator+(const ft::reverse_iterator<Iter>& lhs,
          typename Iter::difference_type n)
{
    return reverse_iterator<Iter>(lhs.base() - n);
}

template<typename Iter1, typename Iter2>
typename reverse_iterator<Iter1>::difference_type
operator-(const ft::reverse_iterator<Iter1>& lhs,
          const ft::reverse_iterator<Iter2>& rhs)
{
    return rhs.base() - lhs.base();
}

// }}}

// }}}

}

#endif
