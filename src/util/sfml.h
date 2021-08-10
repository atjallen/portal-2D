#pragma once

#include <iostream>

#include <SFML/System.hpp>

template <typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& vector) {
    return os << "(" << vector.x << ", " << vector.y << ")";
}
