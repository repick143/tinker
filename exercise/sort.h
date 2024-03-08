//
// Created by ccx on 2024/2/29.
//

#ifndef TINKER_SORT_H
#define TINKER_SORT_H

#include <cstdint>

namespace tinker {
void BubbleSort(int64_t *arr, int32_t len);
void InsertionSort(int64_t *arr, int32_t len);

void MergeSort(int64_t *arr, int32_t len);
void QuickSort(int64_t *arr, int len);
void QuickSortN(int64_t *arr, int len);
}

#endif //TINKER_SORT_H
