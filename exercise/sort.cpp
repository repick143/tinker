//
// Created by ccx on 2024/2/29.
//

#include <algorithm>
#include "fmt/core.h"
#include "fmt/format.h"

namespace tinker {
void Merge(int64_t *arr, int32_t p, int32_t q, int32_t r) {
  int64_t tmp_arr[r - p + 1];
  int i = p, j = q + 1;
  int k = 0;
  while (i <= q && j <= r) {
    if (arr[i] < arr[j]) {
      tmp_arr[k++] = arr[i++];
    } else {
      tmp_arr[k++] = arr[j++];
    }
  }
  auto start = i;
  auto end = q;
  if (i > q) {
    start = j;
    end = r;
  }
  memcpy(&tmp_arr[k], &arr[start], sizeof(int64_t) * (end - start + 1));
  memcpy(&arr[p], tmp_arr, sizeof(int64_t) * (r - p + 1));
}

void MergeSortC(int64_t *arr, int32_t p, int32_t r) {
  if (p >= r) return;
  int32_t q = (p + r) / 2;
  MergeSortC(arr, p, q);
  MergeSortC(arr, q + 1, r);
  Merge(arr, p, q, r);
}
void MergeSort(int64_t *arr, int32_t length) {
  MergeSortC(arr, 0, length - 1);
}

void BubbleSort(int64_t *arr, int32_t len) {
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

void InsertionSort(int64_t *arr, int32_t len) {
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

int32_t Partition(int64_t *arr, int p, int r) {
  auto pivot = arr[r];
  int j = p;
  for (auto i = p; i < r; i++) {
    if (arr[i] < pivot) {
      std::swap(arr[j++], arr[i]);
    }
  }
  std::swap(arr[j], arr[r]);
  return j;
}

void QuickSortC(int64_t *arr, int p, int r) {
  if (p >= r) return;
  auto q = Partition(arr, p, r);
  QuickSortC(arr, p, q - 1);
  QuickSortC(arr, q + 1, r);
}
void QuickSort(int64_t *arr, int len) {
  QuickSortC(arr, 0, len - 1);
}
} // namespace tinker
