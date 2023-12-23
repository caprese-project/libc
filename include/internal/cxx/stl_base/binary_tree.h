#ifndef CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_BINARY_TREE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_BINARY_TREE_H_

#include <cassert>
#include <internal/attribute.h>
#include <internal/cxx/iterator/tags.h>
#include <internal/cxx/memory/addressof.h>
#include <internal/cxx/memory/allocator_traits.h>
#include <internal/cxx/stddef.h>
#include <internal/cxx/utility/fwd.h>
#include <internal/cxx/utility/pair.h>

namespace std {
  template<typename T>
  struct __splay_tree_node {
    T                  value;
    __splay_tree_node* left;
    __splay_tree_node* right;
    __splay_tree_node* parent;

#ifndef __CXX_STD_20__
    __splay_tree_node(const T& value, __splay_tree_node* left, __splay_tree_node* right, __splay_tree_node* parent): value(value), left(left), right(right), parent(parent) { }

    __splay_tree_node(T&& value, __splay_tree_node* left, __splay_tree_node* right, __splay_tree_node* parent): value(std::move(value)), left(left), right(right), parent(parent) { }
#endif // __CXX_STD_20__

    template<typename Allocator, typename... Args>
    static __splay_tree_node* create(Allocator& allocator, __splay_tree_node* left, __splay_tree_node* right, __splay_tree_node* parent, Args&&... args) {
      __splay_tree_node* node = allocator_traits<Allocator>::allocate(allocator, 1);
      allocator_traits<Allocator>::construct(allocator, node, T(std::forward<Args>(args)...), left, right, parent);
      return node;
    }

    template<typename Allocator>
    void destroy(Allocator& allocator) {
      allocator_traits<Allocator>::destroy(allocator, this);
      allocator_traits<Allocator>::deallocate(allocator, this, 1);
    }

    void rotate() {
      __splay_tree_node* parent_node = parent;
      __splay_tree_node* middle      = nullptr;

      if (parent_node->left == this) {
        middle            = this->right;
        this->right       = parent_node;
        parent_node->left = middle;
      } else {
        middle             = this->left;
        this->left         = parent_node;
        parent_node->right = middle;
      }

      if (middle != nullptr) {
        middle->parent = parent_node;
      }

      this->parent        = parent_node->parent;
      parent_node->parent = this;

      if (this->parent != nullptr) {
        if (this->parent->left == parent_node) {
          this->parent->left = this;
        } else if (this->parent->right == parent_node) {
          this->parent->right = this;
        }
      }
    }

    void splay() {
      while (this->parent != nullptr) {
        if (this->parent->parent == nullptr) {
          this->rotate();
        } else if (this->parent->left == this && this->parent->parent->left == this->parent) {
          this->parent->rotate();
          this->rotate();
        } else if (this->parent->right == this && this->parent->parent->right == this->parent) {
          this->parent->rotate();
          this->rotate();
        } else {
          this->rotate();
          this->rotate();
        }
      }
    }
  };

  template<typename T, typename Compare, typename Allocator>
  class __splay_tree;

  template<typename T>
  class __splay_tree_node_iterator {
  public:
    using __node_type       = __splay_tree_node<typename __remove_const<T>::type>;
    using difference_type   = __ptrdiff_t;
    using value_type        = T;
    using pointer           = value_type*;
    using reference         = value_type&;
    using iterator_category = bidirectional_iterator_tag;

    template<typename U, typename Compare, typename Allocator>
    friend class __splay_tree;

  private:
    __node_type* _current;

  public:
    __splay_tree_node_iterator(): _current(nullptr) { }

    explicit __splay_tree_node_iterator(__node_type* current): _current(current) { }

    __splay_tree_node_iterator(const __splay_tree_node_iterator& other): _current(other._current) { }

    ~__splay_tree_node_iterator() = default;

    __splay_tree_node_iterator& operator=(const __splay_tree_node_iterator& other) {
      _current = other._current;
    }

    reference operator*() const {
      return _current->value;
    }

    pointer operator->() const {
      return __addressof(_current->value);
    }

    __splay_tree_node_iterator& operator++() {
      if (_current->right != nullptr) {
        _current = _current->right;
        while (_current->left != nullptr) {
          _current = _current->left;
        }
      } else {
        __node_type* parent = _current->parent;
        while (parent != nullptr && _current == parent->right) {
          _current = parent;
          parent   = parent->parent;
        }
        _current = parent;
      }
      return *this;
    }

    __splay_tree_node_iterator operator++([[maybe_unused]] int) {
      __splay_tree_node_iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    __splay_tree_node_iterator& operator--() {
      if (_current->left != nullptr) {
        _current = _current->left;
        while (_current->right != nullptr) {
          _current = _current->right;
        }
      } else {
        __node_type* parent = _current->parent;
        while (parent != nullptr && _current == parent->left) {
          _current = parent;
          parent   = parent->parent;
        }
        _current = parent;
      }
      return *this;
    }

    __splay_tree_node_iterator operator--([[maybe_unused]] int) {
      __splay_tree_node_iterator tmp = *this;
      --(*this);
      return tmp;
    }

    friend bool operator==(const __splay_tree_node_iterator& lhs, const __splay_tree_node_iterator& rhs) {
      return lhs._current == rhs._current;
    }

    friend bool operator!=(const __splay_tree_node_iterator& lhs, const __splay_tree_node_iterator& rhs) {
      return lhs._current != rhs._current;
    }
  };

  template<typename T, typename Compare, typename Allocator>
  class __splay_tree {
  public:
    using node_type           = __splay_tree_node<T>;
    using node_allocator_type = typename allocator_traits<Allocator>::template rebind_alloc<node_type>;
    using iterator            = __splay_tree_node_iterator<T>;
    using const_iterator      = __splay_tree_node_iterator<const T>;

  private:
    Compare             _compare;
    node_allocator_type _allocator;
    mutable node_type*  _root;
    node_type*          _min;
    node_type*          _max;
    __size_t            _size;

  public:
    __splay_tree(const Compare& compare, const Allocator&): _compare(compare), _allocator(), _root(nullptr), _min(nullptr), _max(nullptr), _size(0) { }

    __splay_tree(const __splay_tree& other): _compare(other._compare), _allocator(other._allocator), _root(nullptr), _min(nullptr), _max(nullptr), _size(0) {
      for (auto&& elem : other) {
        this->insert(elem);
      }
    }

    __splay_tree(__splay_tree&& other): _compare(std::move(other._compare)), _allocator(std::move(other._allocator)), _root(other._root), _min(other._min), _max(other._max), _size(other._size) {
      other._root = nullptr;
      other._size = 0;
    }

    __constexpr_cxx_std_20 ~__splay_tree() {
      this->clear();
    }

    __splay_tree& operator=(const __splay_tree& other) {
      if (this != &other) {
        this->clear();

        for (auto&& elem : other) {
          this->insert(elem);
        }
      }

      return *this;
    }

    __splay_tree& operator=(__splay_tree&& other) {
      if (this != &other) {
        this->clear();

        _compare   = std::move(other._compare);
        _allocator = std::move(other._allocator);
        _root      = other._root;
        _min       = other._min;
        _max       = other._max;
        _size      = other._size;

        other._root = nullptr;
        other._min  = nullptr;
        other._max  = nullptr;
        other._size = 0;
      }

      return *this;
    }

    __size_t size() const {
      return this->_size;
    }

    __size_t max_size() const {
      return allocator_traits<node_allocator_type>::max_size(this->_allocator);
    }

    iterator begin() {
      return this->_begin<iterator>();
    }

    const_iterator begin() const {
      return this->_begin<const_iterator>();
    }

    iterator end() {
      return this->_end<iterator>();
    }

    const_iterator end() const {
      return this->_end<const_iterator>();
    }

    void clear() {
      this->_clear(this->_root);
      this->_size = 0;
      this->_root = nullptr;
    }

    template<typename U>
    iterator erase(U&& val) {
      return this->_erase(forward<U>(val));
    }

    pair<iterator, bool> insert(const T& val) {
      return this->_insert(val);
    }

    pair<iterator, bool> insert(T&& val) {
      return this->_insert(std::move(val));
    }

    template<typename... Args>
    pair<iterator, bool> emplace(Args&&... args) {
      if (this->_root != nullptr) {
        return this->_insert(T(std::forward<Args>(args)...));
      }

      this->_root = node_type::create(this->_allocator, nullptr, nullptr, nullptr, std::forward<Args>(args)...);
      ++this->_size;

      return pair<iterator, bool>(iterator(this->_root), true);
    }

    template<typename U>
    iterator find(U&& val) {
      return this->_find<iterator>(forward<U>(val));
    }

    template<typename U>
    const_iterator find(U&& val) const {
      return this->_find<const_iterator>(forward<U>(val));
    }

    template<typename U>
    iterator lower_bound(U&& val) {
      return this->_lower_bound<iterator>(forward<U>(val));
    }

    template<typename U>
    const_iterator lower_bound(U&& val) const {
      return this->_lower_bound<const_iterator>(forward<U>(val));
    }

    template<typename U>
    iterator upper_bound(U&& val) {
      return this->_upper_bound<iterator>(forward<U>(val));
    }

    template<typename U>
    const_iterator upper_bound(U&& val) const {
      return this->_upper_bound<const_iterator>(forward<U>(val));
    }

  private:
    void _splay(node_type* node) const {
      node->splay();
      this->_root = node;
    }

    void _clear(node_type* node) {
      if (node == nullptr) {
        return;
      }

      this->_clear(node->left);
      this->_clear(node->right);
      node->destroy(this->_allocator);
    }

    template<typename Iterator>
    Iterator _begin() const {
      if (this->_root == nullptr) {
        return _end<Iterator>();
      }

      return Iterator(this->_min);
    }

    template<typename Iterator>
    Iterator _end() const {
      return Iterator(nullptr);
    }

    template<typename U>
    pair<iterator, bool> _insert(U&& val) {
      if (_root == nullptr) {
        this->_root = this->_min = this->_max = node_type::create(this->_allocator, nullptr, nullptr, nullptr, std::forward<U>(val));
      } else if (this->_compare(val, this->_min->value)) {
        this->_min->left = node_type::create(this->_allocator, nullptr, nullptr, this->_min, std::forward<U>(val));
        this->_min       = this->_min->left;
        this->_splay(this->_min);
      } else if (this->_compare(this->_max->value, val)) {
        this->_max->right = node_type::create(this->_allocator, nullptr, nullptr, this->_max, std::forward<U>(val));
        this->_max        = this->_max->right;
        this->_splay(this->_max);
      } else {
        node_type* node = this->_lower_bound<iterator>(val)._current;
        if (this->_compare(node->value, val)) {
          this->_splay(node);
          return pair<iterator, bool>(this->_root, false);
        }

        node->left = node_type::create(this->_allocator, node->left, nullptr, node, std::forward<U>(val));
        if (node->left->left != nullptr) {
          node->left->left->parent = node->left;
        }

        this->_splay(node->left);
      }

      ++_size;

      return pair<iterator, bool>(iterator(this->_root), true);
    }

    template<typename U>
    iterator _erase(U&& val) {
      iterator iter = this->find(val);
      if (iter == this->end()) {
        return this->end();
      }

      node_type* node = iter._current;
      assert(node == this->_root);

      if (this->_root->left == nullptr) {
        assert(this->_root == this->_min);

        if (this->_root->right == nullptr) {
          assert(this->_root == this->_max);

          this->_root = nullptr;
          this->_min  = nullptr;
          this->_max  = nullptr;
        } else {
          this->_root         = this->_root->right;
          this->_root->parent = nullptr;
          this->_min          = this->_root;
          while (this->_min->left != nullptr) {
            this->_min = this->_min->left;
          }
          this->_splay(this->_min);
        }
      } else if (this->_root->right != nullptr) {
        this->_root         = this->_root->left;
        this->_root->parent = nullptr;
        this->_max          = this->_root;
        while (this->_max->right != nullptr) {
          this->_max = this->_max->right;
        }
        this->_splay(this->_max);
      } else {
        this->_root->left->parent = nullptr;
        node_type* next_root      = this->_root->left;
        while (next_root->right != nullptr) {
          next_root = next_root->right;
        }
        this->_splay(next_root);
        next_root->right         = node->right;
        next_root->right->parent = next_root;
        this->_root->parent      = nullptr;
      }

      iterator result(node->right);
      node->destroy(this->_allocator);

      --this->_size;

      return result;
    }

    template<typename Iterator, typename U>
    Iterator _find(U&& val) const {
      Iterator iter = this->_lower_bound<Iterator>(val);

      if (this->_root == nullptr || _compare(val, this->_root->value) || _compare(this->_root->value, val)) {
        return this->_end<Iterator>();
      }

      return Iterator(_root);
    }

    template<typename Iterator, typename U>
    Iterator _lower_bound(U&& val) const {
      node_type* node  = nullptr;
      node_type* left  = _root;
      node_type* right = nullptr;

      while (left != nullptr) {
        node = left;
        if (_compare(left->value, val)) {
          left = left->right;
        } else {
          right = left;
          left  = left->left;
        }
      }

      if (right == nullptr && node != nullptr) {
        this->_splay(node);
      }

      if (right != nullptr) {
        this->_splay(right);
      }

      return Iterator(right);
    }

    template<typename Iterator, typename U>
    Iterator _upper_bound(U&& val) const {
      node_type* node  = nullptr;
      node_type* left  = _root;
      node_type* right = nullptr;

      while (left != nullptr) {
        node = left;
        if (_compare(val, left->value)) {
          right = left;
          left  = left->left;
        } else {
          left = left->right;
        }
      }

      if (right == nullptr && node != nullptr) {
        this->_splay(node);
      }

      if (right != nullptr) {
        this->_splay(right);
      }

      return Iterator(right);
    }
  };

  template<typename T, typename Compare, typename Allocator>
  using __binary_tree = __splay_tree<T, Compare, Allocator>;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_BINARY_TREE_H_
