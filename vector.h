#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <cstddef>
#include <utility>

template <typename T>
class  Vector {
private:
  using size_type = size_t;
  T* arr;
  size_type _size;
  size_type _capacity;
  static constexpr size_type DEFAULT_CAP = 32;

public:
  Vector(size_type cap = DEFAULT_CAP) : arr(new T[cap]), _size(0), _capacity(cap) {}
  Vector(const Vector& v) : arr(new T[v._capacity]), _size(v._size), _capacity(v._capacity) {
    for (size_type i = 0; i < _size; i++)
      arr[i] = v[i];
  }
  Vector(Vector&& v) : arr(std::move(v.arr)), _size(std::move(v._size)), _capacity(std::move(v._capacity)) {
    v.arr = nullptr;
    v._size = 0;
    v._capacity = 0;
  }

  ~Vector() { delete[] arr; }

  Vector& operator=(const Vector& other) {
    if (this != &other) {
      if (_capacity < other._capacity) {
        delete[] arr;
        _capacity = other._capacity;
        arr = new T[_capacity];
      }
      _size = other._size;
      for (size_type i = 0; i < _size; i++)
        arr[i] = other.arr[i];
    }
    return *this;
  }
  Vector& operator=(Vector&& other) {
    std::swap(arr, other.arr);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    other._size = 0;
    return *this;
  }

  inline T& front() { return arr[0]; }
  const inline T& front() const { return arr[0]; }

  inline T& back() { return arr[_size - 1]; }
  const inline T& back() const { return arr[_size - 1]; }

  inline T& operator[](size_type idx) { return arr[idx]; }
  const inline T& operator[](size_type idx) const { return arr[idx]; }

  void push_back(const T& val) {
    if (_size >= _capacity) {
      if (_capacity < DEFAULT_CAP)
        _capacity = DEFAULT_CAP;
      else
        _capacity *= 2;
      T *t_arr = new T[_capacity];
      for (size_type i = 0; i < _size; i++)
        t_arr[i] = arr[i];
      delete[] arr;
      arr = t_arr;
    }
    arr[_size++] = val;
  }
  void push_back(T&& val) {
    if (_size >= _capacity) {
      if (_capacity < DEFAULT_CAP)
        _capacity = DEFAULT_CAP;
      else
        _capacity *= 2;
      T *t_arr = new T[_capacity];
      for (size_type i = 0; i < _size; i++)
        t_arr[i] = arr[i];
      delete[] arr;
      arr = t_arr;
    }
    arr[_size++] = std::move(val);
  }

  void pop_back() { _size = _size > 0 ? _size - 1 : 0; }

  void resize(size_type n, T val = T()) {
    T *t_arr = new T[n];
    _size = _size < n ? _size : n;
    _capacity = n;
    for (size_type i = 0; i < _size; i++)
      t_arr[i] = arr[i];
    for (size_type i = _size; i < _capacity; i++)
      t_arr[i] = val;
    delete[] arr;
    arr = t_arr;
    _size = n;
  }

  void reserve(size_type n) {
    if (n <= _capacity)
      return;
    T *t_arr = new T[n];
    for (size_type i = 0; i < _size; i++)
      t_arr[i] = arr[i];
    delete[] arr;
    arr = t_arr;
    _capacity = n;
  }

  void swap(Vector& other) {
    std::swap(arr, other.arr);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
  }

  inline size_type capacity() const { return _capacity; }
  inline size_type size() const { return _size; }
  inline bool empty() const { return _size == 0; }
  void clear() { _size = 0; }

  inline bool operator==(const Vector& other) const {
    if (_size != other._size)
      return false;
    for (size_type i = 0; i < _size; i++)
      if (arr[i] != other[i])
        return false;
    return true;
  }
  inline bool operator!=(const Vector& other) const { return !(*this == other); }
  inline bool operator< (const Vector& other) const {
    bool is_all_same = true;
    size_type min_size = _size < other._size ? _size : other._size;
    size_type idx = 0;
    for (; idx < min_size; idx++) {
      if (arr[idx] != other[idx]) {
        is_all_same = false;
        break;
      }
    }

    if (is_all_same) {
      if (_size < other._size)
        return true;
    } else {
      if (arr[idx] < other[idx])
        return true;
    }
    return false;
  }
  inline bool operator<=(const Vector& other) const { return !(other < *this); }
  inline bool operator> (const Vector& other) const { return (other < *this); }
  inline bool operator>=(const Vector& other) const { return !(*this < other); }
};

#endif
