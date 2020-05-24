#ifndef _QUEUE_H_
#define _QUEUE_H_

template <typename T>
class Queue {
private:
  using size_type = size_t;
  T* arr;
  size_type head;
  size_type tail;
  size_type _size;
  size_type _capacity;
  static constexpr size_type DEFAULT_CAP = 4;

  void increaseCapacity() {
    size_type prev_cap = _capacity;
    if (_capacity < DEFAULT_CAP)
      _capacity = DEFAULT_CAP;
    else
      _capacity *= 2;
    T *t_arr = new T[_capacity];
    for (size_type i = 0; i < _size; i++)
      t_arr[i] = arr[(head + i) % prev_cap];
    head = 0;
    tail = _size;
    delete[] arr;
    arr = t_arr;
  }

public:
  Queue() : arr{new T[DEFAULT_CAP]}, head(0), tail(0), _size(0), _capacity(DEFAULT_CAP) {}
  Queue(const Queue& q) : arr(new T[q._capacity]), head(q.head), tail(q.tail), _size(q._size), _capacity(q._capacity) {
    for (size_type i = 0; i < _size; i++)
      arr[i] = q[i];
  }
  Queue(Queue&& q) : arr(std::move(q.arr)), head(std::move(q.head)), tail(std::move(q.tail)), _size(std::move(q._size)), _capacity(std::move(q._capacity)) {
    q.arr = nullptr;
    q.head = 0;
    q.tail = 0;
    q._size = 0;
    q._capacity = 0;
  }

  ~Queue() { delete[] arr; }

  Queue& operator=(const Queue& other) {
    if (this != &other) {
      if (_capacity < other._capacity) {
        delete[] arr;
        _capacity = other._capacity;
        arr = new T[_capacity];
      }
      head = other.head;
      tail = other.tail;
      _size = other._size;
      for (size_type i = 0; i < _size; i++)
        arr[i] = other.arr[i];
    }
    return *this;
  }
  Queue& operator=(Queue&& other) {
    swap(arr, other.arr);
    swap(_size, other._size);
    swap(_capacity, other._capacity);
    other._size = 0;
    return *this;
  }

  inline bool empty() const { return _size == 0; }
  inline size_type size() const { return _size; }

  inline T& front() { return arr[head]; }
  const inline T& front() const { return arr[head]; }

  inline T& back() {
    return arr[(head + _size - 1) % _capacity]; }
  const inline T& back() const { return arr[(head + _size - 1) % _capacity]; }

  void push(const T& val) {
    if(_size >= _capacity)
      increaseCapacity();
    arr[tail] = val;
    tail = (tail + 1) % _capacity;
    _size++;
  }

  void push(T&& val) {
    if(_size >= _capacity)
      increaseCapacity();
    arr[tail] = std::move(val);
    tail = (tail + 1) % _capacity;
    _size++;
  }

  void pop() {
    if (_size > 0) {
      head = (head + 1) % _capacity;
      _size--;
    }
  }

  void swap(Queue& other) {
    std::swap(arr, other.arr);
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
  }
};

#endif
