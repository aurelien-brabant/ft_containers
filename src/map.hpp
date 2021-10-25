#include "AVLTree.hpp"
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

    class value_compare
    {
        Compare comp;

      public:
        value_compare(void)
          : comp(Compare())
        {}

        value_compare(Compare c)
          : comp(c)
        {}

        ~value_compare(void) {}

        bool operator()(const value_type& lhs, const value_type& rhs) const
        {
            return comp(lhs.first, rhs.first);
        }
    };

    key_compare key_comp(void) const { return _compare; }
    value_compare value_comp(void) const { return value_compare(_compare); }

  private:
    Compare _compare;
    Allocator _allocator;

  public:
    size_type max_size(void) { return _allocator.max_size(); }

    allocator_type get_allocator() const { return _allocator; }

  private:
    typedef AVLTree<value_type, value_compare, allocator_type> InternalBTree;

  public:
    typedef typename InternalBTree::iterator iterator;
    typedef typename InternalBTree::const_iterator const_iterator;
    InternalBTree _data;

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
            _data = rhs._data;
        }
    }

    size_type size(void) { return _data.size(); }

    std::pair<iterator, bool> insert(const value_type& value)
    {
        return _data.insert(value);
    }

    template<typename InputIt>
    void insert(InputIt first, InputIt last)
    {
        _data.insert(first, last);
    }

    iterator find(const Key& key)
    {
        value_type p;

        return _data.find(make_pair(key, typename value_type::second_type()));
    }

    const_iterator find(const Key& key) const
    {
        value_type p;

        return _data.find(make_pair(key, typename value_type::second_type()));
    }

    size_t erase(const Key& key)
    {
        return _data.erase(make_pair(key, typename value_type::second_type()));
    }

    void erase(iterator pos) { _data.erase(pos); }

    iterator begin(void) { return _data.begin(); }

    iterator end(void) { return _data.end(); }
};

/* END OF namespace ft */
}
