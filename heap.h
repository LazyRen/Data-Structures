#ifndef _HEAP_H_
#define _HEAP_H_

template <typename T>
class Heap {
private:
  using size_type = size_t;
  T* arr;
  size_type _size;
  size_type _capacity;
  bool is_max_heap;
  static constexpr size_type DEFAULT_CAP = 32;

public:
  Heap(bool is_max_heap = true) : arr{new T[DEFAULT_CAP]}, _size{0}, _capacity{DEFAULT_CAP}, is_max_heap{is_max_heap} {}
  Heap(T inp[], size_type length, bool is_max_heap = true) : arr{nullptr}, _size{length}, _capacity{DEFAULT_CAP}, is_max_heap{is_max_heap} {
    heapify(inp, length);
  }
  ~Heap() { delete[] arr; }

  void heapify(T inp[], size_type length, bool is_max_heap = true) {
    this->is_max_heap = is_max_heap;
    if (length > _capacity) {
      while (length > _capacity)
        _capacity *= 2;
      delete[] arr;
      arr = new T[_capacity];
    }

    for (size_type i = 0; i < length; i++)
      arr[i] = inp[i];

    _size = length;
    size_type cur = getParent(_size - 1);

    while (cur > 0)
      siftDown(cur--);
    siftDown(cur);
  }

  void push(T item) {
    if (_size == _capacity) {
      _capacity *= 2;
      T *tmp = new T[_capacity];
      for (size_type i = 0; i < _size; i++)
        tmp[i] = arr[i];
      delete[] arr;
      arr = tmp;
    }
    arr[_size] = item;
    siftUp(_size++);
  }

  void pop() {
    if (_size == 0)
      throw std::out_of_range("Empty heap");
    arr[0] = arr[--_size];
    siftDown(0);
  }

  T top() const {
    if (_size == 0)
      throw std::out_of_range("Empty heap");
    return arr[0];
  }

  void reserve(size_type cap) {
    if (_capacity >= cap)
      return;
    T *tmp = new T[cap];
    for (size_type i = 0; i < _size; i++)
      tmp[i] = arr[i];
    delete[] arr;
    arr = tmp;
    _capacity = cap;
  }

  void clear(bool is_max_heap) {
    delete[] arr;
    arr = new T[DEFAULT_CAP];
    _size = 0;
    _capacity = DEFAULT_CAP;
    this->is_max_heap = is_max_heap;
  }
  void clear() {
    clear(is_max_heap);
  }

  inline size_type size() const { return _size; }
  inline size_type capacity() const { return _capacity; }
  inline bool empty() const { return _size == 0; }

private:
  inline size_type getParent(size_type idx) const { return (idx - 1) >> 1; }
  inline size_type getLeftChild(size_type idx) const { return (idx << 1) + 1; }
  inline size_type getRightChild(size_type idx) const { return (idx << 1) + 2; }

  inline bool needToSwap(T& a, T& b) const {
    if (is_max_heap)
      return a < b;
    else
      return b < a;
  }

  inline void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
  }

  void siftUp(size_type cur) {
    while (true) {
      if (cur == 0)
        break;
      size_type parent = getParent(cur);
      if (needToSwap(arr[parent], arr[cur]))
        swap(arr[cur], arr[parent]);
      else
        break;
      cur = parent;
    }
  }

  void siftDown(size_type cur) {
    while (getLeftChild(cur) < _size) {
      size_type left = getLeftChild(cur), right = getRightChild(cur);
      size_type to_swap = cur;

      if (needToSwap(arr[to_swap], arr[left]))
        to_swap = left;
      if (right < _size && needToSwap(arr[to_swap], arr[right]))
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
