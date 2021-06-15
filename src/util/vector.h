#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <cmath>
#include <iostream>

#include <SFML/System.hpp>

namespace util {

template <typename T>
double length(sf::Vector2<T> a) {
    return std::sqrt(a.x * a.x + a.y * a.y);
}

template <typename T>
double dot(sf::Vector2<T> a, sf::Vector2<T> b) {
    return a.x * b.x + a.y * b.y;
};

template <typename T>
double angleBetween(sf::Vector2<T> a, sf::Vector2<T> b) {
    return std::atan2(b.y, b.x) - std::atan2(a.y, a.x);
}

template <typename NumType>
NumType radToDeg(NumType rads) {
    return rads * 180 / M_PI;
}

template <typename NumType>
NumType degToRad(NumType degs) {
    return degs * M_PI / 180;
}

}  // namespace util