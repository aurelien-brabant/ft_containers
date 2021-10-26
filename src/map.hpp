#include "AVLTree.hpp"
#include "utility.hpp"
#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>

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
    size_type max_size(void) const { return _data.max_size(); }

    allocator_type get_allocator() const { return _allocator; }

  private:
    typedef AVLTree<value_type, value_compare, allocator_type> InternalBTree;

  public:
    typedef typename InternalBTree::iterator iterator;
    typedef typename InternalBTree::const_iterator const_iterator;
    typedef typename InternalBTree::reverse_iterator reverse_iterator;
    typedef
      typename InternalBTree::const_reverse_iterator const_reverse_iterator;
    InternalBTree _data;

    map(void)
      : _compare()
      , _allocator()
    {}

    explicit map(const Compare& cmp, const Allocator& alloc = Allocator())
      : _compare(cmp)
      , _allocator(alloc)
    {}

    template<typename InputIt>
    map(InputIt first,
        InputIt last,
        const Compare& comp = Compare(),
        const Allocator& alloc = Allocator())
      : _compare(comp)
      , _allocator(alloc)
    {
        while (first != last) {
            _data.insert(*first);
            ++first;
        }
    }

    map(const map& other) { *this = other; }

    ~map(void) {}

    map& operator=(const map& rhs)
    {
        if (this != &rhs) {
            _allocator = rhs._allocator;
            _compare = rhs._compare;
            _data = rhs._data;
        }

        return *this;
    }

    size_type size(void) const { return _data.size(); }

    ft::pair<iterator, bool> insert(const value_type& value)
    {
        return _data.insert(value);
    }

    iterator insert(iterator hint, const value_type& value)
    {
        return _data.insert(hint, value);
    }

    template<typename InputIt>
    void insert(InputIt first, InputIt last)
    {
        _data.insert(first, last);
    }

    iterator find(const Key& key)
    {
        value_type p;

        return _data.find(
          ft::make_pair(key, typename value_type::second_type()));
    }

    const_iterator find(const Key& key) const
    {
        value_type p;

        return _data.find(
          ft::make_pair(key, typename value_type::second_type()));
    }

    mapped_type& operator[](const Key& key)
    {
        iterator it(find(key));

        return it != end() ? it->second
                           : (insert(ft::make_pair(
                                       key, typename value_type::second_type()))
                                .first)
                               ->second;
    }

    mapped_type& at(const Key& key)
    {
        iterator it = find(key);

        if (it == end()) {
            throw std::out_of_range("map::at - index out of range");
        }

        return it->second;
    }

    const mapped_type& at(const Key& key) const
    {
        const_iterator cit = find(key);

        if (cit == end()) {
            throw std::out_of_range("map::at - index out of range");
        }

        return cit->second;
    }

    size_type count(const Key& key) const
    {
        const_iterator it = find(key);

        return it != end();
    }

    bool empty(void) const { return size() == 0; }

    iterator lower_bound(const Key& key)
    {
        return _data.lower_bound(
          ft::make_pair(key, typename value_type::second_type()));
    }

    const_iterator lower_bound(const Key& key) const
    {
        return _data.lower_bound(
          ft::make_pair(key, typename value_type::second_type()));
    }

    iterator upper_bound(const Key& key)
    {
        return _data.upper_bound(
          ft::make_pair(key, typename value_type::second_type()));
    }

    const_iterator upper_bound(const Key& key) const
    {
        return _data.upper_bound(
          make_pair(key, typename value_type::second_type()));
    }

    ft::pair<iterator, iterator> equal_range(const Key& key)
    {
        return _data.equal_range(
          ft::make_pair(key, typename value_type::second_type()));
    }

    ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
    {
        return _data.equal_range(
          ft::make_pair(key, typename value_type::second_type()));
    }

    size_t erase(const Key& key)
    {
        return _data.erase(
          ft::make_pair(key, typename value_type::second_type()));
    }

    void erase(iterator pos) { _data.erase(pos); }

    void erase(iterator first, iterator last) { _data.erase(first, last); }

    iterator begin(void) { return _data.begin(); }
    const_iterator begin(void) const { return _data.begin(); }

    iterator end(void) { return _data.end(); }
    const_iterator end(void) const { return _data.end(); }

    reverse_iterator rbegin(void) { return _data.rbegin(); }
    const_reverse_iterator rbegin(void) const { return _data.rbegin(); }

    reverse_iterator rend(void) { return _data.rend(); }
    const_reverse_iterator rend(void) const { return _data.rend(); }

    void clear(void) { _data.clear(); }

    void swap(map& rhs)
    {
        if (this != &rhs) {
            _data.swap(rhs._data);
        }
    }

    friend bool operator==(const ft::map<Key, T, Compare, Allocator>& lhs,
                           const ft::map<Key, T, Compare, Allocator>& rhs)
    {
        return lhs._data == rhs._data;
    }

    friend bool operator!=(const ft::map<Key, T, Compare, Allocator>& lhs,
                           const ft::map<Key, T, Compare, Allocator>& rhs)
    {
        return lhs._data != rhs._data;
    }

    friend bool operator<(const ft::map<Key, T, Compare, Allocator>& lhs,
                          const ft::map<Key, T, Compare, Allocator>& rhs)
    {
        return lhs._data < rhs._data;
    }

    friend bool operator>(const ft::map<Key, T, Compare, Allocator>& lhs,
                          const ft::map<Key, T, Compare, Allocator>& rhs)
    {
        return lhs._data > rhs._data;
    }

    friend bool operator<=(const ft::map<Key, T, Compare, Allocator>& lhs,
                           const ft::map<Key, T, Compare, Allocator>& rhs)
    {
        return lhs._data <= rhs._data;
    }

    friend bool operator>=(const ft::map<Key, T, Compare, Allocator>& lhs,
                           const ft::map<Key, T, Compare, Allocator>& rhs)
    {
        return lhs._data >= rhs._data;
    }
};

}

namespace std {

template<typename Key, typename T, typename Compare, typename Allocator>
void
swap(ft::map<Key, T, Compare, Allocator>& lhs,
     ft::map<Key, T, Compare, Allocator>& rhs)
{
    lhs.swap(rhs);
}

}
