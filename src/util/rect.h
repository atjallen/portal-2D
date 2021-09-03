#pragma once

#include <array>

#include <SFML/Graphics.hpp>

namespace util {

template <typename T>
std::array<sf::Vector2<T>, 4> rectToPoints(const sf::Rect<T>& rect) {
    return {sf::Vector2<T>(rect.left, rect.top), sf::Vector2<T>(rect.left + rect.width, rect.top),
            sf::Vector2<T>(rect.left + rect.width, rect.top + rect.height),
            sf::Vector2<T>(rect.left, rect.top + rect.height)};
}

}  // namespace util
