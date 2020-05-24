#ifndef _PAIR_H_
#define _PAIR_H_

template <typename T1, typename T2>
class Pair{
public:
  T1 first;
  T2 second;

  constexpr Pair() : first(T1()), second(T2()) {};

  Pair(const T1& f, const T2& s) : first(f), second(s) {};

  template<typename U1, typename U2>
  Pair(U1&& f, U2&& s) : first(std::forward<U1>(f)), second(std::forward<U2>(s)) {};

  template<typename U1, typename U2>
  Pair(const Pair<U1,U2>& other) : first(other.first), second(other.second) {};

  template<typename U1, typename U2>
  Pair(Pair<U1,U2>&& other) : first(std::forward<U1>(other.first)), second(std::forward<U2>(other.second)) {};

  ~Pair() = default;

  void swap(Pair& other) {
    std::swap(first, other.first);
    std::swap(second, other.second);
  }

  Pair& operator=(const Pair& other) {
    first = other.first;
    second = other.second;
    return *this;
  }

  Pair& operator=(Pair&& other) {
    first = std::move(other.first);
    second = std::move(other.second);
    return *this;
  }
  template<typename U1, typename U2>
  Pair& operator=(const Pair<U1, U2>& other) {
    first = other.first;
    second = other.second;
    return *this;
  }

  template<typename U1, typename U2>
  Pair& operator=(Pair<U1, U2>&& other) {
    first = std::forward<T1>(other.first);
    second = std::forward<T2>(other.second);
    return *this;
  }

  inline bool operator==(const Pair& other) const { return (first == other.first && second == other.second); }
  inline bool operator!=(const Pair& other) const { return !(*this == other); }
  inline bool operator< (const Pair& other) const { return (first < other.first || (first == other.first && second < other.second)); }
  inline bool operator<=(const Pair& other) const { return !(other < *this); }
  inline bool operator> (const Pair& other) const { return (other < *this); }
  inline bool operator>=(const Pair& other) const { return !(*this < other); }
};

// comment below function if overloading conflict happens.(using namespace std;)
template <typename U1, typename U2>
inline Pair<U1,U2> make_pair(U1&& x, U2&& y) {
  return Pair<U1,U2> {x, y};
}

#endif
