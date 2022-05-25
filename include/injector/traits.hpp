#pragma once

#include <vector>
#include <type_traits>

namespace injector
{
    template<class T>
    struct is_vector : public std::false_type {};

    template<class T>
    struct is_vector<std::vector<T>> : public std::true_type {};

    template<class T>
    constexpr bool is_vector_v = is_vector<T>::value;

    template<class T>
    struct is_shared : public std::false_type {};

    template<class T>
    struct is_shared<std::shared_ptr<T>> : public std::true_type {};

    template<class T>
    constexpr bool is_shared_v = is_shared<T>::value;
} // namespace injector