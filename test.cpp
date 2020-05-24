#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <chrono>
#include "pair.h"
#include "vector.h"
#include "BST/bst.h"
#include "queue.h"
using namespace std::chrono;
using std::cout;
using std::endl;

constexpr int MAXI = 100000;

auto seed = system_clock::now().time_since_epoch().count();
std::default_random_engine engine(std::random_device{}());
std::uniform_int_distribution<int> distribution(0,1);

template <typename T>
bool testQueue(T arr[], int arr_size);

int main() {
  int test[MAXI];
  for (int i = 0; i < MAXI; i++)
    test[i] = i;
  std::shuffle(test, test+MAXI, engine);
  testQueue(test, MAXI);
}

template <typename T>
bool testQueue(T arr[], int arr_size) {
  cout << "Starting Queue Test with " << arr_size << " elements\n";
  system_clock::time_point start = system_clock::now();
  Queue<T> q;
  for (int i = 0; i < arr_size; i++) {
    q.push(arr[i]);
    if (q.size() != i + 1) {
      cout << "push() FAILED: queue size is not correct!\n" \
      << "should be " << i + 1 << " but " << q.size() << "\n";
      return false;
    }
    if (q.back() != arr[i]) {
      cout << "back() FAILED: " << i+1 << "th value is incorrect!\n" \
      << "should be " << arr[i] << " but " << q.back() << "\n";
      return false;
    }
  }
  system_clock::time_point end = system_clock::now();
  microseconds duration = duration_cast<microseconds>(end - start);
  cout << "push() & back() took " << duration.count() << " microseconds\n";

  start = system_clock::now();
  int cnt = 0;
  while (!q.empty()) {
    T cur = q.front(); q.pop();
    if (q.size() != arr_size - cnt - 1) {
      cout << "pop() FAILED: queue size is not correct!\n" \
      << "should be " << arr_size - cnt - 1 << " but " << q.size() << "\n";
      return false;
    }
    if (cur != arr[cnt++]) {
      cout << "front() FAILED: value is incorrect!\n" \
      << "should be " << arr[cnt - 1] << " but " << cur << "\n";
      return false;
    }
  }
  if (cnt != arr_size) {
    cout << "pop() FAILED: " << arr_size - cnt << " values are not poped!\n";
    return false;
  }
  end = system_clock::now();
  duration = duration_cast<microseconds>(end - start);
  cout << "front() & pop() took " << duration.count() << " microseconds\n";

  start = system_clock::now();
  int front = 0, back = 0, pushed = 0, poped = 0;
  for (int i = 0; i < arr_size; i++) {
    if (distribution(engine) & 1 || pushed <= poped) {
      pushed++;
      q.push(arr[back++]);
      if (q.front() != arr[front]) {
        cout << "front() & push() FAILED: " << front << "th value is incorrect!\n" \
        << "should be " << arr[front] << " but " << q.front() << "\n" \
        << " in " << i+1 << "th operation\n";
        return false;
      }
      if (q.back() != arr[back - 1]) {
        cout << "back() FAILED: " << back - 1 << "th value is incorrect!\n" \
        << "should be " << arr[back - 1] << " but " << q.back() << "\n" \
        << " in " << i+1 << "th operation\n";
        return false;
      }
    } else {
      poped++;
      T cur = q.front(); q.pop();
      if (cur != arr[front++]) {
        cout << "front() & pop() FAILED: value is incorrect!\n" \
        << "should be " << arr[front - 1] << " but " << cur \
        << " in " << i+1 << "th operation\n";
        return false;
      }
    }
  }
  if (pushed - poped != q.size()) {
    cout << "random push() & pop() FAILED: size should be " << pushed - poped << " but " << q.size() << "\n";
    return false;
  }
  end = system_clock::now();
  duration = duration_cast<microseconds>(end - start);
  cout << "random push() & pop() took " << duration.count() << " microseconds\n";

  return true;
}
