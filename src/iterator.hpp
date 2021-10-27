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
