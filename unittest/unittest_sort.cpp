//
// Created by ccx on 2024/3/1.
//
#include "exercise/sort.h"
#include "gtest/gtest.h"

TEST(sort, quick_sort) {
  int64_t arr[] = {3, 2, 1, 5, 66};
  tinker::QuickSort(arr, sizeof(arr) / sizeof(arr[0]));
}