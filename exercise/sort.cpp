//
// Created by ccx on 2024/2/29.
//

#include <algorithm>
#include "sort.h"

namespace tinker {
void quick_sort(int *arr, int32_t length) {}

void BubbleSort(int64_t arr[], int32_t len) {
  if (len <= 1) return;
  if (arr == nullptr) return;
  for (auto i = len - 1; i > 0; i--) {
    for (auto j = 0; j < i; j++) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void InsertionSort(int64_t arr[], int32_t len) {
  if (len <= 1) return;
  for (auto i = 1; i < len; i++) {
    auto v = arr[i];
    auto j = i - 1;
    for (; j >= 0; j--) {
      if (arr[j] > v) {
        arr[j + 1] = arr[j];
      } else {
        break;
      }
    }
    arr[j + 1] = v;
  }
}

} // namespace tinker
