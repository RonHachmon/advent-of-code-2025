#ifndef AOC_CONTAINERUTILS_HPP
#define AOC_CONTAINERUTILS_HPP

#include <algorithm>   // For std::find
#include <iostream>    // For std::cout
#include <type_traits> // For std::false_type, std::true_type, and std::void_t
#include <utility>     // For std::declval

namespace aoc {

    // Check if a container has a find method that takes a value of type ValueType
    template <typename Container, typename ValueType, typename = void>
    struct has_find_method : std::false_type 
    {
    };
    
    template <typename Container, typename ValueType>
    struct has_find_method<Container, ValueType, 
        std::void_t<decltype(std::declval<const Container&>().find(std::declval<const ValueType&>()))>> 
        : std::true_type
    {
    };
    
    template <typename Container, typename ValueType>
    constexpr bool has_find_method_v = has_find_method<Container, ValueType>::value;
    
    template <typename Container, typename ValueType>
    bool isInContainer(const Container& container, const ValueType& value) {
        // For associative containers with find method
        if constexpr (has_find_method_v<Container, ValueType>) {
            return container.find(value) != container.end();
        } 
        // For other containers (vectors, lists, std::array, etc.)
        else {
            return std::find(container.begin(), container.end(), value) != container.end();
        }
    }
    
    // Specialization for C-style arrays
    template <typename T, size_t N>
    bool isInContainer(const T (&array)[N], const T& value) {
        return std::find(std::begin(array), std::end(array), value) != std::end(array);
    }

} // namespace aoc

#endif // AOC_CONTAINERUTILS_HPP