//
// Created by hapoe on 5/28/2026.


#pragma once

#include <concepts>
template<typename T>
concept Scalar = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
    { a - b } -> std::same_as<T>;
    { a * b } -> std::same_as<T>;
    { a / b } -> std::same_as<T>;

    {a.sqrt()} -> std::same_as<T>;
};