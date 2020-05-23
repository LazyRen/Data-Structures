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
void quickSort(T arr[], int left, int right) {
  if(left >= right)
    return;

  T pivot = arr[(left+right) / 2];
  int l = left, r = right;

  while(l <= r) {
    while(arr[l] < pivot)
      l++;
    while(arr[r] > pivot)
      r--;
    if(l <= r)
      swap(arr[l++],arr[r--]);
  }

  quickSort(arr, left, r);
  quickSort(arr, l, right);
}

#endif
