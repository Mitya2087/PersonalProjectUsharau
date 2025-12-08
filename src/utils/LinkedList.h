#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstddef>
#include <stdexcept>

/**
 * @brief Templated doubly-linked list data structure
 * @tparam T Type of elements stored in the list
 *
 * Custom implementation of a doubly-linked list with iterator support.
 * Demonstrates manual memory management and template programming.
 */
template <typename T> class LinkedList {
private:
  /**
   * @brief Node structure for doubly-linked list
   */
  struct Node {
    T data;
    Node *next;
    Node *prev;

    Node(const T &value) : data(value), next(nullptr), prev(nullptr) {}
  };

  Node *head_;
  Node *tail_;
  size_t size_;

public:
  /**
   * @brief Construct empty linked list
   */
  LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

  /**
   * @brief Destructor - frees all nodes
   */
  ~LinkedList() { clear(); }

  /**
   * @brief Copy constructor
   */
  LinkedList(const LinkedList &other)
      : head_(nullptr), tail_(nullptr), size_(0) {
    Node *current = other.head_;
    while (current) {
      pushBack(current->data);
      current = current->next;
    }
  }

  /**
   * @brief Copy assignment operator
   */
  LinkedList &operator=(const LinkedList &other) {
    if (this != &other) {
      clear();
      Node *current = other.head_;
      while (current) {
        pushBack(current->data);
        current = current->next;
      }
    }
    return *this;
  }

  /**
   * @brief Add element to the end
   * @param value Element to add
   */
  void pushBack(const T &value) {
    Node *newNode = new Node(value);
    if (!tail_) {
      head_ = tail_ = newNode;
    } else {
      tail_->next = newNode;
      newNode->prev = tail_;
      tail_ = newNode;
    }
    ++size_;
  }

  /**
   * @brief Add element to the front
   * @param value Element to add
   */
  void pushFront(const T &value) {
    Node *newNode = new Node(value);
    if (!head_) {
      head_ = tail_ = newNode;
    } else {
      newNode->next = head_;
      head_->prev = newNode;
      head_ = newNode;
    }
    ++size_;
  }

  /**
   * @brief Insert element at specific index
   * @param index Position to insert at
   * @param value Element to insert
   * @throws std::out_of_range if index > size
   */
  void insert(size_t index, const T &value) {
    if (index > size_) {
      throw std::out_of_range("Index out of range");
    }

    if (index == 0) {
      pushFront(value);
      return;
    }
    if (index == size_) {
      pushBack(value);
      return;
    }

    Node *current = head_;
    for (size_t i = 0; i < index - 1; ++i) {
      current = current->next;
    }

    Node *newNode = new Node(value);
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
    ++size_;
  }

  /**
   * @brief Remove element at specific index
   * @param index Position to remove from
   * @throws std::out_of_range if index >= size
   */
  void remove(size_t index) {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }

    Node *toDelete = head_;
    for (size_t i = 0; i < index; ++i) {
      toDelete = toDelete->next;
    }

    if (toDelete->prev) {
      toDelete->prev->next = toDelete->next;
    } else {
      head_ = toDelete->next;
    }

    if (toDelete->next) {
      toDelete->next->prev = toDelete->prev;
    } else {
      tail_ = toDelete->prev;
    }

    delete toDelete;
    --size_;
  }

  /**
   * @brief Access element at index
   * @param index Position to access
   * @return Reference to element
   * @throws std::out_of_range if index >= size
   */
  T &at(size_t index) {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }

    Node *current = head_;
    for (size_t i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }

  /**
   * @brief Access element at index (const version)
   */
  const T &at(size_t index) const {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }

    Node *current = head_;
    for (size_t i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }

  /**
   * @brief Get number of elements
   * @return Size of list
   */
  size_t size() const { return size_; }

  /**
   * @brief Check if list is empty
   * @return true if empty
   */
  bool empty() const { return size_ == 0; }

  /**
   * @brief Remove all elements
   */
  void clear() {
    while (head_) {
      Node *next = head_->next;
      delete head_;
      head_ = next;
    }
    tail_ = nullptr;
    size_ = 0;
  }

  /**
   * @brief Iterator for LinkedList
   */
  class Iterator {
  private:
    Node *current_;

  public:
    Iterator(Node *node) : current_(node) {}

    T &operator*() { return current_->data; }

    Iterator &operator++() {
      if (current_) {
        current_ = current_->next;
      }
      return *this;
    }

    bool operator!=(const Iterator &other) const {
      return current_ != other.current_;
    }

    bool operator==(const Iterator &other) const {
      return current_ == other.current_;
    }
  };

  /**
   * @brief Get iterator to beginning
   */
  Iterator begin() { return Iterator(head_); }

  /**
   * @brief Get iterator to end
   */
  Iterator end() { return Iterator(nullptr); }
};

#endif // LINKEDLIST_H
