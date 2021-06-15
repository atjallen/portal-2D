#pragma once

#include <algorithm>

namespace util {

template <typename ContainerType, typename ElementType>
bool contains(const ContainerType& container, const ElementType& element) {
    return std::find(container.begin(), container.end(), element) !=
           container.end();
}

template <typename ContainerType, typename UnaryPredicate>
bool containsIf(const ContainerType& container, UnaryPredicate p) {
    return std::find_if(container.begin(), container.end(), p) !=
           container.end();
}

template <typename ContainerType, typename ElementType>
bool containsFast(const ContainerType& container, const ElementType& element) {
    return container.find(element) != container.end();
}

}  // namespace util