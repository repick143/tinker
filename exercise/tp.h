//
// Created by ccx on 2024/3/5.
//

#ifndef TINKER_EXERCISE_TP_H_
#define TINKER_EXERCISE_TP_H_

#include <type_traits>
#include "fmt/core.h"

namespace tinker {
template<typename T, typename = std::void_t<>>
struct has_reserve : std::false_type {};

template<typename T>
struct has_reserve<T, std::void_t<decltype(std::declval<T &>().reserve(1U))>> : std::true_type {};

template<typename T>
static constexpr bool has_reserve_v = has_reserve<T>::value;
}

template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
auto doSomething(T t) -> decltype(t) {
  fmt::println("T is int");
  return t;
}

template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
auto doSomething(T t) -> decltype(t) {
  fmt::println("T is float");
  return t;
}

#endif //TINKER_EXERCISE_TP_H_
