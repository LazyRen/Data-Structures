#ifndef _VECTOR_H_
#define _VECTOR_H_

template <typename T>
class  Vector {
private:
  using size_type = size_t;
  T* arr;
  size_type _size;
  size_type _capacity;
  static constexpr size_type DEFAULT_CAP = 32;

public:
  Vector(size_type cap = DEFAULT_CAP) : arr{new T[cap]}, _size{0}, _capacity{cap} {}
  Vector(const Vector<T>& v) : arr{new T[v._capacity]}, _size{v._size}, _capacity{v._capacity} {
    for (size_type i = 0; i < _size; i++)
      arr[i] = v[i];
  }
  Vector(Vector<T>&& v) : arr{std::move(v.arr)}, _size{std::move(v._size)}, _capacity{std::move(v._capacity)} {

    v.arr = nullptr;
    v._size = 0;
    v._capacity = 0;
  }

  ~Vector() { delete[] arr; }

  Vector<T>& operator=(const Vector<T>& other) {
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
  Vector<T>& operator=(Vector<T>&& other) {
    swap(arr, other.arr);
    swap(_size, other._size);
    swap(_capacity, other._capacity);
    other._size = 0;
    return *this;
  }

  T& front() { return arr[0]; }
  const T& front() const { return arr[0]; }

  T& back() const { return arr[_size - 1]; }
  const T& back() { return arr[_size - 1]; }

  T& operator[](size_type idx) { return arr[idx]; }
  const T& operator[](size_type idx) const { return arr[idx]; }

  void push_back(const T& value) {
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
    arr[_size++] = value;
  }

  void pop_back() { _size = _size > 0 ? _size - 1 : 0; }

  void resize(size_type n) {
    T *t_arr = new T[n];
    _size = _size < n ? _size : n;
    _capacity = n;
    for (size_type i = 0; i < _size; i++)
      t_arr[i] = arr[i];
    delete[] arr;
    arr = t_arr;
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

  void swap(Vector<T>& other) {
    std::swap(arr, other.arr);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
  }

  inline size_type capacity() const { return _capacity; }
  inline size_type size() const { return _size; }
  inline bool empty() const { return _size == 0; }
  void clear() { _size = 0; }
};

#endif
