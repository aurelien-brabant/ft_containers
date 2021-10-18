#include "utility.hpp"
#include <cstddef>
#include <functional>
#include <memory>

namespace ft {

template<typename Key,
         typename T,
         typename Compare = std::less<Key>,
         typename Allocator = std::allocator<ft::pair<Key, T> > >
class map
{
  private:
    Compare _compare;
    Allocator _allocator;

  public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef ft::pair<Key, T> value_type;
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    // missing: iterator typedefs

    map(void)
      : _compare()
      , _allocator()
    {}

    explicit map(const Compare& cmp, const Allocator& alloc = Allocator())
      : _compare(cmp)
      , _allocator(alloc)
    {}

    map(const map& other) { *this = other; }

    ~map(void) {}

    map& operator=(const map& rhs)
    {
        if (this != &rhs) {
            _allocator = rhs._allocator;
            _compare = rhs._compare;
        }
    }

    class value_compare
      : public std::binary_function<value_type, value_type, bool>
    {
      protected:
        Compare comp;

      public:
        value_compare(Compare c)
          : comp(c)
        {}

        bool operator()(const value_type& lhs, const value_type& rhs) const
        {
            return comp(lhs.first, rhs.first);
        }
    };

    size_type max_size(void) { return _allocator.max_size(); }

    allocator_type get_allocator() const { return _allocator; }

    key_compare key_comp(void) const { return _compare; }
    value_compare value_comp(void) const { return value_compare(_compare); }
};

/* END OF namespace ft */

}