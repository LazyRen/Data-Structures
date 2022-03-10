#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <cstddef>
#include <utility>

template <typename T>
class  Vector {
private:
  static constexpr size_t DEFAULT_CAP = 32;
  T* arr;
  size_t m_size;
  size_t m_capacity;

public:
  Vector(size_t cap = DEFAULT_CAP) : arr(new T[cap]), m_size(0), m_capacity(cap) {}
  Vector(const Vector& v) : arr(new T[v.m_capacity]), m_size(v.m_size), m_capacity(v.m_capacity) {
    for (size_t i = 0; i < m_size; i++)
      arr[i] = v[i];
  }
  Vector(Vector&& v) : arr(std::move(v.arr)), m_size(std::move(v.m_size)), m_capacity(std::move(v.m_capacity)) {
    v.arr = nullptr;
    v.m_size = 0;
    v.m_capacity = 0;
  }

  ~Vector() { delete[] arr; }

  Vector& operator=(const Vector& other) {
    if (this != &other) {
      if (m_capacity < other.m_capacity) {
        delete[] arr;
        m_capacity = other.m_capacity;
        arr = new T[m_capacity];
      }
      m_size = other.m_size;
      for (size_t i = 0; i < m_size; i++)
        arr[i] = other.arr[i];
    }
    return *this;
  }
  Vector& operator=(Vector&& other) {
    std::swap(arr, other.arr);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    other.m_size = 0;
    return *this;
  }

  T* begin() const { return arr; }

  T* end() const { return arr + m_size; }

  T& front() { return arr[0]; }
  const T& front() const { return arr[0]; }

  T& back() { return arr[m_size - 1]; }
  const T& back() const { return arr[m_size - 1]; }

  T& operator[](size_t idx) { return arr[idx]; }
  const T& operator[](size_t idx) const { return arr[idx]; }

  void push_back(const T& val) {
    if (m_size >= m_capacity) {
      if (m_capacity < DEFAULT_CAP)
        m_capacity = DEFAULT_CAP;
      else
        m_capacity *= 2;
      T *t_arr = new T[m_capacity];
      for (size_t i = 0; i < m_size; i++)
        t_arr[i] = arr[i];
      delete[] arr;
      arr = t_arr;
    }
    arr[m_size++] = val;
  }
  void push_back(T&& val) {
    if (m_size >= m_capacity) {
      if (m_capacity < DEFAULT_CAP)
        m_capacity = DEFAULT_CAP;
      else
        m_capacity *= 2;
      T *t_arr = new T[m_capacity];
      for (size_t i = 0; i < m_size; i++)
        t_arr[i] = arr[i];
      delete[] arr;
      arr = t_arr;
    }
    arr[m_size++] = std::move(val);
  }

  void pop_back() { m_size = m_size > 0 ? m_size - 1 : 0; }

  void resize(size_t n, T val = T()) {
    T *t_arr = new T[n];
    m_size = m_size < n ? m_size : n;
    m_capacity = n;
    for (size_t i = 0; i < m_size; i++)
      t_arr[i] = arr[i];
    for (size_t i = m_size; i < m_capacity; i++)
      t_arr[i] = val;
    delete[] arr;
    arr = t_arr;
    m_size = n;
  }

  void reserve(size_t n) {
    if (n <= m_capacity)
      return;
    T *t_arr = new T[n];
    for (size_t i = 0; i < m_size; i++)
      t_arr[i] = arr[i];
    delete[] arr;
    arr = t_arr;
    m_capacity = n;
  }

  void swap(Vector& other) {
    std::swap(arr, other.arr);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  }

  size_t capacity() const { return m_capacity; }
  size_t size() const { return m_size; }
  bool empty() const { return m_size == 0; }
  void clear() { m_size = 0; }

  bool operator==(const Vector& other) const {
    if (m_size != other.m_size)
      return false;
    for (size_t i = 0; i < m_size; i++)
      if (arr[i] != other[i])
        return false;
    return true;
  }
  bool operator!=(const Vector& other) const { return !(*this == other); }
  bool operator< (const Vector& other) const {
    bool is_all_same = true;
    size_t minm_size = m_size < other.m_size ? m_size : other.m_size;
    size_t idx = 0;
    for (; idx < minm_size; idx++) {
      if (arr[idx] != other[idx]) {
        is_all_same = false;
        break;
      }
    }

    if (is_all_same) {
      if (m_size < other.m_size)
        return true;
    } else {
      if (arr[idx] < other[idx])
        return true;
    }
    return false;
  }
  bool operator<=(const Vector& other) const { return !(other < *this); }
  bool operator> (const Vector& other) const { return (other < *this); }
  bool operator>=(const Vector& other) const { return !(*this < other); }
};

#endif
