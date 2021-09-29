#pragma once

namespace util {

template <class TestType, class T>
bool isType(const T& src) {
    return dynamic_cast<const TestType*>(&src) != nullptr;
}

}  // namespace util
