#pragma once
#include "algorithm.hpp"
#include "iterator.hpp"
#include "utility.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <stdint.h>

template<typename T,
         typename Compare,
         typename Allocator >
class AVLTree
{
  public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef size_t size_type;

  private:
    // Node Class {{{
    struct Node
    {
        Node *parent, *left, *right;
        T value;
        unsigned height;

      public:
        Node(const T& value,
             Node* parent,
             Node* left = 0,
             Node* right = 0,
             unsigned height = 1)
          : parent(parent)
          , left(left)
          , right(right)
          , value(value)
          , height(height)
        {}
        Node(const Node& other) { *this = other; }
        ~Node(void) {}

        Node& operator=(const Node& rhs)
        {
            if (this != &rhs) {
                value = rhs.value;
                left = rhs.left;
                right = rhs.right;
                parent = rhs.parent;
                height = rhs.height;
            }

            return *this;
        }

        bool isLeaf(void) const { return !left && !right; }

        void swap(Node& rhs)
        {
            Node *leftTmp = left, *rightTmp = right;
            // this gets rhs's attributes

            left = rhs.left == this ? &rhs : rhs.left;
            right = rhs.right == this ? &rhs : rhs.right;
            if (left) {
                left->parent = this;
            }
            if (right) {
                right->parent = this;
            }

            rhs.left = leftTmp == &rhs ? this : leftTmp;
            rhs.right = rightTmp == &rhs ? this : rightTmp;
            if (leftTmp) {
                leftTmp->parent = &rhs;
            }
            if (rightTmp) {
                rightTmp->parent = &rhs;
            }

            Node* parentTmp = parent;

            parent = rhs.parent == this ? &rhs : rhs.parent;
            if (parent) {
                if (parent->left == &rhs) {
                    parent->left = this;
                } else if (parent->right == &rhs) {
                    parent->right = this;
                }
            }

            rhs.parent = parentTmp;
            if (rhs.parent) {
                if (rhs.parent->left == this) {
                    rhs.parent->left = &rhs;
                } else if (parent->right == this) {
                    rhs.parent->right = &rhs;
                }
            }

            std::swap(height, rhs.height);
            std::swap(value, rhs.value);
        }
    };

    typedef typename Allocator::template rebind<Node>::other NodeAllocator;

    Node* allocateNode(NodeAllocator& alloc,
                       const_reference value,
                       Node* parent,
                       Node* left = 0,
                       Node* right = 0,
                       unsigned height = 1) const
    {
        Node* node = alloc.allocate(1);
        alloc.construct(node, Node(value, parent, left, right, height));

        // Node* node = new Node(value, parent, left, right);

        return node;
    }

    void deallocateNode(Node* p)
    {
        _allocator.destroy(p);
        _allocator.deallocate(p, 1);
    }

    // }}}

  public:
    // iterator {{{

    template<typename ItT, bool IsConst = false>
    class TreeIterator
    {
        Node* _current;

      public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef ItT value_type;
        typedef ItT* pointer;
        typedef ItT& reference;
        typedef std::ptrdiff_t difference_type;

        TreeIterator(void)
          : _current(0)
        {}
        explicit TreeIterator(Node* p)
          : _current(p)
        {}
        TreeIterator(const TreeIterator& other) { *this = other; }
        ~TreeIterator(void) {}

        void* serializedNode(void) const { return _current; }

        // allow conversion from iterator to const_iterator
        operator TreeIterator<const ItT, true>()
        {
            return TreeIterator<const ItT, true>(_current);
        }

        TreeIterator& operator=(const TreeIterator& rhs)
        {
            if (this != &rhs) {
                _current = rhs._current;
            }

            return *this;
        }

        reference operator*(void) { return _current->value; }
        const_reference operator*(void) const { return _current->value; }

        pointer operator->(void) { return &_current->value; }
        const T* operator->(void) const { return &_current->value; }

        // iterator - bidirectional: pre/post increment/decrement {{{

        TreeIterator& operator++(void)
        {
            if (!_current->right) {
                Node* prev = 0;
                do {
                    prev = _current;
                    _current = _current->parent;
                } while (_current && _current->right &&
                         _current->right == prev);
            } else {
                _current = _findInOrderSuccessor(_current->right);
            }

            return *this;
        }

        TreeIterator operator++(int)
        {
            TreeIterator it(*this);

            operator++();

            return it;
        }

        TreeIterator& operator--(void)
        {
            if (_current->left) {
                _current = _findInOrderPredecessor(_current->left);
            } else {
                Node* prev = 0;
                do {
                    prev = _current;
                    _current = _current->parent;
                } while (_current && _current->left && _current->left == prev);
            }

            return *this;
        }

        TreeIterator operator--(int)
        {
            TreeIterator it(*this);

            operator--();

            return it;
        }

        // }}}

        // logical operators {{{

        bool operator!=(TreeIterator<ItT, false> rhs) const
        {
            return serializedNode() != rhs.serializedNode();
        }
        bool operator==(TreeIterator<ItT, false> rhs) const
        {
            return serializedNode() == rhs.serializedNode();
        }

        bool operator==(TreeIterator<const ItT, true> rhs) const
        {
            return serializedNode() == rhs.serializedNode();
        }
        bool operator!=(TreeIterator<const ItT, true> rhs) const
        {
            return serializedNode() != rhs.serializedNode();
        }

        // }}}
    };

    typedef TreeIterator<T, false> iterator;
    typedef TreeIterator<const T, true> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    // }}}

  private:
    static Node* _findInOrderPredecessor(Node* p)
    {
        while (p && p->right && p->right) {
            p = p->right;
        }

        return p;
    }

    static Node* _findInOrderSuccessor(Node* p)
    {
        while (p && p->left && p->left) {
            p = p->left;
        }

        return p;
    }

    bool hasLeft(Node* p) const { return p->left && p != _begin; }

    bool hasRight(Node* p) const { return p->right && p != _end; }

    unsigned _computeNodeHeight(Node* node) const
    {
        unsigned hl, hr;

        hl = node->left ? node->left->height : 0;
        hr = node->right ? node->right->height : 0;

        return hl >= hr ? hl + 1 : hr + 1;
    }

    // balanceFactor such as { -1, 0, 1 }
    int8_t _computeBalanceFactor(Node* node)
    {
        unsigned hl, hr;

        hl = node->left ? node->left->height : 0;
        hr = node->right ? node->right->height : 0;

        return hl - hr; /* height of left subtree - height of right subtree */
    }

  private:
    // private attributes {{{

    NodeAllocator _allocator;
    Node *_root, *_begin, *_end;
    size_t _size;
    Compare _comparator;

    // }}}

    // algorithms {{{

    Node* _copyRecursively(NodeAllocator& alloc,
                           Node* p,
                           Node* parent = 0) const
    {
        if (!p) {
            return 0;
        }

        Node* newNode = allocateNode(alloc, p->value, parent, 0, 0, p->height);

        newNode->left = _copyRecursively(alloc, p->left, newNode);
        newNode->right = _copyRecursively(alloc, p->right, newNode);

        return newNode;
    }

#ifdef DEBUG
    void _printInOrder(std::ostream& os, Node* root) const
    {
        if (root->left) {
            _printInOrder(os, root->left);
        }
        if (root == _begin)
            os << "BEGIN\n";
        else if (root == _end)
            os << "END\n";
        else
            os << root->value.first << "\n";
        if (root->right) {
            _printInOrder(os, root->right);
        }
    }
#endif

    // lookup - recursive find algorithm {{{
    Node* _findNodeRecursively(Node* root, const_reference value) const
    {
        if (!root || root == _begin || root == _end) {
            return 0;
        }

        if (_comparator(value, root->value)) {
            return _findNodeRecursively(root->left, value);
        } else if (_comparator(root->value, value)) {
            return _findNodeRecursively(root->right, value);
        } else {
            return root;
        }
    }
    // }}}

    // lower bound {{{

    Node* _findLowerBoundRecursively(Node* root,
                                     const_reference value,
                                     Node* last = 0) const
    {
        if (!root || root == _begin || root == _end) {
            return last;
        }

        if (_comparator(root->value, value)) {
            return _findLowerBoundRecursively(root->right, value, last);
        } else {
            return _findLowerBoundRecursively(root->left, value, root);
        }
    }

    // }}}

    // upper bound {{{

    Node* _findUpperBoundRecursively(Node* root,
                                     const_reference value,
                                     Node* last = 0) const
    {
        if (!root || root == _begin || root == _end) {
            return last;
        }

        if (_comparator(root->value, value) || _equals(root->value, value)) {
            return _findUpperBoundRecursively(root->right, value, last);
        } else {
            return _findUpperBoundRecursively(root->left, value, root);
        }
    }

    // }}}

    // deletion: - recursive node deletion {{{

    Node* _deleteNodeRecursively(Node* root, const_reference value)
    {
        if (!root) {
            return 0;
        }

        if (_equals(value, root->value)) {
            if (root == _end || root == _begin) {
                return root;
            }

            /* SPECIAL CASE: last element is deleted: we need to join begin and
             * end together. */
            if (root->left == _begin && root->right == _end) {
                deallocateNode(root);
                _begin->right = _end;
                _end->parent = _begin;
                _begin->parent = 0;
                --_size;
                return _begin;
            }

            /* A leaf node is a node which has a NULL pointer as its left and
             right child. We also want to handle two more special cases here:
             - When pointer to left child is NULL and right child is the _end
             node, we want to update links to keep the end where it should be.
             - When pointer to right child is NULL and left child is the
             _begin node, we want to update links to keep the _begin where it
             should be. */

            if (root->isLeaf() || (!root->left && root->right == _end) ||
                (!root->right && root->left == _begin)) {

                /* update begin position */
                if (root->left == _begin) {
                    _begin->parent = root->parent;
                    root->parent->left = _begin;
                }
                /* update end position */
                else if (root->right == _end) {
                    _end->parent = root->parent;
                    root->parent->right = _end;
                } else {
                    if (root->parent) {
                        if (root->parent->left == root) {
                            root->parent->left = 0;
                        } else {
                            root->parent->right = 0;
                        }
                    }
                }

                Node* ret = root->isLeaf() ? 0 : (root->left ? _begin : _end);
                deallocateNode(root);
                --_size;

                return ret;
            }

            bool leftSide;
            /* if root has both left and right children, selects the taller
            subtree. */
            if (hasLeft(root) && hasRight(root)) {
                leftSide = root->left->height >= root->right->height;
                /* otherwise, selects the only available child */
            } else {
                leftSide = hasLeft(root);
            }

            Node* tmp = leftSide ? _findInOrderPredecessor(root->left)
                                 : _findInOrderSuccessor(root->right);

            /* swap root and tmp contents */
            root->swap(*tmp);

            /* swap root and tmp pointers: we want the root pointer to point to
            the current node that now has the content of tmp */
            std::swap(root, tmp);
            root->value = tmp->value;

            /* recurse until a leaf node or one of the leafs is _begin or _end
             */
            if (leftSide) {
                root->left = _deleteNodeRecursively(root->left, tmp->value);
            } else {
                root->right = _deleteNodeRecursively(root->right, tmp->value);
            }

        }

        /* value is not found for now, search continues... */
        else {
            /* ...left */
            if (_comparator(value, root->value)) {
                root->left = _deleteNodeRecursively(root->left, value);
            }
            /* ...right */
            else {
                root->right = _deleteNodeRecursively(root->right, value);
            }
        }

        /* Rebalance tree */

        root->height = _computeNodeHeight(root);
        int8_t bf = _computeBalanceFactor(root), bf2 = 0;

        /* we deleted on right hand side, the tree has became unbalanced on the
         * left hand side */
        if (bf == 2) {
            bf2 = _computeBalanceFactor(root->left);

            /* L1 rotation */
            if (bf2 == 1) {
                return _LL_rotate(root);
            }
            /* L-1 rotation */
            else if (bf2 == -1) {
                return _LR_rotate(root);
            }
            /* L0 rotation: L1 or L-1 can be performed */
            else if (bf2 == 0) {
                return _LL_rotate(root);
            }
        }

        /* we deleted on left hand side, the tree has became unbalanced on the
           right hand side */
        else if (bf == -2) {
            bf2 = _computeBalanceFactor(root->right);

            /* L-1 rotation */
            if (bf2 == 1) {
                return _RL_rotate(root);
            }
            /* L-1 rotation */
            else if (bf2 == -1) {
                return _RR_rotate(root);
            }
            /* L0 rotation: L1 or L-1 can be performed */
            else if (bf2 == 0) {
                return _RR_rotate(root);
            }
        }

        return root;
    }

    // }}}

    // insert - recursive node insertion {{{

    Node* _insert(const T& value, Node* root, Node*& inserted, Node* parent = 0)
    {
        if (!root) {
            ++_size;
            return inserted = allocateNode(_allocator, value, parent);
        }

        if (root == _end) {
            root = inserted =
              allocateNode(_allocator, value, parent, 0, root, 1);
            _end->parent = root;
            ++_size;
            return root;
        }

        if (root == _begin) {
            Node* p = inserted =
              allocateNode(_allocator, value, parent, _begin, _begin->right);
            _begin->parent = p;

            /* if this is the first inserted element, _end's parent must be
             * updated too */
            if (_begin->right == _end) {
                _end->parent = p;
                _begin->right = 0;
            }
            ++_size;
            return p;
        }

        if (_comparator(value, root->value)) {
            root->left = _insert(value, root->left, inserted, root);
        } else if (_comparator(root->value, value)) {
            root->right = _insert(value, root->right, inserted, root);
        }
        /* duplicate is inserted, throw a runtime_error that will be caught by
           insert */
        else {
            inserted = root;
            throw std::runtime_error("insert: duplicate value");
        }

        root->height = _computeNodeHeight(root);

        /* From that line, we'll find out if the tree is balanced or not. In the
        latter case, rotations will be required to make it balanced. */

        int8_t bf = _computeBalanceFactor(root), bf2 = 0;

        /* if bf == 2 then we need to balance left side */
        if (bf == 2) {
            bf2 = _computeBalanceFactor(root->left);
            if (bf2 == 1) {
                return _LL_rotate(root);
            } else if (bf2 == -1) {
                return _LR_rotate(root);
            }

            /* if bf == -2 we need to balance right side */
        } else if (bf == -2) {
            bf2 = _computeBalanceFactor(root->right);
            if (bf2 == 1) {
                return _RL_rotate(root);
            }
            if (bf2 == -1) {
                return _RR_rotate(root);
            }
        }

        return root;
    }

    // }}}

    void _destroy(Node* root)
    {
        if (root->left) {
            _destroy(root->left);
        }
        if (root->right) {
            _destroy(root->right);
        }

        if (root != _begin && root != _end) {
            deallocateNode(root);
        }
    }

    // rotations {{{

    Node* _LL_rotate(Node* p)
    {
#ifdef DEBUG
        std::clog << "[LL] " << *p << "\n";
#endif

        Node *pl = p->left, *plr = pl->right;

        pl->right = p;
        p->left = plr;
        if (plr) {
            plr->parent = p;
        }
        pl->parent = p->parent;
        p->parent = pl;
        p->height = _computeNodeHeight(p);
        pl->height = _computeNodeHeight(pl);

        if (_root == p) {
            _root = pl;
        }

        return pl;
    }

    Node* _LR_rotate(Node* p)
    {
#ifdef DEBUG
        std::clog << "[LR] " << *p << "\n";
#endif
        Node *pl = p->left, *plr = pl->right;

        pl->right = plr->left;
        if (plr->left) {
            plr->left->parent = pl;
        }

        p->left = plr->right;
        if (plr->right) {
            plr->right->parent = p;
        }

        plr->right = p;
        plr->parent = p->parent;
        p->parent = plr;
        plr->left = pl;
        pl->parent = plr;

        pl->height = _computeNodeHeight(pl);
        p->height = _computeNodeHeight(p);
        plr->height = _computeNodeHeight(plr);

        if (_root == p) {
            _root = plr;
        }

        return plr;
    }

    Node* _RR_rotate(Node* p)
    {
#ifdef DEBUG
        std::clog << "[RR] " << *p << "\n";
#endif
        Node *pr = p->right, *prl = pr->left;

        pr->left = p;
        p->right = prl;
        if (prl) {
            prl->parent = p;
        }
        pr->parent = p->parent;
        p->parent = pr;
        p->height = _computeNodeHeight(p);
        pr->height = _computeNodeHeight(pr);

        if (_root == p) {
            _root = pr;
        }

        return pr;
    }

    Node* _RL_rotate(Node* p)
    {
#ifdef DEBUG
        std::clog << "[RL] " << *p << "\n";
#endif
        Node *pr = p->right, *prl = pr->left;

        pr->left = prl->right;
        if (prl->right) {
            prl->right->parent = pr;
        }

        p->right = prl->left;
        if (prl->left) {
            prl->left->parent = p;
        }

        prl->left = p;
        prl->parent = p->parent;
        p->parent = prl;
        prl->right = pr;
        pr->parent = prl;

        pr->height = _computeNodeHeight(pr);
        p->height = _computeNodeHeight(p);
        prl->height = _computeNodeHeight(prl);

        if (_root == p) {
            _root = prl;
        }

        return prl;
    }

    // }}}

    // }}}

#ifdef DEBUG
    friend std::ostream& operator<<(std::ostream& os, const Node& rhs)
    {
        os << "v=" << rhs.value.first << ", h=" << rhs.height
           << ", l=" << (rhs.left ? "yes" : "no")
           << ", r=" << (rhs.right ? "yes" : "no")
           << ", p=" << (rhs.parent ? "yes" : "no");

        return os;
    }
#endif

  private:
    bool _equals(const_reference lhs, const_reference rhs) const
    {
        return !_comparator(lhs, rhs) && !_comparator(rhs, lhs);
    }

  public:
    // constructors - destructor {{{

    AVLTree(void)
      : _allocator()
      , _size(0)
    {
        _begin = allocateNode(_allocator, T(), 0);
        _end = allocateNode(_allocator, T(), _begin);
        _begin->height = _end->height = 0;
        _begin->right = _end;
        _root = _begin;
    }

    AVLTree(const AVLTree& other)
      : _allocator(other._allocator)
      , _root(_copyRecursively(_allocator, other._root))
      , _begin(_findInOrderSuccessor(_root))
      , _end(_findInOrderPredecessor(_root))
      , _size(other.size())
    {}

    ~AVLTree(void)
    {
        _destroy(_root);
        deallocateNode(_begin);
        deallocateNode(_end);
    }

    // }}}

    AVLTree& operator=(const AVLTree& rhs)
    {
        if (this != &rhs) {
            _destroy(_root);
            deallocateNode(_begin);
            deallocateNode(_end);

            _allocator = rhs._allocator;
            _root = _copyRecursively(_allocator, rhs._root);
            _end = _findInOrderPredecessor(_root);
            _begin = _findInOrderSuccessor(_root);
            _size = rhs._size;
        }

        return *this;
    }

    size_type size(void) const { return _size; }

    size_type max_size(void) const { return _allocator.max_size(); }

    ft::pair<iterator, bool> insert(const T& value)
    {
        Node* inserted = 0;

        try {
            _root = _insert(value, _root, inserted);
        } catch (std::runtime_error& e) {
            return ft::make_pair(iterator(inserted), false);
        }

        return ft::make_pair(iterator(inserted), true);
    }

    /* hint is not used */
    iterator insert(iterator hint, const value_type& value)
    {
        (void)hint;
        return insert(value).first;
    }

    template<typename InputIt>
    void insert(InputIt first, InputIt last)
    {
        while (first != last) {
            insert(*first++);
        }
    }

    void erase(iterator first, iterator last)
    {
        while (first != last) {
            erase(*first++);
        }
    }

    void erase(iterator it) { erase(*it); }

    size_type erase(const T& value)
    {
        size_type oldSize = size();

        _root = _deleteNodeRecursively(_root, value);

        return oldSize - size();
    }

    iterator begin(void)
    {
        if (!_begin->parent) {
            return end();
        }
        return iterator(_begin->parent);
    }

    const_iterator begin(void) const
    {
        if (!_begin->parent) {
            return end();
        }
        return const_iterator(_begin->parent);
    }

    iterator end(void) { return iterator(_end); }

    const_iterator end(void) const { return iterator(_end); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() { return reverse_iterator(begin()); }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }

    iterator find(const T& value)
    {
        Node* p = _findNodeRecursively(_root, value);

        return p ? iterator(p) : end();
    }

    const_iterator find(const T& value) const
    {
        Node* p = _findNodeRecursively(_root, value);

        return p ? const_iterator(p) : end();
    }

    iterator lower_bound(const_reference value)
    {
        Node* p = _findLowerBoundRecursively(_root, value);

        return p ? iterator(p) : end();
    }

    const_iterator lower_bound(const_reference value) const
    {
        Node* p = _findLowerBoundRecursively(_root, value);

        return p ? const_iterator(p) : end();
    }

    iterator upper_bound(const_reference value)
    {
        Node* p = _findUpperBoundRecursively(_root, value);

        return p ? iterator(p) : end();
    }

    const_iterator upper_bound(const_reference value) const
    {
        Node* p = _findUpperBoundRecursively(_root, value);

        return p ? const_iterator(p) : end();
    }

    ft::pair<iterator, iterator> equal_range(const_reference value)
    {
        return ft::make_pair(lower_bound(value), upper_bound(value));
    }

    ft::pair<const_iterator, const_iterator> equal_range(
      const_reference value) const
    {
        return ft::make_pair(lower_bound(value), upper_bound(value));
    }

#ifdef DEBUG
    std::ostream& printInOrder(std::ostream& os = std::cout) const
    {
        if (_root) {
            _printInOrder(os, _root);
        }
        return os;
    }
#endif

    void swap(AVLTree& rhs)
    {
        if (this != &rhs) {
            std::swap(_root, rhs._root);
            std::swap(_begin, rhs._begin);
            std::swap(_end, rhs._end);
            std::swap(_size, rhs._size);
            std::swap(_allocator, rhs._allocator);
        }
    }

    void clear(void)
    {
        _destroy(_root);
        _root = _begin;
        _begin->parent = 0;
        _begin->right = _end;
        _end->parent = _begin;
        _size = 0;
    }
};

template<typename T, typename Compare, typename Alloc>
bool
operator==(const AVLTree<T, Compare, Alloc>& lhs,
           const AVLTree<T, Compare, Alloc>& rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }

    return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, typename Compare, typename Alloc>
bool
operator!=(const AVLTree<T, Compare, Alloc>& lhs,
           const AVLTree<T, Compare, Alloc>& rhs)
{
    return !(lhs == rhs);
}

template<typename T, typename Compare, typename Alloc>
bool
operator<(const AVLTree<T, Compare, Alloc>& lhs,
          const AVLTree<T, Compare, Alloc>& rhs)
{
    return std::lexicographical_compare(
      lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, typename Compare, typename Alloc>
bool
operator>(const AVLTree<T, Compare, Alloc>& lhs,
          const AVLTree<T, Compare, Alloc>& rhs)
{
    return rhs < lhs;
}

template<typename T, typename Compare, typename Alloc>
bool
operator<=(const AVLTree<T, Compare, Alloc>& lhs,
           const AVLTree<T, Compare, Alloc>& rhs)
{
    return !(lhs > rhs);
}

template<typename T, typename Compare, typename Alloc>
bool
operator>=(const AVLTree<T, Compare, Alloc>& lhs,
           const AVLTree<T, Compare, Alloc>& rhs)
{
    return !(lhs < rhs);
}
