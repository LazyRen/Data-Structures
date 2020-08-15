#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

template <typename T>
void swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

/*
 * Sort all elements in arr[]; range of closed interval [left, right].
 */
template <typename T>
void sort(T arr[], int left, int right) {
  if (left >= right) return;

  T pivot = arr[(left + right) / 2];
  int l = left, r = right;

  while (l <= r) {
    while (arr[l] < pivot) l++;
    while (arr[r] > pivot) r--;
    if (l <= r) swap(arr[l++], arr[r--]);
  }

  sort(arr, left, r);
  sort(arr, l, right);
}

/*
 * Sort all elements in [arr, end). use it with iterator begin() & end().
 */
template <typename T>
void sort(T* arr, T* end) {
  int l = 0, r = (end - arr) - 1;
  if (l >= r) return;
  T pivot = arr[(l + r) / 2];
  while (l <= r) {
    while (arr[l] < pivot) l++;
    while (arr[r] > pivot) r--;
    if (l <= r) swap(arr[l++], arr[r--]);
  }
  sort(arr, arr + l);
  sort(arr + l, end);
}

#endif
