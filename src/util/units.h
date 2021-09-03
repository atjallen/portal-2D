#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include <SFML/System.hpp>

namespace util {

template <typename T>
float radToDeg(T rads) {
    return rads * 180 / M_PI;
}

template <typename T>
float degToRad(T degs) {
    return degs * M_PI / 180;
}

template <typename T>
sf::Vector2<T> angleToVector(T angle) {
    return sf::Vector2<T>(std::cos(angle), std::sin(angle));
}

template <typename T>
float vectorToAngle(const sf::Vector2<T>& vector) {
    return std::atan2(vector.y, vector.x);
}

}  // namespace util
