#ifndef CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_BINARY_TREE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_BINARY_TREE_H_

#include <cassert>
#include <internal/attribute.h>
#include <internal/cxx/algorithm/minmax.h>
#include <internal/cxx/iterator/tags.h>
#include <internal/cxx/memory/addressof.h>
#include <internal/cxx/memory/allocator_traits.h>
#include <internal/cxx/stddef.h>
#include <internal/cxx/utility/fwd.h>
#include <internal/cxx/utility/pair.h>

namespace std {
  template<typename T>
  struct __avl_tree_node {
    T                value;
    int              height;
    __avl_tree_node* parent;
    __avl_tree_node* left;
    __avl_tree_node* right;

#ifndef __CXX_STD_20__

    __avl_tree_node(const T& value, int height, __avl_tree_node* parent, __avl_tree_node* left, __avl_tree_node* right): value(value), height(height), parent(parent), left(left), right(right) { }

    __avl_tree_node(T&& value, int height, __avl_tree_node* parent, __avl_tree_node* left, __avl_tree_node* right)
        : value(std::move(value)),
          height(height),
          parent(parent),
          left(left),
          right(right) { }

#endif // __CXX_STD_20__

    template<typename Allocator, typename... Args>
    static __avl_tree_node* create(Allocator& allocator, Args&&... args) {
      __avl_tree_node* node = allocator_traits<Allocator>::allocate(allocator, 1);
      allocator_traits<Allocator>::construct(allocator, node, T(std::forward<Args>(args)...), 0, nullptr, nullptr, nullptr);
      return node;
    }

    template<typename Allocator>
    void destroy(Allocator& allocator) {
      assert(this->left == nullptr);
      assert(this->right == nullptr);

      if (this->parent != nullptr) {
        if (this->parent->left == this) {
          this->parent->left = nullptr;
        } else {
          assert(this->parent->right == this);
          this->parent->right = nullptr;
        }
        this->parent = nullptr;
      }

      allocator_traits<Allocator>::destroy(allocator, this);
      allocator_traits<Allocator>::deallocate(allocator, this, 1);
    }

    int bias() const {
      return (left ? left->height : 0) - (right ? right->height : 0);
    }

    void update() {
      height = std::max(left ? left->height : 0, right ? right->height : 0) + 1;
    }

    void set_left(__avl_tree_node* node) {
      if (node != nullptr && node->parent != nullptr) {
        if (node->parent->left == node) {
          node->parent->left = nullptr;
        } else {
          assert(node->parent->right == node);
          node->parent->right = nullptr;
        }
      }

      if (this->left != nullptr) {
        this->left->parent = nullptr;
      }

      if (node != nullptr) {
        node->parent = this;
      }

      this->left = node;
    }

    void set_right(__avl_tree_node* node) {
      if (node != nullptr && node->parent != nullptr) {
        if (node->parent->left == node) {
          node->parent->left = nullptr;
        } else {
          assert(node->parent->right == node);
          node->parent->right = nullptr;
        }
      }

      if (this->right != nullptr) {
        this->right->parent = nullptr;
      }

      if (node != nullptr) {
        node->parent = this;
      }

      this->right = node;
    }

    __avl_tree_node* get_max_node() {
      __avl_tree_node* node = this;
      while (node->right != nullptr) {
        node = node->right;
      }
      return node;
    }

    __avl_tree_node* get_min_node() {
      __avl_tree_node* node = this;
      while (node->left != nullptr) {
        node = node->left;
      }
      return node;
    }

    /**
     * T:   this
     * T.P: this->parent
     * T.L: this->left
     * T.R: this->right
     * O:   other
     * O.L: other->left
     * O.R: other->right
     *
     *     +-----+            +-----+
     *     | T.P |            | T.P |
     *     +-----+            +-----+
     *        |                  |
     *     +-----+            +-----+
     *     |  T  |      =>    |  O  |
     *     +-----+            +-----+
     *      |   |              |   |
     * +-----+ +-----+    +-----+ +-----+
     * | T.L | | T.R |    | O.L | | O.R |
     * +-----+ +-----+    |-----+ +-----+
     */
    void replace(__avl_tree_node* other) {
      if (this->parent != nullptr) {
        if (this->parent->left == this) {
          this->parent->left = other;
        } else {
          assert(this->parent->right == this);
          this->parent->right = other;
        }
      }

      if (other != nullptr) {
        other->parent = this->parent;
      }

      this->parent = nullptr;
    }

    /**
     * T:   this
     * T.P: this->parent
     * T.L: this->left
     * T.R: this->right
     * R.L: this->right->left
     * R.R: this->right->right
     *
     *     +-----+                    +-----+
     *     | T.P |                    | T.P |
     *     +-----+                    +-----+
     *        |                          |
     *     +-----+                    +-----+
     *     |  T  |                    | T.R |
     *     +-----+                    +-----+
     *      |   |          =>          |   |
     * +-----+ +-----+            +-----+ +-----+
     * | T.L | | T.R |            |  T  | | R.R |
     * +-----+ +-----+            +-----+ +-----+
     *          |   |              |   |
     *     +-----+ +-----+    +-----+ +-----+
     *     | R.L | | R.R |    | T.L | | R.L |
     *     +-----+ +-----+    +-----+ +-----+
     */
    __avl_tree_node* rotate_left() {
      assert(this->right != nullptr);

      __avl_tree_node* node = this->right;
      this->replace(node);
      this->set_right(node->left);
      node->set_left(this);
      node->left->update();
      node->update();
      return node;
    }

    /**
     * T:   this
     * T.P: this->parent
     * T.L: this->left
     * T.R: this->right
     * L.L: this->left->left
     * L.R: this->left->right
     *
     *         +-----+                    +-----+
     *         | T.P |                    | T.P |
     *         +-----+                    +-----+
     *            |                          |
     *         +-----+                    +-----+
     *         |  T  |                    | T.L |
     *         +-----+                    +-----+
     *          |   |          =>          |   |
     *     +-----+ +-----+            +-----+ +-----+
     *     | T.L | | T.R |            | L.L | |  T  |
     *     +-----+ +-----+            +-----+ +-----+
     *      |   |                              |   |
     * +-----+ +-----+                    +-----+ +-----+
     * | L.L | | L.R |                    | L.R | | T.R |
     * +-----+ +-----+                    +-----+ +-----+
     */
    __avl_tree_node* rotate_right() {
      assert(this->left != nullptr);

      __avl_tree_node* node = this->left;
      this->replace(node);
      this->set_left(node->right);
      node->set_right(this);
      node->right->update();
      node->update();
      return node;
    }

    __avl_tree_node* rotate_left_right() {
      this->left->rotate_left();
      return this->rotate_right();
    }

    __avl_tree_node* rotate_right_left() {
      this->right->rotate_right();
      return this->rotate_left();
    }

    __avl_tree_node* balance_i() {
      __avl_tree_node* node = this;

      while (node->parent != nullptr) {
        __avl_tree_node* target     = node->parent;
        int              old_height = target->height;

        if (target->left == node) {
          if (target->bias() == 2) {
            if (target->left->bias() >= 0) {
              target = target->rotate_right();
            } else {
              target = target->rotate_left_right();
            }
          } else {
            target->update();
          }
        } else {
          if (target->bias() == -2) {
            if (target->right->bias() <= 0) {
              target = target->rotate_left();
            } else {
              target = target->rotate_right_left();
            }
          } else {
            target->update();
          }
        }

        if (target->height == old_height) {
          break;
        }

        node = target;
      }

      return node;
    }

    __avl_tree_node* balance_d() {
      __avl_tree_node* node = this;

      while (node->parent != nullptr) {
        __avl_tree_node* target     = node->parent;
        int              old_height = target->height;

        if (target->left != node) {
          if (target->bias() == 2) {
            if (target->left->bias() >= 0) {
              target = target->rotate_right();
            } else {
              target = target->rotate_left_right();
            }
          } else {
            target->update();
          }
        } else {
          if (target->bias() == -2) {
            if (target->right->bias() <= 0) {
              target = target->rotate_left();
            } else {
              target = target->rotate_right_left();
            }
          } else {
            target->update();
          }
        }

        if (target->height == old_height) {
          break;
        }

        node = target;
      }

      return node;
    }
  };

  template<typename T>
  class __avl_tree_iterator {
  private:
    using node_type = __avl_tree_node<typename std::__remove_const<T>::type>;

  public:
    using difference_type   = __ptrdiff_t;
    using value_type        = T;
    using pointer           = value_type*;
    using reference         = value_type&;
    using iterator_category = bidirectional_iterator_tag;

    template<typename, typename Compare, typename Allocator>
    friend class __avl_tree;

  private:
    node_type* _current;

  public:
    explicit __avl_tree_iterator(node_type* current = nullptr): _current(current) { }

    __avl_tree_iterator(const __avl_tree_iterator& other): _current(other._current) { }

    __avl_tree_iterator(__avl_tree_iterator&& other): _current(other._current) {
      other._current = nullptr;
    }

    ~__avl_tree_iterator() = default;

    __avl_tree_iterator& operator=(const __avl_tree_iterator& other) & {
      if (this != &other) {
        this->_current = other._current;
      }

      return *this;
    }

    __avl_tree_iterator& operator=(__avl_tree_iterator&& other) & {
      if (this != &other) {
        this->_current = other._current;
        other._current = nullptr;
      }

      return *this;
    }

    reference operator*() const {
      return _current->value;
    }

    pointer operator->() const {
      return std::__addressof(_current->value);
    }

    __avl_tree_iterator& operator++() {
      assert(_current != nullptr);

      if (_current->right != nullptr) {
        _current = _current->right;
        while (_current->left != nullptr) {
          _current = _current->left;
        }
      } else {
        node_type* node = _current;
        while (node->parent != nullptr && node->parent->right == node) {
          node = node->parent;
        }
        _current = node->parent;
      }

      return *this;
    }

    __avl_tree_iterator operator++(int) {
      __avl_tree_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    __avl_tree_iterator& operator--() {
      assert(_current != nullptr);

      if (_current->left != nullptr) {
        _current = _current->left;
        while (_current->right != nullptr) {
          _current = _current->right;
        }
      } else {
        node_type* node = _current;
        while (node->parent != nullptr && node->parent->left == node) {
          node = node->parent;
        }
        _current = node->parent;
      }

      return *this;
    }

    __avl_tree_iterator operator--(int) {
      __avl_tree_iterator tmp(*this);
      --(*this);
      return tmp;
    }

    friend bool operator==(const __avl_tree_iterator& lhs, const __avl_tree_iterator& rhs) {
      return lhs._current == rhs._current;
    }

    friend bool operator!=(const __avl_tree_iterator& lhs, const __avl_tree_iterator& rhs) {
      return lhs._current != rhs._current;
    }
  };

  template<typename T, typename Compare, typename Allocator>
  class __avl_tree {
  public:
    using node_type      = __avl_tree_node<T>;
    using iterator       = __avl_tree_iterator<T>;
    using const_iterator = __avl_tree_iterator<const T>;

  private:
    using compare_type   = Compare;
    using allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<node_type>;

  private:
    compare_type   _compare;
    allocator_type _allocator;
    node_type*     _root;
    __size_t       _size;

  public:
    __avl_tree(const compare_type& compare, const Allocator&): _compare(compare), _allocator(), _root(nullptr), _size(0) { }

    __avl_tree(const __avl_tree& other): _compare(other._compare), _allocator(other._allocator), _root(nullptr), _size(0) {
      for (auto&& elem : other) {
        this->insert(elem);
      }
    }

    __avl_tree(__avl_tree&& other): _compare(std::move(other._compare)), _allocator(std::move(other._allocator)), _root(other._root), _size(other._size) {
      other._root = nullptr;
      other._size = 0;
    }

    ~__avl_tree() {
      this->clear();
    }

    __avl_tree& operator=(const __avl_tree& other) & {
      if (this != &other) {
        this->clear();

        for (auto&& elem : other) {
          this->insert(elem);
        }
      }

      return *this;
    }

    __avl_tree& operator=(__avl_tree&& other) & {
      if (this != &other) {
        this->clear();

        this->_compare   = std::move(other._compare);
        this->_allocator = std::move(other._allocator);
        this->_root      = other._root;
        this->_size      = other._size;

        other._root = nullptr;
        other._size = 0;
      }

      return *this;
    }

    __size_t size() const {
      return _size;
    }

    __size_t max_size() const {
      return std::allocator_traits<allocator_type>::max_size(this->_allocator);
    }

    iterator begin() {
      __if_unlikely (this->_root == nullptr) {
        return this->end();
      }
      return iterator(this->_root->get_min_node());
    }

    const_iterator begin() const {
      __if_unlikely (this->_root == nullptr) {
        return this->end();
      }
      return const_iterator(this->_root->get_min_node());
    }

    iterator end() {
      return iterator(nullptr);
    }

    const_iterator end() const {
      return const_iterator(nullptr);
    }

    void clear() {
      node_type* node = this->_root;

      while (node != nullptr) {
        if (node->left != nullptr) {
          node = node->left;
        } else if (node->right != nullptr) {
          node = node->right;
        } else {
          node_type* parent = node->parent;
          node->destroy(this->_allocator);
          node = parent;
        }
      }

      this->_root = nullptr;
      this->_size = 0;
    }

    template<typename U>
    iterator erase(U&& value) {
      __if_unlikely (this->_root == nullptr) {
        return this->end();
      }

      iterator iter = this->lower_bound(value);
      // !(*iter < value) && value < *iter -> value != *iter
      if (iter == this->end() || this->_compare(value, *iter)) {
        return iter;
      }

      node_type* next;
      if (iter._current->left != nullptr) {
        node_type* left  = iter._current->left;
        node_type* right = iter._current->right;
        next             = left->get_max_node();
        next->replace(next->left);
        next->set_left(left);
        next->set_right(right);
      } else {
        next = iter._current->right;
      }

      iter._current->replace(next);
      iter._current->destroy(this->_allocator);

      this->_root = next->balance_d();

      --this->_size;

      return iterator(next);
    }

    template<typename U>
    std::pair<iterator, bool> insert(U&& value) {
      __if_unlikely (this->_root == nullptr) {
        this->_root = node_type::create(this->_allocator, std::forward<U>(value));
        this->_size = 1;
        return std::pair<iterator, bool>(iterator(this->_root), true);
      }

      iterator iter = this->lower_bound(value);
      // !(*iter < value) && !(value < *iter) -> value == *iter
      if (iter != this->end() && !this->_compare(value, *iter)) {
        return std::pair<iterator, bool>(iter, false);
      }

      node_type* node = node_type::create(this->_allocator, std::forward<U>(value));

      if (iter == this->end()) {
        this->_root->get_max_node()->set_right(node);
      } else if (iter._current->left == nullptr) {
        iter._current->set_left(node);
      } else {
        node_type* pos = iter._current->left;
        while (pos->right != nullptr) {
          pos = pos->right;
        }
        pos->set_right(node);
      }

      this->_root = node->balance_i();

      ++this->_size;

      return std::pair<iterator, bool>(iterator(node), true);
    }

    template<typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args) {
      if (this->_root != nullptr) {
        return this->insert(T(std::forward<Args>(args)...));
      }

      this->_root = node_type::create(this->_allocator, std::forward<Args>(args)...);
      this->_size = 1;

      return std::pair<iterator, bool>(iterator(this->_root), true);
    }

    template<typename U>
    iterator find(U&& value) {
      iterator iter = this->lower_bound(value);
      if (iter != this->end() && !this->_compare(value, *iter)) {
        return iter;
      }
      return this->end();
    }

    template<typename U>
    const_iterator find(U&& value) const {
      const_iterator iter = this->lower_bound(value);
      if (iter != this->end() && !this->_compare(value, *iter)) {
        return iter;
      }
      return this->end();
    }

    template<typename U>
    iterator lower_bound(U&& value) {
      node_type* node = this->_root;
      while (node != nullptr) {
        if (this->_compare(node->value, value)) {
          node = node->right;
        } else if (this->_compare(value, node->value)) {
          if (node->left != nullptr && this->_compare(value, node->left->value)) {
            node = node->left;
          } else {
            break;
          }
        } else {
          break;
        }
      }
      return iterator(node);
    }

    template<typename U>
    const_iterator lower_bound(U&& value) const {
      node_type* node = this->_root;
      while (node != nullptr) {
        if (this->_compare(node->value, value)) {
          node = node->right;
        } else if (this->_compare(value, node->value)) {
          if (node->left != nullptr && this->_compare(value, node->left->value)) {
            node = node->left;
          } else {
            break;
          }
        } else {
          break;
        }
      }
      return const_iterator(node);
    }

    template<typename U>
    iterator upper_bound(U&& value) {
      iterator iter = this->lower_bound(value);
      if (iter != this->end() && !this->_compare(value, *iter)) {
        ++iter;
      }
      return iter;
    }

    template<typename U>
    const_iterator upper_bound(U&& value) const {
      iterator iter = this->lower_bound(value);
      if (iter != this->end() && !this->_compare(value, *iter)) {
        ++iter;
      }
      return iter;
    }
  };

  template<typename T, typename Compare, typename Allocator>
  using __binary_tree = __avl_tree<T, Compare, Allocator>;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_BINARY_TREE_H_
