#ifndef _HEAP_H_
#define _HEAP_H_
#include <stdexcept>

template <typename T>
class Heap {
private:
  static constexpr size_t DEFAULT_CAP = 32;
  T* arr;
  size_t m_size;
  size_t m_capacity;
  bool is_max_heap;

public:
  Heap(bool is_max_heap = true) : arr{new T[DEFAULT_CAP]}, m_size{0}, m_capacity{DEFAULT_CAP}, is_max_heap{is_max_heap} {}
  Heap(T inp[], size_t length, bool is_max_heap = true) : arr{nullptr}, m_size{length}, m_capacity{DEFAULT_CAP}, is_max_heap{is_max_heap} {
    heapify(inp, length);
  }
  ~Heap() { delete[] arr; }

  void heapify(T inp[], size_t length, bool is_max_heap = true) {
    this->is_max_heap = is_max_heap;
    if (length > m_capacity) {
      while (length > m_capacity)
        m_capacity *= 2;
      delete[] arr;
      arr = new T[m_capacity];
    }

    for (size_t i = 0; i < length; i++)
      arr[i] = inp[i];

    m_size = length;
    size_t cur = getParent(m_size - 1);

    while (cur > 0)
      siftDown(cur--);
    siftDown(cur);
  }

  void push(T item) {
    if (m_size == m_capacity) {
      m_capacity *= 2;
      T *tmp = new T[m_capacity];
      for (size_t i = 0; i < m_size; i++)
        tmp[i] = arr[i];
      delete[] arr;
      arr = tmp;
    }
    arr[m_size] = item;
    siftUp(m_size++);
  }

  void pop() {
    if (m_size == 0)
      throw std::out_of_range("Empty heap");
    arr[0] = arr[--m_size];
    siftDown(0);
  }

  T top() const {
    if (m_size == 0)
      throw std::out_of_range("Empty heap");
    return arr[0];
  }

  void reserve(size_t cap) {
    if (m_capacity >= cap)
      return;
    T *tmp = new T[cap];
    for (size_t i = 0; i < m_size; i++)
      tmp[i] = arr[i];
    delete[] arr;
    arr = tmp;
    m_capacity = cap;
  }

  void clear(bool is_max_heap) {
    if (m_capacity != DEFAULT_CAP) {
      delete[] arr;
      arr = new T[DEFAULT_CAP];
      m_capacity = DEFAULT_CAP;
    }
    m_size = 0;
    this->is_max_heap = is_max_heap;
  }
  void clear() { clear(is_max_heap); }

  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; }
  bool empty() const { return m_size == 0; }

private:
  size_t getParent(size_t idx) const { return (idx - 1) >> 1; }
  size_t getLeftChild(size_t idx) const { return (idx << 1) + 1; }
  size_t getRightChild(size_t idx) const { return (idx << 1) + 2; }

  bool needToSwap(T& a, T& b) const {
    if (is_max_heap)
      return a < b;
    else
      return b < a;
  }

  void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
  }

  void siftUp(size_t cur) {
    while (true) {
      if (cur == 0)
        break;
      size_t parent = getParent(cur);
      if (needToSwap(arr[parent], arr[cur]))
        swap(arr[cur], arr[parent]);
      else
        break;
      cur = parent;
    }
  }

  void siftDown(size_t cur) {
    while (getLeftChild(cur) < m_size) {
      size_t left = getLeftChild(cur), right = getRightChild(cur);
      size_t to_swap = cur;

      if (needToSwap(arr[to_swap], arr[left]))
        to_swap = left;
      if (right < m_size && needToSwap(arr[to_swap], arr[right]))
        to_swap = right;

      if (to_swap != cur) {
        swap(arr[to_swap], arr[cur]);
        cur = to_swap;
      } else {
          return;
      }
    }
  }
};

#endif
