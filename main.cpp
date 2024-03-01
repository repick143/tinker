//
// Created by ccx on 2024/2/29.
//
#include <iostream>
#include <fmt/core.h>

int main() {
    int32_t&& i = 1;
    i = 2;
    {
        int32_t origin_value1 = 1;
        int32_t origin_value2 = 2;
        auto& v = origin_value1;
        v = origin_value2;
        std::cout << "xx=" << i << " " << origin_value1 << "/" << origin_value2 << std::endl;
    }
    {
        int32_t origin_value1 = 1;
        int32_t origin_value2 = 2;
//        int32_t&& v = origin_value1;
        int32_t&& v = std::move(origin_value1);
        v = origin_value2;
        std::cout << "xx=" << i << " " << origin_value1 << "/" << origin_value2 << std::endl;
    }

}