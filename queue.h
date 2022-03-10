#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <cstddef>
#include <utility>

template <typename T>
class Queue {
private:
  static constexpr size_t DEFAULT_CAP = 4;
  T* arr;
  size_t head;
  size_t tail;
  size_t m_size;
  size_t m_capacity;

  void increaseCapacity() {
    size_t prev_cap = m_capacity;
    if (m_capacity < DEFAULT_CAP)
      m_capacity = DEFAULT_CAP;
    else
      m_capacity *= 2;
    T *t_arr = new T[m_capacity];
    for (size_t i = 0; i < m_size; i++)
      t_arr[i] = arr[(head + i) % prev_cap];
    head = 0;
    tail = m_size;
    delete[] arr;
    arr = t_arr;
  }

public:
  Queue() : arr{new T[DEFAULT_CAP]}, head(0), tail(0), m_size(0), m_capacity(DEFAULT_CAP) {}
  Queue(const Queue& q) : arr(new T[q.m_capacity]), head(q.head), tail(q.tail), m_size(q.m_size), m_capacity(q.m_capacity) {
    for (size_t i = 0; i < m_size; i++)
      arr[i] = q[i];
  }
  Queue(Queue&& q) : arr(std::move(q.arr)), head(std::move(q.head)), tail(std::move(q.tail)), m_size(std::move(q.m_size)), m_capacity(std::move(q.m_capacity)) {
    q.arr = nullptr;
    q.head = 0;
    q.tail = 0;
    q.m_size = 0;
    q.m_capacity = 0;
  }

  ~Queue() { delete[] arr; }

  Queue& operator=(const Queue& other) {
    if (this != &other) {
      if (m_capacity < other.m_capacity) {
        delete[] arr;
        m_capacity = other.m_capacity;
        arr = new T[m_capacity];
      }
      head = other.head;
      tail = other.tail;
      m_size = other.m_size;
      for (size_t i = 0; i < m_size; i++)
        arr[i] = other.arr[i];
    }
    return *this;
  }
  Queue& operator=(Queue&& other) {
    swap(arr, other.arr);
    swap(m_size, other.m_size);
    swap(m_capacity, other.m_capacity);
    other.m_size = 0;
    return *this;
  }

  bool empty() const { return m_size == 0; }
  size_t size() const { return m_size; }

  T& front() { return arr[head]; }
  const T& front() const { return arr[head]; }

  T& back() {
    return arr[(head + m_size - 1) % m_capacity]; }
  const T& back() const { return arr[(head + m_size - 1) % m_capacity]; }

  void push(const T& val) {
    if(m_size >= m_capacity)
      increaseCapacity();
    arr[tail] = val;
    tail = (tail + 1) % m_capacity;
    m_size++;
  }

  void push(T&& val) {
    if(m_size >= m_capacity)
      increaseCapacity();
    arr[tail] = std::move(val);
    tail = (tail + 1) % m_capacity;
    m_size++;
  }

  void pop() {
    if (m_size > 0) {
      head = (head + 1) % m_capacity;
      m_size--;
    }
  }

  void swap(Queue& other) {
    std::swap(arr, other.arr);
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  }
};

#endif
