//
// Created by ccx on 2024/3/1.
//
#include "exercise/sort.h"
#include "gtest/gtest.h"

TEST(sort, quick_sort) {
  int arr[] = {3, 2, 1, 5, 66};
  tinker::quick_sort(arr, sizeof(arr) / sizeof(arr[0]));
}