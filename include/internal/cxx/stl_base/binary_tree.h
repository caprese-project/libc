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
    static __constexpr_cxx_std_14 __splay_tree_node* create(Allocator& allocator, __splay_tree_node* left, __splay_tree_node* right, __splay_tree_node* parent, Args&&... args) {
      __splay_tree_node* node = allocator_traits<Allocator>::allocate(allocator, 1);
      allocator_traits<Allocator>::construct(allocator, node, T(std::forward<Args>(args)...), left, right, parent);
      return node;
    }

    __constexpr_cxx_std_14 void set_left(__splay_tree_node* child) {
      if (child != nullptr) {
        left          = child;
        child->parent = this;
      } else {
        left = nullptr;
      }
    }

    __constexpr_cxx_std_14 void set_right(__splay_tree_node* child) {
      if (child != nullptr) {
        right         = child;
        child->parent = this;
      } else {
        right = nullptr;
      }
    }

    __constexpr_cxx_std_14 __splay_tree_node* rotate_left() {
      __splay_tree_node* right = this->right;
      this->right              = right->left;
      right->left              = this;

      right->parent = this->parent;
      this->parent  = right;
      if (this->right != nullptr) {
        this->right->parent = this;
      }

      return right;
    }

    __constexpr_cxx_std_14 __splay_tree_node* rotate_right() {
      __splay_tree_node* left = this->left;
      this->left              = left->right;
      left->right             = this;

      left->parent = this->parent;
      this->parent = left;
      if (this->left != nullptr) {
        this->left->parent = this;
      }

      return left;
    }

    template<typename Allocator>
    __constexpr_cxx_std_14 void clear(Allocator& allocator) {
      if (left != nullptr) {
        left->clear(allocator);
        allocator_traits<Allocator>::destroy(allocator, left);
        allocator_traits<Allocator>::deallocate(allocator, left, 1);
      }

      if (right != nullptr) {
        right->clear(allocator);
        allocator_traits<Allocator>::destroy(allocator, right);
        allocator_traits<Allocator>::deallocate(allocator, right, 1);
      }

      allocator_traits<Allocator>::destroy(allocator, this);
      allocator_traits<Allocator>::deallocate(allocator, this, 1);
    }

    template<typename U, typename Compare, typename Allocator>
    __constexpr_cxx_std_14 __splay_tree_node* erase(U&& val, const Compare& compare, Allocator& allocator) {
      __splay_tree_node* target = this;

      while (target != nullptr) {
        if (compare(val, target->value)) {
          target = target->left;
        } else if (compare(target->value, val)) {
          target = target->right;
        } else {
          break;
        }
      }

      if (target == nullptr) {
        return nullptr;
      }

      __splay_tree_node* post_target;

      if (target->left == nullptr) {
        post_target = target->right;
      } else if (target->left->right == nullptr) {
        post_target = target->left;
        post_target->set_right(target->right);
      } else {
        __splay_tree_node* node = target->left;
        while (node->right->right != nullptr) {
          node = node->right;
        }

        post_target = node->right;
        node->set_right(node->right->left);
        post_target->set_left(target->left);
        post_target->set_right(target->right);
      }

      if (target->parent != nullptr) {
        if (target->parent->left == target) {
          target->parent->set_left(post_target);
        } else {
          assert(target->parent->right == target);
          target->parent->set_right(post_target);
        }
      }

      allocator_traits<Allocator>::destroy(allocator, target);
      allocator_traits<Allocator>::deallocate(allocator, target, 1);

      return post_target;
    }

    template<typename U, typename Compare, typename Allocator>
    __constexpr_cxx_std_14 void insert(U&& val, const Compare& compare, Allocator& allocator) {
      __splay_tree_node* target = this;

      while (target != nullptr) {
        if (compare(val, target->value)) {
          if (target->left == nullptr) {
            target->left = create(allocator, nullptr, nullptr, target, std::forward<U>(val));
            break;
          } else {
            target = target->left;
          }
        } else if (compare(target->value, val)) {
          if (target->right == nullptr) {
            target->right = create(allocator, nullptr, nullptr, target, std::forward<U>(val));
            break;
          } else {
            target = target->right;
          }
        } else {
          break;
        }
      }
    }

    template<typename U, typename Compare>
    __constexpr_cxx_std_14 __splay_tree_node* splay(U&& val, const Compare& compare) {
      __splay_tree_node* target = this;

      if (compare(val, target->value)) {
        if (target->left == nullptr) {
          return target;
        }

        if (compare(val, target->left->value)) {
          if (target->left->left != nullptr) {
            target->left->left = target->left->left->splay(std::forward<U>(val), compare);
          }
          target = target->rotate_right();
        } else if (compare(target->left->value, val)) {
          if (target->left->right != nullptr) {
            target->left->right = target->left->right->splay(std::forward<U>(val), compare);
            if (target->left->right != nullptr) {
              target->left = target->left->rotate_left();
            }
          }
        }

        if (target->left == nullptr) {
          return target;
        } else {
          return target->rotate_right();
        }
      } else if (compare(target->value, val)) {
        if (target->right == nullptr) {
          return target;
        }

        if (compare(val, target->right->value)) {
          if (target->right->left != nullptr) {
            target->right->left = target->right->left->splay(std::forward<U>(val), compare);
            if (target->right->left != nullptr) {
              target->right = target->right->rotate_right();
            }
          }
        } else if (compare(target->right->value, val)) {
          if (target->right->right != nullptr) {
            target->right->right = target->right->right->splay(std::forward<U>(val), compare);
          }
          target = target->rotate_left();
        }

        if (target->right == nullptr) {
          return target;
        } else {
          return target->rotate_left();
        }
      } else {
        return target;
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

  private:
    __node_type* _current;

  public:
    __constexpr_cxx_std_11 __splay_tree_node_iterator(): _current(nullptr) { }

    __constexpr_cxx_std_11 explicit __splay_tree_node_iterator(__node_type* current): _current(current) { }

    __constexpr_cxx_std_11 __splay_tree_node_iterator(const __splay_tree_node_iterator& other): _current(other._current) { }

    ~__splay_tree_node_iterator() = default;

    __constexpr_cxx_std_14 __splay_tree_node_iterator& operator=(const __splay_tree_node_iterator& other) {
      _current = other._current;
    }

    __constexpr_cxx_std_11 reference operator*() const {
      return _current->value;
    }

    __constexpr_cxx_std_11 pointer operator->() const {
      return __addressof(_current->value);
    }

    __constexpr_cxx_std_14 __splay_tree_node_iterator& operator++() {
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

    __constexpr_cxx_std_14 __splay_tree_node_iterator operator++([[maybe_unused]] int) {
      __splay_tree_node_iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    __constexpr_cxx_std_14 __splay_tree_node_iterator& operator--() {
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

    __constexpr_cxx_std_14 __splay_tree_node_iterator operator--([[maybe_unused]] int) {
      __splay_tree_node_iterator tmp = *this;
      --(*this);
      return tmp;
    }

    friend __constexpr_cxx_std_11 bool operator==(const __splay_tree_node_iterator& lhs, const __splay_tree_node_iterator& rhs) {
      return lhs._current == rhs._current;
    }

    friend __constexpr_cxx_std_11 bool operator!=(const __splay_tree_node_iterator& lhs, const __splay_tree_node_iterator& rhs) {
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
    __size_t            _size;

  public:
    __constexpr_cxx_std_11 __splay_tree(const Compare& compare, const Allocator&): _compare(compare), _allocator(), _root(nullptr), _size(0) { }

    __constexpr_cxx_std_14 __splay_tree(const __splay_tree& other): _compare(other._compare), _allocator(other._allocator), _root(nullptr), _size(0) {
      for (auto&& elem : other) {
        insert(elem);
      }
    }

    __constexpr_cxx_std_14 __splay_tree(__splay_tree&& other): _compare(std::move(other._compare)), _allocator(std::move(other._allocator)), _root(other._root), _size(other._size) {
      other._root = nullptr;
      other._size = 0;
    }

    __constexpr_cxx_std_20 ~__splay_tree() {
      clear();
    }

    __constexpr_cxx_std_14 __splay_tree& operator=(const __splay_tree& other) {
      if (this != &other) {
        clear();

        for (auto&& elem : other) {
          insert(elem);
        }
      }

      return *this;
    }

    __constexpr_cxx_std_14 __splay_tree& operator=(__splay_tree&& other) {
      if (this != &other) {
        clear();

        _compare   = std::move(other._compare);
        _allocator = std::move(other._allocator);
        _root      = other._root;
        _size      = other._size;

        other._root = nullptr;
        other._size = 0;
      }

      return *this;
    }

    __constexpr_cxx_std_11 __size_t size() const {
      return _size;
    }

    __constexpr_cxx_std_11 __size_t max_size() const {
      return allocator_traits<node_allocator_type>::max_size(_allocator);
    }

    __constexpr_cxx_std_14 iterator begin() {
      return _begin<iterator>();
    }

    __constexpr_cxx_std_14 const_iterator begin() const {
      return _begin<const_iterator>();
    }

    __constexpr_cxx_std_14 iterator end() {
      return _end<iterator>();
    }

    __constexpr_cxx_std_14 const_iterator end() const {
      return _end<const_iterator>();
    }

    __constexpr_cxx_std_14 void clear() {
      if (_root != nullptr) {
        _root->clear(_allocator);
      }

      _size = 0;
      _root = nullptr;
    }

    template<typename U>
    __constexpr_cxx_std_14 iterator erase(U&& val) {
      if (find(val) == end()) {
        return end();
      }

      _root = _root->erase(std::forward<U>(val), _compare, _allocator);
      --_size;

      return iterator(_root);
    }

    __constexpr_cxx_std_14 pair<iterator, bool> insert(const T& val) {
      return _insert(val);
    }

    __constexpr_cxx_std_14 pair<iterator, bool> insert(T&& val) {
      return _insert(std::move(val));
    }

    template<typename... Args>
    __constexpr_cxx_std_14 pair<iterator, bool> emplace(Args&&... args) {
      if (_root != nullptr) {
        return _insert(T(std::forward<Args>(args)...));
      }

      _root = node_type::create(_allocator, nullptr, nullptr, nullptr, std::forward<Args>(args)...);
      ++_size;

      return pair<iterator, bool>(iterator(_root), true);
    }

    template<typename U>
    __constexpr_cxx_std_14 iterator find(U&& val) {
      return _find<iterator>(forward<U>(val));
    }

    template<typename U>
    __constexpr_cxx_std_14 const_iterator find(U&& val) const {
      return _find<const_iterator>(forward<U>(val));
    }

    template<typename U>
    __constexpr_cxx_std_14 iterator lower_bound(U&& val) {
      return _lower_bound<iterator>(forward<U>(val));
    }

    template<typename U>
    __constexpr_cxx_std_14 const_iterator lower_bound(U&& val) const {
      return _lower_bound<const_iterator>(forward<U>(val));
    }

    template<typename U>
    __constexpr_cxx_std_14 iterator upper_bound(U&& val) {
      return _upper_bound<iterator>(forward<U>(val));
    }

    template<typename U>
    __constexpr_cxx_std_14 const_iterator upper_bound(U&& val) const {
      return _upper_bound<const_iterator>(forward<U>(val));
    }

  private:
    template<typename Iterator>
    __constexpr_cxx_std_14 Iterator _begin() const {
      if (_root == nullptr) {
        return _end<Iterator>();
      }

      node_type* current = _root;
      while (current->left != nullptr) {
        current = current->left;
      }

      return Iterator(current);
    }

    template<typename Iterator>
    __constexpr_cxx_std_14 Iterator _end() const {
      return Iterator(nullptr);
    }

    template<typename U>
    __constexpr_cxx_std_14 pair<iterator, bool> _insert(U&& val) {
      iterator iter = find(val);
      if (iter != end()) {
        return pair<iterator, bool>(iter, false);
      }

      if (_root == nullptr) {
        _root = node_type::create(_allocator, nullptr, nullptr, nullptr, std::forward<U>(val));
      } else {
        _root->insert(std::forward<U>(val), _compare, _allocator);
      }

      ++_size;

      return pair<iterator, bool>(iterator(_root), true);
    }

    template<typename Iterator, typename U>
    __constexpr_cxx_std_14 Iterator _find(U&& val) const {
      if (_root == nullptr) {
        return _end<Iterator>();
      }

      _root = _root->splay(val, _compare);
      if (_compare(val, _root->value) || _compare(_root->value, val)) {
        return _end<Iterator>();
      }

      return Iterator(_root);
    }

    template<typename Iterator, typename U>
    __constexpr_cxx_std_14 Iterator _lower_bound(U&& val) const {
      if (_root == nullptr) {
        return _end<Iterator>();
      }

      _root = _root->splay(val, _compare);
      if (_compare(val, _root->value)) {
        return Iterator(_root);
      }

      node_type* target = _root->right;
      if (target == nullptr) {
        return _end<Iterator>();
      }

      while (target->left != nullptr) {
        target = target->left;
      }

      return Iterator(target);
    }

    template<typename Iterator, typename U>
    __constexpr_cxx_std_14 Iterator _upper_bound(U&& val) const {
      if (_root == nullptr) {
        return _end<Iterator>();
      }

      _root = _root->splay(val, _compare);
      if (!_compare(_root->value, val)) {
        return Iterator(_root);
      }

      node_type* target = _root->right;
      if (target == nullptr) {
        return _end<Iterator>();
      }

      while (target->left != nullptr) {
        target = target->left;
      }

      return Iterator(target);
    }
  };

  template<typename T, typename Compare, typename Allocator>
  using __binary_tree = __splay_tree<T, Compare, Allocator>;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_BINARY_TREE_H_
