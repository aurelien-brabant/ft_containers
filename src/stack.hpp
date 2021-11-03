#pragma once
#include "vector.hpp"

namespace ft {
template<typename T, typename Container = ft::vector<T> >
class stack
{
  protected:
    Container c;

  public:
    /* member types */
    typedef Container container_type;
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;

    /* CTORs */
    explicit stack(const Container& cont = Container())
      : c(cont)
    {}

    stack(const stack& other)
      : c(other.c)
    {}

    stack& operator=(const stack& rhs)
    {
        if (this != &rhs) {
            c = rhs.c;
        }

        return *this;
    }

    ~stack(void) {}

    /* member functions */

    // element access {{{

    value_type& top(void) { return c.back(); }

    // }}}

    // capacity {{{

    bool empty(void) const { return c.empty(); }

    size_type size(void) const { return c.size(); }

    // }}}

    // modifiers {{{

    void push(const value_type& value) { c.push_back(value); }

    void pop(void) { c.pop_back(); }

    // }}}

    // friend non-member operators {{{

    friend bool operator==(const ft::stack<T, Container>& lhs,
                           const ft::stack<T, Container>& rhs)
    {
        return lhs.c == rhs.c;
    }
    friend bool operator>=(const ft::stack<T, Container>& lhs,
                           const ft::stack<T, Container>& rhs)
    {
        return lhs.c >= rhs.c;
    }
    friend bool operator<=(const ft::stack<T, Container>& lhs,
                           const ft::stack<T, Container>& rhs)
    {
        return lhs.c <= rhs.c;
    }
    friend bool operator!=(const ft::stack<T, Container>& lhs,
                           const ft::stack<T, Container>& rhs)
    {
        return lhs.c != rhs.c;
    }
    friend bool operator>(const ft::stack<T, Container>& lhs,
                          const ft::stack<T, Container>& rhs)
    {
        return lhs.c > rhs.c;
    }
    friend bool operator<(const ft::stack<T, Container>& lhs,
                          const ft::stack<T, Container>& rhs)
    {
        return lhs.c < rhs.c;
    }

    // }}}
};

}
