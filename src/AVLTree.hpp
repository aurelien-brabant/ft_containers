#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <stdint.h>
#include <utility>

template<typename T,
         typename Compare = std::less<T>,
         typename Allocator = std::allocator<T> >
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
    };

    typedef typename Allocator::template rebind<Node>::other NodeAllocator;

    NodeAllocator _nodeAllocator;

    Node* allocateNode(const_reference value,
                       Node* parent,
                       Node* left = 0,
                       Node* right = 0,
                       unsigned height = 1)
    {

        Node* node = _nodeAllocator.allocate(1);
        _nodeAllocator.construct(node,
                                 Node(value, parent, left, right, height));

        // Node* node = new Node(value, parent, left, right);

        return node;
    }

    void deallocateNode(Node* p)
    {
        _nodeAllocator.destroy(p);
        _nodeAllocator.deallocate(p, 1);
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

        void* serializedNode(void) { return _current; }

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

        pointer operator->(void) { return &_current->value; }

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

        bool operator!=(TreeIterator<ItT, false> rhs)
        {
            return serializedNode() != rhs.serializedNode();
        }
        bool operator==(TreeIterator<ItT, false> rhs)
        {
            return serializedNode() == rhs.serializedNode();
        }

        bool operator==(TreeIterator<const ItT, true> rhs)
        {
            return serializedNode() == rhs.serializedNode();
        }
        bool operator!=(TreeIterator<const ItT, true> rhs)
        {
            return serializedNode() != rhs.serializedNode();
        }

        // }}}
    };

    typedef TreeIterator<T, false> iterator;
    typedef TreeIterator<const T, true> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // }}}

  private:
    static Node* _findInOrderPredecessor(Node* p)
    {
        while (p && p->right) {
            p = p->right;
        }

        return p;
    }

    static Node* _findInOrderSuccessor(Node* p)
    {
        while (p && p->left) {
            p = p->left;
        }

        return p;
    }

  private:
    // private attributes {{{

    Node *_begin, *_end, *_root; // keeping track of begin and end of the tree -
                                 // the value gets updated
    size_t _size;
    Compare _comparator;

    // }}}

    // algorithms {{{

    Node* _copyRecursively(Node* p, Node* parent = 0)
    {
        if (!p) {
            return 0;
        }

        Node* newNode = allocateNode(p->value, parent, 0, 0, p->height);

        newNode->left = _copyRecursively(p->left, newNode);
        newNode->right = _copyRecursively(p->right, newNode);

        return newNode;
    }

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
            os << root->value << "\n";
        if (root->right) {
            _printInOrder(os, root->right);
        }
    }

    // lookup - recursive find algorithm {{{
    Node* _findNodeRecursively(Node* root, const_reference value)
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

    Node* _findLowerBoundRecursively(Node* root,
                                     const_reference value,
                                     Node* last = 0)
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

    Node* _findUpperBoundRecursively(Node* root,
                                     const_reference value,
                                     Node* last = 0)
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

    // deletion: - recursive node deletion {{{

    Node* _deleteNodeRecursively(Node* root, const_reference value)
    {
        if (!root) {
            return 0;
        }

        if (_equals(value, root->value)) {
            // _begin and _end are acting as delimiters, we can't delete them
            if (root == _end || root == _begin) {
                return root;
            }

            // SPECIAL CASE: last element is deleted: we need to join begin and
            // end together.
            if (root->left == _begin && root->right == _end) {
                deallocateNode(root);
                _begin->right = _end;
                _end->parent = _begin;
                _begin->parent = 0;
                --_size;
                return _begin;
            }

            // A leaf node is a node which has a NULL pointer as its left and
            // right child.
            // We also want to handle two more special cases here:
            // - When pointer to left child is NULL and right child is the _end
            // node, we want to update links to keep the end where it should be.
            // - When pointer to right child is NULL and left child is the
            // _begin node, we want to update links to keep the _begin where it
            // should be.

            if (root->isLeaf() || (!root->left && root->right == _end) ||
                (!root->right && root->left == _begin)) {

                // update begin position
                if (root->left == _begin) {
                    _begin->parent = root->parent;
                    root->parent->left = _begin;
                    // update end position
                } else if (root->right == _end) {
                    _end->parent = root->parent;
                    root->parent->right = _end;
                }

                Node* ret = root->isLeaf() ? 0 : (root->left ? _begin : _end);
                deallocateNode(root);
                --_size;

                return ret;
            }

            // Take inorder predecessor
            if ((root->left && root->left != _begin) ||
                (root->right && root->right == _end)) {
                Node* pred = _findInOrderPredecessor(root->left);

                //   std::cout << "Left swap\n";

                if (root->right) {
                    root->right->parent = pred;
                }

                if (pred->left) {
                    pred->left->parent = root;
                }

                // swap parents
                Node* pp = pred->parent;
                pred->parent = root->parent;
                root->parent = pp == root ? pred : pp;

                // swap right pointers
                pred->right = root->right;
                root->right = 0;

                // swap left pointers
                Node* rl = root->left;
                root->left = pred->left;
                pred->left = rl == pred ? root : rl;

                root->value = pred->value;

                std::swap(root->height, pred->height);

                std::swap(root, pred);

                root->left = _deleteNodeRecursively(root->left, pred->value);
            }

            // Take inorder successor
            else {
                // std::cout << "right stuff\n";
                Node* succ = _findInOrderSuccessor(root->right);

                // swap successor with root
                Node *sp = succ->parent, *rright = root->right;
                T sval = succ->value;

                if (root->left) {
                    root->left->parent = succ;
                }

                if (succ->right) {
                    succ->right->parent = root;
                }

                // swap parents
                succ->parent = root->parent;
                root->parent = sp == root ? succ : sp;

                // swap left pointers
                succ->left = root->left;
                // succ->parent->left = root;
                root->left = 0;

                root->right = succ->right;
                succ->right = rright == succ ? root : rright;

                root->value = succ->value;

                std::swap(succ->height, root->height);

                std::swap(succ, root);

                root->right = _deleteNodeRecursively(root->right, succ->value);
            }

        } else {
            // continue to search left...
            if (_comparator(value, root->value)) {
                root->left = _deleteNodeRecursively(root->left, value);
                // ... or right
            } else {
                root->right = _deleteNodeRecursively(root->right, value);
            }
        }

        // Ensure tree is still balanced
        root->height = _computeNodeHeight(root);

        int8_t bf = _computeBalanceFactor(root), bf2 = 0;

        // we deleted on right hand side, the tree has become unbalanced on the
        // left hand side
        if (bf == 2) {
            bf2 = _computeBalanceFactor(root->left);

            // L1 rotation
            if (bf2 == 1) {
                return _LL_rotate(root);
            }
            // L-1 rotation
            else if (bf2 == -1) {
                return _LR_rotate(root);
                // L0 rotation: L1 or L-1 can be performed.
            } else if (bf2 == 0) {
                return _LL_rotate(root);
            }
        }

        // we deleted on left hand side, the tree has become unbalanced on the
        // right hand side
        else if (bf == -2) {
            bf2 = _computeBalanceFactor(root->right);

            if (bf2 == 1) {
                return _RL_rotate(root);
            }
            // L-1 rotation
            else if (bf2 == -1) {
                return _RR_rotate(root);
                // L0 rotation: L1 or L-1 can be performed.
            } else if (bf2 == 0) {
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
            return inserted = allocateNode(value, parent);
        }

        if (root == _end) {
            root = inserted = allocateNode(value, parent, 0, root, 1);
            _end->parent = root;
            ++_size;
            return root;
        }

        if (root == _begin) {
            Node* p = inserted =
              allocateNode(value, parent, _begin, _begin->right);
            _begin->parent = p;

            // if this is the first inserted element, _end's parent must be
            // updated too.
            if (_begin->right == _end) {
                _end->parent = p;
                _begin->right = 0;
            }
            ++_size;
            return p;
        }

        // value < root->value
        if (_comparator(value, root->value)) {
            root->left = _insert(value, root->left, inserted, root);
            // value > root->value
        } else if (_comparator(root->value, value)) {
            root->right = _insert(value, root->right, inserted, root);
            // value == root->value
            // NOTE: inserting a duplicate is a no-op
        } else {
            inserted = root;
            throw std::runtime_error("insert: duplicate value");
        }

        root->height = _computeNodeHeight(root);

        // from that line, we'll find out if the tree is balanced or not. In the
        // latter case, rotations will be required to make it balanced.

        int8_t bf = _computeBalanceFactor(root), bf2 = 0;

        // if bf == 2 then we need to balance left side
        if (bf == 2) {
            bf2 = _computeBalanceFactor(root->left);
            if (bf2 == 1) {
                return _LL_rotate(root);
            } else if (bf2 == -1) {
                return _LR_rotate(root);
            }

            // if bf == -2 we need to balance right side
        } else if (bf == -2) {
            bf2 = _computeBalanceFactor(root->right);
            if (bf2 == 1) {
                return _RL_rotate(root);
            }
            if (bf2 == -1) {
                return _RR_rotate(root);
            }
        }

        // end of tree balancing

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

        _nodeAllocator.destroy(root);
        _nodeAllocator.deallocate(root, 1);
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

    // algorithms - helper functions {{{

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

        return hl - hr; // height of left subtree - height of right subtree
    }

    // }}}

    friend std::ostream& operator<<(std::ostream& os, const Node& rhs)
    {
        os << "v=" << rhs.value << ", h=" << rhs.height
           << ", l=" << (rhs.left ? "yes" : "no")
           << ", r=" << (rhs.right ? "yes" : "no")
           << ", p=" << (rhs.parent ? "yes" : "no");

        return os;
    }

  private:
    bool _equals(const_reference lhs, const_reference rhs)
    {
        return !_comparator(lhs, rhs) && !_comparator(rhs, lhs);
    }

  public:
    AVLTree(void)
      : _nodeAllocator(NodeAllocator())
      , _size(0)
    {
        _begin = allocateNode(T(), 0, 0, 0, 0);
        _end = allocateNode(T(), _begin, 0, 0, 0);
        _begin->right = _end;
        _root = _begin;
    }

    AVLTree(const AVLTree& other) { *this = other; }

    AVLTree& operator=(const AVLTree& rhs)
    {
        if (this != &rhs) {
            _root = _copyRecursively(rhs._root);
            _end = _findInOrderPredecessor(_root);
            _begin = _findInOrderSuccessor(_root);
            _nodeAllocator = rhs._nodeAllocator;
            _size = rhs._size;
        }

        return *this;
    }

    ~AVLTree(void)
    {
        if (_root) {
            _destroy(_root);
        }
    }

    size_t size(void) const { return _size; }

    std::pair<iterator, bool> insert(const T& value)
    {
        Node* inserted = 0;

        try {
            _root = _insert(value, _root, inserted);
        } catch (std::runtime_error& e) {
            return std::make_pair(iterator(inserted), false);
        }

        return std::make_pair(iterator(inserted), true);
    }

    // hint is not used
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
            erase(first++);
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

    const_iterator end(void) const { return const_iterator(_end); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }

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

    std::pair<iterator, iterator> equal_range(const_reference value)
    {
        return std::make_pair(lower_bound(value), upper_bound(value));
    }

    std::pair<const_iterator, const_iterator> equal_range(
      const_reference value) const
    {
        return std::make_pair(lower_bound(value), upper_bound(value));
    }

    std::ostream& printInOrder(std::ostream& os = std::cout) const
    {
        if (_root) {
            _printInOrder(os, _root);
        }
        return os;
    }

    void swap(AVLTree& rhs)
    {
        if (this != &rhs) {
            std::swap(_root, rhs._root);
            std::swap(_begin, rhs._begin);
            std::swap(_end, rhs._end);
            std::swap(_size, rhs._size);
        }
    }
};

template<typename T>
bool
operator==(AVLTree<T>& lhs, AVLTree<T>& rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }

    for (typename AVLTree<T>::const_iterator first1 = lhs.begin(),
                                             first2 = rhs.begin();
         first1 != lhs.end();
         ++first1, ++first2) {
        if (*first1 != *first2) {
            return false;
        }
    }

    return true;
}

template<typename T>
bool
operator!=(AVLTree<T>& lhs, AVLTree<T>& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
bool
operator<(AVLTree<T>& lhs, AVLTree<T>& rhs)
{
    return std::lexicographical_compare(
      lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T>
bool
operator>(AVLTree<T>& lhs, AVLTree<T>& rhs)
{
    return rhs < lhs;
}

template<typename T>
bool
operator<=(AVLTree<T>& lhs, AVLTree<T>& rhs)
{
    return !(lhs > rhs);
}

template<typename T>
bool
operator>=(AVLTree<T>& lhs, AVLTree<T>& rhs)
{
    return !(lhs < rhs);
}

template<typename T>
void
swap(AVLTree<T>& lhs, AVLTree<T>& rhs)
{
    lhs.swap(rhs);
}